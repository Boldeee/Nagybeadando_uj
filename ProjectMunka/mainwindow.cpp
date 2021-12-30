#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "builder.h"
#include <QTime> //dunno
#include <QKeyEvent> //dunno2.0
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Upload();
    placement();
    setupField(XX , YY);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupField(int XX, int YY)
{
    qDeleteAll(ui->gridLayout->children());
    for (Builder * b: buildvector )
    {
        delete b;
    }
    buildvector.clear();

    int size = std::min(500/XX, 500/YY);

    ui->gridLayout->setSpacing(size/10);
    ui->widthBox->setValue(XX);
    ui->heightBox->setValue(YY);

    for(int i=0; i<XX; i++)
    {
        for(int j=0; j<YY; j++)
        {
            Builder *b = new Builder(i , j ,size);
            ui->gridLayout->addWidget(b, i ,j);
            buildvector.push_back(b);
            b->setFunction(Builder::base);
            /*connect(f,&Field::clicked,this, &MainWindow::on_field_clicked);
            connect(f,&Field::hovered,this, &MainWindow::on_field_hovered);*/
            //Sztem nem kell
        }
    }
    //LENYEGES RESZ SAFOI(ASDUFOUASDKUHGIUSDHUFGOUILDSAHG
    BrumBrum = RouteMaker(XX, YY);
    BrumBrum.setStart(inspected_Producer);
    BrumBrum.setEnd(inspected_Consumer); //Ide kene majd a mindenseg is, vagy lehet skippelni idk
    /*setOrigin(0,0);
    setFinal(x-1, y-1);
    shiftPressed = false;
    ctrlPressed = false;
    mousePressed = false; Ez szerintem nem kell*/
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
        int fogyasztoszam=0;
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
               termelok.push_back(tmp);

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
               tmp.fogyasztoID=fogyasztoszam;               //Azert kell mert a maszkok[i]-edik matrixa aza valahanyas fogyasztoID-hez kapcsolodik
               QVector<QVector<double>> maszk(XX,QVector<double>(YY,0));
               tavolsag(maszk,tmp.x,tmp.y);
               Infotmp.push_back(tmp);
               fogyasztok.push_back(tmp);
               maszkok.push_back(maszk);
               fogyasztoszam++;
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

void MainWindow::tavolsag(QVector<QVector<double>>& maszk,int fogyasztoX,int fogyasztoY)//csinal egy maszkot amin az adott fogyasztotol vett..
{                                                                                   //..tavolsagok vannak eltarolva
    for(int i=0;i<maszk.size();i++)
    {
        for(int j=0;j<maszk[i].size();j++)
        {
            maszk[i][j]=tavolsag_alt(i,j,fogyasztoX,fogyasztoY);
            //qDebug()<<maszk[i][j]<<' ';
        }
        //qDebug()<<' ';
    }
}
double MainWindow::tavolsag_alt(double x1,double y1,double x2, double y2)
{
    double eredmeny=-1;
    eredmeny=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return eredmeny;
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
