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

    }
    setPixmap(basicImage.scaled(size,size));

}
void Builder::drawszalagra()
{
    QPainter doboz(&basicImage);
    QRect dobozka;
    dobozka.setHeight(30);
    dobozka.setWidth(30);
    //dobozka.setCoords(x-10,y-10,x+10,y+10);

    switch (function) {
    case convR:
        doboz.setBrush(Qt::red);
        doboz.drawRect(dobozka);
        break;
    case convG:
        doboz.setBrush(Qt::green);
        doboz.drawRect(dobozka);
        break;
    case convB:
        doboz.setBrush(Qt::blue);
        doboz.drawRect(dobozka);
        break;
    case convRG:
        doboz.setBrush(Qt::yellow);
        doboz.drawRect(dobozka);
        break;
    case convRB:
        doboz.setBrush(Qt::magenta);
        doboz.drawRect(dobozka);
        break;
    case convGB:
        doboz.setBrush(Qt::cyan);
        doboz.drawRect(dobozka);
        break;
    case convW:
        doboz.setBrush(Qt::white);
        doboz.drawRect(dobozka);
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
        }
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
void Builder::setszalagFunction(Function f)
{
    function=f;
    drawszalagra();
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
