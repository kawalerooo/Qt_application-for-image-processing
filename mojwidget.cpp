#include "mojwidget.h"

#include <QGridLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QWidget>


MyNewWidget::MyNewWidget(QWidget*parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout();

    label = new QLabel(this);
    label->setText("Kanał niebieski:");
    layout->addWidget(label);
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    layout->addWidget(slider);

    label2 = new QLabel(this);
    label2->setText("Kanał zielony:");
    layout->addWidget(label2);
    slider2 = new QSlider(this);
    slider2->setOrientation(Qt::Horizontal);
    layout->addWidget(slider2);

    label3 = new QLabel(this);
    label3->setText("Kanał czerwony:");
    layout->addWidget(label3);
    slider3 = new QSlider(this);
    slider3->setOrientation(Qt::Horizontal);
    layout->addWidget(slider3);

    QPushButton *button = new QPushButton(this);
    button->setText("Generuj obraz");
    layout->addWidget(button);

    connect(button, SIGNAL(clicked()), this, SLOT(generujObraz()));

    label4 = new QLabel(this);
    label4->setText("Kanał alfa:");
    layout->addWidget(label4);
    slider4 = new QSlider(this);
    slider4->setOrientation(Qt::Horizontal);
    layout->addWidget(slider4);

    label5 = new QLabel(this);
    label5->setText("Kanał beta:");
    layout->addWidget(label5);
    slider5 = new QSlider(this);
    slider5->setOrientation(Qt::Horizontal);
    layout->addWidget(slider5);

    QPushButton *button2 = new QPushButton(this);
    button2->setText("Generuj obraz convertTo");
    layout->addWidget(button2);
    connect(button2, SIGNAL(clicked()), this, SLOT(generujObrazConvert()));


    setLayout(layout);
}

void MyNewWidget::generujObraz()
{
    if(!sciezkaObrazu.isEmpty())
    {
        string str = sciezkaObrazu.toStdString();
        Mat obraz_in = imread(str);
        Mat obraz_out=cv::Mat::zeros(obraz_in.size(), obraz_in.type());

        double a_Blue = 100 - slider->value();
        double b_Blue = slider->value();
        double a_Green = 100 - slider2->value();
        double b_Green = slider2->value();
        double a_Red = 100 - slider3->value();
        double b_Red = slider3->value();

        for(int y=0; y<obraz_in.rows; y++)
        for(int x=0; x<obraz_in.cols; x++)
        {
        // kanal niebieski
        obraz_out.at<cv::Vec3b>(y,x)[0] = cv::saturate_cast<uchar>(a_Blue*( obraz_in.at<cv::Vec3b>(y,x)[0] ) + b_Blue);
        // kanal zielony
        obraz_out.at<cv::Vec3b>(y,x)[1] = cv::saturate_cast<uchar>(a_Green*( obraz_in.at<cv::Vec3b>(y,x)[1] ) + b_Green);
        // kanal czerwony
        obraz_out.at<cv::Vec3b>(y,x)[2] = cv::saturate_cast<uchar>(a_Red*(obraz_in.at<cv::Vec3b>(y,x)[2] + b_Red));
        }

        imshow("obrazekKontrastJasnosc", obraz_out);
    }

}

void MyNewWidget::generujObrazConvert()
{
    if(!sciezkaObrazu.isEmpty())
    {
        string str = sciezkaObrazu.toStdString();
        Mat obraz_in = imread(str);
        Mat obraz_out=cv::Mat::zeros(obraz_in.size(), obraz_in.type());

        obraz_in.convertTo(obraz_out, -1, slider4->value(), slider5->value());
        imshow("obrazekKontrastJasnosc", obraz_out);
    }
}
