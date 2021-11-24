#include "field.h"
#include <QMouseEvent>

Field::Field(int x, int y, int _size) : QLabel()
{
    id_x = x;
    id_y = y;
    size = _size;
    basicImage = QPixmap(size, size);
}

void Field::drawPicture()
{

    switch (function) {
    case origin:
        basicImage.fill(Qt::green);
        break;
    case way:
        basicImage.fill(Qt::yellow);
        break;
    case base:
        basicImage.fill(Qt::white);
        break;
    case wall:
        basicImage.fill(Qt::black);
        break;
    case selected:
        basicImage.fill(Qt::gray);
        break;
    case end:
        basicImage.fill(Qt::red);
        break;
    }

    setPixmap(basicImage.scaled(size,size));

}

int Field::getY() const
{
    return id_y;
}

int Field::getX() const
{
    return id_x;
}

void Field::setFunction(Function f)
{
    function = f;
    drawPicture();
}

Field::Function Field::getFunction() const
{
    return function;
}

void Field::mousePressEvent(QMouseEvent *event)
{
    emit clicked(id_x, id_y, event->button());
    event->ignore();
}

void Field::enterEvent(QEvent *event){
    emit hovered(id_x, id_y);
    event->accept();
}


