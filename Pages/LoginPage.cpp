#include "LoginPage.h"
#include "../ui_LoginPage.h"
#include "../RPC/RpcCalls.h"
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    //    connect(ui->signInButton, &QPushButton::clicked, this, &LoginPage::on_signInButton_clicked);

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_signInButton_clicked()
{
    
    QString username_q = ui->usernameInputEdit->text();
    
    std::string username = username_q.toUtf8().constData();
    
    QString password_q = ui->passwordInputEdit->text();
    
    std::string password = password_q.toUtf8().constData();
    
    LoginStatus loginStatus = client::login(username, password);
        
    
    switch (loginStatus) {
            
        case loginSucess:
            hide();
            home = new HomePage(this);
            home->setUsername(username);
            home->show();
            break;
            
        case wrongPassword:
            QMessageBox::information(this, tr("Try Again"), tr("Wrong Password !"));
            break;
        
        case wrongUsername:
            QMessageBox::information(this, tr("Error"), tr("Username Not Found !"));
            break;
            
        default:
            break;
    }
}
