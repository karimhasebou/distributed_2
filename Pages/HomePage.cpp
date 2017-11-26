#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"
#include "../RequestHandler.h"
#include "../RPC/RpcStub.h"

int views = 5; //global for 
std::vector<imageEntry> imageEntries;


struct imageEntry {
    std::string imageName;
    std::string ipAddress;
};


HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    image_path = "../Images/";
    
    img_default.load(image_path+"default.jpg");
    
    ui->Image_holder->setPixmap(img_default);
    ui->Image_holder->setScaledContents(true);

   

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::set_ips(const std::vector<std::string> & ips)
{
    ip_addresses = ips;
}


void HomePage::on_requestImageButton_clicked()
{
    int index = ui->imagesList->currentIndex().row();
    QString image_selected = model->stringList().at(index);
    
    std::string imageName = image_selected.toUtf8().constData();    
    
    Image img = client::getImage(imageName, imageEntries[index].ipAddress);

    std::string imageFilePath = "../DownloadedImages/" + imageName;

    std::ofstream outfile(imageFilePath , std::ofstream::binary);
    
    outfile.write(img.content, img.length);

    
    ui->imageStatusLabel->setText("Image Available");
    
}

void HomePage::on_viewImageButton_clicked()
{
    if(views!=0)
    {
        
        int index = ui->imagesList->currentIndex().row();
        QString image_selected = model->stringList().at(index);
        QString path = image_path + image_selected;
        
        QPixmap img;
        img.load(path);
        ui->Image_holder->setPixmap(img);
        ui->Image_holder->setScaledContents(true);
        ui->viewsNumLabel->setText("No. of Views " + QString::number(views));
        views--;
    }
    else
    {
        ui->viewsNumLabel->setText("No. of Views reached 0!!");
        ui->imageStatusLabel->setText("No Image Requested");
        
        ui->Image_holder->setPixmap(img_default);

    }
}

void HomePage::on_getImagesButton_clicked()
{
    std::vector<std::string> IPAddresses =  client::getIPAddress();

    printf("IP numbers %d", IPAddresses.size());

    for (int ip = 0; ip < (int)IPAddresses.size(); ++ip) {
        
        std::vector<std::string> tmp;
        tmp = client::getAccessibleImages(MyUsername , IPAddresses[ip]);

        for (int i = 0; i < (int) tmp.size(); i++)
        {
            imageEntry img;
            img.imageName = tmp[i]; 
            img.ipAddress = IPAddresses[ip];

            imageEntries.push_back(img);
        }
    }
    

    model = new QStringListModel(this);
    QStringList List;
    printf("got %d images\n", (int)imageEntries.size());
    for(int i = 0; i < (int)imageEntries.size(); i++)
        List << imageEntries[i].imageName.c_str();

    
    // Populate our model
    model->setStringList(List);
    // Glue model and view together
    ui->imagesList->setModel(model);
    
    
    
    model_my_images = new QStringListModel(this);
    QStringList List2;
    List2 << "nawawy.jpg" << "farida.jpg" << "karim.jpg";
    // Populate our model
    model_my_images->setStringList(List);
    // Glue model and view together
    ui->my_images->setModel(model_my_images);
    

}


void HomePage::on_update_views_clicked()
{
    QString username_to_update = ui->usernameToUpdateEdit->text();
    QString views_to_update = ui->viewsToUpdateEdit->text();
    
    int index = ui->my_images->currentIndex().row();
    QString image_selected = model_my_images->stringList().at(index);
    QString path = image_path + image_selected;
    \
    //callRPC
    
    
    
}

void HomePage::setUsername(std::string username)
{
    this->MyUsername = username;
}

