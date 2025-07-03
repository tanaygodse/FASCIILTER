#pragma once

#include <opencv2/opencv.hpp>

class WebcamCapture {
private:
    cv::VideoCapture cap;
    bool is_initialized;
    
public:
    WebcamCapture();
    ~WebcamCapture();
    
    bool initialize(int device_id = 0);
    bool captureFrame(cv::Mat& frame);
    void release();
    bool isOpened() const;
    
    cv::Size getFrameSize() const;
    double getFPS() const;
};