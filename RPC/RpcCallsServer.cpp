//
//  RpcCallsServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"

#define IMG_DIR 
#define IMG_LIST_FILE "/run/media/karim/345858115857CFEA/AUC/FALL17/DIST-CSCE441102/test/distributed_2/MyImages/images.txt"
#define AUTHORIZED_USERS ""

using namespace std;

vector<string> listImages();
set<string> getAuthorizedUsers(const string&);
map<string, int> getAuthorizedUsersCount();
void updateCountInImage(map<string, int>);
void stegUserList(const string&);
void unstegUserList(const string&);

const string currentDir = "/run/media/karim/345858115857CFEA/AUC/FALL17/DIST-CSCE441102/test/distributed_2/MyImages";

Image server::getImage(string imageName)
{
    Image image;
    imageName = currentDir + imageName;
    ifstream imagefile(imageName, ios::in | ios::binary | ios::ate);
    debug_print("reading image (%s)\n", imageName.c_str());

    if(imagefile.is_open()) {
        image.length = imagefile.tellg();
        imagefile.seekg(0, imagefile.beg) ;
        image.content = new char[image.length];
        imagefile.read(image.content, image.length);
        imagefile.close();
	debug_print("done! (%s)\n", imageName.c_str());
    }
    else {
        image.content = NULL;
	debug_print("failed to read image %s\n", imageName.c_str());
        image.length = -1;
    }
    return image;
}


vector<string> listImages()
{
    vector<string> imageList;
    ifstream imageListfile(IMG_LIST_FILE, ios::in);      // change
    printf("searching for images\n");
    while(imageListfile.is_open()) {
        string imageName;
        imageListfile>>imageName;
        if(!imageListfile.eof()) {
            imageList.push_back(imageName);
	    printf("image .. %s", imageName.c_str());
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
    exec_command += imagename +" -ef "+ imagename + AUTHORIZED_USERS + ".txt" + " -p root";
    system(exec_command.c_str());
}

void unstegUserList(const string& filePath)
{
    printf("unsteging %s ...\n", filePath.c_str());
    string exec_command = "/usr/bin/steghide extract -sf ";
    exec_command += "MyImages/" + filePath +  " -f -p root";
    system(exec_command.c_str());
    printf("unsetg: done getting list\n");
}

set<string> getAuthorizedUsers(const string& filePath)
{
    set<string> usersList;
    int userViewCount;
    
    unstegUserList(filePath);

    printf("openning list in txt file %s \n", string(filePath + AUTHORIZED_USERS + ".txt").c_str());
    ifstream usernamesFile(string(filePath + AUTHORIZED_USERS + ".txt").c_str()
        , ios::in);

    while(usernamesFile.is_open()){
        
        string username;
        usernamesFile>>username;
        usernamesFile>>userViewCount;   // skip user image count
        printf("name: %s\n", username.c_str());

        if(!usernamesFile.eof()) {
            usersList.insert(username);
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
    printf("getting images for %s\n", username.c_str());
    for(string& image : listImages()){
        set<string> imageUsers = getAuthorizedUsers(image);
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

