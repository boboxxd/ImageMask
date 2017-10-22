#ifndef SHOWLABEL_H
#define SHOWLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QImage>
#include<QResizeEvent>
#include"common.h"

//图形选项：0：矩形 1：多边形 2:箭头

///
/// \brief 存储坐标伸缩因子
///
struct Factor
{
    qreal ratex=1;
    qreal ratey=1;
};

///
/// \brief 图片显示界面
///
class ShowLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ShowLabel(QWidget *parent = 0);

    //处理各种事件
    void paintEvent(QPaintEvent *e);   
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

    //返回所有点的坐标
    QVector<QPoint> getpoints();

    //清空图片上和底层数据结构上所有图形
    void clear();

    //获取伸缩因子
    Factor getfactor();

    //判断界面上是否为空
    bool isEmpty();

    //记录保存日志
    QString toLog();

signals:

public slots:
    //选择绘制图形type
    void setKind(int i);

    //载入本地图片
    void loadimage(QString imagename);

    //载入内存中的文件
    void loadimage(const QImage& _image);
private:
    QPainter *painter;

    //摄像机上获取的原图
    QImage image;

    //原图大小
    int imagewidth;
    int imageheight;

    //缩放比例
    qreal widthrate;
    qreal heightrate;

    //缩小后的图片
    QImage scaleimage;

    //鼠标当前坐标
    QPoint cur;

    //存储当前所绘图形
    Polygon polyon;
    Rect rect;

    //存储已经绘制好的图形
    QVector<Rect> rectvec;
    QVector<Polygon> polygonvec;

    //
    bool isfinished=false;

    //图形type
    int kind;
};

#endif // SHOWLABEL_H
