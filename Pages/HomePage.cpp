#include "HomePage.h"
#include "../ui_HomePage.h"
#include "../RPC/RpcCalls.h"
#include "../RequestHandler.h"
#include "../RPC/RpcStub.h"

int views_num = 0;

namespace homepage {
std::vector<std::string> splitString(std::string sentence);
std::vector<std::string> listFilesInDir();
};

struct imageEntry {
    std::string imageName;
    std::string ipAddress;
};

std::vector<imageEntry> imageEntries;


HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    image_path = "DownloadedImages/";
    
    img_default.load("MyImages/default.jpg");
    
    ui->Image_holder->setPixmap(img_default);
    ui->Image_holder->setScaledContents(true);

   

}

HomePage::~HomePage()
{
    delete ui;
}

//remove this
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
    

    std::string imageFilePath = "DownloadedImages/" + imageName;
    
    std::ofstream outfile(imageFilePath , std::ios::out | std::ios::binary);

    outfile.write(img.content, img.length);
    
    outfile.close();


    std:string image_name = image_selected.toUtf8().constData();  
    extractViews(image_name);

  //  std::ofstream outfile(imageFilePath , std::ofstream::binary);
    
   // outfile.write(img.content, img.length);
    // printf("length of image %s" , img.length);
    // outfile.write(img.content, img.length);

    std::string username; 
    
    std::string path_to_list = image_name + ".txt";
    
    ifstream file;
    file.open(path_to_list.c_str());
    
    if(file.fail())
        printf("Opening list of view failed: %s\n", image_name);
    else
    {
        while(!file.eof())
        {
            file >> username >> views_num;

            if (username == MyUsername)
                break;
        }
    }

    ui->imageStatusLabel->setText("Image Available");    
    
}

void HomePage::on_viewImageButton_clicked()
{
    int index = ui->imagesList->currentIndex().row();
    QString image_selected = model->stringList().at(index);
    QString path = image_path + image_selected; 
        
   
    if(views_num!=0)
    {
        QPixmap img;
        img.load(path);

        ui->Image_holder->setPixmap(img);
        ui->Image_holder->setScaledContents(true);
        ui->viewsNumLabel->setText("No. of Views " + QString::number(views_num));
        views_num--;
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

    for ( int i =  0; i < (int) IPAddresses.size(); i++)
    {
        printf("\nIP ADDRESSES : %s\n", IPAddresses[i].c_str());
    }

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
    // printf("got %d images\n", (int)imageEntries.size());
    for(int i = 0; i < (int)imageEntries.size(); i++)
        List << imageEntries[i].imageName.c_str();

    
    // Populate our model
    model->setStringList(List);
    // Glue model and view together
    ui->imagesList->setModel(model);
    
    
    //ls and get images in my directory

    std::vector<std::string> myImages = homepage::listFilesInDir();

    model_my_images = new QStringListModel(this);
    QStringList List2;

    for (int i = 0; i < (int)myImages.size(); i++)
        List2 << myImages[i].c_str();
        
    // Populate our model
    model_my_images->setStringList(List2);
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

    std::string usernameToUpdate = username_to_update.toUtf8().constData(); 
    std::string viewsString = views_to_update.toUtf8().constData();

    int viewsToUpdate = atoi(viewsString.c_str());

    std::string imageName = image_selected.toUtf8().constData(); 
    
    
    bool updated = client::updateCount(imageName, usernameToUpdate, viewsToUpdate);

    //callRPC
    
    
    
}

void HomePage::setUsername(std::string username)
{
    this->MyUsername = username;
}

void HomePage::extractViews(std::string imageName)
{
    std::string exec_command = "steghide extract -sf DownloadedImages/" + imageName;
    exec_command += " -p root -f";

    system(exec_command.c_str());
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

std::vector<std::string> homepage::listFilesInDir()
{
    using namespace std;
    FILE  *file = popen("ls MyImages/", "r");
    
    int ch;
    string result;
    
    do{
        ch = fgetc(file);
        
        if(ch == EOF) break;
        
        result += ch;
    }while(1);

    pclose(file);

    return homepage::splitString(result);
}
