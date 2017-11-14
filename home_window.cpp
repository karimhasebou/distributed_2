#include "home_window.h"
#include "ui_home_window.h"

int views = 5;

home_window::home_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);

    image_path = "/home/nawawy/Distributed_2/images/";

    img_default.load(image_path+"default.jpg");

    ui->image_holder->setPixmap(img_default);
    ui->image_holder->setScaledContents(true);


}

home_window::~home_window()
{
    delete ui;
}

void home_window::on_getImages_clicked()
{

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

    //request image from peer

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
