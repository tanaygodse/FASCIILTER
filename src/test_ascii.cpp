#include <iostream>
#include <opencv2/opencv.hpp>
#include "ascii_converter.h"

int main() {
    ASCIIConverter converter(80, 24);
    
    cv::Mat test_image = cv::Mat::zeros(480, 640, CV_8UC3);
    
    cv::circle(test_image, cv::Point(320, 240), 100, cv::Scalar(255, 255, 255), -1);
    cv::rectangle(test_image, cv::Point(200, 150), cv::Point(440, 330), cv::Scalar(128, 128, 128), 2);
    cv::putText(test_image, "TEST", cv::Point(280, 250), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
    
    std::string ascii_art = converter.convertToASCII(test_image);
    std::cout << "ASCII Art Test:" << std::endl;
    std::cout << ascii_art << std::endl;
    
    cv::Mat ascii_image = converter.convertASCIIToImage(ascii_art);
    
    cv::imshow("Original", test_image);
    cv::imshow("ASCII Art", ascii_image);
    
    std::cout << "Press any key to exit..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}