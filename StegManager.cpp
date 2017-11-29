#include "StegManager.h"
using namespace std;

mutex imgProtect;
std::string DEFAULT = "DEFAULT.jpg";

namespace stego_utils {
    map<string, int> getAuthorizedUsersCount(std::string path);
    string stegHideCmd(string cover, string hide);
    string stegUnhideCmd(string cover);
    int getUserCount(const string& user, const string& img);
    std::map<std::string, int> getAllCount(const std::string&);
    void updateCountInFile(map<string, int> list, std::string path);
}

map<string, int> stego_utils::getAuthorizedUsersCount(std::string path)
{
    map<string, int> list;
    imgProtect.lock();
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
    imgProtect.unlock();
    return list;
}

string stego_utils::stegHideCmd(string cover, string hide)
{
    string cmd = "steghide embed -cf " + cover + " " +
        hide + " -p root";
    return cmd;
}

string stego_utils::stegUnhideCmd(string cover)
{
    string cmd = "steghide extract -sf " + cover + " -p roof -f";
    return cmd;
}

void stego::stegPicture(const string& imgCover, const string& imgHide)
{
    imgProtect.lock();

    std::string cmd = stego_utils::stegHideCmd(imgCover, imgHide);
    system(cmd.c_str());

    imgProtect.unlock();
}

void stego::unstegPicture(const string& img)
{
    imgProtect.lock();

    std::string cmd = stego_utils::stegUnhideCmd(DEFAULT + img);
    system(cmd.c_str());
    cmd = stego_utils::stegUnhideCmd(img);
    system(cmd.c_str());

    imgProtect.unlock();
}

int stego::getUserCount(const string& user, const string& img)
{
    int count = -1;
    std::map<std::string, int> allCount = stego_utils::getAuthorizedUsersCount(img);

    if (allCount.count(user) > 0)
        count = allCount[user];

    return count;   
}

std::map<std::string, int> stego_utils::getAllCount(const std::string& img)
{
    std::map<std::string, int> usersCount = stego_utils::getAuthorizedUsersCount(img);
    return usersCount;
}

void stego_utils::updateCountInFile(map<string, int> list, std::string path)
{
    imgProtect.lock();
    ofstream imageListFile(path, ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }

        long pos = imageListFile.tellp();
        
        imageListFile.close();
    }
    imgProtect.unlock();
}

void stego::updateUserCount(const std::string& img, const std::string& user, const int& count)
{
    std::map<std::string, int> allCount = stego_utils::getAuthorizedUsersCount(img);

    if (allCount.count(user) > 0) {
        allCount[user] = count;
        stego_utils::updateCountInFile(allCount, img + ".txt");
        stego::stegPicture(img, img + ".txt");
        stego::stegPicture(DEFAULT + img, img);
    }
}