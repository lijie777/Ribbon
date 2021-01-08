#include "MainWindow.h"
#include <QApplication>
#include <QElapsedTimer>
#include <QDebug>
#include <QPropertyAnimation>
#include "UITest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 0
	MainWindow w;
#else
	UITest  w;
#endif
    

    w.show();


    return a.exec();
}
