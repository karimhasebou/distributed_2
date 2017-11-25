#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"

int views = 5; //global for now


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
    
    //
    
    //request image from peer
    
    
    //
    
    //download image locally
    
    
    //Acknowledge that image is available
    
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

   // std::string username =  client::getUsername("10.40.48.60");
    
  //  printf("Found Username: %s ", username.c_str());

    
    /*
     vector<pair<int, std::string>> getImagesList()
     {
     for(int i = 0; i < ip_addresses.size(); i++)
     {
     //MessageType = request
     
     //id = 2
     
     //msg = marshall(Messagetype, id)
     
     //sendto msg to ipaddresses[i]
     
     //recvfrom server msg
     
     //vector = unmarshall(msg)
     
     
     //Loop over vector
     //makepair<i, vector[iter]>
     }
     
     }
     */
    
    
    model = new QStringListModel(this);
    QStringList List;
    
    List << "nawawy.jpg" << "farida.jpg" << "karim.jpg";
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
