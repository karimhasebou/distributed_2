//
// Created by parallels on 11/29/17.
//

#ifndef DISTRIBUTED_2_STEGMANAGER_H
#define DISTRIBUTED_2_STEGMANAGER_H

#include <string>
#include <map>
#include <fstream>
#include <mutex>
#include <QPixmap>

struct StegImage {
	QPixmap image;
	std::map<std::string, int> users;
};


namespace stego 
{
	void unstegPicture(const std::string&);
	int getUserCount(const std::string&, const std::string&);
	void updateUserCount(const std::string&, const std::string&, const int&);
	void stegPicture(const std::string&, const std::string&);
	std::map<std::string, int> getAuthorizedUsersCount(std::string path);
	std::map<std::string, int> infraSteg(const std::string& img);
	void ultraSteg(std::map<std::string, int>, const std::string&);
	void clean(std::string);

	void updateCountInMap(std::map<std::string, int> list, std::string path);

	StegImage getImgAndCreds(const std::string&, const std::string&);
	StegImage getMyImgAndCreds(const std::string&, const std::string&);
};

#endif //DISTRIBUTED_2_STEGMANAGER_H
