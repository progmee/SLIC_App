#include "window.h"
#include "ui_window.h"

void Window::onActionOpenImage() {
    QString imagePath = QFileDialog::getOpenFileName(
        this,
        "Open Image",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp)");

    QImage image = loadImage(imagePath);
    renderImage(image); // Render image
}

QImage Window::loadImage(QString path) {
    if (path.isEmpty()) {
        qWarning() << "Incorrect path for loadImage.";
        return QImage();
    }

    QImage image(path); // Initialize image

    if (image.isNull()) {
        qWarning() << "Failed to load image.";
    }

    return image;
}

void Window::renderImage(QImage image) {
    if (image.isNull()) return;

    scene->clear();

    // Convert image to pixmap
    QPixmap pixmap = QPixmap::fromImage(image);

    // Pixmap pointer from scene
    QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
    scene->setSceneRect(item->boundingRect());

    // Centralize image
    ui->GraphicsView->fitInView(item, Qt::KeepAspectRatio);
}

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this); // Init UI

    // Declare scene and connect with existing object
    scene = new QGraphicsScene();
    ui -> GraphicsView -> setScene(scene);

    // Connection of event
    connect(ui->actionOpenImage, &QAction::triggered, this, &Window::onActionOpenImage);
}

Window::~Window()
{
    delete ui;
}
