#include "showlabel.h"
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<exception>
#include"xmltool.h"
ShowLabel::ShowLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
    this->setToolTipDuration(1000);
    //图形选项：0：矩形 1：多边形
    //kind=0;
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
        qDebug()<<"if(this->width()<imagewidth||this->height()<image->height())";
        //scaleimage=QImage("/Users/xuxudong/Temp/2017101256171001.jpg").scaled(this->width(),this->height(),Qt::KeepAspectRatio);
        scaleimage=image.scaled(this->width(),this->height(),Qt::KeepAspectRatio);
qDebug()<<scaleimage.depth();

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

        //绘制矩形
        if(rectvec.size()>=1)
        {
            for(int i=0;i<rectvec.size();i++)
            {
                Rect tmp=rectvec[i];
                     painter->drawRect(QRect(tmp.first(),tmp.last()));
            }
        }

}


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
if(kind==0)
{
        if(rect.size()>=1)
        {
         if(rect.iscomplete==false)
            painter->drawRect(QRect(rect.first(),cur));
        painter->end();
        }
}
}





void ShowLabel::mousePressEvent(QMouseEvent *e)
{


    switch(e->button())
    {
        case Qt::LeftButton:
        setCursor(Qt::CrossCursor);
        if(kind==1){
            if(polyon.iscomplete==true)
            {
                Polygon tmp;
                polyon=tmp;
            }

            cur=e->pos();
            polyon.add(cur);
        }
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
            //rect.add(cur);

        }
        break;

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
    if(rectvec.isEmpty()||polygonvec.isEmpty())
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

