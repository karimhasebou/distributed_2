#ifndef CUSTOMMAP_HPP
#define CUSTOMMAP_HPP

#include "CustomObject.h"
#include <map>

class CustomMap : public CustomObject {

private:
    std::map<std::string, std::string> value;

public:
    CustomMap(){};
    CustomMap(std::map<std::string, std::string>&);
    std::string& operator[](const std::string);
    std::map<std::string, std::string> getValue();
    virtual std::string marshal();
    virtual int unmarshal(MarshalledMessage &, const int&);
};

#endif