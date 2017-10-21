#ifndef XMLTOOL_H
#define XMLTOOL_H
#include<QTXML>
#include<QFile>

QString toString(QPoint point);
class XmlTool
{
public:
    XmlTool()=default;
    XmlTool(const QString &filename,QVector<QPoint> vec);
    void setFile(const QString &filename,QVector<QPoint> vec);
private:
    QFile file;
};

#endif // XMLTOOL_H
