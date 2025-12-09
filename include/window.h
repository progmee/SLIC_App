#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>

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

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    QGraphicsScene* scene;

    QImage loadImage(QString path);
    void renderImage(QImage image);

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
