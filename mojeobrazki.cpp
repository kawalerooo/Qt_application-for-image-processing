#include "mojeobrazki.h"
#include "ui_mojeobrazki.h"
#include "mynewwidget.h"




MojeObrazki::MojeObrazki(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MojeObrazki)
{
    ui->setupUi(this);

    zegarek = new QTimer(this);
    connect(zegarek, SIGNAL(timeout()), this, SLOT(mam_zegarek()));
    zegarek->start(1000);

    licznik_info = 0;
    ui->progressBar->setValue(0);
    czas_info.setFixedWidth(100);
    ui->statusBar->addPermanentWidget(&czas_info,1);
    ui->statusBar->addPermanentWidget(ui->progressBar,2);
    ui->statusBar->addPermanentWidget(ui->label,3);

    licznik_info= 10;
}


MojeObrazki::~MojeObrazki()
{
    delete ui;
    zegarek->stop();


    }
void MojeObrazki::mam_zegarek()
{
    czas_info.setText(czas.currentTime().toString("HH:mm:ss"));
    if (licznik_info > 0) {
        licznik_info--;
    }

}


void MojeObrazki::on_actionOtw_rz_triggered()
{


   ui-> progressBar->setValue(0);
       QString imagePath = QFileDialog::getOpenFileName(this,tr("Otwórz Plik"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
   ui-> progressBar->setValue(50);

   if (!imagePath.isEmpty())
       {
           PokazObrazek = imagePath;
           image = new QImage();
           image->load(imagePath);
           pixmap = QPixmap::fromImage(*image);
           scene = new QGraphicsScene(this);
           obrazek_sceny = scene->addPixmap(pixmap);
           scene->setSceneRect(pixmap.rect());
           ui->graphicsView->setScene(scene);
           delete (image); // zabezpieczenie przed wyciekiem pamięci.
           ui ->label->setText("Wybrany Plik:"+imagePath+" "
           "rozmiar:"+QString::number(pixmap.width())+"x"+QString::number(pixmap.height()));

   }
       ui->progressBar->setValue(100);

}

void MojeObrazki::on_actionZapisz_triggered()
{

        ui->progressBar->setValue(0);

        if (obrazek_sceny!=NULL)
        {
            QString imagePath = QFileDialog::getSaveFileName(this,tr("Zapisz  Plik"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));
            ui->progressBar->setValue(50);
            if (!imagePath.isEmpty())
            {
                QImage image = obrazek_sceny->pixmap().toImage();
                if (image.size().isValid()==true) image.save(imagePath);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Information,"Informacja","Nie załadowano pliku obrazu! Nie ma co zapisać",QMessageBox::Ok).exec();
        }
        ui->progressBar->setValue(100);

}

void MojeObrazki::on_actionWyj_cie_triggered()
{
    QMessageBox MojeOkienkoWiadomosci(QMessageBox::Warning,"Wyjście z Programu","Czy chcesz wyjść z programu?",QMessageBox::Yes|QMessageBox::No);
        MojeOkienkoWiadomosci.setButtonText(QMessageBox::Yes,"Tak");
        MojeOkienkoWiadomosci.setButtonText(QMessageBox::No,"Nie");
        if (MojeOkienkoWiadomosci.exec()==QMessageBox::Yes)
        {
            QApplication::quit();
        }

}




void MojeObrazki::on_actionPokaz_obrazek_triggered()
{
    if(!PokazObrazek.isEmpty())
        {
            cv::Mat obrazek_wejsciowy = cv::imread(PokazObrazek.toStdString().c_str());
            cv::imshow("Obrazek Przetwarzany",obrazek_wejsciowy);
        }
}





void MojeObrazki::on_actionR_triggered()
{
   if(!PokazObrazek.isEmpty())
   {

       string str = PokazObrazek.toStdString();
       Mat obrazek = imread(str);
       Mat d2,x, r;
       cvtColor(obrazek,d2, CV_8UC1);
       vector<Mat> v1, v4;
       split(d2, v1);
       x = Mat::zeros(Size(d2.cols, d2.rows), CV_8UC1);
       v4.push_back(x);
       v4.push_back(x);
       v4.push_back(v1[2]);
       merge(v4, r);

       imshow("obrazekR", r);
   }

   }


void MojeObrazki::on_actionG_triggered()
{
    if(!PokazObrazek.isEmpty())
    {

        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2,x, z;
        cvtColor(obrazek,d2, CV_8UC1);
        vector<Mat> v1, v3;
        split(d2, v1);
        x = Mat::zeros(Size(d2.cols, d2.rows), CV_8UC1);
        v3.push_back(x);
        v3.push_back(v1[1]);
        v3.push_back(x);
        merge(v3, z);
        imshow("obrazekG", z);
    }

    }


void MojeObrazki::on_actionB_triggered()
{
    if(!PokazObrazek.isEmpty())
    {

        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2,x, y;
        cvtColor(obrazek,d2, CV_8UC1);
        vector<Mat> v1, v2;
        split(d2, v1);
        x = Mat::zeros(Size(d2.cols, d2.rows), CV_8UC1);
        v2.push_back(v1[0]);
        v2.push_back(x);
        v2.push_back(x);

        merge(v2, y);
        imshow("obrazekB", y);
    }

    }


void MojeObrazki::on_actionY_triggered()
{

    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_BGR2YCrCb);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("składowa Y", v1[0]);
    }

}


void MojeObrazki::on_actionCr_triggered()
{

    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_BGR2YCrCb);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("składowa S", v1[1]);
    }

}



void MojeObrazki::on_actionCb_triggered()
{


    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_BGR2YCrCb);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("składowa H", v1[2]);
    }

}
//void MojeObrazki::on_actionYRB_triggered()
//{

 //   if(!PokazObrazek.isEmpty())
  //  {
  //      string str = PokazObrazek.toStdString();
  //      Mat obrazek = imread(str);
  //      Mat d2, x, y;
  //      cvtColor(obrazek, d2, COLOR_HSV2BGR);
  //      vector<Mat> v1, v2;
  //      split(d2, v1);
  //      imshow("składowa S", v1[0]);
 //   }
//





void MojeObrazki::on_actionH_triggered()
{
    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_YCrCb2BGR);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("H", v1[0]);
    }

}


void MojeObrazki::on_actionS_triggered()
{
    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_BGR2HSV);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("S", v1[0]);
    }

}

void MojeObrazki::on_actionV_triggered()
{
    if(!PokazObrazek.isEmpty())
    {
        string str = PokazObrazek.toStdString();
        Mat obrazek = imread(str);
        Mat d2, x, y;
        cvtColor(obrazek, d2, COLOR_HSV2BGR);
        vector<Mat> v1, v2;
        split(d2, v1);
        imshow("V", v1[0]);
    }
}

void MojeObrazki::on_actionLAB07_triggered()
{
    MyNewWidget *nw = new MyNewWidget();
    nw->sciezkaObrazu= PokazObrazek;
    nw->show();
}



void MojeObrazki::Progowanie()
{
    cv::threshold(zrodlo, wynik, prog, 255, typ);
    cv::imshow("Progowanie", wynik);
}

static void Prog_callback(int v, void* p)
{
       MojeObrazki *img = (MojeObrazki*) p;
       img->Progowanie();
}


void MojeObrazki::on_actionProgowanie_triggered()
{
    if(!PokazObrazek.isEmpty())
       {
       zrodlo = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);

       cv::Mat obrazek_wejsciowy = cv::imread(PokazObrazek.toStdString().c_str());
       cv::cvtColor(obrazek_wejsciowy, scr_gray, COLOR_BGR2GRAY);
       cv::namedWindow("Progowanie", cv::WINDOW_AUTOSIZE);
       cv::createTrackbar("Rodzaje: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted", "Progowanie", &typ, 4, &Prog_callback, this);
       cv::createTrackbar("Wartość progu", "Progowanie", &prog, 255, &Prog_callback, this);
       Progowanie();

    }
}


void MojeObrazki::Rotacja( )
{

    punkt.x = pixmap.width()/2;
    punkt.y = pixmap.height()/2;


    kat = 360 - kat_obrotu;
    skala = 1;

    rozmiar.width  = pixmap.width();
    rozmiar.height = pixmap.height();


     cv::Mat r = cv::getRotationMatrix2D(punkt, kat, skala);
     cv::warpAffine(src, dst, r, rozmiar);
     cv::imshow("Rotacja", dst );
}
void MojeObrazki::Skaluj( )
{
    rozmiar.width = 500;
    rozmiar.height = 500;

    rozmiar.width  = pixmap.width() - kat_obrotu;
    rozmiar.height = pixmap.height() - kat_obrotu;


    cv::resize(src, dst, rozmiar, Skala_x, Skala_y, cv::INTER_LINEAR);
    cv::imshow("Skalowanie", dst );

}


static void  Rotacja_callback(int v, void* p)
{
    MojeObrazki *img =( MojeObrazki*) p;
    img->Rotacja();
}


static void Skaluj_callback(int v, void* p)
{
    MojeObrazki *img = (MojeObrazki*) p;
    img->Skaluj();
}


void MojeObrazki::on_actionSkalowanie_triggered()
{
    if(!PokazObrazek.isEmpty())

    {
        src = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);
        cv::namedWindow("Skalowanie", cv::WINDOW_AUTOSIZE);
        cv::createTrackbar("Współ. Skali", "Skalowanie", &kat_obrotu, 100, &Skaluj_callback, this);
        Skaluj( );
    }
}


void MojeObrazki::on_actionRotacja_triggered()
{
    if(!PokazObrazek.isEmpty())
    {
        src = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);
        cv::namedWindow("Rotacja",cv::WINDOW_AUTOSIZE);
        cv::createTrackbar("Kąt Obrotu", "Rotacja", &kat_obrotu, 360, &Rotacja_callback, this);
        Rotacja( );
    }
}



static void Mediana_callback (int value, void* p ) {

    MojeObrazki *img =( MojeObrazki*) p;
    img->Mediana();


}

static void Usrednianie_callback (int value, void* p ) {

    MojeObrazki *img =( MojeObrazki*) p;
    img->Usrednianie();

}

static void Gauss_callback(int value, void* p) {

    MojeObrazki *img =( MojeObrazki*) p;
    img->Gauss_Demo();

}

void MojeObrazki::Mediana( )
{

    int rozmycie = 1;
        if(wielkosc_okna % 2 == 1) {
            rozmycie = wielkosc_okna;
        } else if (wielkosc_okna >= 2) {
            rozmycie = wielkosc_okna - 1;
        }


    cv::medianBlur(src, dst, rozmycie);
    cv::imshow("Mediana", dst);

}

void MojeObrazki::Usrednianie( ) {


    if (wymiar_okna < 1)
        wymiar_okna = 1;


    cv::blur(src, dst, cv::Size(wymiar_okna, wymiar_okna) );
    cv::imshow("Usrednianie", dst);

}

void MojeObrazki::Gauss_Demo()  {

    int rozmycie = 1;
        if(wymiar_okna % 2 == 1) {
            rozmycie = wymiar_okna;
        } else if (wymiar_okna >= 2) {
            rozmycie = wymiar_okna - 1;
        }


    cv::GaussianBlur(src, dst, cv::Size(rozmycie, rozmycie), 0, 0);
    cv::imshow("Gauss", dst);

}



void MojeObrazki::on_actionMediana_triggered()
{

           if(!PokazObrazek.isEmpty())

           src = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);

           cv::namedWindow("Mediana", cv::WINDOW_AUTOSIZE);
           cv::createTrackbar("Wielkość okna","Mediana", &wielkosc_okna, 100, &Mediana_callback, this);

           Mediana();
}


void MojeObrazki::on_actionUsrednianie_triggered()
{
           if(!PokazObrazek.isEmpty())

           src = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);

           cv::namedWindow("Usrednianie", cv::WINDOW_AUTOSIZE);
           cv::createTrackbar("Wielkość okna","Usrednianie", &wymiar_okna, 100, &Usrednianie_callback, this);

           Usrednianie();
}


void MojeObrazki::on_actionGauss_triggered()
{
          if(!PokazObrazek.isEmpty())

          src = imread(PokazObrazek.toStdString().c_str(), IMREAD_COLOR);

          cv::namedWindow("Gauss", cv::WINDOW_AUTOSIZE);
          cv::createTrackbar("Wielkość okna","Gauss", &wymiar_okna, 100, &Gauss_callback, this);

          Gauss_Demo();
}

