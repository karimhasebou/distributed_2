//
//  main.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Marshalling/MarshallingManager.h"
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"
#include "CustomObjects/CustomObject.h"
#include "Marshalling/MarshalledMessage.h"
#include "CustomObjects/CustomVector.h"
#include "CustomObjects/CustomBool.h"
#include <iostream>

int main() {
    
    
    CustomInt * param1 = new CustomInt(1);
    
    CustomInt * param2 = new CustomInt(2);
    
    CustomString * param3 = new CustomString("Parameter 3");
    
    CustomVector * param4 = new CustomVector();
    
    param4->push_back("Parameter 4 a");
    param4->push_back("Parameter 4 b");
    param4->push_back("Parameter 4 c");
    
    CustomVector * param5 = new CustomVector();
    
    param5->push_back("Parameter 5 a");
    param5->push_back("Parameter 5 b");
    param5->push_back("Parameter 5 c");
    
    CustomBool * param6 = new CustomBool();
    param6->setValue(true);
    
    CustomInt * param7 = new CustomInt();
    param7->setValue(7);
    
    CustomVector * param8 = new CustomVector();
    
    param8->push_back("Parameter 8 a");
    param8->push_back("Parameter 8 b");
    param8->push_back("Parameter 8 c");
    
    CustomString * param9 = new CustomString("Parameter 9 and Final");
    
    std::vector<CustomObject*> parameters = {dynamic_cast<CustomObject*>(param1),
        dynamic_cast<CustomObject*>(param2), dynamic_cast<CustomObject*>(param3),
        dynamic_cast<CustomObject*>(param4), dynamic_cast<CustomObject*>(param5),
        dynamic_cast<CustomObject*>(param6), dynamic_cast<CustomObject*>(param7),
        dynamic_cast<CustomObject*>(param8), dynamic_cast<CustomObject*>(param9)};
    
    MarshalledMessage message = marshal(parameters);
    
    std::vector<CustomObject*> returnParameters = {new CustomInt(), new CustomInt(),
        new CustomString(), new CustomVector(), new CustomVector(), new CustomBool,
        new CustomInt(), new CustomVector(), new CustomString()};
    
    unmarshal(message, 0, returnParameters);
    
    CustomInt * returnParam1 = dynamic_cast<CustomInt*>(returnParameters[0]);
    
    CustomInt * returnParam2 = dynamic_cast<CustomInt *>(returnParameters[1]);
    
    CustomString * returnParam3 = dynamic_cast<CustomString *>(returnParameters[2]);
    
    CustomVector * returnParam4 = dynamic_cast<CustomVector *>(returnParameters[3]);
    
    CustomVector * returnParam5 = dynamic_cast<CustomVector*>(returnParameters[4]);
    
    CustomBool * returnParam6 = dynamic_cast<CustomBool*>(returnParameters[5]);
    
    CustomInt * returnParam7 = dynamic_cast<CustomInt*>(returnParameters[6]);
    
    CustomVector * returnParam8 = dynamic_cast<CustomVector*>(returnParameters[7]);
    
    CustomString * returnParam9 = dynamic_cast<CustomString*>(returnParameters[8]);
    
    std::cout<<returnParam1->getValue()<<std::endl;
    
    std::cout<<returnParam2->getValue()<<std::endl;
    
    std::cout<<returnParam3->getValue()<<std::endl;
    
    for (int i = 0; i < returnParam4->getValue().size(); i++) {
        std::cout<<returnParam4->getValue()[i]<<std::endl;
    }
    
    for (int i = 0; i < returnParam5->getValue().size(); i++) {
        std::cout<<returnParam5->getValue()[i]<<std::endl;
    }
    
    std::cout<<returnParam6->getValue()<<std::endl;
    
    std::cout<<returnParam7->getValue()<<std::endl;
    
    for (int i = 0; i < returnParam8->getValue().size(); i++) {
        std::cout<<returnParam8->getValue()[i]<<std::endl;
    }
    
    std::cout<<returnParam9->getValue()<<std::endl;
}
