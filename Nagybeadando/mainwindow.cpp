#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    beolvas(szin,termelok);
    //kiirat(szin);
}
struct  RGB
{
    int r,g,b;
    RGB()
    {
        int r=0,g=0,b=0;
    }
    RGB(int _r,int _g, int _b)
    {
        r=_r;
        g=_g;
        b=_b;
    }
};
struct koord
{
    int x,y;
    QVector<int> type;
    koord()
    {
        x=-1;
        y=-1;
        QVector<int> type;//0:(0 üres, 1 termelo, 2 fogyaszto),1:(hany tickenkent/hanyat var),2:(mit termel/mit fogyaszt),3:(mit fogyaszt meg)...10(mit fogyaszt meg)
    }
    koord(int _x,int _y)
    {
        x=_x;
        y=_y;
    }
};


void beolvas(QVector<QVector<RGB>>&szin,QMap<QString,koord>&termelok)
{
    ifstream is("initial.txt");
    int n,m;
    QString ss;
    is>>n >>m;
    RGB szinek(0,0,0);
    szin=QVector<QVector<RGB>>(n,QVector<RGB>(m,szinek));
    RGB k;
    koord kord;
    if(k.r==1)
    {
        if(k.g==1)
        {
           if(k.b==1)
           {
               kord.type[7]--;
           }
           kord.type[5]--;
        }else if(k.b==1){

        }
        kord.type[1]--;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

/*void kiirat(const QVector<QVector<RGB>>& szin)
{
    for(int i=0;i<szin.size();i++)
    {
        for(int j=0;j<5;j++)
        {
            qDebug()<<szin[i][j].b<<' ';
        }
    }
}*/

void MainWindow::on_pushButton_clicked()
{
    int XX=0;
    for(int i=0;i<szin.size();i++)
    {
        for(int j=0;j<5;j++)
        {
            qDebug().nospace()<<'R'<<szin[i][j].r<<'G'<<szin[i][j].g<<'B'<<szin[i][j].b<<';';
        }
        XX++;
        qDebug()<<XX;
    }
}

