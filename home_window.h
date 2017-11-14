#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H


#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

namespace Ui {
class home_window;
}

class home_window : public QDialog
{
    Q_OBJECT

public:
    explicit home_window(QWidget *parent = 0);
    ~home_window();

private slots:
    void on_getImages_clicked();

    void on_request_image_clicked();

    void on_view_image_clicked();

private:
    Ui::home_window *ui;
    QStringListModel *model;
    QPixmap img_default;
    QString image_path;
};

#endif // HOME_WINDOW_H
