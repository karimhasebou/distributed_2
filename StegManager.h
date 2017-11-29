//
// Created by parallels on 11/29/17.
//

#ifndef DISTRIBUTED_2_STEGMANAGER_H
#define DISTRIBUTED_2_STEGMANAGER_H

#include <string>
#include <map>

void stegUserList(const std::string&, const std::string&);

void unstegUserList(const std::string&);

std::map<std::string, int> getUsersCount(const std::string&, const std::string&);

void updateUserCount(const std::string&, const int&);



#endif //DISTRIBUTED_2_STEGMANAGER_H
