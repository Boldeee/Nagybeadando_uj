#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <cmath>
using namespace std;

struct Coordinate {
    int x;
    int y;

    Coordinate(int _x, int _y) {
        x = _x;
        y = _y;
    }
    Coordinate() {
        x = 0;
        y = 0;
    }
};


class PathFinder
{
    vector<vector<int>> fieldmatrix;
    Coordinate origin;
    Coordinate final;

public:
    PathFinder(int x_size, int y_size);

    void setValue(int x, int y, int val);
    int getValue(int x, int y);
    void setOrigin(Coordinate _origin);
    void setFinal(Coordinate _final);
    void getPath(vector<Coordinate> &shortestPath,
                 vector<Coordinate> &discoveredFields);

};

#endif // PATHFINDER_H
