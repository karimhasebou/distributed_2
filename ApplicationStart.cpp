//
//  ApplicationStart.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/24/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include <QApplication>
#include "Pages/LoginPage.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    LoginPage loginPage;
    
    loginPage.show();
    
    return application.exec();
}

