#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Upload();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Upload()
{
    QString line;
    QStringList linesplit;
    int howmany;
    QFile infile("asd.txt"); // Kiválasztási lehetőség?
    if(infile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&infile);
        line = stream.readLine();
        linesplit = line.split(QLatin1Char(','), Qt::SkipEmptyParts);
        Parameters s;
        s.x = linesplit[0].toInt();
        s.y = linesplit[1].toInt();
        //qDebug() << s.x;
        //qDebug() << s.y;
        //Ide egy void generate_field() különben nincs tárolás, és a többi résznek kell tudni tájékozódni
        Generate_Field(s.x , s.y);
        line = stream.readLine();
        howmany = line.toInt();
        //qDebug() << howmany;
        QMap<int, QVector<int>> Infotmp;
        for(int i = 0; i < howmany; i++)
        {
            //qDebug() << "Beléptem";
           line = stream.readLine();
           linesplit = line.split(QLatin1Char(','), Qt::SkipEmptyParts);
           //qDebug() << linesplit[2].toInt();
           if(linesplit[2].toInt() == 0)
           {
               //qDebug() << "Semmi";

           }
           else if (linesplit[2].toInt() == 1)
           {
               //qDebug() << "Chad Termelő";
               QVector<int> tmp;
               tmp.push_back(linesplit[2].toInt()); //Termelő jelölés
               tmp.push_back(linesplit[3].toInt()); //
               tmp.push_back(linesplit[4].toInt()); //Hány Tic
               //qDebug() << linesplit[2] << linesplit[3] << linesplit[4];
               Infotmp[linesplit[0].toInt()*10+linesplit[1].toInt()] = tmp;
           }
           else if (linesplit[2].toInt() == 2) {
               //qDebug() << "Béta Fogyasztó";
               QVector<int> tmp;
               /*for(QStringList::iterator it = linesplit.begin()+2; it != linesplit.end(); it++)
               {
               tmp.push_back(*it).toInt();
               }Nemvágom miért nem mükszik de ez szépítésnek jó lenne*/
               tmp.push_back(linesplit[2].toInt()); //Fogyasztó jelölés
               tmp.push_back(linesplit[3].toInt()); //Mennyi R
               tmp.push_back(linesplit[4].toInt()); //Mennyi G
               tmp.push_back(linesplit[5].toInt()); //Mennyi B
               tmp.push_back(linesplit[6].toInt()); //Mennyi R+G
               tmp.push_back(linesplit[7].toInt()); //Mennyi R+B
               tmp.push_back(linesplit[8].toInt()); //Mennyi B+G
               tmp.push_back(linesplit[9].toInt()); //Mennyi R+G+B
               Infotmp[linesplit[0].toInt()*10+linesplit[1].toInt()] = tmp;
           }
        }
        setInfo(Infotmp);
        infile.close();
    }
}

void MainWindow::Generate_Field(int x, int y)
{
    //qDebug() << "Beléptem a Generate Fieldbe";
    QVector<QVector<int>> Fieldtmp(x, QVector<int>(y));
    for (int i = 0; i < x ;i++ ) {
       // qDebug() << "Beléptem a Generate Fieldbe ebbe a részébe is";
        for (int j = 0; j < y ;j++ ) {
           // qDebug() << ((i+1)*10+(j+1));
        Fieldtmp[i][j] = ((i+1)*10+(j+1));
        }

    }
    setField(Fieldtmp);
    qDebug() << "Pipa";
}

const QMap<int, QVector<int> > &MainWindow::getInfo() const
{
    return Info;
}

void MainWindow::setInfo(const QMap<int, QVector<int> > &newInfo)
{
    Info = newInfo;
}

const QVector<QVector<int> > &MainWindow::getField() const
{
    return Field;
}

void MainWindow::setField(const QVector<QVector<int> > &newField)
{
    Field = newField;
}
