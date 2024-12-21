#include "chatclient.h"
#include "ui_chatclient.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QDebug>

ChatClient::ChatClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatClient) {
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, [this]() {
        QMessageBox::information(this, "Connection", "Connected to server!");
        ui->textBrowser_messages->append("New User Connect\n[ IP: " + ui->lineEdit_ip->text() + " ] [ User: " + userID + " ]");
        ui->textBrowser_messages->append("=================================");
        socket->write(userID.toUtf8()); // 사용자 ID를 서버에 전송
    });

    connect(socket, &QTcpSocket::disconnected, this, [this]() {
        QMessageBox::warning(this, "Connection Lost", "Disconnected from server.");
        ui->textBrowser_messages->append(userID + " disconnected.");
    });

    connect(socket, &QTcpSocket::readyRead, this, &ChatClient::readMessage);
    connect(ui->button_connect, &QPushButton::clicked, this, &ChatClient::connectToServer);
    connect(ui->button_send, &QPushButton::clicked, this, &ChatClient::sendMessage);
    connect(ui->button_sendFile, &QPushButton::clicked, this, &ChatClient::sendFile); // send a file 버튼 연결
}

ChatClient::~ChatClient() {
    delete ui;
}

void ChatClient::connectToServer() {
    QString ip = ui->lineEdit_ip->text();
    quint16 port = static_cast<quint16>(ui->lineEdit_port->text().toInt());
    userID = ui->lineEdit_user->text();
    socket->connectToHost(ip, port);

    if (socket->waitForConnected(3000)) {
        // 연결 성공 후 추가 작업은 QTcpSocket::connected 슬롯에서 처리합니다.
    } else {
        QMessageBox::critical(this, "Connection Error", "Failed to connect to server.");
    }
}

void ChatClient::sendMessage() {
    QString message = ui->lineEdit_message->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a message.");
        return; // 메시지가 비어있다면 함수 종료
    }
    QString formattedMessage = QString("[%1] %2: %3")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
            .arg(userID)
            .arg(message); // 사용자 ID와 함께 메시지
    socket->write(formattedMessage.toUtf8()); // formattedMessage 전송
    ui->textBrowser_messages->append(formattedMessage); // 자신의 메시지 출력
    ui->lineEdit_message->clear(); // 메시지 입력창 비우기
}

void ChatClient::sendFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray fileData = file.readAll();
            socket->write("FILE:" + QFileInfo(fileName).fileName().toUtf8() + "\n"); // 파일 이름 전송
            socket->write(fileData); // 파일 데이터 전송
            ui->textBrowser_messages->append(userID + " sent a file: " + QFileInfo(fileName).fileName()); // 파일 전송 메시지
            file.close();
        }
    }
}

void ChatClient::readMessage() {
    QByteArray data = socket->readAll(); // 서버에서 받은 데이터 읽기
    QString receivedMessage = QString(data); // 서버에서 받은 메시지를 QString으로 변환

    // 로그 추가
    qDebug() << "Received message: " << receivedMessage;

    // 메시지 형식: "userID: message" 또는 "Server: message"
    if (receivedMessage.startsWith("FILE:")) {
        // 파일 수신 처리
        QString fileName = receivedMessage.mid(5).trimmed(); // "FILE:" 이후의 파일 이름
        ui->textBrowser_messages->append(QString("Received file: %1").arg(fileName));
    } else {
        // 모든 메시지를 textBrowser_messages에 추가
        ui->textBrowser_messages->append(receivedMessage);
    }
}

void ChatClient::receiveFile() {
    QByteArray fileData = socket->readAll(); // 모든 데이터 읽기
    QString fileName = "received_file.txt"; // 수신할 파일 이름 지정

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(fileData);
        file.close();
        ui->textBrowser_messages->append("Received file: " + fileName);
    } else {
        ui->textBrowser_messages->append("Failed to save file.");
    }
}
