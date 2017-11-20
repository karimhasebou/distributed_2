#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void hideInImg(std::string img_path, std::map<std::string, int> table)
{
	CustomMap custom_table(table);
	std::string marshalled = custom_table.marshal();
	int bin_len = marshalled.size();
	
	char* data_stream = new char[bin_len];

	cv::Mat img = imread(img_path.c_str(), cv::IMREAD_COLOR);
	unsigned char* img_pointer = img.data;
	for (int i = 0; i < 32; ++i) {
		for (int j = 0; j < 8; ++j) {
			char bit = (*img_pointer) & 1;
			char stego_bit = (bin_len >> j) & 1;
			if (stego_bit) {
				(*img_pointer) |= 1;
			}
			else {
				(*img_pointer) &= 0xFE;
			}
			++img_pointer;
	}

	for (int i = 0; i < bin_len; ++i)
		for (int j = 0; j < 8; ++j) {
			char bit = (*img_pointer) & 1;
			char stego_bit = (data_stream[i] >> j) & 1;
			if (stego_bit) {
				(*img_pointer) |= 1;
			}
			else {
				(*img_pointer) &= 0xFE;	
			}
			++img_pointer;
		}
	}
}

std::map<std::string, int> recoverFormImage(std::string img_path)
{
	int str_len;
	cv::Mat img = imread(img_path.c_str());
	unsigned char* img_pointer = img.data; 	

	for (int i = 0; i < 32; ++i) {
		str_len = (str_len < 1) | ((*img_pointer) & 1);
		++img_pointer;
	}

	char* data_stream = new char[str_len];

	for (int i = 0; i < str_len; ++i) {
		for (int j = 0; j < 8; ++j) {
			data_stream[i] = (data_stream[i] < 1) | ((*img_pointer) & 1);
			++img_pointer;
		}
	}

	CustomMap list;
	list.unmarshal(data_stream, 0);
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

