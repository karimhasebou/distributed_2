//
//  RpcCallsServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"

#define IMG_DIR ""
#define IMG_LIST_FILE ""
#define AUTHORIZED_USERS ""

using namespace std;

vector<string> listImages();
set<string> getAuthorizedUsers(const string&);
map<string, int> getAuthorizedUsersCount();
void updateCountInImage(map<string, int>);
void stegUserList(const string&);
void unstegUserList(const string&);

const string currentDir = "";

Image server::getImage(string imageName)
{
    Image image;
    imageName = currentDir + imageName;

//    imgName = "/Users/faridaeid/Desktop/Desktop/Project Files/GitHub/distributed_2/circle.png";

    ifstream imagefile(imageName, ios::in | ios::binary | ios::ate);

    if(imagefile.is_open()) {
        
        image.length = imagefile.tellg();
        imagefile.seekg(0, imagefile.beg) ;
        image.content = new char[image.length];
        imagefile.read(image.content, image.length);
        imagefile.close();
        
    } else {
        
        image.content = NULL;
        image.length = -1;
        
    }
    
    return image;
}


vector<string> listImages()
{
    vector<string> imageList;

    ifstream imageListfile(IMG_LIST_FILE, ios::in);      // change

    while(imageListfile.is_open()) {
        
        string imageName;
        imageListfile>>imageName;

        if(!imageListfile.eof()) {
            
            imageList.push_back(imageName);
            
        }
        else {
            
            imageListfile.close();
        }
    }

    return imageList;
}

void stegUserList(const string& imagename)
{
    string exec_command = "/usr/bin/steghide embed -cf ";
    exec_command += imagename +" -ef "+AUTHORIZED_USERS+" -p root";
    system(exec_command.c_str());
}

void unstegUserList(const string& filePath)
{
    string exec_command = "/usr/bin/steghide extract -sf ";
    exec_command += filePath + " -p root";
    system(exec_command.c_str());
}

set<string> getAuthorizedUsers(const string& filePath)
{
    set<string> usersList;
    int userViewCount;
    
    unstegUserList(filePath);

    ifstream usernamesFile(AUTHORIZED_USERS, ios::in);

    while(usernamesFile.is_open()){
        
        string username;
        usernamesFile>>username;

        if(!usernamesFile.eof()) {
            
            usersList.insert(username);
            usernamesFile>>username;
            usernamesFile>>userViewCount;   // skip user image count
            
        }
        else {
            
            usernamesFile.close();
        }
    }

    return usersList;
}


vector<string> server::getAccessibleImages(const string& username)
{
    vector<string> imageList;

    for(string& image : listImages()){
        
        set<string> imageUsers = getAuthorizedUsers(username);
        
        if(imageUsers.count(username)) {
            
            imageList.push_back(image);
        }
    }

    return imageList;
}

bool server::canUpdateCount(string imgName, string username)
{
    return true; // ;p
}


bool server::updateCount(string imgName, string username, int count)
{
    unstegUserList(currentDir + imgName);
    // getAuthorizedUsers(imgName); // use it for its side effect,
    // // which is extracting the secret file from the img
    map<string, int> countList = getAuthorizedUsersCount();
    
    countList[username] = count;
    
    updateCountInImage(countList);

    stegUserList(imgName);
    
    return true;
}

map<string, int> getAuthorizedUsersCount()
{
    map<string, int> list;

    ifstream imageListFile(IMG_LIST_FILE, ios::in);

    while(imageListFile.is_open()) {
        
        string username;
        int viewCount;
        
        imageListFile>>username;
        imageListFile>>viewCount;

        if(!imageListFile.eof()) {
            
            list[username] = viewCount;
        }
        else {
            
            imageListFile.close();
        }
    }

    return list;
}

void updateCountInImage(map<string, int> list)
{
    ofstream imageListFile(IMG_LIST_FILE, ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }

        long pos = imageListFile.tellp();
        
        if(pos > 0){
            
            imageListFile.seekp(pos - 1);
            imageListFile.put(EOF);
        }

        imageListFile.close();
    }
}

std::string server::pingUser()    //change
{
        return "s";
}

