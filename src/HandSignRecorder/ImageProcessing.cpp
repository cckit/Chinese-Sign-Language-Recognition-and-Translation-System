#include "lodepng.h"
#include <vector>
#include <iostream>
using namespace std;

void loadImage(vector <unsigned char> &dest, unsigned width, unsigned height, string fileName){
	vector<unsigned char> tempP;

	if(lodepng::decode(tempP, width, height, fileName)){
		cout << "PNG Load Error" << endl;
		exit(1);
	}

	size_t u2 = 1; while(u2 < width) u2 *= 2;
	size_t v2 = 1; while(v2 < height) v2 *= 2;
	double u3 = (double)width / u2;
	double v3 = (double)height / v2;

	dest.assign(u2*v2*4, 0);
	for(size_t y = 0; y < height; y++)
		for(size_t x = 0; x < width; x++)
			for(size_t c = 0; c < 4; c++){
				dest[4 * u2 * y + 4 * x + c] = tempP[4 * width * y + 4 * x + c];
			}
}