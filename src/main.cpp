#include "window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Connect style to UI
    QFile file(":/resource/customStyle.qss");
    file.open(QFile::ReadOnly);
    qApp->setStyleSheet(file.readAll());

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SLIC_App_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    Window w;
    w.show();
    return a.exec();
}
