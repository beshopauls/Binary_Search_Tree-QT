#include "renderarea.h"
#include <QApplication>
#include <QPainter>
#include <qglobal.h>
#include <QTime>
#include <QPen>

RenderArea::RenderArea(BinarySearchTree<int> *bst, QWidget *parent) : QWidget(parent), bst(),
    scale(1.0)
{
    this->bst = bst;
    this->scale = 1;
    this->nodeColor = Qt::green;
    this->backgroundColor = Qt::gray;
    this->textColor = Qt::black;
}
QSize RenderArea::sizeHint() const
{
    return QSize(50, 50);
}
QSize RenderArea::minimumSizeHint() const
{
    return QSize(50, 50);
}
void RenderArea::paintEvent(QPaintEvent *  event )
{
    if (this->bst->isEmpty())
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush;
    brush.setColor(this->nodeColor);
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setColor(this->textColor);
    painter.setBrush(brush);
    painter.setPen(pen);
    this->bst->draw(&painter, this->scale);
    this->autoSize();
}
void RenderArea::callRepaint()
{
    if (this->bst->isEmpty())
        return;
    this->scale += 0.1;
    this->repaint();
    this->scale -= 0.1;
    this->repaint();
}

void RenderArea::autoSize() {
    QSize size(bst->getTotalX(), bst->getTotalY());
    this->setMinimumSize(size);
    this->resize(size);
}

