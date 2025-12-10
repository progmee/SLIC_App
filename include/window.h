#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QDesktopServices>
#include <QUrl>

#include "slic.h"
#include <QImage>
#include <QDebug>

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

    QImage loadImage(const QString& path);
    SLICConfig getConfig();
    void renderImage();
    void redirectToBrowser();

private:
    const QUrl url = QUrl("https://github.com/progmee/SLIC_App");

    QGraphicsScene scene;    // убрал указатель
    QImage image;            // убрал указатель
    SLIC slic;               // убрал указатель

    Ui::Window *ui;
};

#endif // WINDOW_H
