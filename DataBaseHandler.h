#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <set>
#include <map>


class DataBaseHandler
{
public:
    void readDataBase();
    std::set<std::string>& getOnlinePeers()    
    int logIn(std::string, std::string);

private:
    std::map<std::string, std::string> db;
    std::set<std::string> online_peers;
    
};

#endif