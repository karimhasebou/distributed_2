//
// Created by parallels on 11/29/17.
//

#ifndef DISTRIBUTED_2_STEGMANAGER_H
#define DISTRIBUTED_2_STEGMANAGER_H

#include <string>
#include <map>
#include <fstream>
#include <mutex>

namespace stego {

void unstegPicture(const std::string&);
int getUserCount(const std::string&, const std::string&);
void updateUserCount(const std::string&, const std::string&, const int&);
void stegPicture(const std::string&, const std::string&);

std::map<std::string, int> getAuthorizedUsersCount(std::string path);

void updateCountInMap(std::map<std::string, int> list, std::string path);

};

#endif //DISTRIBUTED_2_STEGMANAGER_H
