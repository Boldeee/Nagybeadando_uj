#ifndef ROUTEMAKER_H
#define ROUTEMAKER_H
#include "mainwindow.h"

class RouteMaker
{

    //vector<vector<int>> fieldmatrix;
    //Coordinate origin;
    //Coordinate final;
    QVector<QVector<int>> field;
    MainWindow::Informacio start;
    MainWindow::Informacio end;

public:
   /* PathFinder(int x_size, int y_size);

    void setValue(int x, int y, int val);
    int getValue(int x, int y);
    void setOrigin(Coordinate _origin);
    void setFinal(Coordinate _final);
    void getPath(vector<Coordinate> &shortestPath,
                 vector<Coordinate> &discoveredFields);*/
    RouteMaker(int XX, int YY);

    void setStart(const MainWindow::Informacio &newStart);
    void setEnd(const MainWindow::Informacio &newEnd);
    void getPath(QVector<MainWindow::Informacio> &shortestPath,
                 QVector<MainWindow::Informacio> &discoveredFields);
    const MainWindow::Informacio &getEnd() const;
};

#endif // ROUTEMAKER_H
