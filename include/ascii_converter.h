#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class ASCIIConverter {
private:
    std::vector<char> ascii_chars;
    int target_width;
    int target_height;
    
public:
    ASCIIConverter(int width = 80, int height = 24);
    
    std::string convertToASCII(const cv::Mat& image);
    cv::Mat convertASCIIToImage(const std::string& ascii_art);
    
private:
    char getASCIIChar(int intensity);
    cv::Mat preprocessImage(const cv::Mat& image);
};