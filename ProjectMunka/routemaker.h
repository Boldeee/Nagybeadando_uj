#ifndef ROUTEMAKER_H
#define ROUTEMAKER_H
#include <QVector>
//#include "mainwindow.h"

struct Coord {
    int x; int y;

       Coord(int _x, int _y) {
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
    int XX;
    int YY;


    QVector<QVector<int>> field;
    Coord start;
    Coord end;


public:
    RouteMaker(int XX, int YY);
   /* PathFinder(int x_size, int y_size); 
    void setOrigin(Coordinate _origin);
    void setFinal(Coordinate _final);
    void getPath(vector<Coordinate> &shortestPath,
                 vector<Coordinate> &discoveredFields);
    void setValue(int x, int y, int val);
    int getValue(int x, int y);*/
    void setStart(const Coord &newStart);
    void setEnd(const Coord &newEnd);
    void getPath(QVector<Coord> &shortestPath,
                 QVector<Coord> &discoveredFields);

};

#endif // ROUTEMAKER_H
