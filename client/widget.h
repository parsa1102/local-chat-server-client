#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMetaEnum>
#include <QNetworkProxy>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

public slots:
    void connectToHost(QString host, quint16 port);
    void disconnect();

private slots:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();

    void on_sendButton_clicked();

    void on_connectButton_clicked();
    void showMessage(QString sender, QString message , QString time);

private:
    QTcpSocket m_socket;
};
#endif // WIDGET_H
