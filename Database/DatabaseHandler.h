#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <set>
#include <map>
#include "vector"

void readDatabase();
std::map<std::string, std::string> getOnlinePeers();
int checkInDatabase(std::string, std::string);
std::string getUserNamefromIP(std::string);
std::string getIPfromUser(std::string);

#endif
