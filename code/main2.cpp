#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv\cvaux.h>
#include <opencv\ml.h>

#include <iostream>
#include <vector>

#include "DetectRegions.h"
#include "OCR.h"

using namespace std;
using namespace cv;

string getFilename(string s) {

	char sep = '/';
	char sepExt = '.';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		string fn = (s.substr(i + 1, s.length() - i));
		size_t j = fn.rfind(sepExt, fn.length());
		if (i != string::npos) {
			return fn.substr(0, j);
		}
		else {
			return fn;
		}
	}
	else {
		return "";
	}
}

int main(int argc, char** argv)
{
	cout << "OpenCV Automatic Number Plate Recognition\n";
	char* filename;
	Mat input_image;
	//Check if user specify image to process
	if (argc >= 2)
	{
		filename = argv[1];
		//이미지 그레이스케일로 불러오기
		input_image = imread(filename, 1);
	}
	else {
		printf("Use:\n\t%s image\n", argv[0]);
		return 0;
	}
	if (!input_image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	
	string filename_whithoutExt = getFilename(filename);
	cout << "working with file: " << filename_whithoutExt << "\n";
	//번호판 지역 검출
	DetectRegions detectRegions;
	detectRegions.setFilename(filename_whithoutExt);
	detectRegions.saveRegions = false;
	detectRegions.showSteps = false;
	detectRegions.run(input_image);
	

	
	return 0;
}