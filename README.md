# SLIC_App

SLIC_App is a minimal Qt-based tool for image segmentation using the SLIC (Simple Linear Iterative Clustering) algorithm.

## Features
- Load PNG / JPG / JPEG / BMP images  
- Zoom & pan inside `QGraphicsView`  
- SLIC parameters: clusters, spacing, iterations  
- Visualization of boundaries and cluster centers  
- Light Windows-11-style UI

## Tech Stack
- C++20  
- Qt 6 (Widgets)  
- CMake  
- Custom SLIC implementation (LAB space)

## Build
```bash
mkdir build
cd build
cmake ..
make -j8
