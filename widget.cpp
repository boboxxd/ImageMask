#include "widget.h"
#include "ui_widget.h"
#include<QPixmap>
#include"getimage.h"
#define LABELWIDTH 1080/2
#define LABELHIGHT 720/2
#include"xmltool.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initwindow();
    connect(ui->rectbtn,SIGNAL(clicked(bool)),this,SLOT(drawRect()));
    connect(ui->polygonbtn,SIGNAL(clicked(bool)),this,SLOT(drawPolygon()));
    connect(ui->savebtn,SIGNAL(clicked(bool)),this,SLOT(save()));
    connect(ui->connectbtn,SIGNAL(clicked(bool)),this,SLOT(onconnectbtn()));
    connect(ui->clearbtn,SIGNAL(clicked(bool)),this,SLOT(onclearbtn()));
}

void Widget::onconnectbtn()
{
    qDebug()<<ui->lineEdit->text();
    ui->label->clear();
    //开启捕获图片的线程
    Controller *con=new Controller;
    connect(con,SIGNAL(image(QImage)),ui->label,SLOT(loadimage(QImage)));
    con->operate(ui->lineEdit->text());
}

 void Widget::onclearbtn()
 {
     ui->label->clear();
 }

void Widget::initwindow()
{
    this->setWindowTitle("ImageMark");
    this->setFixedSize(870,600);
    ui->label->loadimage(":/background.png");
    ui->lineEdit->setPlaceholderText("输入摄像机地址");
   // rtsp://admin:ad53937301@49.91.240.16:554/h264/ch1/main/av_stream
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawRect()
{
    qDebug()<<"void Widget::drawRect()";
    ui->label->clear();//目的是在界面上只能出现一个区域
    ui->label->setKind(0);
    ui->label->update();
}

void Widget::drawPolygon()
{
    qDebug()<<"void Widget::drawPolygon()";
    ui->label->clear();//目的是在界面上只能出现一个区域
    ui->label->setKind(1);
    ui->label->update();
}

void Widget::save()
{
    if(ui->label->isEmpty()==false)
    {
        XmlTool  xml("text.xml",ui->label->getpoints());
        qDebug()<<ui->label->getpoints();
        qDebug()<<ui->label->getpoints().size()<<toString(ui->label->getpoints()[0]);
    }

}
