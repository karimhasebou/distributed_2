#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
#include <iomanip>
#include <iostream>
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"

using namespace cv;
using namespace std;

char *global_data_stream;
Mat global_mat;


void printMap(std::map<std::string, int> Map);

void hideInImg(std::string img_path, std::map<std::string, int> table)
{
	CustomMap custom_table(table);
	std::string marshalled = custom_table.marshal();
	int bin_len = marshalled.size();

	cv::Mat img = imread(img_path.c_str(), cv::IMREAD_COLOR);

	unsigned char* img_pointer = img.data;
	for (int i = 0; i < 32; ++i) {
		char stego_bit = (bin_len >> i) & 1;
		if (stego_bit) {
			(*img_pointer) |= 1;
		}
		else {
			(*img_pointer) &= 0xFE;
		}
		++img_pointer;
	
	}

	for (int i = 0; i < bin_len; ++i){
		for (int j = 0; j < 8; ++j) {
			char stego_bit = (marshalled[i] >> j) & 1;
			if (stego_bit) {
				(*img_pointer) |= 1;
			}
			else {
				(*img_pointer) &= 0xFE;	
			}
			++img_pointer;
		}
	}
	cout << endl;
	global_mat = img.clone();
	std::string imgwrite = "/home/hasebou/Pictures/test5.bmp";

	vector<int> imgWriteParams;
	imgWriteParams.push_back(CV_IMWRITE_JPEG_QUALITY);
	imgWriteParams.push_back(100);

	imwrite(imgwrite, img, imgWriteParams);
}

std::map<std::string, int> recoverFormImage(std::string img_path)
{
	int str_len = 0;
	cv::Mat img = imread(img_path.c_str());
	// Mat img = global_mat;
	unsigned char* img_pointer = img.data; 	

	for (int i = 0; i < 32; ++i) {
		str_len |= ((*img_pointer) & 1)<<i;
		++img_pointer;
	}

	printf("%d\n", str_len);

	char* data_stream = new char[str_len]();

	for (int i = 0; i < str_len; ++i) {
		for (int j = 0; j < 8; ++j) {
			data_stream[i] |= ((*img_pointer) & 1)<<j;
			++img_pointer;
		}
	}

	CustomMap list;
	list.unmarshal(data_stream, str_len);
	delete[] data_stream;
	return list.getValue();
}

void printMap(std::map<std::string, int> Map)
{
	std::map<std::string, int>::iterator it = Map.begin();
	std::cout << Map.size() << std::endl;
	for (; it != Map.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}


using namespace std;

template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(),
                      rhs.begin());
}


int main()
{
	map<string, int> content;

    for(int i = 0; i < 33; ++i){
        string key = "key " + std::to_string(i);
        int randNum = rand();

        content[key] = randNum;
    }

	CustomMap testMap(content);
	CustomMap recMap;

	string marshalled = testMap.marshal();
	char* cstr = new char[marshalled.length()];
	memcpy(cstr, marshalled.c_str(), marshalled.length());
	printMap(content);
	printf("##################\n");
	hideInImg("/home/hasebou/Pictures/test.bmp", content);
	map<string, int> map2;
	map2 = recoverFormImage("/home/hasebou/Pictures/test5.bmp");
	printMap(map2);

	return 0;
}

// test for farid code
// int main()
// {
//     srand(time(NULL));

//     map<string, int> content;
//     string path = "/home/hasebou/Pictures/test.bmp";
// 	std::string imgwrite = "/home/hasebou/Pictures/test2.bmp";

//     for(int i = 0; i < 10; ++i){
//         string key = "key " + std::to_string(i);
//         int randNum = rand();

//         content[key] = randNum;
//     }

//     hideInImg(path, content);

//     map<string, int> retrieved =recoverFormImage(imgwrite);

	

// 	// printMap(content);
// 	// cout<<"!!!!!!!!!!!!!!!\n";
// 	// printMap(retrieved);

//     if(map_compare(content, retrieved)){
//         puts("test passed");
//     }else{
//         puts("test failed");
//     }
    
//     return 0;
// }


// int main()
// {
// 	CustomString custom;
// 	CustomString custReturn;

// 	string test = "hello,woqwdrld";
	
// 	custom.setValue(test);
// 	string marshalled = custom.marshal();

// 	char * cstr = new char [marshalled.length()+1];
//   	memcpy(cstr, marshalled.c_str(), marshalled.length() + 1);

// 	cout<<custom.getValue()<<endl;

// 	int start = 0;

// 	custReturn.unmarshal(cstr, start);

// 	cout<<custReturn.getValue()<<endl;

// 	return 0;
// }
// int main() {
// 	std::map<std::string, int> testMap;
// 	testMap["karim"] = 12;
// 	testMap["afd"] = 4;
// 	printMap(testMap);

// 	CustomMap test_custom_map(testMap);
// 	CustomMap return_custom_map;

// 	std::string marshalled = test_custom_map.marshal();
// 	char* test_c_string = new char[marshalled.size() + 1];
// 	std::copy(marshalled.begin(), marshalled.end(), test_c_string);
// 	test_c_string[marshalled.size()] = '\0';

// 	return_custom_map.unmarshal(test_c_string, 0);
// 	std::map<std::string, int> return_map;
// 	return_map = return_custom_map.getValue();
// 	printMap(return_map);
// 	return 0;
// }
