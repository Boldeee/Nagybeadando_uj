#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Upload();
    placement();
    tavolsag m(termelok,fogyasztok);

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
        XX= linesplit[0].toInt();
        YY= linesplit[1].toInt();
        Generate_Field(XX , YY);
        line = stream.readLine();
        howmany = line.toInt();
        //qDebug() << howmany;
        QVector<Informacio> Infotmp;
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
               Informacio tmp;
               tmp.ID=linesplit[2].toInt(); //Termelő jelölés
               if(linesplit[3].toInt()==1)tmp.r=1;
               if(linesplit[3].toInt()==2)tmp.g=1;
               if(linesplit[3].toInt()==3)tmp.b=1;
               tmp.freq=linesplit[4].toInt(); //Hány Tickenként
               //qDebug() << linesplit[2] << linesplit[3] << linesplit[4];
               tmp.x=linesplit[0].toInt();
               tmp.y=linesplit[1].toInt();
               Infotmp.push_back(tmp);
               termelok.insert(tmp);
           }
           else if (linesplit[2].toInt() == 2) {
               //qDebug() << "Béta Fogyasztó";
               Informacio tmp;
               tmp.ID=linesplit[2].toInt(); //Fogyasztó jelölés
               tmp.need_r=linesplit[3].toInt(); //Mennyi R
               tmp.need_g=linesplit[4].toInt(); //Mennyi G
               tmp.need_b=linesplit[5].toInt(); //Mennyi B
               tmp.need_r_g=linesplit[6].toInt(); //Mennyi R+G
               tmp.need_r_b=linesplit[7].toInt(); //Mennyi R+B
               tmp.need_g_b=linesplit[8].toInt(); //Mennyi B+G
               tmp.need_w=linesplit[9].toInt(); //Mennyi R+G+B
               tmp.x=linesplit[0].toInt();
               tmp.y=linesplit[1].toInt();
               Infotmp.push_back(tmp);
               fogyasztok.insert(tmp);

           }
        }
        setInfo(Infotmp);
        infile.close();

    }
}

void MainWindow::Generate_Field(int x, int y)
{
    //qDebug() << "Beléptem a Generate Fieldbe";
    QVector<QVector<Informacio>> Fieldtmp(x,QVector<Informacio>(y));
    /*//QVector<Informacio> tempo;
    for (int i = 0; i < x ;i++ ) {
       // qDebug() << "Beléptem a Generate Fieldbe ebbe a részébe is";
        for (int j = 0; j < y ;j++ ) {
            //qDebug() << ((i+1)*10+(j+1));
            //Fieldtmp[i]=tempo;
            //qDebug()<<Fieldtmp[i][(i+1)*10+(j+1)];
        }

    }*/
    setField(Fieldtmp);
}
void MainWindow::placement()
{
    /*for(int ss=0;ss<Info.size();ss++)
    {
        qDebug()<<Info[ss].ID<<Info[ss].x<<Info[ss].y;
    }*/
    for(int i=0;i<Field.size();i++)
    {
        for(int it2=0;it2<Field[i].size();it2++)
        {
        for (int it=0;it<Info.size();it++)
        {
               if(it2==Info[it].y&&i==Info[it].x)
               {
                   Field[i][it2]=Info[it];
               }
        }
        }
    }
    /*int szamlalo=1;
    for (int i = 0; i < XX ;i++ ) {
        for (int j = 0; j < YY ;j++ ) {
            if(Field[i][j].ID!=0)
            {
            qDebug()<<Field[i][j].ID<<szamlalo ;
            szamlalo++;
            }
        }}*/
}

const QVector<MainWindow::Informacio> &MainWindow::getInfo() const
{
    return Info;
}
const QVector<QVector<MainWindow::Informacio>> &MainWindow::getField() const
{
    return Field;
}
void MainWindow::setInfo(const QVector<Informacio> &newInfo)
{
    Info = newInfo;
}
void MainWindow::setField(const QVector<QVector<Informacio>> &newField)
{
    Field = newField;
}
