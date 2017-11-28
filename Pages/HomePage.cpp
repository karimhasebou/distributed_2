#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"
#include "../RequestHandler.h"

namespace homepage {
    std::vector<std::string> splitString(std::string sentence);
    std::vector<std::string> listFilesInDir();
};


HomePage::HomePage(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::HomePage)
{
    ui->setupUi(this);

    imagePreview.load("MyImages/default.jpg");
    ui->imageView->setPixmap(imagePreview);
    ui->imageView->setScaledContents(true);

    ui->editImageButton->setEnabled(false);
    ui->requestImageButton->setEnabled(false);

    setEditEntriesVisible(false);

    connect(ui->allImagesButton, &QPushButton::clicked, this, &HomePage::getAllImages);
    connect(ui->myImagesButton, &QPushButton::clicked, this, &HomePage::getMyImages);
    connect(ui->editImageButton, &QPushButton::clicked, this, &HomePage::editImageSettings);
    connect(ui->requestImageButton, &QPushButton::clicked, this, &HomePage::requestImage);

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::getAllImages() {

    usersIpAddress = client::getUsersIpAddress();

    std::map<std::string, std::string>::iterator it;

    availableImages.clear();
    availableImages.resize(0);

    for (it = usersIpAddress.begin(); it != usersIpAddress.end(); i++) {

        std::vector<std::string> imageNames = client::getAccessibleImages(myUsername, it->second);

        for (int i = 0;i < imageNames.size(); i++) {

            ImageEntry imageEntry;
            imageEntry.imageName = imageNames[i];
            imageEntry.username = it->first;
            availableImages.push_back(imageEntry);
        }
    }

    showImagesInList(ui->availableImagesList, availableImages);
}

void HomePage::getMyImages() {



}

void HomePage::editImageSettings() {


}

void HomePage::requestImage() {


}

void HomePage::on_requestImageButton_clicked()
{
//    int index = ui->imagesList->currentIndex().row();
//    QString image_selected = model->stringList().at(index);
//
//    std::string imageName = image_selected.toUtf8().constData();
//
//    Image img = client::getImage(imageName, imageEntries[index].ipAddress);
//
//
//    std::string imageFilePath = "DownloadedImages/" + imageName;
//
//    std::ofstream outfile(imageFilePath , std::ios::out | std::ios::binary);
//
//    outfile.write(img.content, img.length);
//
//    outfile.close();
//
//
//    std::string image_name = image_selected.toUtf8().constData();
//    extractViews(image_name);
//
//    std::string username;
//
//    std::string path_to_list = image_name + ".txt";
//
//    ifstream file;
//    file.open(path_to_list.c_str());
///
//    if(file.fail())
//        printf("Opening list of view failed: %s\n", image_name.c_str());
//    else
//    {
//        while(!file.eof())
//        {
//            file >> username >> views_num;
//
//            if (username == MyUsername)
//                break;
//        }
//    }
//

}

void HomePage::on_viewImageButton_clicked()
{
//    int index = ui->imagesList->currentIndex().row();
//    QString image_selected = model->stringList().at(index);
//
//
//    QString path = image_path + image_selected;
//        
//   
//    if(views_num!=0)
//    {
//        QPixmap img;
//        img.load(path);
//
//        ui->Image_holder->setPixmap(img);
//        ui->Image_holder->setScaledContents(true);
//        ui->viewsNumLabel->setText("No. of Views " + QString::number(views_num));
//        views_num--;
//    }
//    else
//    {
//        ui->viewsNumLabel->setText("No. of Views reached 0!!");
//        ui->imageStatusLabel->setText("No Image Requested");
//
//
//
//        ui->Image_holder->setPixmap(img_default);
//    }
}

void HomePage::on_getImagesButton_clicked()
{
//    std::vector<std::string> IPAddresses =  client::getIPAddress();
//
//    printf("IP numbers %d", (int)IPAddresses.size());
//
//    for ( int i =  0; i < (int) (int)IPAddresses.size(); i++)
//    {
//        printf("\nIP ADDRESSES : %s\n", IPAddresses[i].c_str());
//    }
//
//    for (int ip = 0; ip < (int)IPAddresses.size(); ++ip) {
//
//
//        std::vector<std::string> tmp;
//        tmp = client::getAccessibleImages(MyUsername , IPAddresses[ip]);
//
//        for (int i = 0; i < (int)tmp.size(); i++)
//        {
//            imageEntry img;
//            img.imageName = tmp[i];

//            img.ipAddress = IPAddresses[ip];
//
//            imageEntries.push_back(img);
//        }
//    }
//

//
//    model = new QStringListModel(this);
//    
//    QStringList List;
//    // printf("got %d images\n", (int)imageEntries.size());
//    for(int i = 0; i < (int)imageEntries.size(); i++)
//        List << imageEntries[i].imageName.c_str();
//
//
//
//    // Populate our model
//    model->setStringList(List);
//    // Glue model and view together
//    ui->imagesList->setModel(model);



    
//    //ls and get images in my directory
//
//    std::vector<std::string> myImages = homepage::listFilesInDir();
//
//    model_my_images = new QStringListModel(this);
//    QStringList List2;
//
//    for (int i = 0; i < (int)myImages.size(); i++)
//        List2 << myImages[i].c_str();
//
//
//    // Populate our model
//    model_my_images->setStringList(List2);
//    // Glue model and view together
//    ui->my_images->setModel(model_my_images);
//
//

}


void HomePage::on_update_views_clicked()
{
//    QString username_to_update = ui->usernameToUpdateEdit->text();
//    QString views_to_update = ui->viewsToUpdateEdit->text();
//
////    int index = ui->my_images->currentIndex().row();
//    QString image_selected = model_my_images->stringList().at(index);
//    QString path = image_path + image_selected;
//
//    std::string usernameToUpdate = username_to_update.toUtf8().constData();
//    std::string viewsString = views_to_update.toUtf8().constData();
//
//    int viewsToUpdate = atoi(viewsString.c_str());
//
//
//    std::string imageName = image_selected.toUtf8().constData();
//    
//    // WARNING unused variable
//    bool updated = client::updateCount(imageName, usernameToUpdate, viewsToUpdate);
//
//    //callRPC
//
//
//
//    
    
}

void HomePage::setUsername(std::string username)
{
    this->myUsername = username;
}

void HomePage::extractViews(std::string imageName)
{
//    std::string exec_command = "steghide extract -sf DownloadedImages/" + imageName;
//    exec_command += " -p root -f";
//
//    system(exec_command.c_str());
}

std::vector<std::string> homepage::splitString(std::string sentence)
{
  std::stringstream ss;
  ss<<sentence;

  std::string to;
  std::vector<std::string> files;

    while(std::getline(ss,to,'\n')){
        files.push_back(to);
    }


    return files;
}

std::vector<std::string> homepage::listFilesInDir(const std:string& folderName)
{
    using namespace std;
    std::string command = "ls " + foder
    FILE  *file = popen("ls MyImages/", "r");

    int ch;
    string result;

    do{
        ch = fgetc(file);

        if(ch == EOF) {
            break;
        }

        result += ch;

    }while(1);

    pclose(file);

    return homepage::splitString(result);
}

void HomePage::setEditEntriesVisible(const bool & visible) {

    ui->usernameEdit->setVisible(visible);
    ui->updateEditsButton->setVisible(visible);
    ui->viewCountEdit->setVisible(visible);
    ui->viewCountLabel->setVisible(visible);
    ui->addUsernameLabel->setVisible(visible);

}

void HomePage::showImagesInList(QListView * listView, const std::vector<ImageEntry> & images) {

    QStandardItemModel * model = new QStandardItemModel(images.size(), 1, this);

    for (int i = 0; i < images.size(); i++) {

        QString imageName = QString::fromStdString(images[i].imageName);

        QStandardItem * standardItem = new QStandardItem(imageName);

        model->setItem(i, 0, standardItem);
    }

    listView->setModel(model);
}