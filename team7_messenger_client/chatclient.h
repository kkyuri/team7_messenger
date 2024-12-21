#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class ChatClient;
}

class ChatClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatClient(QWidget *parent = nullptr);
    ~ChatClient();

private slots:
    void connectToServer();
    void sendMessage();
    void sendFile();
    void receiveFile(); // 이 줄을 추가합니다.
    void readMessage();

private:
    Ui::ChatClient *ui;
    QTcpSocket *socket;
    QString userID;
};

#endif // CHATCLIENT_H
