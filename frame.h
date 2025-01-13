#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>


class frame : public QGraphicsView
{
    Q_OBJECT
public:
    explicit frame(QWidget *parent = nullptr);
    frame(const frame &toCopy);
    frame& operator=(const frame &toCopy);
    // Methods
    void clear();
    enum Tool{pen, eraser, eyedrop, mirror};
    Tool currentTool;
    QColor currentColor;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override; // Added for drag functionality
    void mouseReleaseEvent(QMouseEvent *event) override;
    void scrollContentsBy(int, int) override;

private:
    QPixmap frameData;
    QGraphicsPixmapItem *frameItem;
    bool isDragging = false;
    void updatePixelColor(int x, int y, const QColor &color);
    void getPixelColor(int x, int y);


signals:

};

#endif // FRAME_H
