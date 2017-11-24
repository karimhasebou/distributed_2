#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <fstream>
#include "HomePage.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();
    
private slots:
    void on_signInButton_clicked();


private:
    HomePage* home;
    Ui::LoginPage *ui;
    void readDataBase();
    std::map<std::string, std::pair<std::string, bool>> db;
    std::ifstream database_file;
    std::vector<std::string> connected_peers;
};

#endif // LOGINPAGE_H
