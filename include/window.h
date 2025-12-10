#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QDesktopServices>
#include <QUrl>
#include <QImage>
#include <QDebug>
#include <QTranslator>

#include "slic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

private slots:
    void onActionOpenImage();
    void on_ApplyButton_clicked();
public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:
    const QUrl url = QUrl("https://github.com/progmee/SLIC_App");
    const QString translationsPath = ":/resource/i18n/SLIC_App_";

    QGraphicsScene scene;
    QImage image;
    SLIC slic;
    QTranslator translator;

    Ui::Window *ui;

    QImage loadImage(const QString& path);
    SLICConfig getConfig();
    void redirectToBrowser();

    void applyTranslation(const QString& langCode);
};

#endif // WINDOW_H
