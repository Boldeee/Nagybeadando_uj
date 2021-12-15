#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QTextStream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int XX,YY;
    const QVector<QMap<int,QVector<int>>> &getField() const;
    void setField(const QVector<QMap<int,QVector<int>>> &newField);

    const QMap<int, QVector<int> > &getInfo() const;
    void setInfo(const QMap<int, QVector<int> > &newInfo);
    struct Parameters
    {
        int x;
        int y;

        Parameters()
        {
            x=-1;
            y=-1;
        }
        Parameters(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    };

private:
    Ui::MainWindow *ui;

    struct Info{
    int ID;
    QVector<int> Info;
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

    //
    struct Color{
    int r;
    int g;
    int b;
    };

    void Upload();
    void Generate_Field(int x, int y);
    void placement();
    QVector<QMap<int,QVector<int>>> Field;
    QMap<int, QVector<int>> Info;

};
#endif // MAINWINDOW_H
