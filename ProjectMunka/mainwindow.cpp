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
//    advance();
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
    ui->groupBox->setFixedWidth(100);

    for(int i=0; i<XX; i++)
    {
        for(int j=0; j<YY; j++)
        {
            Builder *b = new Builder(i , j ,size);
            ui->gridLayout->addWidget(b, i ,j);
            buildvector.push_back(b);
            b->setFunction(Builder::base);
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
 //       fieldAt(Fogyaszto[i].x, Fogyaszto[i].y)->setText(QString::number(Fogyaszto[i].need_r));
        fieldAt(Fogyaszto[i].x, Fogyaszto[i].y)->setFunction(Builder::Consumer);        
        check.x = Fogyaszto[i].x; check.y = Fogyaszto[i].y;
        ui->reqR->setText(QString::number(Fogyaszto[i].need_r));
        ui->reqG->setText(QString::number(Fogyaszto[i].need_g));
        ui->reqB->setText(QString::number(Fogyaszto[i].need_b));
        ui->reqRG->setText(QString::number(Fogyaszto[i].need_r_g));
        ui->reqRB->setText(QString::number(Fogyaszto[i].need_r_b));
        ui->reqBC->setText(QString::number(Fogyaszto[i].need_g_b));
        ui->reqRGB->setText(QString::number(Fogyaszto[i].need_w));
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

/*void MainWindow::on_showWayButton_clicked()
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

}*/
void MainWindow::setdoboz(int x, int y, Builder::Function f)
{
    fieldAt(x,y)->setszalagFunction(f);
}
void MainWindow::setSelected(int x, int y, Builder::Function f)
{
   /*if (!(x == final.x && y == final.y) &&
        !(x == origin.x && y == origin.y) &&
        validField(x,y)) {*/
        //Lehet kelleni fog, mert ez egy elég masszív check
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
    qDebug() << "stonks";
}

void MainWindow::Generate_Field(int x, int y)
{
    QVector<QVector<Informacio>> Fieldtmp(x,QVector<Informacio>(y));
    setField(Fieldtmp);
}
void MainWindow::placement()
{
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
}

void MainWindow::tavolsag(QVector<QVector<double>>& maszk,int fogyasztoX,int fogyasztoY)//csinal egy maszkot amin az adott fogyasztotol vett..
{                                                                                   //..tavolsagok vannak eltarolva
    for(int i=0;i<maszk.size();i++)
    {
        for(int j=0;j<maszk[i].size();j++)
        {
            maszk[i][j]=tavolsag_alt(i,j,fogyasztoX,fogyasztoY);
        }
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

     //qDebug() << "Blublu1";
    for (int i = 0; i < Fogyaszto.size(); ++i) {
        int melyiktermelorolvanszoR=-1,melyiktermelorolvanszoG=-1,melyiktermelorolvanszoB=-1;
        Coord closestR;
        double closest_R = 1000;
        Coord closestG;
        double closest_G = 1000;
        Coord closestB;
        double closest_B = 1000;
        Coord consumer;
        consumer.x = Fogyaszto[i].x; consumer.y = Fogyaszto[i].y;

        for (int j=0;j < Termelo.size() ;j++ ) {

            if(Termelo[j].felhasznaltuk_e == false && Termelo[j].r !=0 && (Fogyaszto[i].need_r !=0 || Fogyaszto[i].need_r_g !=0 || Fogyaszto[i].need_r_b !=0 || Fogyaszto[i].need_w !=0)) // Ez vagy a kovi szar
            {
                if(maszkok[i][Termelo[j].x][Termelo[j].y] < closest_R )
                {
                closest_R = maszkok[i][Termelo[j].x][Termelo[j].y];
                closestR.x = Termelo[j].x; closestR.y =Termelo[j].y;
                melyiktermelorolvanszoR=j;
                //Ezt valahogy kikene zarni ezutan
                qDebug() << "R" << j;
                //Termelo[j].felhasznaltuk_e = true;
                }
            }       else if (Termelo[j].felhasznaltuk_e == false && Termelo[j].g !=0 && (Fogyaszto[i].need_g !=0 || Fogyaszto[i].need_r_g !=0 || Fogyaszto[i].need_g_b !=0 || Fogyaszto[i].need_w !=0)){
                    if(maszkok[i][Termelo[j].x][Termelo[j].y] < closest_G )
                    {
                    closest_G = maszkok[i][Termelo[j].x][Termelo[j].y];
                    closestG.x = Termelo[j].x; closestG.y =Termelo[j].y;
                    melyiktermelorolvanszoG=j;
                    qDebug() << "G" << j;
                    //Termelo[j].felhasznaltuk_e = true;
                    //Ezt valahogy kikene zarni ezutan
                    }
            }           else if (Termelo[j].felhasznaltuk_e == false && Termelo[j].b !=0 && (Fogyaszto[i].need_b !=0 || Fogyaszto[i].need_r_b !=0 || Fogyaszto[i].need_g_b !=0 || Fogyaszto[i].need_w !=0)){
                        if(maszkok[i][Termelo[j].x][Termelo[j].y]<closest_B )
                        {
                        closest_B = maszkok[i][Termelo[j].x][Termelo[j].y];
                        closestB.x = Termelo[j].x; closestB.y =Termelo[j].y;
                        melyiktermelorolvanszoB=j;
                        qDebug() << "B" << j;
                        //Termelo[j].felhasznaltuk_e = true;
                        //Ezt valahogy kikene zarni ezutan
                        }
    }
}
        //qDebug() << Fogyaszto.size() << Termelo.size();
//R
        if(melyiktermelorolvanszoR != -1)
        {
            QString red="r"+QString::number(termelok[melyiktermelorolvanszoR].freq);
            Convbelts[i][red] = CalculateRoutes_alt(closestR , consumer,red);
        }

//G
        if(melyiktermelorolvanszoG != -1)
        {
            QString green="g"+QString::number(termelok[melyiktermelorolvanszoG].freq);
            Convbelts[i][green] = CalculateRoutes_alt(closestG , consumer,green);
        }

//B
       if(melyiktermelorolvanszoB != -1)
       {
           QString blue="b"+QString::number(termelok[melyiktermelorolvanszoB].freq);
           Convbelts[i][blue] = CalculateRoutes_alt(closestB , consumer,blue);
       }

}
    meret(Beltmasolat);
     //qDebug() << "Blublu4";
}

QVector<Coord> MainWindow::CalculateRoutes_alt(const Coord& inspected_Producer,const Coord& inspected_Consumer,const QString& szin)
{
    murBmurB.setStart(inspected_Producer);
    //qDebug()<<inspected_Producer.x<<inspected_Producer.y;
    murBmurB.setEnd(inspected_Consumer);
    QVector<Coord> way;
    QVector<Coord> discoveredField;
    murBmurB.getPath(way, discoveredField);
    for (Coord c: way) {
        if(szin[0]=='r')
        {        setSelected(c.x, c.y, Builder::wayR);
        }
        if(szin[0]=='g')
        {        setSelected(c.x, c.y, Builder::wayG);
        }
        if(szin[0]=='b')
        {        setSelected(c.x, c.y, Builder::wayB);
        }
        murBmurB.setFieldmezo(c.x,c.y);
        murBmurB.setFieldmezo(inspected_Consumer.x, inspected_Consumer.y);
    }
    return way;
}
void MainWindow::advance()
{
    spawn();
    eloreleptet();
    lepteto++;
    refresh();
}
void MainWindow::spawn()
{
 //Coord prev(-1,-1);
 for(int j=0; j<Convbelts.count(); j++ )
 {
     for(QMap <QString, QVector<Coord>>::iterator it=Convbelts[j].begin();it!=Convbelts[j].end();it++)
     {
             if(lepteto%(it.key().back().digitValue())==0)
             {
                 if(it.key()[0]=='r')
                 {Beltmasolat[j][it.key()][Beltmasolat[j][it.key()].size()-1].r+=1;
                     qDebug()<<"asdd";
                 }else
                 if(it.key()[0]=='g')
                 {Beltmasolat[j][it.key()][Beltmasolat[j][it.key()].size()-1].g+=1;
                     qDebug()<<"kek";
                 }else
                 if(it.key()[0]=='b')
                 {Beltmasolat[j][it.key()][Beltmasolat[j][it.key()].size()-1].b+=1;
                     qDebug()<<"333";
                 }
             }
             /*for(int timer=0;timer<it.key().back().digitValue();timer++){
             delay(50);
             }*/
             //int f=Convbelts[j][it.key()].size()-1;
             //qDebug()<<Convbelts[j][it.key()][std::min(i,f)].x<<Convbelts[j][it.key()][std::min(i,f)].y;
     }
 }
     /*if(prev.x!=-1&&prev.y!=-1)
       {
       }*/

}



void MainWindow::eloreleptet()
{
    for(int j=0; j<Convbelts.count(); j++ )
    {
    for(QMap <QString, QVector<rgbszin>>::iterator it=Beltmasolat[j].begin();it!=Beltmasolat[j].end();it++)
    {
        eattheweak(it.key() , j);
        for (int i=0;i<Beltmasolat[j][it.key()].size()-1;i++)
        {
            Beltmasolat[j][it.key()][i].r+=Beltmasolat[j][it.key()][i+1].r;
            Beltmasolat[j][it.key()][i+1].r=0;
            Beltmasolat[j][it.key()][i].r=std::min(1,Beltmasolat[j][it.key()][i].r);

            Beltmasolat[j][it.key()][i].g+=Beltmasolat[j][it.key()][i+1].g;
            Beltmasolat[j][it.key()][i+1].g=0;
            Beltmasolat[j][it.key()][i].g=std::min(1,Beltmasolat[j][it.key()][i].g);

            Beltmasolat[j][it.key()][i].b+=Beltmasolat[j][it.key()][i+1].b;
            Beltmasolat[j][it.key()][i+1].b=0;
            Beltmasolat[j][it.key()][i].b=std::min(1,Beltmasolat[j][it.key()][i].b);
            qDebug()<<Beltmasolat[j][it.key()][i].r<<Beltmasolat[j][it.key()][i].g<<Beltmasolat[j][it.key()][i].b;

            //tovabb adja a szineket, hatulrol huzza a conveyor-n
            szintesztelo(it.key(),i, j);
        }
        qDebug()<<"beltvege";
    }
    }
}
void MainWindow::szintesztelo(QString itkey, int iterator, int j)
{
    if(Beltmasolat[j][itkey][iterator].r==1)
    {
        if(Beltmasolat[j][itkey][iterator].g==1)
        {
            if(Beltmasolat[j][itkey][iterator].b==1)
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convW);
            }else
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convRG);
            }
        }
        if(Beltmasolat[j][itkey][iterator].b==1)
        {
        setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convRB);
        }
    setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::Producer_Red);

    }else if(Beltmasolat[j][itkey][iterator].g==1)
    {
        if(Beltmasolat[j][itkey][iterator].r==1)
        {
            if(Beltmasolat[j][itkey][iterator].b==1)
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convW);
            }else
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convRG);
            }
        }
        if(Beltmasolat[j][itkey][iterator].b==1)
        {
        setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convGB);
        }
    setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::Producer_Green);


    }else if(Beltmasolat[j][itkey][iterator].b==1)
    {
        if(Beltmasolat[j][itkey][iterator].g==1)
        {
            if(Beltmasolat[j][itkey][iterator].r==1)
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convW);
            }else
            {
            setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convGB);
            }
        }
        if(Beltmasolat[j][itkey][iterator].r==1)
        {
        setdoboz(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::convRB);
        }
    setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::Producer_Blue);
    }
    else if(itkey[0]=='r')
    {
        setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::wayR);
    }
    else if(itkey[0]=='g')
    {
        setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::wayG);
    }
    else if(itkey[0]=='b')
    {
        setSelected(Convbelts[j][itkey][iterator].x,Convbelts[j][itkey][iterator].y,Builder::wayB);
    }
}

void MainWindow::eattheweak(QString itkey, int j)
{
    //kene tudni a fogyasztot exactly akit vizsgalunk
    if( maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
        Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].r == 1 &&
        Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].g == 1 &&
        Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].b == 1 &&
        fogyasztok[0].need_w != 0)
    {
        fogyasztok[0].need_w -=1;
    }else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
             Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].r == 1 &&
             Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].g == 1 &&
             fogyasztok[0].need_r_g != 0)
    {
        fogyasztok[0].need_r_g-=1;
    }
    else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
            Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].r == 1 &&
            Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].b == 1 &&
            fogyasztok[0].need_r_b != 0)
    {
        fogyasztok[0].need_r_b-=1;
    }
    else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
            Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].g == 1&&
            Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].b == 1&&
            fogyasztok[0].need_g_b != 0)
    {
        fogyasztok[0].need_g_b -=1;
    }else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
             Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].r == 1&&
             fogyasztok[0].need_r != 0)
    {
        fogyasztok[0].need_r -=1;
    }else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
             Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].g == 1&&
             fogyasztok[0].need_g != 0)
    {
         fogyasztok[0].need_g -=1;
    }else if(maszkok[j][(Convbelts[j][itkey][0]).x][(Convbelts[j][itkey][0]).y] == 1 &&
             Beltmasolat[j][itkey][Beltmasolat[j][itkey].size()-1].b == 1&& fogyasztok[0].need_b != 0)
    {
         fogyasztok[0].need_b -=1;
    }else
    {
        wedone = true;
    }
}

void MainWindow::refresh()
{
    for(int i=0; i<fogyasztok.size(); i++)//Ezt fixált adattal kikell potolni
    {
        ui->reqR->setText(QString::number(fogyasztok[i].need_r));
        ui->reqG->setText(QString::number(fogyasztok[i].need_g));
        ui->reqB->setText(QString::number(fogyasztok[i].need_b));
        ui->reqRG->setText(QString::number(fogyasztok[i].need_r_g));
        ui->reqRB->setText(QString::number(fogyasztok[i].need_r_b));
        ui->reqBC->setText(QString::number(fogyasztok[i].need_g_b));
        ui->reqRGB->setText(QString::number(fogyasztok[i].need_w));
    }
}
int MainWindow::leghosszabbkereses(QMap <QString, QVector<Coord>>& keresett)
{
    int leghosszabb=0;
    for(QMap <QString, QVector<Coord>>::iterator it=keresett.begin();it!=keresett.end();it++)
    {
        if(keresett[it.key()].size()>leghosszabb)
        {
            leghosszabb=keresett[it.key()].size();
        }
    }
    return leghosszabb;
}
QMap <int , QMap <QString, QVector<rgbszin>>> MainWindow::meret(QMap< int, QMap <QString, QVector<rgbszin>>>& beltmasolat_alt)
{
    rgbszin tempszin;
    tempszin.r=0;
    tempszin.g=0;
    tempszin.b=0;
    for(int j=0; j<Convbelts.count(); j++ )
    {


    for( QMap <QString, QVector<Coord>>::iterator it=Convbelts[j].begin();it!=Convbelts[j].end();it++)
    {
        //*qDebug()<<it.key()<<beltmasolat_alt[it.key()];
        for(int i=0;i<Convbelts[j][it.key()].size();i++)
        {
            beltmasolat_alt[j][it.key()].push_back(tempszin);
        }
    }
    }
    return beltmasolat_alt;
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

void MainWindow::on_leptetbtn_clicked()
{
    advance();
}

