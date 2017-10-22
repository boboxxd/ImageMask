#include "showlabel.h"
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<exception>
#include"xmltool.h"
ShowLabel::ShowLabel(QWidget *parent) : QLabel(parent)
{
    kind=-1;
    setMouseTracking(true);
}

void ShowLabel::setKind(int i)
{
    kind=i;
}

void ShowLabel::loadimage(QString imagename)
{
    qDebug()<<"void ShowLabel::loadimage(QString imagename)";
    QImage _image(imagename);    
    loadimage(_image);
}

void ShowLabel::loadimage(const QImage &_image)
{
    qDebug()<<"void ShowLabel::loadimage(QImage _image)";
    if(!_image.isNull())
    {
     qDebug()<<_image.size();
    image=_image;
    imagewidth=image.width();
    imageheight=image.height();
    if(this->width()<imagewidth||this->height()<imageheight)
    {      
        scaleimage=image.scaled(this->width(),this->height(),Qt::KeepAspectRatio);
        widthrate=scaleimage.width()*1.0/imagewidth;
        heightrate=scaleimage.height()*1.0/imageheight;
    }else
    {
        scaleimage=image;
    }
        qDebug()<<"endif";
    }
    update();
}

void ShowLabel::resizeEvent(QResizeEvent *e)
{
    qDebug()<<"void ShowLabel::resizeEvent(QResizeEvent *e)";
    if(this->width()<imagewidth||this->height()<image.height())
    {
        scaleimage=image.scaled(this->width(),this->height(),Qt::KeepAspectRatio);
        widthrate=scaleimage.width()*1.0/imagewidth;
        heightrate=scaleimage.height()*1.0/imageheight;
        qDebug()<<imagewidth<<":"<<imageheight;
    }
    update();
}

void ShowLabel::paintEvent(QPaintEvent *e)
{
    qDebug()<<"void ShowLabel::paintEvent(QPaintEvent *e)";
    painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    if(!scaleimage.isNull())
    {
        painter->drawImage(0,0,scaleimage);
    }else{}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    painter->begin(&scaleimage);
    painter->setPen(QPen(Qt::red,2));

//绘制已经完成的图形
{
 /******************************************************************/
        //绘制多边形
        if(polygonvec.size()>=1)
        {
            for(int i=0;i<polygonvec.size();i++)
            {
                Polygon tmp=polygonvec[i];
                 for(int j=0;j<tmp.size()-1;j++)
                     painter->drawLine(tmp.GetPoints()[j],tmp.GetPoints()[j+1]);
            }
        }
/******************************************************************/
        //绘制矩形
        if(rectvec.size()>=1)
        {
            for(int i=0;i<rectvec.size();i++)
            {
                Rect tmp=rectvec[i];
                     painter->drawRect(QRect(tmp.first(),tmp.last()));
            }
        }
/******************************************************************/
        //绘制箭头

}

/******************************************************************/
    if(kind==0)
    {
            if(rect.size()>=1)
            {
             if(rect.iscomplete==false)
                painter->drawRect(QRect(rect.first(),cur));
            painter->end();
            }
    }
/******************************************************************/
if(kind==1)
{
//绘制已经绘制成功的线段
    if(polyon.size()>=1)
    {
     for(int i=0;i<polyon.size()-1;i++)
         painter->drawLine(polyon.GetPoints()[i],polyon.GetPoints()[i+1]);
//绘制正在绘制的线段
     if(polyon.iscomplete==false)
        painter->drawLine(polyon.last(),cur);

    painter->end();
    }
}
/******************************************************************/
if(kind==2)
{

}

}





void ShowLabel::mousePressEvent(QMouseEvent *e)
{
    switch(e->button())
    {
//###############################鼠标左击事件##############################################
        case Qt::LeftButton:
        setCursor(Qt::CrossCursor);

/******************************************************************/
//绘制矩形
        if(kind==0)
        {
            cur=e->pos();
            rect.add(cur);
            if(rect.size()==2)
            {
               rect.iscomplete=true;
            }
            if(rect.iscomplete==true)
            {
                rectvec.append(rect);
                Rect tmp;
                rect=tmp;
            }
        }

/******************************************************************/
//绘制多边形
        if(kind==1){
            if(polyon.iscomplete==true)
            {
                Polygon tmp;
                polyon=tmp;
            }

            cur=e->pos();
            polyon.add(cur);
        }
/******************************************************************/
//绘制箭头
       if(kind==2)
       {
           //绘制箭头
       }

/******************************************************************/
        break;
//###################################鼠标右击事件##########################################
        case Qt::RightButton:
        if(kind==1)
        {
        if(polyon.iscomplete==false)
        {
            polyon.add(polyon.first());
            polyon.iscomplete=true;
            polygonvec.append(polyon);
            polyon.clear();
            qDebug()<<polyon.size();
        }
        }
        break;
    }
    update();
}

void ShowLabel::mouseMoveEvent(QMouseEvent *e)
{
    cur=e->pos();
    this->setToolTip(toString(cur));
    update();
}

void ShowLabel::mouseReleaseEvent(QMouseEvent *e)
{
    setCursor(Qt::ArrowCursor);
}


QVector<QPoint> ShowLabel::getpoints()
{
    switch(kind)
    {
    case 0:
        if(!rectvec.isEmpty())
        return rectvec.first().GetPoints();

        break;
    case 1:
        if(!polygonvec.isEmpty())
        return polygonvec.first().GetPoints();

        break;
    default:
        break;
    }
}

void ShowLabel::clear()
{
    rect.clear();
    polyon.clear();
    rectvec.clear();
    polygonvec.clear();
    update();
}

bool ShowLabel::isEmpty()
{
    if(rectvec.isEmpty()||polygonvec.isEmpty()||rect.isempty()||polyon.isempty())
        return true;
    return false;
}

Factor ShowLabel::getfactor()
{
    Factor factor;
    factor.ratex=widthrate;
    factor.ratey=heightrate;
    return factor;
}

QString ShowLabel::toLog()
{
    QString logmsg("已设置监控区域：\n");
    auto vec=this->getpoints();
    for(int i=0;i<vec.size();i++)
    {
        logmsg+=" "+toString(vec.at(i));
    }
    //logmsg+=QString('-',10);
    return logmsg;
}
