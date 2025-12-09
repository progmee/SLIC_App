#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsView>
#include <QWidget>
#include <QWheelEvent>
#include <QScrollBar>
#include <QGraphicsPixmapItem>

class ImageView : public QGraphicsView {
private:
    const double stepZoom = .1; // Step for scaling

    // Rangs for zoom
    const double minZoom = 0.1;
    const double maxZoom = 10.;

    double zoom = 1.;
    bool drag = false;

    // Save last mouse position
    QPoint lastMousePos;
protected:
    // Mouse events
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    ImageView(QWidget* parent = nullptr);
};

#endif // IMAGE_H
