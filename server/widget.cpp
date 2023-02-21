#include <widget.h>
#include <ui_widget.h>
#include <QSet>
#include <QDateTime>
#include <QHash>
#include <QShortcut>

QHash<QString , QString> userHolder; //connects socket pointer to username


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->portEdit->setInputMask("999999");
    setWindowTitle("PChat Server");
    connect(&m_server,&QTcpServer::newConnection,this,&Widget::newConnection);
    new QShortcut(QKeySequence(Qt::Key_Return), this, SLOT(on_castButton_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(on_castButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start(qint64 port)
{
    if(m_server.isListening()){
        m_server.close();
    }

    m_server.listen(QHostAddress::Any,port);

    //server up on port message
    QString connectedServer = "server";
    QString bindMessage = "started listening on port " + QString::number(port);
    QString bindTime = QTime::currentTime().toString();
    showMessage(connectedServer , bindMessage , bindTime);
}

void Widget::quit()
{
    m_server.close();
}

void Widget::newConnection()
{


    QTcpSocket* connectedSocket = m_server.nextPendingConnection();

    connect(connectedSocket,&QTcpSocket::disconnected,this,&Widget::disconnected);
    connect(connectedSocket,&QTcpSocket::readyRead,this,&Widget::readyRead);

    //connection notification :
    //QString connectedUserId = "client with yet to be defined" + ptrStr);
    //QString connectionMessage = "connected";
    //QString connectionTime = QTime::currentTime().toString();
    //showMessage(connectedUserId , connectionMessage , connectionTime);
}

void Widget::disconnected()
{
    QTcpSocket* DcSocket = qobject_cast<QTcpSocket*>(sender());

    QTcpSocket *ptr = DcSocket;
    QString ptrStr = QString( "0x%1" ).arg( reinterpret_cast<quintptr>(ptr),
                        QT_POINTER_SIZE * 2, 16, QChar('0') );
    connectedSockets.remove(DcSocket);

    QString DcUserId = userHolder[ptrStr];
    QString DcMessage = "disconnected";
    QString DcTime = QTime::currentTime().toString();

    showMessage(DcUserId , DcMessage , DcTime);
    DcSocket->deleteLater();
}

void Widget::readyRead()
{
    QTcpSocket* senderSocket = qobject_cast<QTcpSocket*>(sender());
    QTcpSocket *ptr = senderSocket;
    QString ptrStr = QString( "0x%1" ).arg( reinterpret_cast<quintptr>(ptr),
                        QT_POINTER_SIZE * 2, 16, QChar('0') );

    if(connectedSockets.find(senderSocket) == connectedSockets.end()){
        qInfo()<<"hello";
        QString userName = senderSocket->readAll();
        QString joinTime = QTime::currentTime().toString();
        userHolder[ptrStr] = userName;
        showMessage(userName , "joined" , joinTime);
        connectedSockets.insert(senderSocket);
        return;
    }
    else{
        QString messageSenderId = userHolder[ptrStr];
        QString messageToRead = senderSocket->readAll();
        QString recieveTime = QTime::currentTime().toString();
        showMessage(messageSenderId , messageToRead , recieveTime);
    }
}


void Widget::on_castButton_clicked()
{
    if(!(ui->messageCastEdit->text().toStdString().find_first_not_of(' ') != std::string::npos))
    {
        return;
    }
    QByteArray dataToCast = ui->messageCastEdit->text().toLatin1();
    QString messageSender = "Server";
    QString sendTime = QTime::currentTime().toString();
    foreach(QTcpSocket *s, connectedSockets){
        s->write(dataToCast);
    }
    showMessage(messageSender , dataToCast , sendTime);
    ui->messageCastEdit->setText("");
    return;
}


void Widget::showMessage(QString sender, QString message, QString time)
{

    ui->messageBrowser->insertHtml("<font size'-2' style='margin-bottom: 0in; line-height: 100%;'><span style='color: #ff6d6d;'>" + sender +"</span></font><br>\n");

    ui->messageBrowser->insertHtml("<font  style='margin-bottom: 0in; line-height: 100%;'><span style='color: #000000;'>"+
                                message+
                                "</span></font>\n");


    QString spacer = "";
    for(int i=0;i<message.size() + 8;i++)
        spacer += " ";
    ui->messageBrowser->insertHtml("<font size='-5' style='margin-bottom: 0in; line-height: 100%;'>"
                                "<span style='color: #999999;'>"+
                                spacer+
                                time+
                                "</span></font><br><br>\n");
}

void Widget::on_goLiveButton_clicked()
{
    QString portToConnect = ui->portEdit->text();
    this->start(portToConnect.toInt());
}
