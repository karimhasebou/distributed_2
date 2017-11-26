#include "DatabaseHandler.h"
#include <fstream>
#include <vector>


struct UserInfo {
    
    std::string password;
    std::string ipAddress;
    
};

std::map<std::string, UserInfo> database;
std::map<std::string, std::string> UsersIps;
std::vector<std::string> onlinePeers;

void readDatabase()
{
    std::string username, password, ipAddress;
    
    std::string databasePath = "/home/nawawy/Nawawy/dist_final/distributed_2/Database/database.txt";
    std::ifstream databaseFile;
    
    databaseFile.open(databasePath.c_str());
    
    if(databaseFile.fail()) {
        printf("Can't open database file\n");
    }
    
    else {
        
        while(!databaseFile.eof())
        {
            databaseFile >> username >> password >> ipAddress;
        
            UserInfo userInfo;
            userInfo.password = password;
            userInfo.ipAddress = ipAddress;
            
            database[username] = userInfo;
            UsersIps[username] = ipAddress;
        }
    }
}

int checkInDatabase(std::string username, std::string password)
{

    if(database.find(username) != database.end())
    {
        if(database[username].password == password) {
            
            onlinePeers.push_back(database[username].ipAddress);
            
            return 1;       //logged in
        }
        else
            return 2;       // wrong password
    }
    else
        return 3;           //wrong username
}

std::vector<std::string>& getOnlinePeers()
{
    return onlinePeers;
}

std::string getUserNamefromIP(std::string IPAddress)
{
    std::map<std::string, UserInfo>::iterator it;
    std::string username = "";
    
    for (it = database.begin(); it != database.end(); ++it )
        if (it->second.ipAddress == IPAddress)
        {
            username = it->first;
            break;
        }
    
    return username;
}

std::map<std::string, std::string> getMapUsers()
{
    return UsersIps;
}

