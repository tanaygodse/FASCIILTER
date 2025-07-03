#include "webcam_capture.h"
#include <iostream>

WebcamCapture::WebcamCapture() : is_initialized(false) {}

WebcamCapture::~WebcamCapture() {
    release();
}

bool WebcamCapture::initialize(int device_id) {
    cap.open(device_id);
    
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        return false;
    }
    
    is_initialized = true;
    return true;
}

bool WebcamCapture::captureFrame(cv::Mat& frame) {
    if (!is_initialized || !cap.isOpened()) {
        return false;
    }
    
    cap >> frame;
    return !frame.empty();
}

void WebcamCapture::release() {
    if (cap.isOpened()) {
        cap.release();
    }
    is_initialized = false;
}

bool WebcamCapture::isOpened() const {
    return cap.isOpened();
}

cv::Size WebcamCapture::getFrameSize() const {
    if (!is_initialized) {
        return cv::Size(0, 0);
    }
    
    return cv::Size(
        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))
    );
}

double WebcamCapture::getFPS() const {
    if (!is_initialized) {
        return 0.0;
    }
    
    return cap.get(cv::CAP_PROP_FPS);
}