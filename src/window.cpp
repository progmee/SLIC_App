#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    qApp->installTranslator(&translator); // Install translator to application

    connect(ui->actionSupportUs, &QAction::triggered, this, &Window::redirectToBrowser);
    connect(ui->actionOpenImage, &QAction::triggered, this, &Window::onActionOpenImage);

    connect(ui->actionEnglish, &QAction::triggered, this, [this]() {
        applyTranslation("en_US");
    });
    connect(ui->actionFrench, &QAction::triggered, this, [this]() {
        applyTranslation("fr_FR");
    });
}

void Window::applyTranslation(const QString& langCode) {
    qApp -> removeTranslator(&translator);

    QString path = translationsPath + langCode + ".qm";

    if (translator.load(path)) {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
    else {
        qWarning() << "Failed to load a translation";
    }
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

    QImage __image(path);

    if (__image.isNull()) {
        qWarning() << "Failed to load image:" << path;
    }

    return __image;
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

    ui->ImageViewer->renderImage(image);
}

void Window::redirectToBrowser()
{
    QDesktopServices::openUrl(url);
}

SLICConfig Window::getConfig()
{
    SLICConfig config(
        ui->IterationsBox->value(),
        ui->SpacingBox->value(),
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

    if (!output.isValide() || !config.showBoundaries) return;

    QRgb color = qRgb(0, 128, 0); // Color in black
    QImage boundaries = drawBoundaries(output, image, color);

    ui->ImageViewer->renderImage(boundaries);
}
