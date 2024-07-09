#include "mainwindow.h"
#include <QApplication>
#include "languagesettings.h"
#include "formsplash.h"
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FormSplash splash;
    QTimer::singleShot(5000, &splash, SLOT(close()));
    splash.exec();


    LanguageSettings lang;
    lang.exec();


    MainWindow w;
    w.show();
    return a.exec();
}
