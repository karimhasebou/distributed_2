#include "RPC.h"


Image getImage(string imgName)
{
    Image img;
    imgName = IMG_DIR + imgName;

    // test purposes
    imgName = "/home/omar_nawawy/Desktop/sad.png";
    //
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


vector<string> listImages()
{
    vector<string> imageList;

    ifstream file(IMG_LIST_FILE, ios::in);
    bool eof = false;

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

void unstegUserList(string filePath)
{
    
    string exec_command = "/usr/bin/steghide extract -sf ";
    exec_command += filePath + " -p root";

    FILE *exec_steghide = popen(exec_command.c_str(), "w");
    pclose(exec_steghide);
}

set<string> getAuthorizedUsers(string filePath)
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

vector<string> getAccessibleImages(string username)
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

bool canUpdateCount(string imgName, string username)
{
    return true; // xp
}

string getPath(string imgName)
{
    string currDir;
    return currDir + imgName;
}

bool updateCount(string imgName, string username, int count)
{
    unstegUserList(getPath(imgName));
    // getAuthorizedUsers(imgName); // use it for its side effect,
    // // which is extracting the secret file from the img
    map<string, int> countList = readAuthorizedUsersDB();
    countList[username] = count;
    // write db
    writeDB(countList);
    return true; // xp
}

map<string, int> readAuthorizedUsersDB()
{
    map<string, int> list;

    ifstream file(IMG_LIST_FILE, ios::in);
    bool eof = false;

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

void writeDB(map<string, int> list)
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