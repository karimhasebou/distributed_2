#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <vector>
#include <string>


namespace Ui {
class HomePage;
}

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();
    
    void set_ips(const std::vector<std::string> &);
    void setUsername(std::string);
    
private slots:
    void on_getImagesButton_clicked();
    
    void on_requestImageButton_clicked();
    
    void on_viewImageButton_clicked();

    void on_update_views_clicked();

private:
    Ui::HomePage *ui;
    QStringListModel *model;
    QStringListModel *model_my_images;
    std::string MyUsername;
    QPixmap img_default;
    QString image_path;
    std::vector<std::string> ip_addresses;
    

};

#endif // HOMEPAGE_H
