#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <fstream>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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
        int x,y,tick;
        koord()
        {
            x=-1;
            y=-1;
            tick=-1;
        }
        koord(int _x,int _y,int _tick)
        {
            x=_x;
            y=_y;
            tick=_tick;
        }
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <QVector<RGB>> szin;
    QMap<QString,koord>termelok;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void beolvas(QVector<QVector<RGB>>,QMap<QString,koord>);
};
#endif // MAINWINDOW_H
