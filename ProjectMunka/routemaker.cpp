#include "routemaker.h"
#include <queue>
#include <cmath>


RouteMaker::RouteMaker(int XX, int YY)
{
start.x = 0; start.y = 0;
end.x = XX-1; end.y = YY-1;
field = QVector<QVector<int>>(YY , QVector<int>(XX, 0));
}

void RouteMaker::setStart(const Informacio &newStart)
{
    start = newStart;
}

void RouteMaker::setEnd(const Informacio &newEnd)
{
    end = newEnd;
}

struct path{  //!!!!!!!!!!!!!!!!!!!
  int x, y , dis;
  path()
  {
      x = 0, y = 0, dis=INT_MAX;
  }
  path(int _x, int _y, int _dis)
  {
   x = _x;
   y = _y;
   dis = _dis;
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
    void sethvalue(Informacio end)
    {
        hvalue=abs(end.x-x)+abs(end.y-y);
        //BOLDI KÓDJA kipotolja majd
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
                 if(i==0||j==0)
                 {
                     int newX=actualstate.x+i;
                     int newY=actualstate.y+j;
                     if(newX>=0 &&newY>=0 &&newX<XX &&newY<YY  &&field[newX][newY]==0 &&convbelt[newX][newY].dis>actualstate.distance+1)
                         {
                         State newstate(newX,newY,actualstate.distance+1);
                         //newstate.sethvalue(end);!!!!!!!!!
                         convbelt[newX][newY] = path(actualstate.x,actualstate.y,newstate.distance);
                         stateQueue.push(newstate);
                         }
                 }
         }
         if(convbelt[end.x][end.y].dis<INT_MAX)
         {
         break;
         }
     }
     path it=convbelt[end.x][end.y];
     while(it.x!=start.x||it.y!=start.x)
     {
         shortestPath.push_back(Coord(it.x,it.y));
         it=convbelt[it.x][it.y];
     }
    }




