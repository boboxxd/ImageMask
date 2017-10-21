#include "getimage.h"
#include<QDebug>

void GetImage::doWork(const QString &path)
{
    qDebug()<<"void GetImage::doWork(const QString &path)";
    QImage result;
    VideoCapture videoCap;
    Mat srcImage;
    videoCap.open(path.toStdString().c_str());
    if(videoCap.isOpened())
    {
        srcImage = Mat::zeros(videoCap.get(CV_CAP_PROP_FRAME_HEIGHT), videoCap.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
        videoCap>>srcImage;
        videoCap.release();
    if(srcImage.data)
    {
        cvtColor(srcImage, srcImage, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR
        result=QImage((uchar*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);
        emit resultReady(result);
    }
    }else
    {
        qDebug()<<"连接失败";
    }

}

void Controller::handleResults(const QImage &_image)
{
    qDebug()<<"void Controller::handleResults(const QImage &_image)";
    qDebug()<<_image.depth();
    emit image(_image);
}
