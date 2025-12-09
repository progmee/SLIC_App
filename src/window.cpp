#include "window.h"
#include "ui_window.h"

void Window::onActionOpenImage() {
    qDebug() << "Button pressed";
}

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this); // Init UI

    // Connection of event
    connect(ui->actionOpenImage, &QAction::triggered, this, &Window::onActionOpenImage);
}
//QImage image("assets/images");
Window::~Window()
{
    delete ui;
}
