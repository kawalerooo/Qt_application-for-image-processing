#ifndef MOJEOBRAZKI_H
#define MOJEOBRAZKI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QProgressBar>
#include <QTimer>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <QWidget>
#include <QDialog>

using namespace std;
using namespace cv;

namespace Ui {
class MojeObrazki;
}

class MojeObrazki : public QMainWindow
{
    Q_OBJECT

public:
    explicit MojeObrazki(QWidget *parent = 0);
    ~MojeObrazki();

    void Skaluj();

    void Rotacja();

    void Mediana();

    void Usrednianie();

    void Gauss_Demo();





private slots:
    void on_actionOtw_rz_triggered();

    void on_actionZapisz_triggered();

    void on_actionWyj_cie_triggered();

    void on_actionPokaz_obrazek_triggered();

    void on_actionR_triggered();

    void on_actionG_triggered();

    void on_actionB_triggered();

    void on_actionY_triggered();

    void on_actionCr_triggered();

    void on_actionCb_triggered();


    void on_actionH_triggered();

    void on_actionS_triggered();

    void on_actionV_triggered();

    void mam_zegarek();

    void on_actionLAB07_triggered();

    void on_actionProgowanie_triggered();




    void on_actionSkalowanie_triggered();

    void on_actionRotacja_triggered();

    void on_actionMediana_triggered();

    void on_actionUsrednianie_triggered();

    void on_actionGauss_triggered();

public slots:
    void Progowanie();



private:

    Mat zrodlo, wynik, scr_gray;  //lab8
    int prog, max, typ;



    Ui::MojeObrazki *ui;

    QImage * image;
    QGraphicsScene *scene;
    QPixmap pixmap;
    QPixmap pixmap2;
    QGraphicsPixmapItem * obrazek_sceny;
    QString  PokazObrazek;
    QTimer *zegarek;
    QTime czas;
    QLabel czas_info;


    int moj_zegar;
    int licznik_info;
    int kat;
    int skala;
    int kat_obrotu;
    int Skala_x;
    int Skala_y;
    int wymiar_okna;
    int wielkosc_okna;


    Mat dst;
    Mat src;

    Point2f punkt;

    Size rozmiar;






};

#endif // MOJEOBRAZKI_H
