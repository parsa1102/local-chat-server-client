#ifndef USERNAMEDIALOG_H
#define USERNAMEDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class usernameDialog;
}

class usernameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit usernameDialog(QWidget *parent = nullptr);
    ~usernameDialog();

private slots:
    void on_comfirmButton_clicked();

private:
    Ui::usernameDialog *ui;
private:
    QString m_username;
    //QStringList takenUsernames;
public:
    QString usernameGetter();
};

#endif // USERNAMEDIALOG_H
