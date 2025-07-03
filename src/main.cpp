#include <iostream>
#include <opencv2/opencv.hpp>
#include "ascii_converter.h"
#include "webcam_capture.h"

int main() {
    WebcamCapture webcam;
    ASCIIConverter converter(120, 40);
    
    if (!webcam.initialize()) {
        std::cerr << "Failed to initialize webcam" << std::endl;
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