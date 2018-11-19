// generating markers
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace cv;
using namespace std;

void createArucoMarker(int id, string outfile_name){
    Mat outputMarker;

    Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);

    aruco::drawMarker(markerDictionary, id, 500, outputMarker, 1);
    // 500 is number of side pixels
    imwrite(outfile_name, outputMarker);
}

int main(int argc, char *argv[]){
    if (argc < 3){
        std::cout << "usage: ./gen id outfile_name" << std::endl; 
        return 1;
    }
    createArucoMarker(atoi(argv[1]), argv[2]);
    return 0;
}
