#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>
#include <QTextCharFormat>
#include <QColor>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    setWindowTitle("PChat Client");
    connect(&m_socket,&QTcpSocket::connected,this,&Widget::connected);
    connect(&m_socket,&QTcpSocket::disconnected,this,&Widget::disconnected);
    connect(&m_socket,&QTcpSocket::stateChanged,this,&Widget::stateChanged);
    connect(&m_socket,&QTcpSocket::readyRead,this,&Widget::readyRead);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::connectToHost(QString host, quint16 port)
{
    if(m_socket.isOpen()) disconnect();

    m_socket.connectToHost(host,port);
    if(m_socket.waitForConnected(5000)){
        ui->statusLabel->setText("connected");
    }else{
        ui->statusLabel->setText("connection timed out");
    }
}
void Widget::disconnect()
{
    m_socket.close();
    ui->statusLabel->setText("disconnecting");
}

void Widget::connected()
{
    ui->statusLabel->setText("status : connected");
}

void Widget::disconnected()
{
    ui->statusLabel->setText("disconnected");
}


void Widget::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum stateHolderMetaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State: " << stateHolderMetaEnum.valueToKey(socketState);
}

void Widget::readyRead()
{
    QByteArray dataToRead = m_socket.readAll();
    QString dataSender = "Server";
    QString sendTime = QTime::currentTime().toString();
    showMessage(dataSender , dataToRead , sendTime);
}



void Widget::on_sendButton_clicked()
{
    if(!m_socket.isOpen()){
        ui->statusLabel->setText("status : offline, failed to send message");
        ui->messageEdit->setText("");
        return;
    }
    QByteArray dataToSend = ui->messageEdit->text().toLatin1();
    QString sendTime = QTime::currentTime().toString();
    QString messageSender = "Me";
    if(m_socket.write(dataToSend) == -1){
        ui->statusLabel->setText("failed to send message");
    }else{
        ui->statusLabel->setText("message sent");
    }
    ui->messageEdit->setText("");
    //ui->textBrowser->append("Me : " + data + " : " + QDateTime::currentDateTime().toString());
    showMessage(messageSender , dataToSend , sendTime);
    return;
}


void Widget::on_connectButton_clicked()
{
    QString portToConnect = ui->portEdit->text();
    QString ipToConnect = ui->IPEdit->text();
    ui->portEdit->setText("");
    ui->IPEdit->setText("");
    ui->statusLabel->setText("connecting to " + ipToConnect + ":"+portToConnect);
    qint64 portToConnectInt = portToConnect.toInt();
    this->connectToHost(ipToConnect , portToConnectInt);
}

void Widget::showMessage(QString sender, QString message, QString time)
{

    ui->messageBrowser->insertHtml("<font size'-1' style='margin-bottom: 0in; line-height: 100%;'><span style='color: #ff6d6d;'>" + sender +"</span></font><br>\n");

    ui->messageBrowser->insertHtml("<font size='+1' style='margin-bottom: 0in; line-height: 100%;'><span style='color: #000000;'>"+
                                message+
                                "</span></font>\n");

    QString spacer = "";
    for(int i=0;i<message.size() + 8;i++)
        spacer += " ";
    ui->messageBrowser->insertHtml("<font size='-4' style='margin-bottom: 0in; line-height: 100%;'>"
                                "<span style='color: #999999;'>"+
                                spacer+
                                time+
                                "</span></font><br>\n");
}


