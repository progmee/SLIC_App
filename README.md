# SLIC Application (C++ / Qt)

A lightweight Qt application designed for visualizing and experimenting with **SLIC (Simple Linear Iterative Clustering) superpixel segmentation**[cite: 5]. The project features adjustable parameters, real-time boundary rendering, and an intuitive image workspace[cite: 5].

## Features

* **Superpixel Segmentation:** Interactive implementation of the SLIC algorithm for image segmentation.
* **Customizable Parameters:** Fine-tune algorithm settings directly through the graphical user interface (GUI).
* **Boundary Rendering:** Real-time visualization of superpixel boundaries over loaded images.
* **Multi-language Support:** Built-in localization files (`.ts`) for English and French.

## Project Structure

* `src/` — Core implementation files and application logic.
* `include/` — Header files and class declarations.
* `resource/` — Icons, styles, and other static assets.
* `CMakeLists.txt` — CMake build configuration file[cite: 5].
* `SLIC_App_en_US.ts` / `SLIC_App_fr_FR.ts` — Translation source files for internationalization[cite: 5].

## Building and Running

### Prerequisites
* A C++ compiler with C++ support.
* **Qt 5** or **Qt 6** framework.
* CMake (version 3.5 or higher).

### Build with CMake
Clone the repository and build the project using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
