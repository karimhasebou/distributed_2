#include "LoginPage.h"
#include "../ui_LoginPage.h"
#include "../RPC/RpcCalls.h"
#include "../UDPLayer/MySocket.h"
#include <QMessageBox>

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
    
    sentMessage.setDestIPAddress("127.0.0.1");
    sentMessage.setDestPortNumber(63000);
    
    socket.callRPC(sentMessage);

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
