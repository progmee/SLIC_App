#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QDesktopServices>
#include <QUrl>

#include "slic.h"

// Debug tools
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

    QImage loadImage(QString path);
    void renderImage(QImage image);
    SLICConfig getConfig();

    void redirectToBrowser();

private:
    const QUrl url = QUrl("https://github.com/progmee/SLIC_App");

    QGraphicsScene* scene;
    SLIC* slic;
    Ui::Window *ui;
};
#endif // WINDOW_H
