# Forehead Extractor

**A lightweight, real-time forehead region extractor using classical computer vision techniques.**

This C++ application uses OpenCV to detect and extract the forehead region from a live webcam feed — entirely without any machine learning or AI models.

---

## ✨ Features

- 📷 Real-time forehead detection from webcam input  
- 🧠 No AI or machine learning dependencies  
- 🟦 Edge detection using Sobel filters  
- 🔍 Contour-based region identification  
- 🖼 ROI (Region of Interest) extraction with tunable parameters  
- 💡 Optimized for performance on low-power systems  

---

## 🔧 Requirements

- OpenCV 4.x  
- C++17 compatible compiler  
- Webcam  

---

## 🚀 Installation

```bash
git clone https://github.com/Mbarek999/Forehead-extractor.git
cd Forehead-extractor
mkdir build && cd build
cmake ..
make
```
Usage
```bash
./forehead_extractor
```

🎯 Motivation
Most facial region extractors rely on machine learning models (e.g., Haar cascades, deep neural networks).
This project demonstrates that classical computer vision techniques are still powerful and efficient for focused tasks — offering faster performance and simpler deployment.

📚 Citation
If you find this project helpful, please consider citing:

@article{elboussaki2023pca,
  title={Non-contact Respiratory Rate Monitoring Based on Principal Component Analysis},
  author={El Boussaki, Hoda and Latif, Rachid and Saddik, Amine and El Khadiri, Zakaria and El Boujaoui, Hicham},
  journal={International Journal of Advanced Computer Science and Applications},
  volume={14},
  number={9},
  year={2023},
  publisher={The Science and Information Organization},
  url={https://www.ijacsa.thesai.org}
}
📄 License
MIT License — feel free to use, modify, and share.
