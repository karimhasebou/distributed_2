#include <iterator>
#include "CustomMap.h"
#include "CustomInt.h"
#include "CustomString.h"

CustomMap::CustomMap(std::map<std::string, int> table)
{
	this->table = table;
}

CustomMap::~CustomMap()
{
}

int CustomMap::getValueAt(int idx)
{
	CustomMap::Table::iterator it = table.begin();
	std::advance(it, idx);
	//it = it + idx;
	return it->second;
}

std::string CustomMap::getKeyAt(int idx)
{
	CustomMap::Table::iterator it = table.begin();
	std::advance(it, idx);
	//it = it + idx;
	return it->first;
}

std::string CustomMap::marshal()
{
	int len = table.size();
	CustomInt map_length(len);
	CustomInt counts[len];
	CustomString strings[len];

	map_length.setValue(len);
	for (int i = 0; i < len; ++i) {
		std::string key = getKeyAt(i);
		int val = getValueAt(i);
		strings[i].setValue(key);	
		counts[i].setValue(val);
	}

	std::string marshalledMap = map_length.marshal();
	for (int i = 0; i < len; ++i) {
		marshalledMap += strings[i].marshal();
		marshalledMap += counts[i].marshal();
	}

	return marshalledMap;
}

int CustomMap::unmarshal(char* buffer, const int& startPosition)
{
	CustomInt header;
	int next = header.unmarshal(buffer, 0);	
	int len = header.getValue();

	for (int i = 0; i < len; ++i) {
		CustomString key;
		CustomInt val;
		next = key.unmarshal(buffer, next);
		next = val.unmarshal(buffer, next);
		this->table[key.getValue()] = val.getValue();
	}
	return next;
}

CustomMap::Table CustomMap::getValue()
{
	return this->table;
}
