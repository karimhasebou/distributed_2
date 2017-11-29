//
// Created by parallels on 11/29/17.
//

#ifndef DISTRIBUTED_2_STEGMANAGER_H
#define DISTRIBUTED_2_STEGMANAGER_H

#include <string>
#include <map>
#include <fstream>
#include <mutex>


struct STEGO_IMAGE{
	QPixmap img;
	std::map<std::string, int> users;		
};

namespace stego 
{
	void unstegPicture(const std::string&);
	int getUserCount(const std::string&, const std::string&);
	void updateUserCount(const std::string&, const std::string&, const int&);
	void stegPicture(const std::string&, const std::string&);
	std::map<std::string, int> getAuthorizedUsersCount(std::string path);
	void updateCountInMap(std::map<std::string, int> list, std::string path);
	std::map<std::string, int> infraSteg(const std::string& img);
	void ultraSteg(std::map<std::string, int>, const std::string&);
	void clean(std::string);

	struct STEGO_IMAGE getImgAndCreds(const std::string& directory, 
		const std::string& filename);
};

#endif //DISTRIBUTED_2_STEGMANAGER_H
