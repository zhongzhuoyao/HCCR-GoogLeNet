#include "gbcodes3755.h"
#include "OfflineGridUBytePicture.h"
#include "gabor.h"
#include "gradient.h"

#define gradient
//#define gabor

void readGNTFile(vector<OfflineGridUBytePicture*> &characters,
		const char* filename) {
	ifstream file(filename, ios::in | ios::binary);
	if (!file) {
		cout << "Cannot find " << filename << endl;
		exit (EXIT_FAILURE);
	}
	cout << "\n" << filename << endl;
	gntCharacterHeader gCH;
	while (file.read((char*) &gCH,
			(sizeof(gCH.sampleSize) + sizeof(gCH.height) + sizeof(gCH.width)
					+ sizeof(gCH.label)))) {
		OfflineGridUBytePicture* character = new OfflineGridUBytePicture(
				gCH.width, gCH.height, gCH.label);
		unsigned char *bitmap;
		try {
			bitmap = new unsigned char[gCH.width * gCH.height];
		} catch (bad_alloc ex) {
			cout << "\nException:" << ex.what() << " " << filename << endl;
			cout << gCH.width << " " << gCH.height << endl;
			exit(-1);

		}
		file.read((char *) bitmap, gCH.width * gCH.height);
		for (int i = 0; i < gCH.width * gCH.height; i++) { //Black (0) background, white (255) ink
			//opposite the color
			character->bitmap[i] = 255 - bitmap[i];
		}	
		character->label = find(gbcodesCRO, gbcodesCRO + 3755,
			character->label) - gbcodesCRO;
		if (character->label < nCharacters)
		{
			characters.push_back(character);
		}
		else
		{
			delete character;
		}	
		delete[] bitmap;
	}
	file.close();
}

cv::Mat maskCharacter(cv::Mat ResizedwordImg, int temp, bool flag) {
	cv::Mat maskImg=cv::Mat::zeros(maskHeight,maskWidth,CV_8UC1);
	int row = 0;
	int col = 0;
	if (flag == true) {
		row = int((maskHeight - characterHeight) / 2);
		col = int(std::floor((maskWidth - temp) / 2))+1;
	} else {
		row = int(std::floor((maskHeight - temp) / 2))+1;
		col = int((maskWidth - characterWidth) / 2);
	}
	for (int i = row; i < (maskHeight - row); i++) {
		for (int j = col; j < (maskWidth - col); j++) {
			maskImg.at<uchar>(i,j) = ResizedwordImg.at<uchar>(i - row, j - col);
		}
	}
	return maskImg;
}

cv::Mat resizeCharacter(OfflineGridUBytePicture *character) {

	int srcwidth = character->width;
	int srcheight = character->height;

	cv::Mat img=cv::Mat::zeros(srcheight,srcwidth,CV_8U);
	for (int m = 0; m < srcheight; m++) {
		for (int n = 0; n < srcwidth; n++) {
			img.at<uchar>(m,n) = character->bitmap[m * srcwidth + n];
		}
	}
	if(srcheight>srcwidth)
	{
		double ratio = (double) characterHeight / srcheight;
		int width = min(int(std::floor(ratio * srcwidth)), characterWidth);
		cv::Mat img_resize=cv::Mat::zeros(characterHeight,width,CV_8UC1);
		resize(img, img_resize, cvSize(width,characterHeight),0,0,CV_INTER_LINEAR);
		cv::Mat maskImg=maskCharacter(img_resize, width, true);
		img.release();
		img_resize.release();
		return maskImg;
	}
	else
	{
		double ratio = (double) characterWidth / srcwidth;
		int height = min(int(std::floor(ratio * srcheight)), characterHeight);
		cv::Mat img_resize=cv::Mat::zeros(characterWidth,height,CV_8UC1);
		resize(img, img_resize, cvSize(characterWidth,height),0,0,CV_INTER_LINEAR);
		cv::Mat maskImg = maskCharacter(img_resize, height, false);
		img.release();
		img_resize.release();
		return maskImg;
	}
}

int main()
{
	const char* filename="1001-c.gnt";
	vector<OfflineGridUBytePicture*> characters;
	readGNTFile(characters,filename);
	int characterNum=characters.size();
	char outfilename[100];
	char filenameAFormat[]=".\\featureMap\\%04d_%01d.png";
	cout<<" character number: "<<characterNum<<endl;
	for(int i=0;i<characterNum;i++)
	{
		cv::Mat img=resizeCharacter(characters[i]);
		vector<cv::Mat> featureMaps;
#ifdef gabor
		gabor_filter(img,featureMaps);
#endif
#ifdef gradient
		 FeaExtractByGradient(img,featureMaps);
#endif
		int featureMapNum=featureMaps.size();
		for(int c=0;c<featureMapNum;c++)
		{
			sprintf(outfilename,filenameAFormat,characters[i]->label,c);
			imwrite(outfilename,featureMaps[c]);
			featureMaps[c].release();
		}
		featureMaps.clear();
		img.release();
		characters[i]->bitmap.clear();
		cout<<i<<"th character has done, total character number is: "<<characterNum<<endl;
	}
	characters.clear();
}



