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

  Motivation
Most facial ROI extractors rely on heavy ML models (like Haar cascades or DNNs). This implementation proves that classical computer vision can still solve focused problems efficiently – with better performance and simpler deployment than AI-based solutions.

@article{elboussaki2023pca,
  title={Non-contact Respiratory Rate Monitoring Based on Principal Component Analysis},
  author={El Boussaki, Hoda and Latif, Rachid and Saddik, Amine and El Khadiri, Zakaria and El Boujaoui, Hicham},
  journal={International Journal of Advanced Computer Science and Applications},
  volume={14},
  number={9},
  year={2023},
  publisher={The Science and Information Organization},
  url={www.ijacsa.thesai.org}
}
