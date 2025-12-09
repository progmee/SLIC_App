#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsView>

class ImageView : public QGraphicsView {
private:
    const double zoomStep = .1; // Step for scaling
    const double minZoom = 0.1;
    const double maxZoom = 10.;

    double currentZoom = 1.;
    bool draging;
    QPoint mousePos;
};

#endif // IMAGE_H
