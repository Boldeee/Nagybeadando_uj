#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QFile>
//#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QTextStream>
#include <cmath>
#include <iostream>
//#include <QSet>
#include <cmath>
#include <list>
#include <queue>
#include "builder.h"
#include "routemaker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef QVector<QVector<double>> matrix;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


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
  /*0)mi ez
    1)termelo mit termel/   fogyaszto Red mennyi/       Üres R
    2)termelo hany tik/     fogyaszto Green mennyi/     Üres G
    3)                      fogyaszto Kék Mennyi/       Üres B
    4)                      fogyaszto R+G /             Üres R+G
    5)                      fogyaszto R+B/              Üres R+B
    6)                      fogyaszto G+B/              Üres G+B
    7)                      fogyaszto R+G+B/            Üres R+G+B
     */
    };
    QVector<Informacio> termelok;
    QVector<Informacio> fogyasztok;
    QVector<matrix> maszkok;
    int XX,YY;
    bool animation; //Lehet kelleni fog


    RouteMaker BrumBrum(int XX,int YY);
    RouteMaker murBmurB;
public slots:
    void setupField(int XX, int YY);
    void setField(const QVector<QVector<Informacio>> &newField);
    void setInfo(const QVector<Informacio> &newInfo);
    void tavolsag(QVector<QVector<double>>& maszk,int fogyasztoX,int fogyasztoY);
    double tavolsag_alt(double x1,double y1,double x2, double y2);

private slots:
    void on_showWayButton_clicked();

    void on_animationButton_clicked();

private:
    Ui::MainWindow *ui;
    const QVector<QVector<Informacio> > &getField() const;
    const QVector<Informacio> &getInfo() const;


    void Upload();
    void Generate_Field(int x, int y);
    void placement();
    //Coord start;
    //Coord end;

    Coord inspected_Producer;
    Coord inspected_Consumer;

    QVector<QVector<Informacio>> Field;
    QVector<Informacio> Info;
    QVector<Builder*> buildvector;
    QVector<Builder*> selectvector; //Lehet szemet
    void delay(int mSec);

   Builder* fieldAt(int x, int y);
   void Painter(QVector<Informacio> Fogyaszto, QVector<Informacio> Termelok);
   void setSelected(int x, int y, Builder::Function f = Builder::selected);
   /*
   void setFinal(int x, int y);
   void setWall(int x, int y);
   void setBase(int x, int y);

   void revertField(int x, int y);
   void revertSelected();
*/
};
#endif // MAINWINDOW_H
