#ifndef BUILDER_H
#define BUILDER_H


#include <QObject>
#include <QWidget>
#include <QLabel>

class Builder : public QLabel
{
    Q_OBJECT
public:
    explicit Builder(int x, int y, int _size);
    enum Function {
        //base, producer, consumer, conveyor,
        base,  conveyor, consumer,  Producer_Red /*wall volt*/, Prodcuer_Green /*selected volt*/,  Producer_Blue /*origin volt*/,
    };
    void setFunction(Function f);
    Function getFunction() const;
    int getX() const;
    int getY() const;

signals:
    void clicked(int x, int y, Qt::MouseButton m);
    void hovered(int x, int y);

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent *event);
    void drawPicture();
    int id_x;
    int id_y;
    int size;
    Function function;
    QPixmap basicImage;

};


#endif // BUILDER_H
