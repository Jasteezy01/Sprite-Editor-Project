#include "sprite.h"
#include "frame.h"
#include <QDebug> // for testing, delete before submission
#include <QTimer>

Sprite::Sprite(QObject *parent) : QObject(parent) {
}

Sprite::Sprite(Sprite& toCopy) {
    // TODO Implement
}

//Todo implement destructor

void Sprite::spritePreview()
{
    emit endSpritePreview();
    QVector<frame*> framesCopy;
    for (frame* f : frameSequence) {
        framesCopy.append(new frame(*f));  // Assuming frame has a copy constructor
    }  // Make a local copy to avoid access issues
    for(int frameIndex = 0; frameIndex <= framesCopy.size(); frameIndex++){
        int delay = frameIndex * 1000;  // Calculate delay for each frame in milliseconds

        QTimer::singleShot(delay, [this, frameIndex, framesCopy]() {
            if (frameIndex == 0) {
                emit updateSpritePreview(nullptr, framesCopy.at(frameIndex));
            }
            else if (frameIndex == framesCopy.size()) {
                qDebug()<<"we are on last frame preview";
                emit updateSpritePreview(framesCopy.at(frameIndex-1), framesCopy.at(0));
            }
            else {
                emit updateSpritePreview(framesCopy.at(frameIndex - 1), framesCopy.at(frameIndex));
            }
        });
    }
}



void Sprite::addFrame() {
    frame *f = new frame();
    frameSequence.push_back(f); //TODO: check this syntax
    currentFrameIndex = frameSequence.size()-1;
    emit updateCurrentFrame(currentFrame, frameSequence.at(currentFrameIndex));
    currentFrame = f;
}

void Sprite::deleteFrame() {
    emit updateCurrentFrame(currentFrame, frameSequence.at(currentFrameIndex-1));
    delete frameSequence[currentFrameIndex];
    frameSequence.removeAt(currentFrameIndex);
    currentFrameIndex--;
    currentFrame = frameSequence[currentFrameIndex];
}

void Sprite::copyFrame() {
    frame* f = new frame(*currentFrame);
    frameSequence.push_back(f); //TODO: check this syntax
    currentFrameIndex = frameSequence.size()-1;
    emit updateCurrentFrame(currentFrame, frameSequence.at(currentFrameIndex));
    currentFrame = f;
}

void Sprite::clearFrame() {
    currentFrame->clear();
}

void Sprite::spawnSprite() {
    frame *f = new frame();
    frameSequence.push_back(f);
    currentFrameIndex = 0;
    emit updateCurrentFrame(currentFrame, frameSequence.at(currentFrameIndex));
    currentFrame = f;
}

void Sprite::setTool(Tool newTool){
    switch(newTool){
        case pen:{
            currentFrame->currentTool = frame::pen;
            qDebug()<<"Current tool: pen";
            break;
        }
        case eraser:{
            currentFrame->currentTool = frame::eraser;
            qDebug()<<"Current tool: eraser";
            break;
        }
        case eyedrop:{
            currentFrame->currentTool = frame::eyedrop;
            break;
        }
        case mirror:{
            currentFrame->currentTool = frame::mirror;
            break;
        }
        default:
            break;
    }
}

void Sprite::setColor(QColor newColor){
    currentFrame->currentColor = newColor;
}
void Sprite::saveSprite() {
}

void Sprite::loadSprite() {
}
