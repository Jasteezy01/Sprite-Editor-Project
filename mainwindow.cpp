#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sprite.h"
#include <QColorDialog>

MainWindow::MainWindow(Sprite& spriteObject, QWidget *parent) : QMainWindow(parent), spriteObject(&spriteObject), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setUiState(true);

    // ------------------------------ Begin Connections ------------------------------
    //Connect New Sprite in Menu to spawnSprite in Model
    connect(ui->actionNew_Sprite, &QAction::triggered, &spriteObject, &Sprite::spawnSprite);

    connect(&spriteObject, &Sprite::updateCurrentFrame, this, &MainWindow::updateCurrentFrame);

    connect(ui->playPreviewBtn, &QPushButton::clicked, &spriteObject, &Sprite::spritePreview);

    connect(&spriteObject, &Sprite::updateSpritePreview, this, &MainWindow::updateFramePreview);

    connect(&spriteObject, &Sprite::endSpritePreview, this, &MainWindow::clearFramePreview);

    //Connect add frame button
    connect(ui->addFrameBtn, &QPushButton::clicked, &spriteObject, &Sprite::addFrame);

    // connect delete frame button
    connect(ui->deleteBtn, &QPushButton::clicked, &spriteObject, &Sprite::deleteFrame);

    // connect copy frame button
    connect(ui->copyBtn, &QPushButton::released, &spriteObject, &Sprite::copyFrame);

    // connect clear frame button
    connect(ui->clearBtn, &QPushButton::released, &spriteObject, &Sprite::clearFrame);

    connect(ui->penButton, &QPushButton::clicked, [&]() {
        spriteObject.setTool(Sprite::pen);
    });

    connect(ui->eraserBtn, &QPushButton::clicked, [&]() {
        spriteObject.setTool(Sprite::eraser);
    });

    connect(ui->eyedropperBtn, &QPushButton::clicked, [&]() {
        spriteObject.setTool(Sprite::eyedrop);
    });

    connect(ui->mirrorBtn, &QPushButton::clicked, [&](){
        spriteObject.setTool(Sprite::mirror);
    });

    connect(ui->colorBtn, &QPushButton::clicked, [&]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");

        if (color.isValid()) { // Check if the user selected a color
            spriteObject.setColor(color);
        }
    });

    //TODO: connecting slider
    //TODO: set slider ticks
    //connect(ui->frameRateSlider, &QSlider::sliderReleased, this, &MainWindow::sliderUpdate);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateCurrentFrame(frame *currentFrame, frame *newFrame)
{
    newFrame->resetTransform();
    newFrame->scale(64, 64);
    newFrame->setMaximumSize(704, 448);
    newFrame->setMinimumSize(704, 448);
    ui->frameLayout->removeWidget(currentFrame);
    ui->frameLayout->addWidget(newFrame);
    setUiState(false);
}

void MainWindow::updateFramePreview(frame *currentFrame, frame *nextFrame)
{
    nextFrame->resetTransform();
    nextFrame->scale(20, 20); //64/1.57=41
    nextFrame->setMaximumSize(200, 127);//200/1.57=127
    nextFrame->setMinimumSize(200, 127);
    ui->previewLayout->removeWidget(currentFrame);
    ui->previewLayout->addWidget(nextFrame);
    setUiState(false);
}

void MainWindow::clearFramePreview() {
    QLayoutItem *item;
    while ((item = ui->previewLayout->takeAt(0)) != nullptr) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();  // Schedule widget for deletion
        }
        delete item;  // Delete the layout item
    }
}



// ------------------------------------- Begin Helper Methods ---------------------------------- //
void MainWindow::setUiState(bool isDisabled) {
    ui->addFrameBtn->setDisabled(isDisabled);
    ui->frameRateSlider->setDisabled(isDisabled);
    ui->actionSave_File->setDisabled(isDisabled);
    //ui->canvas->setDisabled(isDisabled);
    ui->clearBtn->setDisabled(isDisabled);
    ui->colorBtn->setDisabled(isDisabled);
    ui->copyBtn->setDisabled(isDisabled);
    ui->deleteBtn->setDisabled(isDisabled);
    ui->eraserBtn->setDisabled(isDisabled);
    ui->eyedropperBtn->setDisabled(isDisabled);
    ui->penButton->setDisabled(isDisabled);
}
// -------------------------------------- End Helper Methods ----------------------------------- //
