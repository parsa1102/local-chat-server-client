#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QDebug>
#include <QAbstractSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>


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
    void start(qint64 port);
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();

private slots:
    void on_castButton_clicked();

    void on_goLiveButton_clicked();

private:
    QTcpServer m_server;
    QSet<QTcpSocket*> connectedSockets;
    void showMessage(QString sender, QString message, QString time);
};
#endif // WIDGET_H
