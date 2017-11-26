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
    ui->setupUi(this);
    //    connect(ui->signInButton, &QPushButton::clicked, this, &LoginPage::on_signInButton_clicked);
    
    MySocket socket;
    socket.bind(0);
    
    CustomString * customString = new CustomString("hi");
    
    std::vector<CustomObject *> parameters = {customString};
    
    MarshalledMessage marshalledMessage;
    
    marshal(marshalledMessage, parameters);
    
    Message sentMessage(marshalledMessage);
    
    sentMessage.setMessageType(Request);
    sentMessage.setRpcOperation(1);
    sentMessage.setRpcRequestID(1);

    std::cout<<"Sending RPC argument"<<std::endl;
    
    sentMessage.setDestIPAddress("192.168.1.8"); //192.168.1.8
    sentMessage.setDestPortNumber(63000);
    
    Message reply = socket.callRPC(sentMessage);
    
    std::vector<CustomObject*> returnValues = {new CustomString()};
    
    std::string result = dynamic_cast<CustomString*>(returnValues[0])->getValue();
    
    std::cout<<result<<std::endl;
//
    
//    QPixmap backgroundImage("/Users/faridaeid/Desktop/Desktop/Project Files/GitHub/distributed_2/Pages/LoginPageBackground.png");
//    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, backgroundImage);
//    this->setPalette(palette);
//    
//    ui->label->setStyleSheet("QLabel {color: #ffffff;}");
//    ui->label_2->setStyleSheet("QLabel {color: #ffffff;}");
//    ui->label_3->setStyleSheet("QLabel {color: #ffffff;}");


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
