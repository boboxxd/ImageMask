#include "xmltool.h"

QString toString(QPoint point)
{
    QString tmp;
    tmp=QString("(%1,%2)").arg(point.x()).arg(point.y());
    return tmp;
}

XmlTool::XmlTool(const QString &filename,QVector<QPoint> vec)
{
    setFile(filename,vec);
}

void XmlTool::setFile(const QString &filename,QVector<QPoint> vec)
{
    qDebug()<<"void XmlTool::setFile(const QString &filename,QVector<QPoint> vec)";
    file.setFileName(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QXmlStreamWriter writer(&file);
         writer.setAutoFormatting(true);
         writer.writeStartDocument();
         writer.writeStartElement("Area");
         QVector<QPoint>::iterator it;
         int index=0;
         for ( it = vec.begin(); it != vec.end(); it++ )
         {
             writer.writeTextElement(QString("Point%1").arg(++index),toString(*it));
         }
         writer.writeEndElement();
         writer.writeEndDocument();
         file.close();
     }
}

