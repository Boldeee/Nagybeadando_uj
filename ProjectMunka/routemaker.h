#ifndef ROUTEMAKER_H
#define ROUTEMAKER_H
#include <QVector>
//#include "mainwindow.h"
struct Informacio // initially egy üres bázist állit be mindenhova, majd azt változtatjuk
{
int x=-1,y=-1,r=0,g=0,b=0;
bool felhasznaltuk_e=false;
int freq=0;
int need_r=0;
int need_g=0;
int need_b=0;
    int need_r_g=0;//yellow
    int need_r_b=0;//magenta
    int need_g_b=0;//cyan
        int need_w=0;//feher
int ID=0;
int fogyasztoID=-1;
};

class RouteMaker
{
    int XX;
    int YY;
    /*RouteMaker(int mezox, int mezoy)
    {
        XX=mezox;
        YY=mezoy;
    };*/
    RouteMaker(int XX, int YY);
    struct Informacio // initially egy üres bázist állit be mindenhova, majd azt változtatjuk
    {
    int x=-1,y=-1,r=0,g=0,b=0;
    bool felhasznaltuk_e=false;
    int freq=0;
    int need_r=0;
    int need_g=0;
    int need_b=0;
        int need_r_g=0;//yellow
        int need_r_b=0;//magenta
        int need_g_b=0;//cyan
            int need_w=0;//feher
    int ID=0;
    int fogyasztoID=-1;
    };
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

    //vector<vector<int>> fieldmatrix;
    //Coordinate origin;
    //Coordinate final;
    QVector<QVector<int>> field;
    Informacio start;
    Informacio end;

public:

   /* PathFinder(int x_size, int y_size);

    void setValue(int x, int y, int val);
    int getValue(int x, int y);
    void setOrigin(Coordinate _origin);
    void setFinal(Coordinate _final);
    void getPath(vector<Coordinate> &shortestPath,
                 vector<Coordinate> &discoveredFields);*/

    void setStart(const Informacio &newStart);
    void setEnd(const Informacio &newEnd);
    void getPath(QVector<Coord> &shortestPath,
                 QVector<Coord> &discoveredFields);
    const Informacio &getEnd() const;
};

#endif // ROUTEMAKER_H
