// BitmapToGamemap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "bitmap_image.hpp"

using namespace std;

int main()
{
    std::cout << "Hello World!\n";

    bitmap_image image("circuit.bmp");

	ofstream outputFile;
	outputFile.open("testmap3.gamemap");

	rgb_t couleurCircuit;
	couleurCircuit.red = 90;
	couleurCircuit.green = 90;
	couleurCircuit.blue = 90;

	outputFile << image.width() << " " << image.height();

	for (int y = 0; y < image.height(); y++) {
		outputFile << endl;
		for (int x = 0; x < image.width(); x++) {

			if (image.get_pixel(x,y) == couleurCircuit) {
				outputFile << "1 ";
			}
			else {
				outputFile << "0 ";
			}

		}
	}

	outputFile.close();

	std::cout << "fini" << endl;
}

