#include <iostream>
#include <opencv2/opencv.hpp>
#include "ascii_converter.h"
#include "webcam_capture.h"

int main() {
    WebcamCapture webcam;
    ASCIIConverter converter(120, 40);
    
    // Try to find available cameras
    std::cout << "Searching for available cameras..." << std::endl;
    bool camera_found = false;
    
    for (int device_id = 0; device_id < 5; device_id++) {
        std::cout << "Trying camera device " << device_id << "..." << std::endl;
        if (webcam.initialize(device_id)) {
            std::cout << "Successfully connected to camera device " << device_id << std::endl;
            camera_found = true;
            break;
        }
        webcam.release(); // Clean up failed attempt
    }
    
    if (!camera_found) {
        std::cerr << "Failed to initialize any webcam" << std::endl;
        std::cerr << "On macOS, you may need to grant camera permissions:" << std::endl;
        std::cerr << "System Preferences > Security & Privacy > Camera > Allow Terminal" << std::endl;
        return -1;
    }
    
    cv::Mat frame;
    std::cout << "ASCII Webcam Filter - Press 'q' to quit" << std::endl;
    
    while (true) {
        if (!webcam.captureFrame(frame)) {
            std::cerr << "Failed to capture frame" << std::endl;
            break;
        }
        
        cv::Mat ascii_image = converter.convertASCIIToImage(
            converter.convertToASCII(frame)
        );
        
        cv::imshow("ASCII Webcam Filter", ascii_image);
        
        char key = cv::waitKey(30);
        if (key == 'q' || key == 27) {
            break;
        }
    }
    
    webcam.release();
    cv::destroyAllWindows();
    
    return 0;
}