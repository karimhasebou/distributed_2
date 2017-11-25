#include "DatabaseHandler.h"
#include <fstream>

std::map<std::string, std::string> database;
std::set<std::string> online_peers;

void readDatabase()
{
    std::string username, password, ipAddress;
    bool online;
    
    std::string databasePath = "./database.txt";
    std::ifstream databaseFile;
    
    databaseFile.open(databasePath.c_str());
    
    if(databaseFile.fail()) {
        printf("Can't open database file\n");
    }
    
    else {
        
        while(!databaseFile.eof())
        {
            databaseFile >> username >> password >> online >> ipAddress;
        
            database.insert (std::pair<std::string, std::string>(username, password));
        
            if(online)
                online_peers.insert(ipAddress);
            else
            {
                std::set<std::string>::iterator it;
                it = online_peers.find(ipAddress);

                if(it != online_peers.end())
                    online_peers.erase (it, online_peers.end());
            }
        }
    }
}

int checkInDatabase(std::string username, std::string password)
{

    if(database.find(username) != database.end())
    {
        if(database[username] == password)
            return 1;       //logged in
        else
            return 2;       // wrong password
    }
    else
        return 3;           //wrong username
}

std::set<std::string>& getOnlinePeers()
{
    return online_peers;
}


