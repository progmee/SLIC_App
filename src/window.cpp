#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    // Назначаем сцену графическому виджету
    ui->GraphicsView->setScene(&scene);

    // Подключаем сигналы
    connect(ui->actionSupportUs, &QAction::triggered, this, &Window::redirectToBrowser);
    connect(ui->actionOpenImage, &QAction::triggered, this, &Window::onActionOpenImage);
}

Window::~Window()
{
    delete ui;
}

QImage Window::loadImage(const QString& path)
{
    if (path.isEmpty()) {
        qWarning() << "Incorrect path for loadImage.";
        return QImage();
    }

    QImage img(path);

    if (img.isNull()) {
        qWarning() << "Failed to load image:" << path;
    }

    return img; // безопасно, без указателей
}

void Window::onActionOpenImage()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Open Image",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    image = loadImage(path);

    if (image.isNull()) {
        return;
    }

    renderImage();
}

void Window::renderImage()
{
    if (image.isNull())
        return;

    scene.clear();

    QPixmap pixmap = QPixmap::fromImage(image);
    QGraphicsPixmapItem* item = scene.addPixmap(pixmap);

    scene.setSceneRect(item->boundingRect());
    ui->GraphicsView->fitInView(item, Qt::KeepAspectRatio);
}

void Window::redirectToBrowser()
{
    QDesktopServices::openUrl(url);
}

SLICConfig Window::getConfig()
{
    SLICConfig config(
        ui->IterationsBox->value(),
        ui->PixelsBox->value(),
        ui->CompactnessBox->value(),
        ui->BoundariesBox->isChecked()
        );

    return config;
}

void Window::on_ApplyButton_clicked()
{
    if (image.isNull()) {
        qWarning() << "Cannot apply SLIC: no image loaded.";
        return;
    }

    SLICConfig config = getConfig();
    slic.setConfig(config);

    SLICOutput output = slic.apply(image);

    // later: draw boundaries here
}

