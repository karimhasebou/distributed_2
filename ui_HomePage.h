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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *allImagesButton;
    QPushButton *myImagesButton;
    QPushButton *editImageButton;
    QPushButton *requestImageButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *imageView;
    QListWidget *imagesList;
    QGridLayout *editImageEntries;
    QLineEdit *usernameLabel;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *viewCountLabel;
    QPushButton *updateEditsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HomePage)
    {
        if (HomePage->objectName().isEmpty())
            HomePage->setObjectName(QStringLiteral("HomePage"));
        HomePage->resize(800, 600);
        centralwidget = new QWidget(HomePage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 781, 541));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        allImagesButton = new QPushButton(verticalLayoutWidget);
        allImagesButton->setObjectName(QStringLiteral("allImagesButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(allImagesButton->sizePolicy().hasHeightForWidth());
        allImagesButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(allImagesButton);

        myImagesButton = new QPushButton(verticalLayoutWidget);
        myImagesButton->setObjectName(QStringLiteral("myImagesButton"));
        sizePolicy.setHeightForWidth(myImagesButton->sizePolicy().hasHeightForWidth());
        myImagesButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(myImagesButton);

        editImageButton = new QPushButton(verticalLayoutWidget);
        editImageButton->setObjectName(QStringLiteral("editImageButton"));
        sizePolicy.setHeightForWidth(editImageButton->sizePolicy().hasHeightForWidth());
        editImageButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(editImageButton);

        requestImageButton = new QPushButton(verticalLayoutWidget);
        requestImageButton->setObjectName(QStringLiteral("requestImageButton"));

        horizontalLayout->addWidget(requestImageButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        imageView = new QLabel(verticalLayoutWidget);
        imageView->setObjectName(QStringLiteral("imageView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageView->sizePolicy().hasHeightForWidth());
        imageView->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(imageView);

        imagesList = new QListWidget(verticalLayoutWidget);
        imagesList->setObjectName(QStringLiteral("imagesList"));
        sizePolicy1.setHeightForWidth(imagesList->sizePolicy().hasHeightForWidth());
        imagesList->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(imagesList);

        editImageEntries = new QGridLayout();
        editImageEntries->setObjectName(QStringLiteral("editImageEntries"));
        usernameLabel = new QLineEdit(verticalLayoutWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy2);

        editImageEntries->addWidget(usernameLabel, 0, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        editImageEntries->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        editImageEntries->addWidget(label_2, 0, 0, 1, 1);

        viewCountLabel = new QLineEdit(verticalLayoutWidget);
        viewCountLabel->setObjectName(QStringLiteral("viewCountLabel"));
        sizePolicy2.setHeightForWidth(viewCountLabel->sizePolicy().hasHeightForWidth());
        viewCountLabel->setSizePolicy(sizePolicy2);

        editImageEntries->addWidget(viewCountLabel, 1, 1, 1, 1);

        updateEditsButton = new QPushButton(verticalLayoutWidget);
        updateEditsButton->setObjectName(QStringLiteral("updateEditsButton"));

        editImageEntries->addWidget(updateEditsButton, 2, 0, 1, 2);


        horizontalLayout_2->addLayout(editImageEntries);


        verticalLayout->addLayout(horizontalLayout_2);

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
        HomePage->setWindowTitle(QApplication::translate("HomePage", "HomePage", Q_NULLPTR));
        allImagesButton->setText(QApplication::translate("HomePage", "All Images", Q_NULLPTR));
        myImagesButton->setText(QApplication::translate("HomePage", "My Images", Q_NULLPTR));
        editImageButton->setText(QApplication::translate("HomePage", "Edit Image", Q_NULLPTR));
        requestImageButton->setText(QApplication::translate("HomePage", "Request Image", Q_NULLPTR));
        imageView->setText(QString());
        label_3->setText(QApplication::translate("HomePage", "Views Count", Q_NULLPTR));
        label_2->setText(QApplication::translate("HomePage", "Add username", Q_NULLPTR));
        updateEditsButton->setText(QApplication::translate("HomePage", "Update", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
