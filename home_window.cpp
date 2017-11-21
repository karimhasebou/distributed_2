#include "home_window.h"
#include "ui_home_window.h"

int views = 5;

home_window::home_window(QWidget *parent, const std::vector<std::string>& ips) :
    QDialog(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);

    image_path = "/home/nawawy/Distributed_2/images/";

    img_default.load(image_path+"default.jpg");

    ui->image_holder->setPixmap(img_default);
    ui->image_holder->setScaledContents(true);

    ip_addresses = ips;


}

home_window::~home_window()
{
    delete ui;
}

void home_window::on_getImages_clicked()
{

    /*

    std::vector<std::string> get_connected_peers()
    {

        //Messagetype = request
        //id = 1

        //msg = marshall(Messagetype, id)

        //sendto msg server

        //rcvfrom server the vector of connected peers

        //unmarshal recieved msg

        return vector
    }

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
    ui->all_images->setModel(model);


}

void home_window::on_request_image_clicked()
{
    int index = ui->all_images->currentIndex().row();


    QString image_selected = model->stringList().at(index);

    //

    //request image from peer


    //

    //download image locally

    image_path += image_selected;

    //Acknowledge that image is available

    ui->status->setText("Image Available");

}

void home_window::on_view_image_clicked()
{
    if(views!=0)
    {
        QPixmap img;
        img.load(image_path);
        ui->image_holder->setPixmap(img);
        ui->image_holder->setScaledContents(true);
        ui->views_num->setText("No. of Views " + QString::number(views));
        views--;

    }
    else
    {
        ui->views_num->setText("No. of Views reached 0!!");
        ui->status->setText("No Image Requested");

        ui->image_holder->setPixmap(img_default);


    }
}
