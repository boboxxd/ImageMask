#include "getimage.h"
#include<QDebug>

void GetImage::doWork(const QString &path)
{
    qDebug()<<"void GetImage::doWork(const QString &path)";    
    emit msg("正在尝试连接摄像机:"+path+",请稍等...");
    QImage result;
    VideoCapture videoCap;
    Mat srcImage;
    videoCap.open(path.toStdString().c_str());
    if(videoCap.isOpened())
    {
        emit msg("连接摄像机:"+path+"成功");
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
        emit msg("连接摄像机:"+path+"失败，请检查登录信息是否正确");
    }

}

void Controller::handleResults(const QImage &_image)
{
    qDebug()<<"void Controller::handleResults(const QImage &_image)";
    emit msg(QString("从摄像机上取图成功,原图大小:%1*%2").arg(_image.width()).arg(_image.height()));
    emit image(_image);

}
void Controller::getmsg(const QString &_msg)
{
    emit msg(_msg);
}
