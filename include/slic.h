#ifndef SLIC_H
#define SLIC_H

#include <algorithm>
#include <vector>

#include <QImage>
#include <QPoint>

struct SLICConfig {
    SLICConfig(unsigned int __iterations, unsigned int __superpixels, double __compactness, bool __showBoundaries = false)
        : showBoundaries(__showBoundaries), compactness(__compactness), superpixels(__superpixels), iterations(__iterations) {};

    bool showBoundaries; // Flag to show boundaries
    double compactness;
    unsigned int iterations; // Total number of iterations
    unsigned int superpixels; // Total number of created superpixels
    unsigned int spacing; // Size of superpixel
};

// Type to store rgb coordinate as space ordinates
struct LAB {
    LAB(int __r, int __g, int __b) {
        // Convert rgb to lab
        setFromRGB(__r, __g, __b);
    };
    LAB() : l(0), a(0), b(0) {};

    // Set from RGB to LAB values
    LAB& setFromRGB(int __r, int __g, int __b) {
        // Normalize each param
        double norm_r = static_cast<double>(__r) / 255;
        double norm_g = static_cast<double>(__g) / 255;
        double norm_b = static_cast<double>(__b) / 255;

        // Remove gamma correction for each color
        norm_r = (norm_r > 0.04045) ? pow((norm_r + 0.055)/1.055, 2.4) : norm_r / 12.92;
        norm_g = (norm_g > 0.04045) ? pow((norm_g + 0.055)/1.055, 2.4) : norm_g / 12.92;
        norm_b = (norm_b > 0.04045) ? pow((norm_b + 0.055)/1.055, 2.4) : norm_b / 12.92;

        // Apply D65 matrics to rgb values and normalize XYZ
        double x = (0.4124*norm_r + 0.3576*norm_g + 0.1805*norm_b) / 0.95047;
        double y = (0.2126*norm_r + 0.7152*norm_g + 0.0722*norm_b) / 1.00000;
        double z = (0.0193*norm_r + 0.1192*norm_g + 0.9505*norm_b) / 1.08883;

        // Non-linear cube-root function
        auto f = [](double t) {
            return t > 0.008856 ? pow(t, 1.0/3.0) : (7.787*t + 16.0/116.0);
        };

        // Values with applied function
        double fx = f(x);
        double fy = f(y);
        double fz = f(z);

        l = 116 * fy - 16;
        a = 500 * (fx - fy);
        b = 200 * (fy - fz);
    };

    // LAB Values
    int l, a, b;
};

struct Center {
    Center() : position(QPoint(0, 0)), colour(LAB()){};
    Center(QPoint __position, LAB __colour) : position(__position), colour(__colour) {};

    QPoint position;
    LAB colour;
};

struct SLICOutput {
    // Label affiliation to superpixel
    std::vector<int> labels;
    int height, width;

    bool isValide() {
        return !labels.empty();
    };
};

class SLIC {
public:
    // Constructors and destructor
    SLIC();
    SLIC(SLICConfig& __config) : config(__config){};
    ~SLIC();

    // Setters and getters
    void setConfig(const SLICConfig& config);
    SLICConfig& getConfig() const;

    // Apply SLIC algorithm for sellected image
    SLICOutput apply(const QImage& image);
private:
    std::vector<Center> initializeCenters(const std::vector<std::vector<LAB>>& pixels); // Initialize centers
    double distance(const Center& c1, const Center& c2);
    std::vector<int> kMeans(const std::vector<std::vector<LAB>>& pixels, std::vector<Center> centers, unsigned int iterations = 1);

    SLICConfig& config;
};

void convertRGBtoLAB(const QImage& image, std::vector<std::vector<LAB>>& output);

#endif // SLIC_H
