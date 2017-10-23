#ifndef SHOWLABEL_H
#define SHOWLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QImage>
#include<QResizeEvent>
#include<memory>
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

    void drawLine(QPoint,QPoint,int type=0);
    void drawRect(QPoint,QPoint,int type=0);//type:报警区域/处理区域
    void drawPolygon(Polygon&,int type=0);
    void drawArrow(QPoint,QPoint,int type=0);

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

    void allocate(std::shared_ptr<RectAbstract> m,int type);

signals:

public slots:
    //选择绘制图形type
    void setKind(int i);

    //选择区域类型
    void setType(int i);

    //载入本地图片
    void loadimage(QString imagename);

    //载入内存中的文件
    void loadimage(const QImage& _image);

    QVector<std::shared_ptr<RectAbstract>> getAlarmAreas();
    QVector<std::shared_ptr<RectAbstract>> getHandleAreas();
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
    Arrow arrow;

    //存储已经绘制好的图形
    QVector<Rect> rectvec;
    QVector<Polygon> polygonvec;
    QVector<Arrow> arrowvec;

    //报警区域和处理区域
    QVector<std::shared_ptr<RectAbstract>> AlarmAreaVec;
    QVector<std::shared_ptr<RectAbstract>> HandleAreaVec;


    bool isfinished=false;

    //图形type
    int kind;
    //区域类别
    int type;
};

#endif // SHOWLABEL_H
