#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <strings.h>
#include <unistd.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>

#define M_LINE  511
#define MAX_SOCKET 1024
#define MAX_MESSAGE_LENGTH (M_LINE + 20) // 충분한 공간 확보

char *EXIT_STRING = "exit";
int max_fdp1;
int n_user = 0;
int client_sock_list[MAX_SOCKET];
char ip_list[MAX_SOCKET][20];
char user_ids[MAX_SOCKET][20];
int listen_sock;

void addClient(int s, struct sockaddr_in *new_client_addr);
int get_max();
void removeClient(int s);
int tcp_listen(int host, int port, int backlog);
void err_quit(char *msg) { perror(msg); exit(1); }

time_t ct;
struct tm tm;

// Thread for server commands
void *thread_function(void *arg) {
    while (1) {
        char buf_msg[M_LINE + 1];
        printf("server > ");
        fgets(buf_msg, M_LINE, stdin);

        if (!strcmp(buf_msg, "\n")) continue;
        else if (!strcmp(buf_msg, "n_user\n"))
            printf("Now Chatting play User = %d\n", n_user);
        else if (!strcmp(buf_msg, "ip_list\n"))
            for (int i = 0; i < n_user; i++)
                printf("%s\n", ip_list[i]);
        else
            printf("Error\n");
    }
}

// Main
int main(int argc, char *argv[]) {
    struct sockaddr_in client_addr;
    char buf[M_LINE + 1];
    int i, j, nbyte, accp_sock, addrlen = sizeof(struct sockaddr_in);
    fd_set read_fds;
    pthread_t a_thread;

    if (argc != 2) {
        printf("Using :%s port\n", argv[0]);
        exit(0);
    }

    listen_sock = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);
    pthread_create(&a_thread, NULL, thread_function, (void *)NULL);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(listen_sock, &read_fds);

        for (i = 0; i < n_user; i++)
            FD_SET(client_sock_list[i], &read_fds);

        max_fdp1 = get_max() + 1;

        if (select(max_fdp1, &read_fds, NULL, NULL, NULL) < 0)
            err_quit("select fail");

        if (FD_ISSET(listen_sock, &read_fds)) {
            accp_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addrlen);
            if (accp_sock == -1) err_quit("accept fail");
            addClient(accp_sock, &client_addr);
            ct = time(NULL);
            tm = *localtime(&ct);
            printf("[%02d:%02d:%02d]  Connect New User, Now Chatting User = %d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, n_user);
        }

        for (i = 0; i < n_user; i++) {
            if (FD_ISSET(client_sock_list[i], &read_fds)) {
                nbyte = recv(client_sock_list[i], buf, M_LINE, 0);
                if (nbyte <= 0) {
                    removeClient(i);
                    continue;
                }
                buf[nbyte] = 0;

                if (strstr(buf, EXIT_STRING) != NULL) {
                    removeClient(i);
                    continue;
                }

                // 메시지를 다른 모든 클라이언트에게 전송
                for (j = 0; j < n_user; j++) {
                    if (j != i) {
                        send(client_sock_list[j], buf, strlen(buf), 0);
                    }
                }
                printf("%s\n", buf); // 서버 콘솔에 메시지 출력
            }
        }
    }
    return 0;
}

// New User Connect
void addClient(int s, struct sockaddr_in *new_client_addr) {
    char buf[20];
    inet_ntop(AF_INET, &new_client_addr->sin_addr, buf, sizeof(buf));
    printf("[ New User: %s ]\n", buf);

    client_sock_list[n_user] = s;
    strcpy(ip_list[n_user], buf);
    recv(s, user_ids[n_user], sizeof(user_ids[n_user]), 0);
    user_ids[n_user][sizeof(user_ids[n_user]) - 1] = '\0';

    char conn_msg[M_LINE + 20];
    snprintf(conn_msg, sizeof(conn_msg), "Server: Connected to Server\n");
    send(s, conn_msg, strlen(conn_msg), 0);

    // 새로운 사용자 연결 메시지를 모든 클라이언트에게 전송
    char message[MAX_MESSAGE_LENGTH];
    snprintf(message, sizeof(message), "New User Connect\n[ IP: %s ] [ User: %s ]", ip_list[n_user], user_ids[n_user]);
    
    for (int j = 0; j < n_user; j++) {
        send(client_sock_list[j], message, strlen(message), 0);
    }

    n_user++;
}

// Chatting Leave
void removeClient(int s) {
    close(client_sock_list[s]);
    if (s != n_user - 1) {
        client_sock_list[s] = client_sock_list[n_user - 1];
        strcpy(ip_list[s], ip_list[n_user - 1]);
        strcpy(user_ids[s], user_ids[n_user - 1]);
    }
    n_user--;
    ct = time(NULL);
    tm = *localtime(&ct);
    printf("[%02d:%02d:%02d] User Chatting leave.... Now User Count = %d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, n_user);
}

// Max Socket Number find
int get_max() {
    int max = listen_sock;
    int i;
    for (i = 0; i < n_user; i++)
        if (client_sock_list[i] > max)
            max = client_sock_list[i];
    return max;
}

// listen socket create && listen
int tcp_listen(int host, int port, int backlog) {
    int sd;
    struct sockaddr_in server_addr;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("socket fail");
        exit(1);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(host);
    server_addr.sin_port = htons(port);

    if (bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind fail");
        exit(1);
    }

    listen(sd, backlog);
    return sd;
}

