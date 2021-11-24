#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class Field : public QLabel
{
    Q_OBJECT
public:
    explicit Field(int x, int y, int _size);
    enum Function {
        base, origin, end, way, wall, selected
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

#endif // FIELD_H
