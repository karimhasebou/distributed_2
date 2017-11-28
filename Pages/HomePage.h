#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <vector>
#include <string>
#include <QtWidgets/QListView>
#include <QStandardItemModel>
#include <QStandardItem>

struct ImageEntry {
    std::string imageName;
    std::string username;
};

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
    void extractViews(std::string);

private:
    Ui::HomePage *ui;
    std::string myUsername;
    QPixmap imagePreview;
    QString image_path;

    std::map<std::string, std::string> usersIpAddress;
    std::vector<ImageEntry> availableImages;
    const std::string myImagesPath = "DownloadedImages/";
    const std::string otherImagesPath;

    void setEditEntriesVisible(const bool&);
    void getAllImages();
    void getMyImages();
    void editImageSettings();
    void requestImage();

    void showImagesInList(QListView * , const std::vector<ImageEntry>&);


};

#endif // HOMEPAGE_H
