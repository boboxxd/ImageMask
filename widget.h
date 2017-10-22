#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include"common.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void initwindow();
    ~Widget();

signals:

public slots:
    void drawRect();//绘制矩形
    void drawPolygon();//绘制多边形
    void drawArrow();//绘制箭头
    void save();
    void onconnectbtn();
    void onclearbtn();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
