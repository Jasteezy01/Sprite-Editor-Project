#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QVector>
#include "frame.h"

class Sprite : public QObject
{
private: // Data Structure to house frames
    QVector<frame*> frameSequence;
    int currentFrameIndex;
    frame* currentFrame = nullptr;


    Q_OBJECT
public:
    explicit Sprite(QObject *parent = nullptr);
    Sprite(Sprite& toCopy);
    enum Tool{pen, eraser, eyedrop, mirror};


signals:
    void updateCurrentFrame(frame *currentFrame, frame *newFrame);
    void updateSpritePreview(frame *currentFrame, frame *nextFrame);
    void endSpritePreview();

public slots:
    void spritePreview();
    void spawnSprite();
    void saveSprite();
    void loadSprite();

    void addFrame();
    void deleteFrame();
    void copyFrame();
    void clearFrame();

    void setTool(Tool newTool);
    void setColor(QColor newColor);

    friend class frame;
};

#endif // SPRITE_H
