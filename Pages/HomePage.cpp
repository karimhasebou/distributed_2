#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"
#include "../RequestHandler.h"

namespace homepage {
    std::vector<std::string> splitString(std::string);
    std::vector<std::string> listFilesInDir(const std::string&);
};


HomePage::HomePage(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::HomePage)
{
    ui->setupUi(this);

    imagePreview.load("../defaultImage.png");
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
    // connect(ui->updateEditsButton, &QPushButton::clicked, this, &HomePage::updateViews);

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

    QString pushButtonStyleSheet = "QPushButton {color: #00b300; "
            "background-color:#000000;"
            "border-color: #ffffff;"
            "border-radius: 10px;"
            "border-width: 1px;"
            "border-style: outset;"
            "padding: 5px;}";

    ui->allImagesButton->setStyleSheet(pushButtonStyleSheet);
    ui->myImagesButton->setStyleSheet(pushButtonStyleSheet);
    ui->editImageButton->setStyleSheet(pushButtonStyleSheet);
    ui->requestImageButton->setStyleSheet(pushButtonStyleSheet);
    //ui->updateEditsButton->setStyleSheet(pushButtonStyleSheet);

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

        std::vector<std::string> imageNames = client::getAccessibleImages(myUsername, it->second);

        for (int i = 0;i < imageNames.size(); i++) {

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
    
    for (int i = 0; i < myImagesNames.size(); i++) {
        
        ImageEntry imageEntry;
        imageEntry.imageName = myImagesNames[i];
        imageEntry.myImage = true;
        
        allMyImages.push_back(imageEntry);
        
    }
    
    for (int i = 0; i < downloadedImages.size(); i++) {
        
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
    
    for (int i = 0; i < downloadedImages.size() && !alreadyDownloaded; i++) {
        
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

void HomePage::handleMyImagesClick(QListWidgetItem * listItem) {
    
    ui->requestImageButton->setEnabled(false);
    
    int index = getSelectedIndex(ui->myImagesList);
    
    if (allMyImages[index].myImage) {
        
        ui->editImageButton->setEnabled(true);
        
    } else {
        
        ui->editImageButton->setEnabled(false);
    }
    
    std::string imageName = allMyImages[index].imageName;
    
    viewImage(myImagesPath + imageName);
    
}

void HomePage::handleAvailableImagesClick(QListWidgetItem * listItem) {
    
    ui->requestImageButton->setEnabled(true);
    
}

void HomePage::updateViews() {
    
    QString usernameToUpdate = ui->usernameEdit->text();
    QString viewsToUpdate = ui->viewCountEdit->text();
    
    int imageSelected = getSelectedIndex(ui->availableImagesList);
    
    std::string imageName = allMyImages[imageSelected].imageName;
    
    std::string viewsString = viewsToUpdate.toUtf8().constData();
    std::string usernameString = usernameToUpdate.toUtf8().constData();
    
    int views = atoi(viewsString.c_str());
    
    bool updated = client::updateCount(imageName, usernameString, views);
    
    //callRPC
    
    
}

void HomePage::viewImage(const std::string& filePath) {
    
    QPixmap image;
    image.load(QString::fromStdString(filePath));
    
    ui->imagePreview->setPixmap(image);
    ui->imagePreview->setScaledContents(true);
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
    // ui->updateEditsButton->setVisible(visible);
    ui->viewCountEdit->setVisible(visible);
    ui->viewCountLabel->setVisible(visible);
    ui->addUsernameLabel->setVisible(visible);

}

void HomePage::showImagesInList(QListWidget * listWidget, const std::vector<ImageEntry> & images) {

    for (int i = 0; i < images.size(); i++) {
        
        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString::fromStdString(images[i].imageName));
        listWidget->insertItem(i, newItem);
    }
}

int HomePage::getSelectedIndex(QListWidget* list) {
    
    QList<QListWidgetItem*> selection = list->selectedItems();
    int index = list->row(selection[0]);
    return index;

}
