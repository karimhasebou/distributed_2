#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <set>
#include <map>
#include "vector"

void readDatabase();
std::vector<std::string>& getOnlinePeers();
int checkInDatabase(std::string, std::string);
std::string getUserNamefromIP(std::string);

#endif
