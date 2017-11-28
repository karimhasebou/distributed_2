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
    QVBoxLayout *verticalLayout_3;
    QLabel *imagePreview;
    QLabel *countRemaining;
    QVBoxLayout *verticalLayout_2;
    QListWidget *myImagesList;
    QListWidget *availableImagesList;
    QPushButton *refreshButton;
    QGridLayout *editImageEntries;
    QLineEdit *usernameEdit;
    QLabel *viewCountLabel;
    QLabel *addUsernameLabel;
    QLineEdit *viewCountEdit;
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
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        imagePreview = new QLabel(verticalLayoutWidget);
        imagePreview->setObjectName(QStringLiteral("imagePreview"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imagePreview->sizePolicy().hasHeightForWidth());
        imagePreview->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(imagePreview);

        countRemaining = new QLabel(verticalLayoutWidget);
        countRemaining->setObjectName(QStringLiteral("countRemaining"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(countRemaining->sizePolicy().hasHeightForWidth());
        countRemaining->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(countRemaining);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        myImagesList = new QListWidget(verticalLayoutWidget);
        myImagesList->setObjectName(QStringLiteral("myImagesList"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(myImagesList->sizePolicy().hasHeightForWidth());
        myImagesList->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(myImagesList);

        availableImagesList = new QListWidget(verticalLayoutWidget);
        availableImagesList->setObjectName(QStringLiteral("availableImagesList"));
        sizePolicy3.setHeightForWidth(availableImagesList->sizePolicy().hasHeightForWidth());
        availableImagesList->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(availableImagesList);

        refreshButton = new QPushButton(verticalLayoutWidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));

        verticalLayout_2->addWidget(refreshButton);


        horizontalLayout_2->addLayout(verticalLayout_2);

        editImageEntries = new QGridLayout();
        editImageEntries->setObjectName(QStringLiteral("editImageEntries"));
        usernameEdit = new QLineEdit(verticalLayoutWidget);
        usernameEdit->setObjectName(QStringLiteral("usernameEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(usernameEdit->sizePolicy().hasHeightForWidth());
        usernameEdit->setSizePolicy(sizePolicy4);

        editImageEntries->addWidget(usernameEdit, 0, 1, 1, 1);

        viewCountLabel = new QLabel(verticalLayoutWidget);
        viewCountLabel->setObjectName(QStringLiteral("viewCountLabel"));

        editImageEntries->addWidget(viewCountLabel, 1, 0, 1, 1);

        addUsernameLabel = new QLabel(verticalLayoutWidget);
        addUsernameLabel->setObjectName(QStringLiteral("addUsernameLabel"));

        editImageEntries->addWidget(addUsernameLabel, 0, 0, 1, 1);

        viewCountEdit = new QLineEdit(verticalLayoutWidget);
        viewCountEdit->setObjectName(QStringLiteral("viewCountEdit"));
        sizePolicy4.setHeightForWidth(viewCountEdit->sizePolicy().hasHeightForWidth());
        viewCountEdit->setSizePolicy(sizePolicy4);

        editImageEntries->addWidget(viewCountEdit, 1, 1, 1, 1);

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
        imagePreview->setText(QApplication::translate("HomePage", "TextLabel", Q_NULLPTR));
        countRemaining->setText(QString());
        refreshButton->setText(QApplication::translate("HomePage", "Refresh", Q_NULLPTR));
        viewCountLabel->setText(QApplication::translate("HomePage", "Views Count", Q_NULLPTR));
        addUsernameLabel->setText(QApplication::translate("HomePage", "Add username", Q_NULLPTR));
        updateEditsButton->setText(QApplication::translate("HomePage", "Update", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HomePage: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
