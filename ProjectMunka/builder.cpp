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
    case Prodcuer_Green:
        basicImage.fill(Qt::green);
        break;
    case consumer:
        basicImage.fill(Qt::black);
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
