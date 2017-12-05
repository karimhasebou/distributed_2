#include "LoginPage.h"
#include "../ui_LoginPage.h"
#include "../RPC/RpcCalls.h"
#include "../UDPLayer/MySocket.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>


LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    this->setStyleSheet("background-color: #000000;");
    ui->setupUi(this);
    //    connect(ui->signInButton, &QPushButton::clicked, this, &LoginPage::on_signInButton_clicked);
    
//    QPixmap backgroundImage("Pages/background.jpg");
//    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, backgroundImage);
//    this->setPalette(palette);


    QString pushButtonStyleSheet = "QPushButton {color: #ffffff; "
            "background-color:#1a1a1a;"
            "border-color: #595959;"
            "border-radius: 10px;"
            "border-width: 1px;"
            "border-style: outset;"
            "padding: 5px;}";

    ui->signInButton->setStyleSheet(pushButtonStyleSheet);
    ui->pushButton->setStyleSheet(pushButtonStyleSheet);

    ui->pushButton->setVisible(false);

    QString lineEditStyleSheet = "QLineEdit:focus { "
            "border: 2px solid #595959; "
            "color: #ffffff;"
            "} "
            "QLineEdit {"
            "color: #ffffff; }";

    ui->usernameInputEdit->setStyleSheet(lineEditStyleSheet);
    ui->passwordInputEdit->setStyleSheet(lineEditStyleSheet);

    ui->label->setStyleSheet("QLabel {color: #ffffff;}");
    ui->label_2->setStyleSheet("QLabel {color: #ffffff;}");
    ui->label_3->setStyleSheet("QLabel {color: #ffffff;}");

    #ifdef _DEBUGGING_ACTIVE
        home = new HomePage(this);
        home->setUsername("karimhasebo");
        home->show();
    #endif

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
