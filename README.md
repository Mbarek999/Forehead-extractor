# Forehead-extractor
Forehead Region Extractor using OpenCV
A simple computer vision application that detects and extracts forehead regions from live camera feed without using AI.

Features
Real-time forehead detection from webcam feed

Edge detection using Sobel filters

Contour-based region identification

ROI extraction with adjustable parameters

No machine learning/AI dependencies

Requirements
OpenCV 4.x

C++17 compatible compiler

Webcam

Installation
git clone https://github.com/Mbarek999/Forehead-extractor.git
cd forehead-extractor
mkdir build && cd build
cmake ..
make

Usage
./forehead_extractor
