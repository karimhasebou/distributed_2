//
//  RpcCallsServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"
#include "../Stegnography/StegManager.h"

using namespace std;

vector<string> listImages();
set<string> getAuthorizedUsers(const string&);
map<string, int> getAuthorizedUsersCount(const string);
void updateCountInMap(map<string, int>, std::string);
void stegUserList(const string&);
void unstegUserList(const string&);
std::vector<std::string> listFilesInDir();
std::vector<std::string> splitString(std::string sentence);

std::vector<std::string> listFilesInDir();
std::vector<std::string> splitString(std::string);


const string currentDir = "MyImages/";
const string downDir = "DownloadedImages/";

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

    // ifstream imageListfile(IMG_LIST_FILE, ios::in);      // change

    // while(imageListfile.is_open()) {
        
    //     string imageName;
    //     imageListfile>>imageName;

    //     if(!imageListfile.eof()) {
            
    //         imageList.push_back(imageName);
            
    //     }
    //     else {
            
    //         imageListfile.close();
    //     }
    // }

    return imageList;
}


set<string> getAuthorizedUsers(const string& filePath)
{
    set<string> usersList;
    int userViewCount;
    
    // unstegUserList(currentDir + filePath);
    stego::unstegPicture(currentDir + filePath);

    ifstream usernamesFile(string(filePath + ".txt").c_str()
        , ios::in);

    while(usernamesFile.is_open()){
        
        string username;
        usernamesFile>>username;
        usernamesFile>>userViewCount;   // skip user image count
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

    for(string& image : listFilesInDir()){
        printf("extracting image %s\n", image.c_str());
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

/*
 * TO BE CHANGED TO MATCH NEW STEGNOGRAPHY SCHEME
 */
bool server::updateCount(string imgName, string username, int count)
{
    std::string txtPath = imgName + ".txt";
    // unstegUserList(downDir + imgName);
    stego::unstegPicture(downDir + imgName);


    map<string, int> countList = stego::getAuthorizedUsersCount(txtPath);
    countList[username] = count;

    stego::updateCountInMap(countList, txtPath);
    // stegUserList(downDir + imgName, txtPath);
    stego::stegPicture(downDir + imgName, txtPath);
    return true;
}

map<string, int> getAuthorizedUsersCount(std::string path)
{
    map<string, int> list;

    ifstream imageListFile(path, ios::in);

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

void updateCountInMap(map<string, int> list, std::string path)
{
    ofstream imageListFile(path, ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }

        imageListFile.close();
    }
}

std::string server::pingUser()    //change
{
        return "s";
}

std::vector<std::string> splitString(std::string sentence)
{
  std::stringstream ss;
  ss<<sentence;
  
  std::string to;
  std::vector<std::string> files;

    while(std::getline(ss,to,'\n')){
        files.push_back(to);
    }
    
    return files;
}

std::vector<std::string> listFilesInDir()
{
    using namespace std;
    FILE  *file = popen("ls MyImages", "r");
    
    int ch;
    string result;
    
    do{
        ch = fgetc(file);
        if(ch == EOF) break;
        
        result += ch;
        
    }while(1);

    pclose(file);

    return splitString(result);
}

