#ifndef XMLTOOL_H
#define XMLTOOL_H
#include<QtXml>
#include<QFile>

//坐标转string
QString toString(QPoint point);

///
/// \brief 写入xml的类
///
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
