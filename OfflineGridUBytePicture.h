#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <new>
#include <cmath>
using namespace std;

#define nCharacters 3755
#define characterWidth  112
#define characterHeight 112
#define maskWidth  120
#define maskHeight 120

class OfflineGridUBytePicture {

public:
	int label; //for character recognition
	short int width;
	short int height;
	vector<unsigned char> bitmap; //row major order

	OfflineGridUBytePicture(int width, int height, int label_) :
			width(width), height(height) {
		label = label_;
		bitmap.resize(height * width);
	}
	~OfflineGridUBytePicture() {
	}
};

struct gntCharacterHeader {
	unsigned int sampleSize;
	unsigned short label;
	unsigned short width;
	unsigned short height;
};

