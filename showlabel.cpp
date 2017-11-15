#include "showlabel.h"
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
#include<exception>
#include"xmltool.h"
ShowLabel::ShowLabel(QWidget *parent) : QLabel(parent)
{
    kind=-1;
    type=0;
    setMouseTracking(true);
}

void ShowLabel::setKind(int i)
{
    kind=i;
}

void ShowLabel::setType(int i)
{
    type=i;
    if(type==1)
        kind=0;
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

void ShowLabel::drawLine(QPoint begin,QPoint end,int type)
{
    switch(type)
    {
        case 0://报警区域
            painter->setPen(QPen(Qt::red,2));
        break;

        case 1: //处理区域
            painter->setPen(QPen(Qt::blue,2));
        break;
    }
    painter->drawLine(begin,end);
}

void ShowLabel::drawRect(QPoint begin,QPoint end,int type)//type:报警区域/处理区域
{
    switch(type)
    {
        case 0://报警区域
            painter->setPen(QPen(Qt::red,2));
        break;

        case 1: //处理区域
            painter->setPen(QPen(Qt::blue,2));
        break;
    }
     painter->drawRect(QRect(begin,end));
}

void ShowLabel::drawPolygon(Polygon& polygon,int type)
{
    switch(type)
    {
        case 0://报警区域
            painter->setPen(QPen(Qt::red,2));
        break;

        case 1: //处理区域
            painter->setPen(QPen(Qt::blue,2));
        break;
    }
    for(int i=0;i<polygon.size()-1;i++)
        drawLine(polygon.GetPoints()[i],polygon.GetPoints()[i+1],type);
}

//绘制箭头的工具函数
void ShowLabel::drawArrow(QPoint begin,QPoint end,int type)
{
        int x1 = begin.x();                                     //取points[0]起点的x
        int y1 = begin.y();                                     //取points[0]起点的y
        int x2 = end.x();                                       //取points[count-1]终点的x
        int y2 = end.y();                                       //取points[count-1]终点的y
        int l = 10.0;                                           //箭头的长度
        int a = 1;                                            //箭头与线段角度
        int x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);//计算箭头的终点（x3,y3）
        int y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
        int x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);//计算箭头的终点（x4,y4）
        int y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
        switch(type)
        {
            case 0://报警区域
                painter->setPen(QPen(Qt::red,2));
            break;

            case 1: //处理区域
                painter->setPen(QPen(Qt::blue,2));
            break;
        }
        drawLine(QPoint(x2,y2),QPoint(x3,y3),type);                                 //绘制箭头(x2,y2,x3,y3)
        drawLine(QPoint(x2,y2),QPoint(x4,y4),type);                                 //绘制箭头(x2,y2,x4,y4)
        drawLine(begin,end,type);                                   //绘制主干箭头(begin,end)
}

void ShowLabel::allocate(std::shared_ptr<RectAbstract> m,int type)
{
    switch(type)
    {
    case 0:
        AlarmAreaVec.append(m);
        break;
    case 1:
        HandleAreaVec.append(m);
        break;
    default:
        break;
    }
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
                drawPolygon(tmp,tmp.type);
            }
        }
/******************************************************************/
        //绘制矩形
        if(rectvec.size()>=1)
        {
            for(int i=0;i<rectvec.size();i++)
            {
                Rect tmp=rectvec[i];
                drawRect(tmp.first(),tmp.last(),tmp.type);
            }
        }

        if(arrowvec.size()>=1)
        {
            for(int i=0;i<arrowvec.size();i++)
            {
                Arrow tmp=arrowvec[i];
                     drawArrow(tmp.first(),tmp.last(),tmp.type);
            }
        }
/******************************************************************/
}

/******************************************************************/
    if(kind==0)
    {

            if(rect.size()>=1)
            {
             if(rect.iscomplete==false)
                 drawRect(rect.first(),cur,type);
            painter->end();
            }
    }
/******************************************************************/
if(kind==1)
{
//绘制已经绘制成功的线段
    if(polyon.size()>=1)
    {
        drawPolygon(polyon,polyon.type);
//绘制正在绘制的线段
     if(polyon.iscomplete==false)
        drawLine(polyon.last(),cur,type);
    painter->end();
    }
}
/******************************************************************/
if(kind==2)
{
    if(arrow.size()>=1)
    {
     if(arrow.iscomplete==false)
        drawArrow(arrow.first(),cur,type);
    painter->end();
    }
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
            rect.add(cur,type);
            if(rect.size()==2)
            {
               rect.iscomplete=true;
            }
            if(rect.iscomplete==true)
            {
                rectvec.append(rect);
                allocate(std::make_shared<Rect>(rect),rect.type);
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
            polyon.add(cur,type);
        }
/******************************************************************/
//绘制箭头
       if(kind==2)
       {
           //绘制箭头
           cur=e->pos();
           arrow.add(cur,type);
           if(arrow.size()==2)
           {
              arrow.iscomplete=true;
           }
           if(arrow.iscomplete==true)
           {
               arrowvec.append(arrow);
               //allocate(std::make_shared<Arrow>(arrow),arrow.type);
               Arrow tmp;
               arrow=tmp;
           }

       }

/******************************************************************/
        break;
//###################################鼠标右击事件##########################################
        case Qt::RightButton:
        if(kind==1)
        {
        if(polyon.iscomplete==false)
        {
            polyon.add(polyon.first(),type);
            polyon.iscomplete=true;
            polygonvec.append(polyon);
            allocate(std::make_shared<Polygon>(polyon),polyon.type);
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
    this->setToolTip(toString(QPoint(cur.x()/widthrate,cur.y()/heightrate)));
    update();
}

void ShowLabel::mouseReleaseEvent(QMouseEvent *e)
{
    setCursor(Qt::ArrowCursor);
}


QVector<QPoint> ShowLabel::getpoints()
{
    qDebug()<<"QVector<QPoint> ShowLabel::getpoints()";

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
        return rectvec.first().GetPoints();
        break;
    }


}

void ShowLabel::clear()
{
    rect.clear();
    polyon.clear();
    arrow.clear();
    rectvec.clear();
    polygonvec.clear();
    arrowvec.clear();
    AlarmAreaVec.clear();
    HandleAreaVec.clear();
    update();
}

bool ShowLabel::isEmpty()
{
    if(rectvec.isEmpty()&&polygonvec.isEmpty()&&arrowvec.isEmpty()&&arrow.isempty()&&rect.isempty()&&polyon.isempty())
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

QVector<std::shared_ptr<RectAbstract>> ShowLabel::getAlarmAreas()
{
    return AlarmAreaVec;
}

QVector<std::shared_ptr<RectAbstract>> ShowLabel::getHandleAreas()
{
    return HandleAreaVec;
}

QString ShowLabel::toLog()
{
    qDebug()<<"QString ShowLabel::toLog()";
    QString logmsg("\n--begin-----------------------------------------------------\n已设置报警区域：\n");
    auto p=getAlarmAreas();
    if(p.size()==0){logmsg+="(空)\n";}
    for(int i=0;i<p.size();i++)
    {
        if(i==p.size()-1){logmsg+='\n';}
        logmsg+=QString("A%1\t").arg(i);
        auto vec=p[i]->GetPoints();

//-----------------------------------------------------------------------------------------
        //判断每个区域的出入状态，并写入数据结构中
        QPolygon pp(vec);
        int sum=0;
        for(int m=0;m<arrowvec.size();m++)
        {
//out
            if(pp.containsPoint(arrowvec[m].first(),Qt::OddEvenFill)&&
                    !pp.containsPoint(arrowvec[m].last(),Qt::OddEvenFill))
            {
               p[i]->addstate(1);
               //sum++;
            }
//in
            if(pp.containsPoint(arrowvec[m].last(),Qt::OddEvenFill)&&
                    !pp.containsPoint(arrowvec[m].first(),Qt::OddEvenFill))
            {
                p[i]->addstate(0);
                //sum++;
            }

        }

        qDebug()<<p[i]->showState();

//----------------------------------------------------------------------------------------------


        for(int j=0;j<vec.size();j++)
        {
            QPoint tmp(vec.at(j).x()/widthrate,vec.at(j).y()/heightrate);
            logmsg+=' '+toString(tmp);
            if(j==vec.size()-1)
                logmsg+='  '+p[i]->showState()+'\n';
        }
    }



    logmsg+="\n已设置处理区域：\n";
    auto q=getHandleAreas();
    if(q.size()==0){logmsg+="(空)\n";}
    for(int i=0;i<q.size();i++)
    {
        if(i==q.size()-1){logmsg+='\n';}
        logmsg+=QString("H%1\t").arg(i);
        auto vec=q[i]->GetPoints();
        for(int j=0;j<vec.size();j++)
        {
            QPoint tmp(vec.at(j).x()/widthrate,vec.at(j).y()/heightrate);
            logmsg+=' '+toString(tmp);
            if(j==vec.size()-1)
                logmsg+='\n';
        }
    }
    logmsg+="\n--end-------------------------------------------------------";
    return logmsg;

}
