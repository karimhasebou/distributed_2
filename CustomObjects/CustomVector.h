//
//  CustomVector.hpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CustomVector_hpp
#define CustomVector_hpp

#include "CustomObject.h"
#include  <vector>

class CustomVector : public CustomObject {
private:
    std::vector<std::string> value;
    
public:
    CustomVector(){}
    void push_back(const std::string&);
    std::vector<std::string> getValue();
    std::string& operator[](int);
    virtual std::string marshal();
    virtual int unmarshal(char *, const int&);
};


#endif /* CustomVector_hpp */
