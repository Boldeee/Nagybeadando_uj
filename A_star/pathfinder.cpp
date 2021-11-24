#include "pathfinder.h"
#include <cmath>
#include <list>
#include <queue>

#include <QDebug>


PathFinder::PathFinder(int x_size, int y_size):
   origin(0,0), final(x_size-1, y_size-1)
{
    fieldmatrix = std::vector<std::vector<int>>(y_size, std::vector<int>(x_size,0));
}

void PathFinder::setValue(int x, int y, int val)
{
    fieldmatrix[x][y] = val;
}

int PathFinder::getValue(int x, int y)
{
    return fieldmatrix[x][y];
}

void PathFinder::setOrigin(Coordinate _origin)
{
    origin = _origin;
}

void PathFinder::setFinal(Coordinate _final)
{
    final = _final;
}

struct rovidut{
    int xbol,ybol,tav;
    rovidut()
    {
        xbol=0,ybol=0,tav=INT_MAX;
    }
    rovidut(int _xbol,int _ybol,int _tav)
    {
        xbol=_xbol,ybol=_ybol,tav=_tav;
    }
};
struct State{
    int x,y,heurvalue,tavolsag;
    State(int _x,int _y,int _tavolsag)
    {
        x=_x;
        y=_y;
        tavolsag=_tavolsag;
    }
    void setheurvalue(Coordinate final)
    {
        heurvalue=abs(final.x-x)+abs(final.y-y);
    }
};

bool operator<(State const &s1,State const &s2)
{
    return s1.tavolsag+s1.heurvalue>s2.tavolsag+s2.heurvalue;
}
void PathFinder::getPath(vector<Coordinate> &shortestPath, vector<Coordinate> &discoveredFields)
{
    int size_x=fieldmatrix[0].size();
    int size_y=fieldmatrix.size();

    vector<vector<rovidut>> utmatrix(size_y,vector<rovidut>(size_x));
    utmatrix[origin.x][origin.y]=rovidut(origin.x,origin.y,0);

    priority_queue<State> stateQueue;
    State initState(origin.x,origin.y,0);
    stateQueue.push(initState);

    while(stateQueue.size()>0)
    {
        State actualstate =stateQueue.top();
        stateQueue.pop();
        discoveredFields.push_back(Coordinate(actualstate.x,actualstate.y));

        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1;j++)
            {
                if(i==0||j==0)
                {
                    int newX=actualstate.x+i;
                    int newY=actualstate.y+j;
                    if(       newX>=0
                            &&newY>=0
                            &&newX<size_x
                            &&newY<size_y
                            &&fieldmatrix[newX][newY]==0
                            &&utmatrix[newX][newY].tav>actualstate.tavolsag+1)
                    {

                        State newstate(newX,newY,actualstate.tavolsag+1);
                        newstate.setheurvalue(final);
                        utmatrix[newX][newY]=rovidut(actualstate.x,actualstate.y,newstate.tavolsag);
                        stateQueue.push(newstate);
                    }
                }
            }
        }
        if(utmatrix[final.x][final.y].tav<INT_MAX)
        {
            break;
        }
    }
    rovidut it= utmatrix[final.x][final.y];
    while (it.xbol!=origin.x||it.ybol!=origin.y){
        shortestPath.push_back(Coordinate(it.xbol,it.ybol));
        it=utmatrix[it.xbol][it.ybol];
    }

}
