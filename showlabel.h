#ifndef SHOWLABEL_H
#define SHOWLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QImage>
#include<QResizeEvent>
#include"common.h"
struct Factor
{
    qreal ratex=1;
    qreal ratey=1;
};

//坐标乘以伸缩因子



///
/// \brief The ShowLabel class
///
///
class ShowLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ShowLabel(QWidget *parent = 0);


    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);
    QVector<QPoint> getpoints();
    void clear();
    Factor getfactor();
    bool isEmpty();


signals:

public slots:
    void setKind(int i=1000);
    void loadimage(QString imagename);
    void loadimage(QImage _image);
private:
    QPainter *painter;
    QImage *image;

    int imagewidth;
    int imageheight;
    qreal widthrate;
    qreal heightrate;

    QImage *scaleimage;
    QPoint cur;
    Polygon polyon;

    Rect rect;
    QVector<Rect> rectvec;
    QVector<Polygon> polygonvec;
    bool isfinished=false;

    int kind;
};

#endif // SHOWLABEL_H
