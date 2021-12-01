#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <QVector<RGB>> szin;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
