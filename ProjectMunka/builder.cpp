#include "builder.h"

Builder::Builder(int x, int y, int _size) : QLabel()
{
    id_x = x;
    id_y = y;
    size = _size;
    basicImage = QPixmap(size, size);
}

void Builder::drawPicture()
{

    switch (function) {
    case Producer_Blue://
        basicImage.fill(Qt::blue);
        break;
    case conveyor:
        basicImage.fill(Qt::yellow);
        break;
    case base:
        basicImage.fill(Qt::white);
        break;
    case Producer_Red:
        basicImage.fill(Qt::red);
        break;
    case Producer_Green:
        basicImage.fill(Qt::green);
        break;
    case Consumer:
        basicImage.fill(Qt::black);
        break;
    case way:
        basicImage.fill(Qt::darkMagenta);
        break;
    case wayR:
        basicImage.fill(Qt::darkRed);
        break;
    case wayG:
        basicImage.fill(Qt::darkGreen);
        break;
    case wayB:
        basicImage.fill(Qt::darkBlue);
        break;
    case selected:
        basicImage.fill((Qt::gray));
        break;
    case convR:
        basicImage.fill((Qt::red));
        break;
    case convG:
        basicImage.fill((Qt::green));
        break;
    case convB:
        basicImage.fill((Qt::blue));
        break;
    case convRG:
        basicImage.fill((Qt::yellow));
        break;
    case convRB:
        basicImage.fill((Qt::magenta));
        break;
    case convGB:
        basicImage.fill((Qt::cyan));
        break;
    case convW:
        basicImage.fill((Qt::white));
        break;
        }
    setPixmap(basicImage.scaled(size,size));
}

int Builder::getY() const
{
    return id_y;
}

int Builder::getX() const
{
    return id_x;
}

void Builder::setFunction(Function f)
{
    function = f;
    drawPicture();
}


Builder::Function Builder::getFunction() const
{
    return function;
}

/*void Builder::mousePressEvent(QMouseEvent *event) Ötletem sincs mit csinál, talán a klikkelő interaktiv felulet egy resze de nekunk sztem nem kell
{
    emit clicked(id_x, id_y, event->button());
    event->ignore();
}

void Builder::enterEvent(QEvent *event){
    emit hovered(id_x, id_y);
    event->accept();
}
*/
