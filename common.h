#ifndef COMMON_H
#define COMMON_H

//图形抽象类
#include<QVector>
#include<QPoint>
#include<QDebug>


class Arrow
{

};


class RectAbstract
{
public:
    RectAbstract()=default;
    virtual ~RectAbstract(){}
    //返回图形的所有坐标点
    virtual QVector<QPoint> GetPoints()
    {
        QVector<QPoint> tmp=points;
        return tmp;
    }

    //添加一个坐标点
    virtual int add(QPoint point) //返回当前坐标个数
    {
        points.append(point);
        mindex++;
        return this->size();
    }

    QPoint first()
    {
        return *points.begin();
    }

    QPoint last()
    {
        return *(points.end()-1);
    }

    //删除一个坐标点
   virtual int del()//返回当前坐标个数
    {
        points.clear();
//        if(!isempty())
//        {
//            return this->size();
//        }else
//        {
//            points.pop_back();
//            points.clear();
//            return this->size();
//        }

    }

    //清空所有坐标
    virtual void clear()
    {
        points.clear();
    }

    //判断是否为空
    bool isempty()
    {
        return points.empty();
    }

    //返回坐标点个数
    int size()
    {
        return points.size();
    }
 int index()
 {
     return mindex;
 }

protected:
   QVector<QPoint> points;
   int mindex=0;
};

//矩形---斜拉
class Rect:public RectAbstract
{
public:
    Rect()=default;
    bool iscomplete=false;
    virtual QVector<QPoint> GetPoints()
    {
        QVector<QPoint> tmp;
        tmp.append(points.first());
        tmp.append(QPoint (points.last().x(),points.first().y()));
        tmp.append(points.last());
        tmp.append(QPoint(points.first().x(),points.last().y()));
        return tmp;
    }
};



//多边形
class  Polygon:public RectAbstract
{
public:
    Polygon()=default;
    bool iscomplete=false;
};




#endif // COMMON_H
