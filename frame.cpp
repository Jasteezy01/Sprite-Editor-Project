#include "frame.h"
#include <QGraphicsScene>

frame::frame(QWidget *parent)
    : QGraphicsView(parent), frameData(704, 448)
{
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frameData.fill(Qt::white);
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    frameItem = new QGraphicsPixmapItem(frameData);
    scene->addItem(frameItem);

    currentTool = pen;
    currentColor = Qt::black;
}

frame::frame(const frame &toCopy)
    : QGraphicsView(toCopy.parentWidget()), frameData(toCopy.frameData), isDragging(toCopy.isDragging)
{

    // Create a new scene and item
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    frameItem = new QGraphicsPixmapItem(frameData);  // Create a new item with copied pixmap
    scene->addItem(frameItem);

    // Apply the same scale
    setTransform(toCopy.transform());

    currentTool = pen;
    currentColor = Qt::black;
}

frame& frame::operator=(const frame &toCopy) {
    if (this == &toCopy) {
        return *this;
    }

    // Copy frameData
    frameData = toCopy.frameData;

    // Delete the old frameItem and create a new one with the copied pixmap
    if (frameItem) {
        delete frameItem;
    }
    frameItem = new QGraphicsPixmapItem(frameData);
    scene()->addItem(frameItem);  // Add the new frameItem to the scene

    isDragging = false;

    // Copy the scale
    setTransform(toCopy.transform());

    currentTool = pen;
    currentColor = Qt::black;

    return *this;
}


void frame::mousePressEvent(QMouseEvent *event)
{

    QPointF framePos = mapToScene(event->pos());
    int x = framePos.x();
    int y = framePos.y();

    if (currentTool == pen || currentTool == eraser) {
        isDragging = true;
        QColor color = (currentTool == pen) ? currentColor : Qt::white;

        updatePixelColor(x, y, color);
    }
    else if(currentTool == eyedrop)
    {
        getPixelColor(x, y);
    }
    else if(currentTool == mirror)
    {
        isDragging = true;

        updatePixelColor(x, y, currentColor); // draw initial pixel
        updatePixelColor((704/64) - x, y, currentColor);
    }

    QGraphicsView::mousePressEvent(event);
}

void frame::mouseMoveEvent(QMouseEvent *event)
{

    QPointF framePos = mapToScene(event->pos());
    int x = framePos.x();
    int y = framePos.y();

    if (isDragging && (currentTool == pen || currentTool == eraser)) {
        QColor color = (currentTool == pen) ? currentColor : Qt::white;

        updatePixelColor(x, y, color);
    }
    else if(isDragging && currentTool == mirror)
    {
        updatePixelColor(x, y, currentColor); // draw initial pixel
        updatePixelColor((704/64) - x, y, currentColor);
    }

    QGraphicsView::mouseMoveEvent(event);
}

void frame::mouseReleaseEvent(QMouseEvent *event)
{
    if (currentTool == pen || currentTool == eraser || currentTool == mirror) {
        isDragging = false;
    }

    QGraphicsView::mouseReleaseEvent(event);
}


void frame::updatePixelColor(int x, int y, const QColor &color)
{
    QImage image = frameData.toImage();

    if(x >= 0 && x < image.width() && y >= 0 && y < image.height())
    {
        image.setPixelColor(x, y, color);

        frameData = QPixmap::fromImage(image);
        frameItem->setPixmap(frameData);
    }
}

void frame::getPixelColor(int x, int y)
{
    QImage image = frameData.toImage();
    qDebug()<<x<<", "<<y;

    if(x >= 0 && x < image.width() && y >= 0 && y < image.height())
    {
        currentColor = image.pixelColor(x, y);
        qDebug()<<"Current color: "<< currentColor;
    }
}

void frame::scrollContentsBy(int, int)
{
    //do nothing to turn off scrolling
}

void frame::clear() {
    // Fill the frameData pixmap with white
    frameData.fill(Qt::white);

    // Update the QGraphicsPixmapItem to reflect the cleared frameData
    frameItem->setPixmap(frameData);
}
