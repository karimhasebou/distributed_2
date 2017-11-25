#include "LoginPage.h"
#include "../ui_LoginPage.h"
#include "../RPC/RpcCalls.h"
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
   // readDataBase();
    
//    connect(ui->signInButton, &QPushButton::clicked, this, &LoginPage::on_signInButton_clicked);

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::readDataBase()
{
    std::string username, password, ip_address;
    bool online;
    
    std::string db_file = "../database.txt";
    std::ifstream database_file;
    
    database_file.open(db_file);
    
    while(!database_file.eof())
    {
        database_file >> username >> password >> online >> ip_address;
        
        db.insert (std::pair<std::string, std::pair<std::string, bool>>(username, std::make_pair(password, online)));
        
        if(online)
            connected_peers.push_back(ip_address);
        else
        {
            connected_peers.erase(std::remove(connected_peers.begin(), connected_peers.end(), ip_address), connected_peers.end());
        }
        
    }
}

void LoginPage::on_signInButton_clicked()
{
    
    QString username_q = ui->usernameInputEdit->text();
    
    std::string username = username_q.toUtf8().constData();
    
    QString password_q = ui->passwordInputEdit->text();
    
    std::string password = password_q.toUtf8().constData();
    
   // bool loginStatus = client::login(username, password);
        
    
    std::map<std::string, std::pair<std::string, bool>>::iterator it;
    it = db.find(username);
    
    if(it != db.end())
    {
        std::string pw = it->second.first;
        
        if(pw == password)
        {
            hide();
            home = new HomePage(this);
//            home->set_ips(connected_peers);
            home->show();
        }
        else
        {
            QMessageBox::information(
                                     this,
                                     tr("DIstributed"),
                                     tr("Wrong Password") );
        }
    }
    else
    {
        QMessageBox::information(
                                 this,
                                 tr("DIstributed"),
                                 tr("Username Not found") );
    }
    
    /*
     
     void logIn(usernme, password)
     {
     //send username and password "marshalled" to the server to authenticate
     
     msg = marshall(username, password);
     
     sendto(server, msg);
     
     Qstring auth;
     recvfrom(server, auth)
     
     if(auth == true)
     {
     hide();
     home = new home_window(this);
     home->show();
     }
     else
     {
     cout error
     }
     
     }
     
     */
    
}
