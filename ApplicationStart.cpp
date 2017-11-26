//
//  ApplicationStart.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/24/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include <QApplication>
#include "Pages/LoginPage.h"
#include <chrono>
#include "RPC/RpcStub.h"
#include "RequestHandler.h"



int main(int argc, char *argv[])
{
    using namespace std::chrono;
    
    addRequestHandler(4, getAccessibleImages);
    addRequestHandler(5, getImage);
    
    initRequestHandler(64000);

    QApplication application(argc, argv);
    LoginPage loginPage;
    
    loginPage.show();
    return application.exec();
}

