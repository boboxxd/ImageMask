#include "getimage.h"
#include<QDebug>

void GetImage::doWork(const QString &path)
{
    qDebug()<<"doWork";
    QImage result;
    VideoCapture videoCap;
    Mat srcImage;
    if(videoCap.open(path.toStdString().c_str()))
    {
        srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
    }
        videoCap>>srcImage;
        videoCap>>srcImage;

    if(srcImage.data)
    {
        cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        result=QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
        emit resultReady(result);
    }
}

void Controller::handleResults(const QImage _image)
{
    emit image(_image);
}
