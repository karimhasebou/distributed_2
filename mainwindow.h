#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<home_window.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setName(const QString &);
    QString name() const;

    ~MainWindow();

private slots:
    void on_signInButton_clicked();

private:
    Ui::MainWindow *ui;
    home_window* home;
};

#endif // MAINWINDOW_H
