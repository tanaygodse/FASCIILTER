#include "ascii_converter.h"
#include <sstream>

ASCIIConverter::ASCIIConverter(int width, int height) 
    : target_width(width), target_height(height) {
    ascii_chars = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
}

std::string ASCIIConverter::convertToASCII(const cv::Mat& image) {
    cv::Mat processed = preprocessImage(image);
    std::stringstream ascii_stream;
    
    for (int y = 0; y < processed.rows; y++) {
        for (int x = 0; x < processed.cols; x++) {
            uchar pixel = processed.at<uchar>(y, x);
            ascii_stream << getASCIIChar(pixel);
        }
        ascii_stream << '\n';
    }
    
    return ascii_stream.str();
}

cv::Mat ASCIIConverter::convertASCIIToImage(const std::string& ascii_art) {
    cv::Mat image(target_height * 16, target_width * 8, CV_8UC3, cv::Scalar(0, 0, 0));
    
    std::istringstream stream(ascii_art);
    std::string line;
    int y = 0;
    
    while (std::getline(stream, line) && y < target_height) {
        for (int x = 0; x < line.length() && x < target_width; x++) {
            cv::putText(image, std::string(1, line[x]), 
                       cv::Point(x * 8, (y + 1) * 16), 
                       cv::FONT_HERSHEY_SIMPLEX, 0.5, 
                       cv::Scalar(255, 255, 255), 1);
        }
        y++;
    }
    
    return image;
}

char ASCIIConverter::getASCIIChar(int intensity) {
    int index = (intensity * (ascii_chars.size() - 1)) / 255;
    return ascii_chars[index];
}

cv::Mat ASCIIConverter::preprocessImage(const cv::Mat& image) {
    cv::Mat gray, resized;
    
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::resize(gray, resized, cv::Size(target_width, target_height));
    
    return resized;
}