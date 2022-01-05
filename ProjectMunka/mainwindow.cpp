#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QKeyEvent> //dunno
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      murBmurB(0,0),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Upload();
    placement();
    murBmurB={XX,YY};
    setupField(XX , YY);
    Painter(fogyasztok, termelok);
    CalculateRoutes(fogyasztok,termelok,maszkok);
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
}



void MainWindow::delay(int mSec)
{
    QTime dieTime= QTime::currentTime().addMSecs(mSec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Builder* MainWindow::fieldAt(int x, int y)
{
    return buildvector[x*YY + y];
}

void MainWindow::Painter(QVector<Informacio>Fogyaszto, QVector<Informacio>Termelok)// Rápingálja a térképre a termelő/fogyasztokat
{
    Coord check;
    for(int i=0; i<Fogyaszto.size(); i++)
    {
        fieldAt(Fogyaszto[i].x, Fogyaszto[i].y)->setFunction(Builder::Consumer);
        check.x = Fogyaszto[i].x; check.y = Fogyaszto[i].y;
    }
    for(int i=0; i<Termelok.size(); i++)
    {
     Coord tmp;
     tmp.x = Termelok[i].x;
     tmp.y = Termelok[i].y;
     if(Termelok[i].r == 1)fieldAt(Termelok[i].x, Termelok[i].y)->setFunction(Builder::Producer_Red);
     if(Termelok[i].g == 1)fieldAt(Termelok[i].x, Termelok[i].y)->setFunction(Builder::Producer_Green);
     if(Termelok[i].b == 1)fieldAt(Termelok[i].x, Termelok[i].y)->setFunction(Builder::Producer_Blue);
    }
}

void MainWindow::on_showWayButton_clicked()
{
    //Itt nem tudja meg mi kozott keressen utat
    QVector<Coord> way;
    QVector<Coord> discoveredField;
    murBmurB.getPath(way, discoveredField);
    ui->fieldNumLabel->setText(QString::number(discoveredField.size()));
    ui->shortWayLabel->setText(QString::number(way.size()));

    for (Coord c: way) {
        setSelected(c.x, c.y, Builder::way);
    }
}

void MainWindow::on_animationButton_clicked()
{
    QVector<Coord> way;
    QVector<Coord> discoveredField;
    murBmurB.getPath(way, discoveredField);
    animation = true;
    int discovered = 0;


    for (Coord c: discoveredField) {
        delay(50);
        setSelected(c.x, c.y,Builder::selected);
        discovered++;
        ui->fieldNumLabel->setText(QString::number(discovered));
    }


    int wayLength = 0;

    for (Coord c: way) {
        delay(100);
        setSelected(c.x, c.y,Builder::way);
        wayLength++;
        ui->shortWayLabel->setText(QString::number(wayLength));
    }

    animation = false;

}

void MainWindow::setSelected(int x, int y, Builder::Function f)
{
   /*if (!(x == final.x && y == final.y) &&
        !(x == origin.x && y == origin.y) &&
        validField(x,y)) {*/ //Lehet kelleni fog, mert ez egy elég masszív check
      fieldAt(x,y)->setFunction(f);
      selectvector.push_back(fieldAt(x,y));
    /*}*/
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

void MainWindow::CalculateRoutes(const QVector<Informacio>& Fogyaszto,QVector<Informacio>& Termelo, const QVector<matrix>& maszkok)
{
    //qDebug() << "Eddig oke";
    int melyiktermelorolvanszoR=-1,melyiktermelorolvanszoG=-1,melyiktermelorolvanszoB=-1;
    for (int i = 0; i < Fogyaszto.size(); ++i) {
        Coord closestR;
        double closest_R = 1000;
        Coord closestG;
        double closest_G = 1000;
        Coord closestB;
        double closest_B = 1000;
        Coord consumer;
        consumer.x = Fogyaszto[i].x; consumer.y = Fogyaszto[i].y;
        for (int j=0;j < Termelo.size() ;j++ ) {
            if(Termelo[j].r == 1) // Ez vagy a kovi szar
            {
                if(maszkok[i][Termelo[j].x][Termelo[j].y] < closest_R )
                {
                closest_R = maszkok[i][Termelo[j].x][Termelo[j].y];
                closestR.x = Termelo[j].x; closestR.y =Termelo[j].y;
                melyiktermelorolvanszoR=j;
                //Ezt valahogy kikene zarni ezutan
                }
            }       else if (Termelo[j].g == 1){
                    if(maszkok[i][Termelo[j].x][Termelo[j].y] < closest_G )
                    {
                    closest_G = maszkok[i][Termelo[j].x][Termelo[j].y];
                    closestG.x = Termelo[j].x; closestG.y =Termelo[j].y;
                    melyiktermelorolvanszoG=j;
                    //Ezt valahogy kikene zarni ezutan
                    }
            }           else if (Termelo[j].b == 1){
                        if(maszkok[i][Termelo[j].x][Termelo[j].y]<closest_B )
                        {
                        closest_B = maszkok[i][Termelo[j].x][Termelo[j].y];
                        closestB.x = Termelo[j].x; closestB.y =Termelo[j].y;
                        melyiktermelorolvanszoB=j;
                        //Ezt valahogy kikene zarni ezutan
                        }
    }
}
        Termelo[melyiktermelorolvanszoR].felhasznaltuk_e=true;
        Termelo[melyiktermelorolvanszoG].felhasznaltuk_e=true;
        Termelo[melyiktermelorolvanszoB].felhasznaltuk_e=true;
//R
       Convbelts["r"] = CalculateRoutes_alt(closestR , consumer);
//G
       Convbelts["g"] = CalculateRoutes_alt(closestG , consumer);
//B
       Convbelts["b"] = CalculateRoutes_alt(closestB , consumer);
}

}

QVector<Coord> MainWindow::CalculateRoutes_alt(const Coord& inspected_Producer,const Coord& inspected_Consumer)
{
    murBmurB.setStart(inspected_Producer);
    qDebug()<<inspected_Producer.x<<inspected_Producer.y;
    murBmurB.setEnd(inspected_Consumer);
    QVector<Coord> way;
    QVector<Coord> discoveredField;
    murBmurB.getPath(way, discoveredField);
    for (Coord c: way) {
        qDebug()<<c.x<<c.y;
        setSelected(c.x, c.y, Builder::way);
    }
    return way;
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
