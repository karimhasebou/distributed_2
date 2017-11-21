#ifndef SERVER_H
#define SERVER_H

#include<string>
#include<vector>

using namespace std;

class server{

public:
    server();



    ~server();


private:
    vector<string> peers;
    string database_path;
    map<string, string> db;
    void load_database();


};

#endif // SERVER_H
