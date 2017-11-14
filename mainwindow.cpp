#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signInButton_clicked()
{
    QString username = ui->username_input ->text();

    QString password = ui->password_input ->text();

    if(username == "test" && password == "test")
    {
        hide();
        home = new home_window(this);
        home->show();
    }

}
