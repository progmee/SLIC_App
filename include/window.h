#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>

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

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
