#ifndef ROUTEMAKER_H
#define ROUTEMAKER_H
#include <QVector>
//#include "mainwindow.h"

struct Coord {
    int x; int y;

       Coord(int _x, int _y)
       {
        x = _x;
        y = _y;
       }
        Coord() {
        x = 0;
        y = 0;
    }
};

class RouteMaker
{
    QVector<QVector<int>> field;
    Coord start;
    Coord end;

public:

    RouteMaker(int xmeret,int ymeret);
    /*{
    field= QVector<QVector<int>>(ymeret , QVector<int>(xmeret, 0));
    start = {0,0};
    end= {xmeret-1,ymeret-1};
    }*/
 //   RouteMaker(int xmeret, int ymeret);
    int XX,YY;

    void setStart(const Coord &newStart);
    void setFieldmezo(int x, int y);
    void antisetFieldmezo(int x, int y);
    void setEnd(const Coord &newEnd);
    void getPath(QVector<Coord> &shortestPath,
                 QVector<Coord> &discoveredFields);

    void setField(const QVector<QVector<int> > &newField);
    /* PathFinder(int x_size, int y_size);
    void setOrigin(Coordinate _origin);
    void setFinal(Coordinate _final);
    void getPath(vector<Coordinate> &shortestPath,
                 vector<Coordinate> &discoveredFields);
    void setValue(int x, int y, int val);
    int getValue(int x, int y);*/
    const QVector<QVector<int> > &getField() const;
};

#endif // ROUTEMAKER_H
