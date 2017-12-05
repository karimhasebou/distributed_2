#include "StegManager.h"
#include "Paths.h"
#include <stdlib.h>
#include <QPixmap>

using namespace std;



namespace stego_utils {
    std::mutex imgProtect;

    string stegHideCmd(string cover, string hide);
    string stegUnhideCmd(string cover);
    int getUserCount(const string& user, const string& img);
    std::map<std::string, int> getAllCount(const std::string&);
    void updateCountInFile(map<string, int> list, std::string path);
}


std::map<std::string, int> stego::getAuthorizedUsersCount(std::string path)
{
    map<string, int> list;
    stego_utils::imgProtect.lock();
    ifstream imageListFile(path, ios::in);

    while(imageListFile.is_open()) {
        
        string username;
        int viewCount;
        
        imageListFile>>username;
        imageListFile>>viewCount;

        if(!imageListFile.eof()) {
            
            list[username] = viewCount;
        }
        else {
            
            imageListFile.close();
        }
    }
    stego_utils::imgProtect.unlock();
    return list;
}

string stego_utils::stegHideCmd(string cover, string hide)
{
    string cmd = "steghide embed -cf " + cover + " -ef " +
        hide + " -p root";
    return cmd;
}

string stego_utils::stegUnhideCmd(string cover)
{
    string cmd = "steghide extract -sf " + cover + " -p root -f";
    return cmd;
}

void stego::stegPicture(const string& imgCover, const string& imgHide)
{
    stego_utils::imgProtect.lock();

    std::string cmd = stego_utils::stegHideCmd(imgCover, imgHide);
    system(cmd.c_str());

    stego_utils::imgProtect.unlock();
}

void stego::unstegPicture(const string& img)
{
    stego_utils::imgProtect.lock();

    std::string cmd = stego_utils::stegUnhideCmd(img);
    //std::string cmd = stego_utils::stegUnhideCmd(DEFAULT + img);
    system(cmd.c_str());
    cmd = stego_utils::stegUnhideCmd(img);
    system(cmd.c_str());

    stego_utils::imgProtect.unlock();
}

int stego::getUserCount(const string& user, const string& img)
{
    int count = -1;
    std::map<std::string, int> allCount = stego::getAuthorizedUsersCount(img);

    if (allCount.count(user) > 0)
        count = allCount[user];

    return count;   
}

std::map<std::string, int> stego_utils::getAllCount(const std::string& img)
{
    std::map<std::string, int> usersCount = stego::getAuthorizedUsersCount(img);
    return usersCount;
}

void stego_utils::updateCountInFile(map<string, int> list, std::string path)
{
    stego_utils::imgProtect.lock();
    ofstream imageListFile(path, ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }

        
        imageListFile.close();
    }
    stego_utils::imgProtect.unlock();
}

// void stego::updateUserCount(const std::string& img, const std::string& user, const int& count)
// {
//     std::map<std::string, int> allCount = stego::getAuthorizedUsersCount(img);

//     if (allCount.count(user) > 0) {
//         allCount[user] = count;
//         stego_utils::updateCountInFile(allCount, img + ".txt");
//         stego::stegPicture(img, img + ".txt");
//         stego::stegPicture(DEFAULT + img, img);
//     }
// }

/** @param takes path to image to modify
 */
void stego::updateCountInMap(map<std::string, int> list, std::string path)
{
    ofstream imageListFile(path + ".txt", ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }
	    imageListFile.close();

        int pathLen = path.find_last_of("/"); // find were path ends
        string folderName;
        if(pathLen != -1){
            folderName = path.substr(0, pathLen + 1); // pathLen + 1 to include forward slash
        }else{
            folderName = " ";
        }

        std::string cmd = "Stegnography/update_count.sh "+DEFAULT+"  "
            + path + " " + folderName + " " + path + ".txt";
	std::string rmCmd = "rm "  + path + ".txt";


        system(cmd.c_str()); // update count
	system(rmCmd.c_str());
        puts("updated image count");
    }else{
        puts("failed to update count");
    }
}

void stego::updateCountInMapLocal(std::map<std::string, int> list, std::string path)
{
    ofstream imageListFile(path + ".txt", ios::out);
    
    if(imageListFile.is_open()){
        
        for(auto& entry : list){
            
            imageListFile<<entry.first<<" "<<entry.second<<endl;
        }
	    imageListFile.close();

        int pathLen = path.find_last_of("/"); // find were path ends
        string imageName = pathLen == -1 ? path : path.substr(pathLen+1);

        

        imageName = "Stegnography/update_local_count.sh " + imageName;
        printf("Image name %s\n", imageName.c_str());
        system(imageName.c_str());
    }else{
        puts("failed to update count");
    }
}

/** @param directory folder containing image
 *  @param filename img name
 */
StegImage stego::getImgAndCreds(const std::string& directory,
                                const std::string& filename) 
{

    StegImage result;

    string unstegCMD = "Stegnography/unsteg.sh "+directory + filename;
    system(unstegCMD.c_str());


    result.users =  stego::getAuthorizedUsersCount(
            TEMP_FOLDER + filename+".txt");


    result.image.load(QString::fromStdString(TEMP_FOLDER + filename));
    system("Stegnography/clean.sh");

    return result;
}

StegImage stego::getMyImgAndCreds(const std::string& directory,
				  const std::string& filename)
{
	StegImage result;
	
	string unstegCMD = "Stegnography/unstegone.sh " + directory + filename;
	system(unstegCMD.c_str());

	result.users = stego::getAuthorizedUsersCount(TEMP_FOLDER + filename + ".txt");
	result.image.load(QString::fromStdString(directory + filename));
	
	system("Stegnography/clean.sh");
	return result;
}
// std::map<std::string, int> stego::infraSteg(const string& img)
// {
// 	string myImagesPath = "MyImages/";
// 	stego::unstegPicture(DEFAULT + img);
// 	stego::unstegPicture(img);

// 	string mvCmd = "mv " + img + " " +  myImagesPath;
// 	system(mvCmd.c_str());

// 	map<string, int> userMap = stego::getAuthorizedUsersCount(img + ".txt");
// 	return userMap;
// }

void stego::clean(string file)
{
	string path = "rm " + file;
	system(path.c_str());
}

// void stego::ultraSteg(map<string, int> count, const string& img)
// {
// 	string myImagesPath = "MyImages/";
// 	stego_utils::updateCountInFile(count, img + ".txt");
// 	stego::stegPicture(myImagesPath + img, img + ".txt");

// 	stego::stegPicture(stego_utils::DEFAULT + img, myImagesPath + img);
// 	stego::clean(img + ".txt");
// }
