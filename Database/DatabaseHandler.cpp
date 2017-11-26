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
std::set<std::string> tmp_set;

void readDatabase()
{
    std::string username, password, ipAddress;
    
    std::string databasePath = "/home/nawawy/Nawawy/farida/distributed_2/Database/database.txt";
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
            
            tmp_set.insert(database[username].ipAddress);
            
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
    onlinePeers.clear();
    std::set<std::string>::iterator it = tmp_set.begin();
    std::set<std::string>::iterator end = tmp_set.end();    

    while(it != end)
    {
        onlinePeers.push_back(*it);
        it++;
    }
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

std::string getIPfromUser(std::string username)
{
    printf("Username found :: %s" , username.c_str());
    UserInfo userInfo = database[username];
    std::string ip = userInfo.ipAddress;

    printf("In Database %s : " , ip.c_str() );
    return database[username].ipAddress;
}

