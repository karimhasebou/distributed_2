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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QWidget *centralWidget;
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
    QSpacerItem *verticalSpacer_4;
    QPushButton *signInButton;
    QPushButton *signUpButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName(QStringLiteral("LoginPage"));
        LoginPage->resize(393, 429);
        centralWidget = new QWidget(LoginPage);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 371, 358));
        formLayout = new QFormLayout(gridLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(20);
        formLayout->setVerticalSpacing(20);
        formLayout->setContentsMargins(20, 20, 20, 20);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(1, QFormLayout::SpanningRole, label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::SpanningRole, verticalSpacer);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        usernameInputEdit = new QLineEdit(gridLayoutWidget);
        usernameInputEdit->setObjectName(QStringLiteral("usernameInputEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, usernameInputEdit);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(6, QFormLayout::SpanningRole, verticalSpacer_2);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_3);

        passwordInputEdit = new QLineEdit(gridLayoutWidget);
        passwordInputEdit->setObjectName(QStringLiteral("passwordInputEdit"));
        passwordInputEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(7, QFormLayout::FieldRole, passwordInputEdit);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(9, QFormLayout::SpanningRole, verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::SpanningRole, verticalSpacer_4);

        signInButton = new QPushButton(gridLayoutWidget);
        signInButton->setObjectName(QStringLiteral("signInButton"));

        formLayout->setWidget(10, QFormLayout::SpanningRole, signInButton);

        signUpButton = new QPushButton(gridLayoutWidget);
        signUpButton->setObjectName(QStringLiteral("signUpButton"));

        formLayout->setWidget(11, QFormLayout::SpanningRole, signUpButton);

        LoginPage->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginPage);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 393, 22));
        LoginPage->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoginPage);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LoginPage->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoginPage);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LoginPage->setStatusBar(statusBar);

        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QMainWindow *LoginPage)
    {
        LoginPage->setWindowTitle(QApplication::translate("LoginPage", "LoginPage", Q_NULLPTR));
        label->setText(QApplication::translate("LoginPage", "R ^ 2", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginPage", "Username :", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginPage", "Password : ", Q_NULLPTR));
        passwordInputEdit->setText(QString());
        signInButton->setText(QApplication::translate("LoginPage", "Sign In", Q_NULLPTR));
        signUpButton->setText(QApplication::translate("LoginPage", "Sign Up", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
