#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include "pathfinder.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initSetup(int x, int y);


private slots:
    void on_resizeButton_clicked();
    void on_field_clicked(int x, int y, Qt::MouseButton m);
    void on_field_hovered(int x, int y);
    void on_lineMode_stateChanged(int arg1);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void on_animationButton_clicked();

    void on_showWayButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Field*> fieldvector;
    std::vector<Field*> selectvector;

    int x_size;
    int y_size;
    Coordinate origin;
    Coordinate final;
    Coordinate lastClick;
    bool secondClick;
    bool mousePressed;
    bool shiftPressed;
    bool ctrlPressed;
    bool animation;

    PathFinder model;

   Field* fieldAt(int x, int y);
   bool validField(int x, int y);

   void setOrigin(int x, int y);
   void setFinal(int x, int y);
   void setWall(int x, int y);
   void setBase(int x, int y);
   void setSelected(int x, int y, Field::Function f = Field::selected);
   void revertField(int x, int y);
   void revertSelected();
   void delay(int mSec);

};
#endif // MAINWINDOW_H
