/********************************************************************************
** Form generated from reading UI file 'HomePage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomePage
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *usernameToUpdateEdit;
    QLineEdit *viewsToUpdateEdit;
    QPushButton *update_views;
    QLabel *label_2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *requestImageButton;
    QPushButton *viewImageButton;
    QLabel *imageStatusLabel;
    QLabel *viewsNumLabel;
    QListView *imagesList;
    QPushButton *getImagesButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QListView *my_images;
    QLabel *label;
    QLabel *Image_holder;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName(QStringLiteral("HomePage"));
        HomePage->resize(800, 600);
        centralwidget = new QWidget(HomePage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(590, 10, 192, 218));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        usernameToUpdateEdit = new QLineEdit(gridLayoutWidget_2);
        usernameToUpdateEdit->setObjectName(QStringLiteral("usernameToUpdateEdit"));

        gridLayout_2->addWidget(usernameToUpdateEdit, 0, 1, 1, 1);

        viewsToUpdateEdit = new QLineEdit(gridLayoutWidget_2);
        viewsToUpdateEdit->setObjectName(QStringLiteral("viewsToUpdateEdit"));

        gridLayout_2->addWidget(viewsToUpdateEdit, 1, 1, 1, 1);

        update_views = new QPushButton(gridLayoutWidget_2);
        update_views->setObjectName(QStringLiteral("update_views"));

        gridLayout_2->addWidget(update_views, 2, 0, 1, 2);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(380, 235, 401, 291));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        requestImageButton = new QPushButton(gridLayoutWidget_3);
        requestImageButton->setObjectName(QStringLiteral("requestImageButton"));

        gridLayout_3->addWidget(requestImageButton, 2, 0, 1, 1);

        viewImageButton = new QPushButton(gridLayoutWidget_3);
        viewImageButton->setObjectName(QStringLiteral("viewImageButton"));

        gridLayout_3->addWidget(viewImageButton, 3, 0, 1, 1);

        imageStatusLabel = new QLabel(gridLayoutWidget_3);
        imageStatusLabel->setObjectName(QStringLiteral("imageStatusLabel"));

        gridLayout_3->addWidget(imageStatusLabel, 2, 1, 1, 1);

        viewsNumLabel = new QLabel(gridLayoutWidget_3);
        viewsNumLabel->setObjectName(QStringLiteral("viewsNumLabel"));

        gridLayout_3->addWidget(viewsNumLabel, 3, 1, 1, 1);

        imagesList = new QListView(gridLayoutWidget_3);
        imagesList->setObjectName(QStringLiteral("imagesList"));

        gridLayout_3->addWidget(imagesList, 1, 0, 1, 2);

        getImagesButton = new QPushButton(gridLayoutWidget_3);
        getImagesButton->setObjectName(QStringLiteral("getImagesButton"));

        gridLayout_3->addWidget(getImagesButton, 0, 0, 1, 2);

        getImagesButton->raise();
        imagesList->raise();
        requestImageButton->raise();
        viewImageButton->raise();
        viewsNumLabel->raise();
        imageStatusLabel->raise();
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(380, 10, 203, 218));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        my_images = new QListView(gridLayoutWidget);
        my_images->setObjectName(QStringLiteral("my_images"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(my_images->sizePolicy().hasHeightForWidth());
        my_images->setSizePolicy(sizePolicy);

        gridLayout->addWidget(my_images, 1, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Image_holder = new QLabel(centralwidget);
        Image_holder->setObjectName(QStringLiteral("Image_holder"));
        Image_holder->setGeometry(QRect(20, 10, 331, 481));
        HomePage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HomePage);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        HomePage->setMenuBar(menubar);
        statusbar = new QStatusBar(HomePage);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        HomePage->setStatusBar(statusbar);

        retranslateUi(HomePage);

        QMetaObject::connectSlotsByName(HomePage);
    } // setupUi

    void retranslateUi(QMainWindow *HomePage)
    {
        HomePage->setWindowTitle(QApplication::translate("HomePage", "MainWindow", Q_NULLPTR));
        label_3->setText(QApplication::translate("HomePage", "Enter Views :", Q_NULLPTR));
        update_views->setText(QApplication::translate("HomePage", "Update", Q_NULLPTR));
        label_2->setText(QApplication::translate("HomePage", "Enter Username:", Q_NULLPTR));
        requestImageButton->setText(QApplication::translate("HomePage", "Request Image", Q_NULLPTR));
        viewImageButton->setText(QApplication::translate("HomePage", "View Image", Q_NULLPTR));
        imageStatusLabel->setText(QApplication::translate("HomePage", "No Image Requested", Q_NULLPTR));
        viewsNumLabel->setText(QApplication::translate("HomePage", "No. of Views", Q_NULLPTR));
        getImagesButton->setText(QApplication::translate("HomePage", "Get Images", Q_NULLPTR));
        label->setText(QApplication::translate("HomePage", "Select One of your Images :", Q_NULLPTR));
        Image_holder->setText(QApplication::translate("HomePage", "Image", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_HomePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
