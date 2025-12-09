#include "image.h"

ImageView::ImageView(QWidget* parent) : QGraphicsView(parent) {
    // Disable scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
};

void ImageView::wheelEvent(QWheelEvent *event) {
    QPoint delta = event->angleDelta();

    // Change zoom and check for limits
    if (delta.y() > 0 && zoom + stepZoom < maxZoom) zoom += stepZoom;
    else if (delta.y() < 0 && zoom - stepZoom > minZoom) zoom -= stepZoom;

    resetTransform();

    double scaleRatio = std::clamp(zoom, minZoom, maxZoom);

    scale(scaleRatio, scaleRatio);
}

void ImageView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        drag = true; // Change drag flag value
        lastMousePos = event->pos();
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) drag = false; // Change drag flag value
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    // While image drag
    if (drag) {
        QPoint mousePos = event->pos();

        QPoint delta = mousePos - lastMousePos;

        // Chagne horizontal and vertical positions
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue( verticalScrollBar()->value() - delta.y() );

        lastMousePos = mousePos;
    }
}
