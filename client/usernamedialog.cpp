#include "usernamedialog.h"
#include "ui_usernamedialog.h"

usernameDialog::usernameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usernameDialog)
{
    ui->setupUi(this);
    /*QCoreApplication::setOrganizationName("TL");
    QCoreApplication::setApplicationName("userDialog");
    QCoreApplication::setOrganizationDomain("tlsmf.ddns.net");
    QSettings usernameSaver(QCoreApplication::organizationName() , QCoreApplication::applicationName());
    usernameSaver.beginGroup("usernames");
    takenUsernames = usernameSaver.value("takenUsernames").toStringList();
    usernameSaver.endGroup();
    */
}

usernameDialog::~usernameDialog()
{
    delete ui;
}

void usernameDialog::on_comfirmButton_clicked()
{
    /*QString tmp_m_username = ui->usernameEdit->text();
    bool flag = true;
    foreach(QString username , takenUsernames){
        if(username == )
    }*/

    m_username = ui->usernameEdit->text();

    hide();
    return;
}

QString usernameDialog::usernameGetter()
{
    return m_username;
}
