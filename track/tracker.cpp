#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/aruco.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/* 
visual display of all the tracking done: shi-tomasi and aruco
*/

Mat src, src_gray;
int maxFeatures = 88;
RNG rng(12345);
const char* source_window = "Image";
std::vector<std::vector<cv::Point2f> > target_corners;// corners of bounding box for aruco
void detect_features(int, void*);

int main(int argc, char** argv){
    // initiate vid capture
    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    // initiate aruco dictionary 
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

    while (inputVideo.grab()) {
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(src);
        // color conversion for shi tomasi (grayscale)
        cvtColor(src, src_gray, COLOR_BGR2GRAY);
        // aruco detection
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        target_corners = corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        // if at least one marker detected
        if (ids.size() > 0)
            cv::aruco::drawDetectedMarkers(src, corners, ids);
            for (int i = 0; i < ids.size(); i++){
                vector<Point> polypts; 
                for (int j = 0; j < corners[i].size(); j++){
                    polypts.push_back(Point((int)corners[i][j].x, (int)corners[i][j].y));
                }
                fillConvexPoly(src_gray, polypts, Scalar(1.0, 1.0, 1.0), 16, 0);
                // mask target from feature detector
            }
    	namedWindow(source_window);
    	imshow( source_window, src );
        // mask the region where the aruco is  
    	detect_features(0, 0); // shi tomasi feature detector 
    	char key = (char) cv::waitKey(1);
        if (key == 27)
            break;
    }
    return 0;
}

void detect_features(int, void*){
    maxFeatures = MAX(maxFeatures, 1);
    vector<Point2f> featurePts;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3, gradientSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    Mat copy = src.clone();
    goodFeaturesToTrack( src_gray,
                         featurePts,
                         maxFeatures,
                         qualityLevel,
                         minDistance,
                         Mat(),
                         blockSize,
                         gradientSize,
                         useHarrisDetector,
                         k );
    int radius = 4;
    // note that even with mask, there will be features detected on the corners of the
    // target marker. Hopefully that will be fine (only 4 pts)
    for( size_t i = 0; i < featurePts.size(); i++ ){
        circle( copy, featurePts[i], radius, Scalar(rng.uniform(0,255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED );
    }
    namedWindow(source_window);
    imshow(source_window, copy);
}