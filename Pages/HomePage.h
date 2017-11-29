#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <vector>
#include <string>
#include <stdio.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileDialog>
#include "../StegManager.h"

struct ImageEntry {
    std::string imageName;
    std::string username;
    bool myImage;
    
    bool operator==(const ImageEntry& other) {
        return (imageName == other.imageName) && (username == other.username);
    }
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

    std::map<std::string, std::string> usersIpAddress;
    std::vector<ImageEntry> availableImages;
    std::vector<ImageEntry> downloadedImages;
    std::vector<ImageEntry> allMyImages;
    const std::string myImagesPath = "MyImages/";
    const std::string myDownloadsPath = "DownloadedImages/";
    const std::string defaultImagePath = "defaultImage.png";

    void setEditEntriesVisible(const bool&);
    void getAllImages();
    void getMyImages();
    void editImageSettings();
    void requestImage();
    void updateViews();
    void addUser();
    void uploadImage();
    void handleMyImagesClick(QListWidgetItem *);
    void handleAvailableImagesClick(QListWidgetItem *);
    void updateImgCount(std::string, int);

    void showImagesInList(QListWidget * , const std::vector<ImageEntry>&);
    int getMyImageCount(const std::string&);
    void viewImage(const std::string& dir, const std::string& filename);
    int getSelectedIndex(QListWidget*);

};

#endif // HOMEPAGE_H
