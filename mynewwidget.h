#ifndef MYNEWWIDGET_H
#define MYNEWWIDGET_H

#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QTime>
#include <QMessageBox>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QPixmap>
#include <QDebug>
#include <QSlider>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <QTimer>

using namespace std;
using namespace cv;
class MyNewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyNewWidget(QWidget *parent = 0);
    QString sciezkaObrazu;

private slots:
    void generujObraz();

    void generujObrazConvert();

private:
    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QSlider *slider;
    QSlider *slider2;
    QSlider *slider3;
    QSlider *slider4;
    QSlider *slider5;
     QWidget *nr1;
};

#endif // MYNEWWIDGET_H
