#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <set>
#include <map>

void readDatabase();
std::set<std::string>& getOnlinePeers();
int checkInDatabase(std::string, std::string);

#endif
