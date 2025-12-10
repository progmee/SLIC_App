#include "slic.h"

std::vector<Center> SLIC::initializeCenters(const std::vector<std::vector<LAB>>& pixels) {
    // Initialize centers
    std::vector<Center> centers;

    int width = pixels[0].size();
    int height = pixels.size();

    // Pixel spacing
    config.spacing = sqrt((width * height) / config.superpixels);

    for (int y = config.spacing/2; y < height; y += config.spacing) {
        for (int x = config.spacing/2; x < height; x += config.spacing) {
            // Avoid cases when created more superpixels than required
            if (centers.size() >= config.superpixels)
                break;

            centers.push_back(
                Center(QPoint(x, y), pixels[y][x])
            );
        }

        // Avoid cases when created more superpixels than required
        if (centers.size() >= config.superpixels)
            break;
    }

    return centers;
}

double SLIC::distance(const Center& c1, const Center& c2) {
    double dl = c1.colour.l - c2.colour.l;
    double da = c1.colour.a - c2.colour.a;
    double dc = c1.colour.b - c2.colour.b;

    double deltaColour = (dl * dl) + (da * da) + (dc * dc);

    double dx = c1.position.x() - c2.position.x();
    double dy = c1.position.y() - c2.position.y();

    double deltaSpace = (dx * dx) + (dy * dy);
    double ratio = (config.compactness / config.spacing) * (config.compactness / config.spacing); // Ratio of compactness and spacing

    // Calculate Delta E
    return sqrt(
        deltaColour + ratio * deltaSpace
    );
}

SLICOutput SLIC::apply(const QImage& image) {
    // Avoid null image
    if (image.isNull()) {
        return SLICOutput();
    }

    // Save pixels in LAB format
    std::vector<std::vector<LAB>> pixels(image.height(), std::vector<LAB>(image.width()));
    convertRGBtoLAB(image, pixels); // Convert image to pixels in LAB format

    // Initialize centers
    std::vector<Center> centers = initializeCenters(pixels);
    std::vector<int> labels = SLIC::kMeans(pixels, centers, config.iterations); // Group clusters with kMeans method

    SLICOutput output;

    // Fill output data
    output.labels = labels;
    output.height = image.height(); output.width = image.width();

    return output;
}

std::vector<int> SLIC::kMeans(const std::vector<std::vector<LAB>>& pixels, std::vector<Center> centers, unsigned int iterations)
{
    int width  = pixels[0].size();
    int height = pixels.size();

    std::vector<int> labels(width * height, -1);
    std::vector<double> distances(width * height, std::numeric_limits<double>::infinity());

    std::vector<Center> accumulators(centers.size());
    std::vector<int> count(centers.size(), 0);

    for (int iteration = 0; iteration < iterations; iteration++) {

        std::fill(distances.begin(), distances.end(), std::numeric_limits<double>::infinity());

        for (int i = 0; i < centers.size(); i++) {

            QPoint center = centers[i].position;

            int ymin = std::max(0, static_cast<int>(center.y() - config.spacing));
            int ymax = std::min(height, static_cast<int>(center.y() + config.spacing));
            int xmin = std::max(0, static_cast<int>(center.x() - config.spacing));
            int xmax = std::min(width, static_cast<int>(center.x() + config.spacing));

            for (int y = ymin; y < ymax; y++) {
                for (int x = xmin; x < xmax; x++) {

                    int index = y * width + x;

                    double d = distance(
                        centers[i],
                        Center(QPoint(x, y), pixels[y][x])
                        );

                    if (d < distances[index]) {
                        distances[index] = d;
                        labels[index] = i;
                    }
                }
            }
        }

        std::fill(count.begin(), count.end(), 0);

        for (auto &acc : accumulators) {
            acc.colour.l = 0;
            acc.colour.a = 0;
            acc.colour.b = 0;
            acc.position.setX(0);
            acc.position.setY(0);
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                int index  = y * width + x;
                int c = labels[index];

                accumulators[c].colour.l += pixels[y][x].l;
                accumulators[c].colour.a += pixels[y][x].a;
                accumulators[c].colour.b += pixels[y][x].b;

                accumulators[c].position.setX(accumulators[c].position.x() + x);
                accumulators[c].position.setY(accumulators[c].position.y() + y);

                count[c]++;
            }
        }

        for (int i = 0; i < centers.size(); i++) {
            if (count[i] > 0) {
                accumulators[i].colour.l /= count[i];
                accumulators[i].colour.a /= count[i];
                accumulators[i].colour.b /= count[i];

                accumulators[i].position.setX(accumulators[i].position.x() / count[i]);
                accumulators[i].position.setY(accumulators[i].position.y() / count[i]);
            }
        }
    }

    return labels;
}


void convertRGBtoLAB(const QImage& image, std::vector<std::vector<LAB>>& output) {
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb rgb = image.pixel(x, y);

            // Convert rgb to LAB and store it inside of vector
            output[y][x] = LAB(qRed(rgb), qGreen(rgb), qBlue(rgb));
        }
    }
}
