#ifndef BUILDER_H
#define BUILDER_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include<QPainter>

class Builder : public QLabel
{
    Q_OBJECT
public:
    QString stats;
    explicit Builder(int x, int y, int _size);
    enum Function {
        //base, producer, consumer, conveyor,
        base,  conveyor, Consumer,  Producer_Red /*wall volt*/, Producer_Green /*selected volt*/,  Producer_Blue /*origin volt*/, way, selected,
        convR,convG,convB,convRG,convRB,convGB,convW,
        wayR,wayG,wayB,
    };

    void setFunction(Function f);
    Function getFunction() const;
    int getX() const;
    int getY() const;
    void setszalagFunction(Function f);
/*signals:
    void clicked(int x, int y, Qt::MouseButton m);
    void hovered(int x, int y);*/

protected:
    //void mousePressEvent(QMouseEvent* event);
    //void enterEvent(QEvent *event);
    void drawPicture();
    int id_x;
    int id_y;
    int size;
    Function function;
    QPixmap basicImage;

};


#endif // BUILDER_H
