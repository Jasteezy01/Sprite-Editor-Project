

#include "mainwindow.h"

#include <QApplication>
#include "sprite.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sprite spriteObject;
    MainWindow w(spriteObject);
    w.show();
    return a.exec();




    // QApplication a(argc, argv);
    // SimonGameModel gameModel;
    // MainView w(gameModel);
    // w.show();
    // return a.exec();
}
