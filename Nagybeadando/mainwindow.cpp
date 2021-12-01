#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RGB szinek(0,0,0);
    szin=QVector<QVector<RGB>>(3,QVector<RGB>(5,szinek));
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

