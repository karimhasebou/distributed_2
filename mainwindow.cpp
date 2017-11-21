#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readDatabase();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readDatabase()
{
    std::string username, password, ip_address;
    bool online;

    std::string db_file = "/home/nawawy/Distributed_2/Database/database.txt";
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

void MainWindow::on_signInButton_clicked()
{

    QString username_q = ui->username_input ->text();

    std::string username = username_q.toUtf8().constData();

    QString password_q = ui->password_input ->text();

    std::string password = password_q.toUtf8().constData();




    std::map<std::string, std::pair<std::string, bool>>::iterator it;
    it = db.find(username);

    if(it != db.end())
    {
        std::string pw = it->second.first;

        if(pw == password)
        {
            hide();
            home = new home_window(this);
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
