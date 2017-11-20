
void printMap(std::map<std::string, int> Map)
{
	std::map<std::string, int>::iterator it = Map.begin();
	std::cout << Map.size() << std::endl;
	for (; it != Map.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}
int main() {
	std::map<std::string, int> testMap;
	testMap["karim"] = 12;
	testMap["afd"] = 4;
	printMap(testMap);

	CustomMap test_custom_map(testMap);
	CustomMap return_custom_map;

	std::string marshalled = test_custom_map.marshal();
	char* test_c_string = new char[marshalled.size() + 1];
	std::copy(marshalled.begin(), marshalled.end(), test_c_string);
	test_c_string[marshalled.size()] = '\0';

	return_custom_map.unmarshal(test_c_string, 0);
	std::map<std::string, int> return_map;
	return_map = return_custom_map.getValue();
	printMap(return_map);
	return 0;
}

