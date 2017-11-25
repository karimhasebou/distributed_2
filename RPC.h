#ifndef __RPC
#define __RPC

#define IMG_DIR ""
#define IMG_LIST_FILE ""
#define AUTHORIZED_USERS ""

#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <set>
#include <map>
 
using namespace std;

    
typedef struct{
    char *content;
    size_t length;
} Image;

typedef struct{
    string username;
    int viewCount;
} DBEntry;

//utilities
map<string, int> readAuthorizedUsersDB();
void writeDB(map<string, int> list);

// 
vector<string> listImages();
set<string> getAuthorizedUsers(string filePath);
void unstegUserList(string filePath);
string getPath(string imgName);

//supported rpc
Image getImage(string imgName);
vector<string> getAccessibleImages(string username);
bool canUpdateCount(string imgName, string username);
bool updateCount(string imgName, string username, int count);

// returns empty string if no user is currently logged in
string getLoggedUsername();


#endif