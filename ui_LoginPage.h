/********************************************************************************
** Form generated from reading UI file 'LoginPage.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLineEdit *usernameInputEdit;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLineEdit *passwordInputEdit;
    QSpacerItem *verticalSpacer_3;
    QPushButton *signInButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName(QStringLiteral("LoginPage"));
        LoginPage->resize(800, 600);
        centralwidget = new QWidget(LoginPage);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(160, 130, 421, 351));
        formLayout = new QFormLayout(gridLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(20);
        formLayout->setVerticalSpacing(20);
        formLayout->setContentsMargins(20, 20, 20, 20);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::SpanningRole, label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::SpanningRole, verticalSpacer);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        usernameInputEdit = new QLineEdit(gridLayoutWidget);
        usernameInputEdit->setObjectName(QStringLiteral("usernameInputEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, usernameInputEdit);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::SpanningRole, verticalSpacer_2);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_3);

        passwordInputEdit = new QLineEdit(gridLayoutWidget);
        passwordInputEdit->setObjectName(QStringLiteral("passwordInputEdit"));
        passwordInputEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(6, QFormLayout::FieldRole, passwordInputEdit);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(8, QFormLayout::SpanningRole, verticalSpacer_3);

        signInButton = new QPushButton(gridLayoutWidget);
        signInButton->setObjectName(QStringLiteral("signInButton"));

        formLayout->setWidget(9, QFormLayout::SpanningRole, signInButton);

        LoginPage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginPage);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        LoginPage->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginPage);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoginPage->setStatusBar(statusbar);

        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QMainWindow *LoginPage)
    {
        LoginPage->setWindowTitle(QApplication::translate("LoginPage", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("LoginPage", "Welcome", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginPage", "Username :", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginPage", "Password : ", Q_NULLPTR));
        passwordInputEdit->setText(QString());
        signInButton->setText(QApplication::translate("LoginPage", "Sign In", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
