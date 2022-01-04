#include "routemaker.h"
#include <queue>
#include <cmath>
#include <QDebug>

RouteMaker::RouteMaker(int XX, int YY):
    start(5, 2), end(3 , 4)
{
field = QVector<QVector<int>>(YY , QVector<int>(XX, 0));
}



void RouteMaker::setStart(const Coord &newStart)
{
    start = newStart;
}

void RouteMaker::setEnd(const Coord &newEnd)
{
    end = newEnd;
}

struct path{  //!!!!!!!!!!!!!!!!!!!
  int px, py , pdis;
  path()
  {
      px = 0, py = 0, pdis=INT_MAX;
  }
  path(int _px, int _py, int _pdis)
  {
   px = _px;
   py = _py;
   pdis = _pdis;
  }
};
struct State{
    int x,y,hvalue,distance;
    State(int _x, int _y, int _distance )
    {
        x =_x;
        y = _y;
        distance = _distance;
    }
    void sethvalue(Coord end)
    {
        hvalue=abs(end.x-x)+abs(end.y-y);

    }
};

bool operator<(State const &s1,State const &s2)
{
    return s1.distance+s1.hvalue>s2.distance+s2.hvalue;
}

void RouteMaker::getPath(QVector<Coord> &shortestPath, QVector<Coord> &discoveredFields)
    {
     XX =  field[0].size();
     YY =  field.size();

     QVector<QVector<path>>convbelt(YY, QVector<path>(XX));
     convbelt[start.x][start.y] = path(start.x, start.y , 0);

     std::priority_queue<State> stateQueue;
     State initState(start.x, start.y ,0);
     stateQueue.push(initState);

     while(stateQueue.size()>0)
     {
         State actualstate =stateQueue.top();
         stateQueue.pop();
         discoveredFields.push_back(Coord(actualstate.x,actualstate.y));

         for(int i=1;i<=1;i++)
         {
             for(int j=-1; j<=1; j++)
             {
                 if(i==0||j==0)
                 {
                     int newX=actualstate.x+i;
                     int newY=actualstate.y+j;
                     if(newX>=0 &&newY>=0 &&newX<XX &&newY<YY  &&field[newX][newY]==0 &&convbelt[newX][newY].pdis>actualstate.distance+1)
                         {
                         State newstate(newX,newY,actualstate.distance+1);
                         newstate.sethvalue(end);
                         convbelt[newX][newY] = path(actualstate.x,actualstate.y,newstate.distance);
                         stateQueue.push(newstate);
                         }
                 }
         }
     }
     if(convbelt[end.x][end.y].pdis<INT_MAX)
         {
            break;
         }
     }
     path it=convbelt[end.x][end.y];
     while(it.px!=start.x||it.py!=start.x)
     {
         qDebug() << "Valami";
         shortestPath.push_back(Coord(it.px,it.py));
         it=convbelt[it.px][it.py];
     }
    }




