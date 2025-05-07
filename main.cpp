#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <limits>

//ROI_cooerdonate
#define xOffset  20
#define yOffset  30

//ROI_output
cv::Mat foreheadRegion;
double fps;

int main() {
    // Open the default camera (camera index 0)
    cv::VideoCapture cap(0);

    // Check if the camera opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera!" << std::endl;
        return -1;
    }

    // Set camera properties (optional)
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);  // Set the width
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480); // Set the height

    cv::Mat frame; // Matrix to store each video frame

    // Video capture loop
    while (true) {
        // Capture a new frame from the camera
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            std::cerr << "Error: Could not retrieve frame!" << std::endl;
            break;
        }

    // Convert image to Grayscale
    cv::Mat grayImage;
    cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);   

    // Blurring the image
    cv::Mat blurredImage;  
    cv::blur(grayImage, blurredImage, cv::Size(5, 5));   

        // Apply Sobel filter
    cv::Mat sobelX, sobelY, sobelImage;
    cv::Sobel(blurredImage, sobelX, CV_64F, 1, 0, 3);  // Gradient in the X direction
    cv::Sobel(blurredImage, sobelY, CV_64F, 0, 1, 3);// Gradient in the Y direction
    cv::Mat gradientMagnitude;   
    cv::magnitude(sobelX, sobelY, gradientMagnitude);  // Compute the gradient magnitude


    // Normalize the magnitude to display it as an image
    cv::normalize(gradientMagnitude, sobelImage, 0, 255, cv::NORM_MINMAX, CV_8U);


    // Convert to binary using thresholding
    cv::Mat binaryImage;
    cv::threshold(sobelImage, binaryImage, 100, 255, cv::THRESH_BINARY); // Adjust threshold value

    // Find initial contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binaryImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Fill the interior of the contours with white
    cv::Mat filledContours = cv::Mat::zeros(binaryImage.size(), CV_8UC1);
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(filledContours, contours, static_cast<int>(i), cv::Scalar(255), cv::FILLED); // Fill contours with white
    }

    // Apply morphological operations: Dilation
    cv::Mat dilatedImage;
    int kernelSize = 3;  // Define the structuring element (kernel)
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernelSize, kernelSize));
    cv::dilate(filledContours, dilatedImage, kernel);


    // Initialize variables to store the largest contour and its topmost point
    double maxArea = 0;
    int largestContourIndex = -1;
    cv::Point topPoint;

    // Find the largest contour by area
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            largestContourIndex = static_cast<int>(i);
        }
    }

    // Process the largest contour if found
    cv::Mat contourWithTopPoint = cv::Mat::zeros(dilatedImage.size(), CV_8UC3);
    if (largestContourIndex != -1) {
        // Get the largest contour
        const std::vector<cv::Point>& largestContour = contours[largestContourIndex];

        // Find the topmost point in the largest contour
        topPoint = largestContour[0];
        for (const cv::Point& point : largestContour) {
            if (point.y < topPoint.y) {
                topPoint = point;
            }
        }

    // Draw the largest contour
    cv::drawContours(contourWithTopPoint, contours, largestContourIndex, cv::Scalar(0, 255, 0), 2); // Green contour

    // Mark the topmost point on the image
    cv::circle(contourWithTopPoint, topPoint, 5, cv::Scalar(0, 0, 255), -1); // Red circle

    // Output the coordinates of the topmost point
    std::cout << "Topmost Point of the Largest Contour = (" << topPoint.x << ", " << topPoint.y << ")" << std::endl;
}
    // Calculate new coordinates for ROI
    int roiX = std::max(topPoint.x - xOffset, 0); // Ensure the ROI does not go out of bounds
    int roiY = std::max(topPoint.y + yOffset, 0);
    int roiWidth = 50;  // Define the width of the ROI 
    int roiHeight = 30; // Define the height of the ROI

    // Ensure the ROI stays within image boundaries
    roiX = std::min(roiX, frame.cols - 1);
    roiY = std::min(roiY, frame.rows - 1);
    roiWidth = std::min(roiWidth, frame.cols - roiX);
    roiHeight = std::min(roiHeight, frame.rows - roiY);

    // Extract ROI
    cv::Rect roi(roiX, roiY, roiWidth, roiHeight);
    foreheadRegion = frame(roi);

    // Highlight the ROI on the original image
    cv::rectangle(frame, roi, cv::Scalar(255, 0, 0), 2); // Blue rectangle for ROI
    fps = cap.get(cv::CAP_PROP_FPS);
    
    // Display the frame
        cv::imshow("Camera Video", frame);

        // Exit if the user presses the 'q' key
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera resource
    cap.release();

    // Destroy all OpenCV windows
    cv::destroyAllWindows();

    return 0;

}
