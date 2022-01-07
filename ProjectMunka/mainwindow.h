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
#include <QVariant>
#include "builder.h"
#include "routemaker.h"
#include <stdio.h>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef QVector<QVector<double>> matrix;
struct rgbszin
{
    int r=0,g=0,b=0;
};
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
    bool wedone=false;;
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
    rgbszin eattheweak_osszesito{0,0,0};
    QVector<matrix> maszkok;
    QMap<int , QMap <QString, QVector<Coord>>> Convbelts;  //Fogyaszto id-> szin alapjan melyik termeleo -> neki az uta
    QMap<int , QMap <QString, QVector<rgbszin>>> Beltmasolat;
    int XX,YY;
    bool animation; //Lehet kelleni fog
    int lepteto=0;
    bool absolutewedone = false;

    RouteMaker murBmurB{0,0};
    //RouteMaker BrumBrum(int XX,int YY);
public slots:
    void setupField(int XX, int YY);
    void setField(const QVector<QVector<Informacio>> &newField);
    void setInfo(const QVector<Informacio> &newInfo);
    void tavolsag(QVector<QVector<double>>& maszk,int fogyasztoX,int fogyasztoY);
    double tavolsag_alt(double x1,double y1,double x2, double y2);
    void CalculateRoutes(const QVector<Informacio>& Fogyaszto,QVector<Informacio>& Termelo, const QVector<matrix>& maszkok);
    QVector<Coord> CalculateRoutes_alt(const Coord& inspected_Producer, const Coord& inspected_Consumer,const QString& szin);
    void spawn();
    int leghosszabbkereses(QMap <QString, QVector<Coord>>& keresett);
    QMap <int ,QMap <QString, QVector<rgbszin>>> meret(QMap <int, QMap <QString, QVector<rgbszin>>>& beltmasolat_alt);
    void advance();
    void eloreleptet();
    void szintesztelo(QString itkey,int iterator, int j);
    void eattheweak(int j);
    void refresh();

private slots:
   // void on_showWayButton_clicked();

    //void on_animationButton_clicked();

    void on_leptetbtn_clicked();

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
   void setdoboz(int x, int y, Builder::Function f=Builder::selected);
   /*
   void setFinal(int x, int y);
   void setWall(int x, int y);
   void setBase(int x, int y);

   void revertField(int x, int y);
   void revertSelected();
*/
};
#endif // MAINWINDOW_H
