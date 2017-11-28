#include "CustomMap.h"
#include "CustomVector.h"

CustomMap::CustomMap(const std::map<std::string, std::string> & other) {

    value = other;
}

std::map<std::string, std::string> CustomMap::getValue() {

    return this->value;

}

std::string& CustomMap::operator[](const std::string key) {

    return value[key];

}

std::string CustomMap::marshal() {

    CustomVector keys;
    CustomVector values;

    std::map<std::string, std:string>::iterator it;

    for (it = value.begin(); it != value.end(); it++) {

        keys.push_back(it->first);
        keys.push_back(it->second);
    }

    std::string marshalledMap = "";

    marshalledMap += keys.marshal();
    marshalledMap += values.marshal();

    return marshalledMap;

}

int CustomMap::unmarshal(MarshalledMessage & message,
                         const int & startPosition) {

    int bufferPosition = startPosition;

    CustomVector keys;
    CustomVector values;

    this->value.clear();

    bufferPosition = keys.unmarshal(message, bufferPosition);

    bufferPosition = values.unmarshal(message, bufferPosition);

    for (int i = 0; i < keys.getValue().size(); i++) {

        this->value[keys[i]] = values[i];
    }

    return bufferPosition;

}
