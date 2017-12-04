#include <QtWidgets/QFileDialog>
#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"
#include "../RequestHandler.h"
#include "../Stegnography/StegManager.h"
#include "../Stegnography/Paths.h"

namespace homepage {
    std::vector<std::string> splitString(std::string);
    std::vector<std::string> listFilesInDir(const std::string&);
};


HomePage::HomePage(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::HomePage)
{
    ui->setupUi(this);

    imagePreview.load("../defaultImage.jpg");
    ui->imagePreview->setPixmap(imagePreview);
    ui->imagePreview->setScaledContents(true);

    ui->editImageButton->setEnabled(false);
    ui->requestImageButton->setEnabled(false);
    
    ui->myImagesList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->availableImagesList->setSelectionMode(QAbstractItemView::SingleSelection);

    setEditEntriesVisible(false);

    connect(ui->allImagesButton, &QPushButton::clicked, this, &HomePage::getAllImages);
    connect(ui->myImagesButton, &QPushButton::clicked, this, &HomePage::getMyImages);
    connect(ui->editImageButton, &QPushButton::clicked, this, &HomePage::editImageSettings);
    connect(ui->requestImageButton, &QPushButton::clicked, this, &HomePage::requestImage);
    connect(ui->updatePictureButton, &QPushButton::clicked, this, &HomePage::updateViews);
    connect(ui->addUserButton, &QPushButton::clicked, this, &HomePage::addUser);
    connect(ui->uploadImage, &QPushButton::clicked, this, &HomePage::uploadImage);
    
    ui->usersTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Username"));
    ui->usersTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Count"));

    connect(ui->myImagesList,
            &QListWidget::itemClicked, this,
            &HomePage::handleMyImagesClick);

    connect(ui->availableImagesList,
            &QListWidget::itemClicked, this,
            &HomePage::handleAvailableImagesClick);

    QString listStyleSheet = "QListWidget {background-color:#000000;"
                                "color: #ffffff;"
                                "font-size: 14px;"
                                "padding: 5px;"
                                "border-style: outset;"
                                "border-radius: 10px;"
                                "border-color: #ffffff;"
                                "border-width: 1px;}";

    ui->myImagesList->setStyleSheet(listStyleSheet);
    ui->availableImagesList->setStyleSheet(listStyleSheet);

    QString pushButtonStyleSheet = "QPushButton {color: #ffffff; "
            "background-color:#000000;"
            "border-color: #e65c00;"
            "border-radius: 10px;"
            "border-width: 1px;"
            "border-style: outset;"
            "padding: 5px;}";

    ui->allImagesButton->setStyleSheet(pushButtonStyleSheet);
    ui->myImagesButton->setStyleSheet(pushButtonStyleSheet);
    ui->editImageButton->setStyleSheet(pushButtonStyleSheet);
    ui->requestImageButton->setStyleSheet(pushButtonStyleSheet);
    ui->uploadImage->setStyleSheet(pushButtonStyleSheet);
    ui->updatePictureButton->setStyleSheet(pushButtonStyleSheet);
    ui->addUserButton->setStyleSheet(pushButtonStyleSheet);

    ui->addUsernameLabel->setStyleSheet("QLabel {color: #ffffff;}");
    ui->viewCountLabel->setStyleSheet("QLabel {color: #ffffff;}");

    ui->imagePreview->setStyleSheet("QLabel {border-color: #ffffff;"
                                            "border-radius: 10px;"
                                            "border-width: 1px;"
                                            "border-style:outset;}");

}

HomePage::~HomePage() {

    delete ui;
}

void HomePage::getAllImages() {

    usersIpAddress = client::getUsersIpAddress();

    std::map<std::string, std::string>::iterator it;

    availableImages.clear();
    availableImages.resize(0);

    for (it = usersIpAddress.begin(); it != usersIpAddress.end(); it++) {

        printf("ip %d %s\n", 1, it->second.c_str());
        std::vector<std::string> imageNames = client::getAccessibleImages(myUsername, it->second);

        for (size_t i = 0;i < imageNames.size(); i++) {

            ImageEntry imageEntry;
            imageEntry.imageName = imageNames[i];
            imageEntry.username = it->first;
            imageEntry.myImage = false;
            availableImages.push_back(imageEntry);
        }
    }

    showImagesInList(ui->availableImagesList, availableImages);
}

void HomePage::getMyImages() {
    
    std::vector<std::string> myImagesNames = homepage::listFilesInDir(myImagesPath);
    
    allMyImages.clear();
    allMyImages.resize(0);
    
    for (size_t i = 0; i < myImagesNames.size(); i++) {
        
        ImageEntry imageEntry;
        imageEntry.imageName = myImagesNames[i];
        imageEntry.myImage = true;
        
        allMyImages.push_back(imageEntry);
        
    }
    
    for (size_t i = 0; i < downloadedImages.size(); i++) {
        
        allMyImages.push_back(downloadedImages[i]);
        
    }
    
    showImagesInList(ui->myImagesList, allMyImages);
    
}

void HomePage::requestImage() {
    
    int index = ui->availableImagesList->currentIndex().row();
    std::string imageName = availableImages[index].imageName;
    
    Image requestedImage = client::getImage(imageName, usersIpAddress[availableImages[index].username]);

    std::string imageFilePath = myDownloadsPath + imageName;
    
    std::ofstream outfile(imageFilePath , std::ios::out | std::ios::binary);
    outfile.write(requestedImage.content, requestedImage.length);
    outfile.close();
    
    bool alreadyDownloaded = false;
    
    for (size_t i = 0; i < downloadedImages.size() && !alreadyDownloaded; i++) {
        
        if(downloadedImages[i] == availableImages[index]) {
            alreadyDownloaded = true;
        }
    }
    
    if (!alreadyDownloaded) {
        
        downloadedImages.push_back(availableImages[index]);
    }
    
    getMyImages();
}

void HomePage::editImageSettings() {
    
    setEditEntriesVisible(true);

}

void HomePage::uploadImage() {

    std::string filePath = QFileDialog::getOpenFileName(this,
                                                   tr("Choose Image"),
                                                   "",
                                                   tr("Image Files (*.png *.jpg *.bmp)")).toStdString();

    std::string stegNCopy = "../Stegnography/steg_img.sh " + DEFAULT +
         " " + filePath + " " + myImagesPath;

    system(stegNCopy.c_str());
}

void HomePage::addUser() {
    
    QString usernameToUpdate = ui->usernameEdit->text();
    QString viewsToUpdate = ui->viewCountEdit->text();
    
    int rows = ui->usersTableWidget->rowCount();
    
    ui->usersTableWidget->insertRow(rows);
    
    ui->usersTableWidget->setItem(rows, 0, new QTableWidgetItem(usernameToUpdate));
    ui->usersTableWidget->setItem(rows, 1, new QTableWidgetItem(viewsToUpdate));

}

void HomePage::updateImgCount(std::string img, int count)
{
    
}

void HomePage::handleMyImagesClick(QListWidgetItem * listItem) {
    
    ui->requestImageButton->setEnabled(false);
    
    int index = getSelectedIndex(ui->myImagesList);
    bool isMine = allMyImages[index].myImage;
    std::string selectedImgPath = (isMine) ? myImagesPath : myDownloadsPath;

    int count = 1e9;

    if (isMine) {

        ui->editImageButton->setEnabled(true);
        StegImage image = stego::getImgAndCreds(myImagesPath, allMyImages[index].imageName);
        ui->imagePreview->setPixmap(image.image);
        showMapInTable(ui->usersTableWidget, image.users);

    } else {
        ui->editImageButton->setEnabled(false);
        count = getMyImageCount(selectedImgPath);
    }
    
    std::string imageName = allMyImages[index].imageName;
    if (count)
    {
        viewImage(selectedImgPath, imageName);
    }
    if (isMine)
        updateImgCount(selectedImgPath, count - 1);
}

void HomePage::handleAvailableImagesClick(QListWidgetItem * listItem) {
    
    ui->requestImageButton->setEnabled(true);
}

void HomePage::updateViews() {
    
    std::map<std::string, int> usersInfo;
    std::string username;
    int count;
    
    for (int i = 0; i < ui->usersTableWidget->rowCount(); i++) {
        
        username = ui->usersTableWidget->item(i, 0)->text().toStdString();
        count = ui->usersTableWidget->item(i, 0)->text().toInt();

        usersInfo[username] = count;
        
    }
    
}

void HomePage::viewImage(const std::string& dir, const std::string& filename){

}

void HomePage::setUsername(std::string username) {
    
    this->myUsername = username;
}

int HomePage::getMyImageCount(const std::string& imageName) {
    
    extractViews( myDownloadsPath + imageName);
    
    std::string unStaggedListPath = imageName + ".txt";
    
    std::ifstream imageContentFile;
    imageContentFile.open(unStaggedListPath.c_str());
    
    std::string username;
    int viewsCount;
    
    if(imageContentFile.fail()) {
        
        printf("Opening list of view failed: %s\n", imageName.c_str());
        
    } else {
        
        while(!imageContentFile.eof())
        {
            imageContentFile >> username >> viewsCount;
            
            if (username == myUsername)
                return viewsCount;
        }
    }
    
    return -1;
}

void HomePage::extractViews(std::string imagePath) {
    
    std::string exec_command = "steghide extract -sf " + imagePath;
    exec_command += " -p root -f";

    system(exec_command.c_str());
}

std::vector<std::string> homepage::splitString(std::string sentence) {
    
  std::stringstream ss;
  ss<<sentence;

  std::string to;
  std::vector<std::string> files;

    while(std::getline(ss,to,'\n')){
        files.push_back(to);
    }


    return files;
}

std::vector<std::string> homepage::listFilesInDir(const std::string& folderName)
{
    using namespace std;
    string command = "ls " + folderName;
    FILE  *file = popen(command.c_str(), "r");

    int ch;
    string result;

    do{
        ch = fgetc(file);

        if(ch == EOF) {
            break;
        }

        result += ch;

    } while(1);

    pclose(file);

    return homepage::splitString(result);
}

void HomePage::setEditEntriesVisible(const bool & visible) {

    ui->usernameEdit->setVisible(visible);
    ui->updatePictureButton->setVisible(visible);
    ui->addUserButton->setVisible(visible);
    ui->usersTableWidget->setVisible(visible);
    ui->label->setVisible(visible);
    ui->viewCountEdit->setVisible(visible);
    ui->viewCountLabel->setVisible(visible);
    ui->addUsernameLabel->setVisible(visible);

}

void HomePage::showImagesInList(QListWidget * listWidget, const std::vector<ImageEntry> & images) {
    
    listWidget->clear();

    for (size_t i = 0; i < images.size(); i++) {

        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString::fromStdString(images[i].imageName));
        listWidget->insertItem(i, newItem);
    }
}

void HomePage::showMapInTable(QTableWidget* table, std::map<std::string, int> & usersMap) {
    
    table->clear();
    
    std::map<std::string, int>::iterator it;

    int row = 0;

    for (it = usersMap.begin(); it != usersMap.end(); it++) {

        QTableWidgetItem * newItem = new QTableWidgetItem()
        table->insertRow(row);
        
        newItem->setText(QString::fromStdString(it->first));
        table->setItem(row, 0, newItem);
        
        newItem->setText(QString::number(it->second));
        table->setItem(row, 1, newItem);
        
        row++;
        
    }
}

int HomePage::getSelectedIndex(QListWidget* list) {
    
    QList<QListWidgetItem*> selection = list->selectedItems();
    int index = list->row(selection[0]);
    return index;

}
