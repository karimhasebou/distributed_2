//
//  RpcCallsServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include <stdio.h>
#include "RpcCalls.h"

using namespace std;

string server::getLoggedUsername()
{
    return ""; // tmp
}

server::Image server::getImage(string imgName)
{
    server::Image img;
    imgName = IMG_DIR + imgName;

    // test purposes

    imgName = "/Users/faridaeid/Desktop/Desktop/Project Files/GitHub/distributed_2/circle.png";

    ifstream file(imgName, ios::in | ios::binary | ios::ate);

    if(file.is_open()){
        img.length = file.tellg();
        file.seekg(0, file.beg) ;

        img.content = new char[img.length];
        file.read(img.content, img.length);
        file.close();
    }else{
        img.content = NULL;
        img.length = -1;
    }

    ofstream fileCpy(imgName + "copy", ios::out | ios::binary);
    fileCpy.write(img.content, img.length);
    fileCpy.close();

    return img;
}


vector<string> server::listImages()
{
    vector<string> imageList;

    ifstream file(IMG_LIST_FILE, ios::in);
    //bool eof = false;

    while(file.is_open()) {
        string img;
        file>>img;

        if(!file.eof()) {
            imageList.push_back(img);
        }
        else {
            file.close();
        }
    }

    return imageList;
}

void server::stegUserList(string imagename)
{
    string exec_command = "/usr/bin/steghide embed -cf ";
    exec_command += imagename +" -ef "+AUTHORIZED_USERS+" -p root";

    system(exec_command.c_str());
}

void server::unstegUserList(string filePath)
{
    string exec_command = "/usr/bin/steghide extract -sf ";
    exec_command += filePath + " -p root";

    system(exec_command.c_str());
}

set<string> server::getAuthorizedUsers(string filePath)
{
    set<string> usersList;
    unstegUserList(filePath);

    ifstream file(AUTHORIZED_USERS, ios::in);

    while(file.is_open()){
        string username;
        file>>username;

        if(!file.eof()) {
            usersList.insert(username);
            file>>username; // skip user image count
        }
        else {
            file.close();
        }
    }

    return usersList;
}

vector<string> server::getAccessibleImages(string username)
{
    vector<string> imageList;

    for(string& image : listImages()){
        set<string> imageUsers = getAuthorizedUsers(username);
        
        if(imageUsers.count(username)){
            imageList.push_back(image);
        }
    }

    return imageList;
}

bool server::canUpdateCount(string imgName, string username)
{
    return true; // xp
}

string server::getPath(string imgName)
{
    string currDir;
    return currDir + imgName;
}

bool server::updateCount(string imgName, string username, int count)
{
    unstegUserList(getPath(imgName));
    // getAuthorizedUsers(imgName); // use it for its side effect,
    // // which is extracting the secret file from the img
    map<string, int> countList = readAuthorizedUsersDB();
    countList[username] = count;
    // write db
    writeDB(countList);

    stegUserList(imgName);
    
    return true; // xp
}

map<string, int> server::readAuthorizedUsersDB()
{
    map<string, int> list;

    ifstream file(IMG_LIST_FILE, ios::in);

    while(file.is_open()) {
        string username;
        int viewCount;
        
        file>>username;
        file>>viewCount;

        if(!file.eof()) {
            list[username] = viewCount;
        }
        else {
            file.close();
        }
    }

    return list;
}

void server::writeDB(map<string, int> list)
{
    ofstream file(IMG_LIST_FILE, ios::out);
    
    if(file.is_open()){
        for(auto& entry : list){
            file<<entry.first<<" "<<entry.second<<endl;
        }

        long pos = file.tellp();
        if(pos > 0){
            file.seekp(pos - 1);
            file.put(EOF);
        }

        file.close();
    }
}

