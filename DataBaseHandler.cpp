#include "DataBaseHandler.h"

void DataBaseHandler::readDataBase()
{
    std::string username, password, ip_address;
    bool online;
    
    std::string db_file = "/home/nawawy/Nawawy/dist_hope/database.txt";
    std::ifstream database_file;
    
    database_file.open(db_file.c_str());
    
    while(!database_file.eof())
    {
        database_file >> username >> password >> online >> ip_address;
        
        db.insert (std::pair<std::string, std::string>(username, password));
        
        if(online)
            online_peers.insert(ip_address);
        else
        {
            std::set<std::string>::iterator it;
            it = online_peers.find(ip_addresses);

            if(it != online_peers.end())
                online_peers.erase (it, online_peers.end());
        }
        
    }
}

int DataBaseHandler::logIn(std::string username, std::string password)
{
    
    std::map<std::string, std::string>::iterator it;
    it = db.find(username);
    
    if(it != db.end())
    {
        std::string password_db = it->second;
        
        if(password_db == password)
            return 1;
        else
            return 2;
    }
    else
        return 0;

}

std::set<std::string>& getOnlinePeers()
{
    return this->online_peers;
}


