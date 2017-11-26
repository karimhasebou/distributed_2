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
    // std::this_thread::sleep_for(std::chrono::seconds(300));
    // puts("server shutting down...\n");
    
    // shutdown();
    
    // std::this_thread::sleep_for(std::chrono::seconds(100));
    // puts("server shut down...\n");

    
    return application.exec();
}

