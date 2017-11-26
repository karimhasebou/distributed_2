//
//  RpcCallsServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"


using namespace std;

vector<string> listImages();
set<string> getAuthorizedUsers(const string&);
map<string, int> getAuthorizedUsersCount();
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

void stegUserList(const string& imagePath, const string coverPath)
{
    string exec_command = "/usr/bin/steghide embed -cf ";
    exec_command += imagePath + " -ef "+ coverPath + " -p root";
    system(exec_command.c_str());
}

void unstegUserList(const string& filePath)
{
    string exec_command = "/usr/bin/steghide extract -sf ";
    exec_command +=  filePath + " -p root -f";
    system(exec_command.c_str());
}

set<string> getAuthorizedUsers(const string& filePath)
{
    set<string> usersList;
    int userViewCount;
    
    unstegUserList(currentDir + filePath);

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


bool server::updateCount(string imgName, string username, int count)
{
    std::string txtPath = imgName + ".txt";
    unstegUserList(downDir + imgName);

    map<string, int> countList = getAuthorizedUsersCount();
    countList[username] = count;

    updateCountInMap(countList, txtPath);
    stegUserList(downDir + imgName, txtPath);
    return true;
}

map<string, int> getAuthorizedUsersCount(std::string imageName)
{
    map<string, int> list;

    // ifstream imageListFile(IMG_LIST_FILE, ios::in);

    // while(imageListFile.is_open()) {
        
    //     string username;
    //     int viewCount;
        
    //     imageListFile>>username;
    //     imageListFile>>viewCount;

    //     if(!imageListFile.eof()) {
            
    //         list[username] = viewCount;
    //     }
    //     else {
            
    //         imageListFile.close();
    //     }
    // }

    return list;
}

void updateCountInMap(map<string, int> list, std::string path)
{
    ofstream imageListFile(path, ios::out);
    
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

