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

void Window::redirectToBrowser() {
    // Redirect to github
    QDesktopServices::openUrl(url);
}

SLICConfig Window::getConfig() {
    SLICConfig config(
        ui->IterationsBox->value(),
        ui->PixelsBox->value(),
        (double) (ui->CompactnessBox->value()),
        (double) (ui->BoundariesBox->isChecked())
    );

    return config;
}

Window::Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Window), slic(new SLIC()), scene(new QGraphicsScene) {
    ui->setupUi(this); // Init UI

    // Set scene for graphics view
    ui -> GraphicsView -> setScene(scene);

    // Connecting events
    connect(ui->actionSupportUs, &QAction::triggered, this, &Window::redirectToBrowser);
    connect(ui->actionOpenImage, &QAction::triggered, this, &Window::onActionOpenImage);
}

void Window::on_ApplyButton_clicked() {
    // Get config from input fields
    SLICConfig config = getConfig();

    slic->setConfig(config); // Set config for slic algorithm
}

Window::~Window() {
    // Remove objects
    delete ui;
    delete scene;
    delete slic;
}

