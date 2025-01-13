#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Sprite& spriteObject, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Sprite* spriteObject;
    Ui::MainWindow *ui;
    void setUiState(bool isDisabled); // Enables or disables all UI funcitonality except for load and create files.
    enum Tool{pen, eraser, eyedrop, mirror};

signals:
    void createNewSprite();

public slots:
    void updateCurrentFrame(frame *currentFrame, frame *newFrame);
    void updateFramePreview(frame *currentFrame, frame *nextFrame);
    void clearFramePreview();
};
#endif // MAINWINDOW_H
