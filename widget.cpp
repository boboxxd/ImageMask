#include "widget.h"
#include "ui_widget.h"
#include<QPixmap>
#include"getimage.h"
#include"xmltool.h"
#include"logwindow.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initwindow();
    connect(ui->rectbtn,SIGNAL(clicked(bool)),this,SLOT(drawRect()));
    connect(ui->polygonbtn,SIGNAL(clicked(bool)),this,SLOT(drawPolygon()));
    connect(ui->arrowbtn,SIGNAL(clicked(bool)),this,SLOT(drawArrow()));
    connect(ui->savebtn,SIGNAL(clicked(bool)),this,SLOT(save()));

    connect(ui->connectbtn,SIGNAL(clicked(bool)),this,SLOT(onconnectbtn()));
    connect(ui->clearbtn,SIGNAL(clicked(bool)),this,SLOT(onclearbtn()));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(oncheckbox(int)));
    connect(this,SIGNAL(msg(const QString&)),ui->logwnd,SLOT(ShowMsg(const QString &)));
    connect(&radiogroup,SIGNAL(buttonClicked(int)),ui->label,SLOT(setType(int)));
    connect(&radiogroup,SIGNAL(buttonClicked(int)),this,SLOT(setbutton(int)));
}

//初始化窗口
void Widget::initwindow()
{
   this->setWindowTitle("ImageMark");
   this->setFixedSize(870,600);

   this->radiogroup.addButton(ui->alarmareabtn,0);
   this->radiogroup.addButton(ui->handleareabtn,1);



   ui->alarmareabtn->setChecked(true);
   ui->label->loadimage(":/background.png");
   ui->lineEdit->setVisible(false);
   ui->useredit->setPlaceholderText("输入用户名");
   ui->useredit->setText("admin");
   ui->passwdedit->setPlaceholderText("输入密码");
   ui->passwdedit->setText("ad53937301");
   ui->ipedit->setPlaceholderText("输入IP");
   ui->ipedit->setText("49.91.240.8");
   ui->portedit->setPlaceholderText("输入端口号");
   ui->portedit->setText("554");
   ui->channeledit->setPlaceholderText("输入通道号");
   ui->channeledit->setText("1");
   ui->lineEdit->setPlaceholderText("输入rtsp地址");


   // rtsp://admin:ad53937301@49.91.240.8:554/h264/ch1/main/av_stream
   // /Users/xuxudong/Temp/test.avi
}

void Widget::setbutton(int type)
{
    switch(type)
    {
        case 0:
            ui->polygonbtn->setEnabled(true);
            ui->arrowbtn->setEnabled(true);
        break;

        case 1:
            ui->polygonbtn->setEnabled(false);
            ui->arrowbtn->setEnabled(false);
        break;


    }
}

//选择框响应事件
void Widget::oncheckbox(int state)
{
    qDebug()<<"void Widget::oncheckbox()";
    if(state==0)
    {
        qDebug()<<"0:"<<state;
        ui->lineEdit->setVisible(false);
        ui->useredit->setEnabled(true);
        ui->passwdedit->setEnabled(true);
        ui->ipedit->setEnabled(true);
        ui->portedit->setEnabled(true);
        ui->channeledit->setEnabled(true);
    }else
    {
        qDebug()<<"1:"<<state;
        ui->lineEdit->setVisible(true);
        ui->useredit->setEnabled(false);
        ui->passwdedit->setEnabled(false);
        ui->ipedit->setEnabled(false);
        ui->portedit->setEnabled(false);
        ui->channeledit->setEnabled(false);
    }
}

//连接按钮响应事件
void Widget::onconnectbtn()
{
    qDebug()<<ui->lineEdit->text();
    ui->label->clear();

//开启捕获图片的线程
    Controller *con=new Controller;
    connect(con,SIGNAL(image(const QImage&)),ui->label,SLOT(loadimage(const QImage&)));
    connect(con,SIGNAL(msg(const QString &)),ui->logwnd,SLOT(ShowMsg(const QString &)));
    QString url;
    if(!ui->checkBox->isChecked())
    {
        url=QString("rtsp://%1:%2@%3:%4/h264/ch%5/main/av_stream").arg(ui->useredit->text().trimmed())
                .arg(ui->passwdedit->text().trimmed())
                .arg(ui->ipedit->text().trimmed())
                .arg(ui->portedit->text().trimmed())
                .arg(ui->channeledit->text().trimmed());
    }else
    {
        url=ui->lineEdit->text().trimmed();
    }
    con->operate(url);
}

//清空按钮响应事件
 void Widget::onclearbtn()
 {
     ui->label->clear();
     ui->logwnd->clear();
 }



Widget::~Widget()
{
    delete ui;
}

//绘制矩形
void Widget::drawRect()
{
    qDebug()<<"void Widget::drawRect()";
    ui->label->setKind(0);
    ui->label->update();
}

//绘制多边形
void Widget::drawPolygon()
{
    qDebug()<<"void Widget::drawPolygon()";
    ui->label->setKind(1);
    ui->label->update();
}

void Widget::drawArrow()
{
    qDebug()<<"void Widget::drawArrow()";

    ui->label->setKind(2);
    ui->label->update();
}

//保存为xml文件
void Widget::save()
{

    ui->logwnd->clear();
    qDebug()<<"void Widget::save()";
    emit msg(ui->label->toLog());

        qDebug()<<"write xml";
        if(!ui->label->getpoints().isEmpty())
        {
        auto vec=ui->label->getpoints();
        QVector<QPoint> tmp;
        for(auto i=vec.begin();i!=vec.end();i++)
        {
           tmp.push_back(QPoint(i->x()/ui->label->getfactor().ratex,i->y()/ui->label->getfactor().ratey));
        }
        XmlTool  xml("Area.xml",tmp);
    }

}
