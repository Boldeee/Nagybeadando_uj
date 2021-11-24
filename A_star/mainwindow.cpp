#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), model(0,0)
{
    ui->setupUi(this);
    initSetup(10,10);
    qDebug() << __DBL_MAX__ << INT_MAX << __INT_MAX__;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSetup(int x, int y)
{
    lastClick = {0,0};
    x_size = x;
    y_size = y;
    selectvector.clear();

    qDeleteAll(ui->gridLayout->children());
    for (Field * f: fieldvector) {
        delete f;
    }
    fieldvector.clear();

    int size = std::min(500/x, 500/y);

    ui->gridLayout->setSpacing(size/10);
    ui->widthBox->setValue(x_size);
    ui->heightBox->setValue(y_size);

    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {

            Field *f = new Field(i,j,size);
            ui->gridLayout->addWidget(f,i,j);
            fieldvector.push_back(f);
            f->setFunction(Field::base);
            connect(f,&Field::clicked,this, &MainWindow::on_field_clicked);
            connect(f,&Field::hovered,this, &MainWindow::on_field_hovered);

        }
    }
    origin = {0,0};
    final = {x-1, y-1};
    animation = false;

    model = PathFinder(x_size, y_size);
    model.setOrigin(origin);
    model.setFinal(final);

    setOrigin(0,0);
    setFinal(x-1, y-1);
    shiftPressed = false;
    ctrlPressed = false;
    mousePressed = false;

}


void MainWindow::on_resizeButton_clicked()
{
    initSetup(ui->heightBox->value(),ui->widthBox->value());
}

void MainWindow::on_field_clicked(int x, int y, Qt::MouseButton m)
{
    if (animation) return;

    revertSelected();
    ui->fieldNumLabel->setText("-");
    ui->shortWayLabel->setText("-");
    if (m == Qt::RightButton) {
        if (shiftPressed)
            setFinal(x,y);
        else
            setOrigin(x,y);

    } else {
        mousePressed = true;
        if (ui->lineMode->isChecked()) {
            if (secondClick)
            {
                for (int i = std::min(x, lastClick.x); i<=std::max(x, lastClick.x); i++) {
                    for (int j = std::min(y, lastClick.y); j<=std::max(y, lastClick.y); j++) {
                        qDebug() << fieldvector.size() << j*x_size+i;
                        if (shiftPressed) {
                            setBase(i,j);
                        } else {
                            setWall(i,j);
                        }
                    }
                }
                secondClick = false;
            } else {
                revertSelected();
                setSelected(x,y);
                secondClick = true;
            }
        } else {
            Field* f = fieldAt(x,y);
            if (f->getFunction() == Field::base) {
                setWall(x,y);
            } else if(f->getFunction() == Field::wall){
                f->setFunction(Field::base);
            }
        }

        lastClick = {x, y};
    }
}

void MainWindow::on_field_hovered(int x, int y)
{
    if (ui->lineMode->isChecked()) {
        if (secondClick) {
            revertSelected();
            for (int i = std::min(x, lastClick.x); i<=std::max(x, lastClick.x); i++) {
                for (int j = std::min(y, lastClick.y); j<=std::max(y, lastClick.y); j++) {
                    setSelected(i,j);
                }
            }
        }


    } else {
        if (ctrlPressed) {
            if (shiftPressed) {
                setBase(x,y);
            } else {
                setWall(x,y);
            }
        }
    }
}


void MainWindow::on_lineMode_stateChanged(int arg1)
{
    revertSelected();

    if (arg1) {
        secondClick = false;
    }
}

Field* MainWindow::fieldAt(int x, int y)
{
    return fieldvector[x*y_size + y];
}

bool MainWindow::validField(int x, int y)
{
    return 0<=x && 0<=y && x<x_size && y<y_size;
}

void MainWindow::setOrigin(int x, int y)
{
    if (!(x==final.x && y==final.y) && validField(x,y))
    {
        Coordinate prev = origin;
        origin = {x,y};

        if (validField(prev.x, prev.y)) {
            revertField(prev.x, prev.y);
        }

        fieldAt(origin.x, origin.y)->setFunction(Field::origin);
        model.setOrigin(origin);
    }
}

void MainWindow::setFinal(int x, int y)
{
    if (!(x==origin.x && y==origin.y) && validField(x,y))
    {
        Coordinate prev = final;
        final = {x,y};
        if (validField(prev.x, prev.y)) {
           revertField(prev.x, prev.y);
        }
        fieldAt(final.x, final.y)->setFunction(Field::end);
        model.setFinal(final);
    }
}

void MainWindow::setWall(int x, int y)
{
    if (!(x == final.x && y == final.y) &&
        !(x == origin.x && y == origin.y)
            && validField(x,y)) {
        fieldAt(x,y)->setFunction(Field::wall);
        model.setValue(x,y,1);
    }
}

void MainWindow::setBase(int x, int y)
{
    if (!(x == final.x && y == final.y) &&
        !(x == origin.x && y == origin.y) &&
        validField(x,y)) {
      fieldAt(x,y)->setFunction(Field::base);
      model.setValue(x,y,0);
    }
}

void MainWindow::setSelected(int x, int y, Field::Function f)
{
    if (!(x == final.x && y == final.y) &&
        !(x == origin.x && y == origin.y) &&
        validField(x,y)) {
      fieldAt(x,y)->setFunction(f);
      selectvector.push_back(fieldAt(x,y));
    }
}

void MainWindow::revertField(int x, int y)
{
    if (model.getValue(x,y) == 0) {
        setBase(x,y);
    } else if (model.getValue(x,y) == 1) {
        setWall(x,y);
    }
}

void MainWindow::revertSelected()
{
    for (Field *f: selectvector) {
        revertField(f->getX(), f->getY());
    }
    selectvector.clear();
}

void MainWindow::delay(int mSec)
{
    QTime dieTime= QTime::currentTime().addMSecs(mSec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    mousePressed = true;
    event->ignore();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    mousePressed = false;
    event->ignore();
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Control) {
        ctrlPressed = true;
    } else if (event->key() == Qt::Key_Shift) {
        shiftPressed = true;
    }
    event->ignore();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Control) {
        ctrlPressed = false;
    } else if (event->key() == Qt::Key_Shift) {
        shiftPressed = false;
    }

}


void MainWindow::on_animationButton_clicked()
{
    revertSelected();
    vector<Coordinate> way;
    vector<Coordinate> discoveredField;
    model.getPath(way, discoveredField);
    animation = true;
    int discovered = 0;


    for (Coordinate c: discoveredField) {
        delay(50);
        setSelected(c.x, c.y,Field::selected);
        discovered++;
        ui->fieldNumLabel->setText(QString::number(discovered));
    }


    int wayLength = 0;

    for (Coordinate c: way) {
        delay(100);
        setSelected(c.x, c.y,Field::way);
        wayLength++;
        ui->shortWayLabel->setText(QString::number(wayLength));
    }

    animation = false;

}


void MainWindow::on_showWayButton_clicked()
{
    revertSelected();
    vector<Coordinate> way;
    vector<Coordinate> discoveredField;
    model.getPath(way, discoveredField);
    ui->fieldNumLabel->setText(QString::number(discoveredField.size()));
    ui->shortWayLabel->setText(QString::number(way.size()));

    for (Coordinate c: way) {
        setSelected(c.x, c.y, Field::way);
    }
}

