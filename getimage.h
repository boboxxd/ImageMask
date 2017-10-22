#ifndef GETIMAGE_H
#define GETIMAGE_H
#include<opencv2/opencv.hpp>
#include<QImage>
#include<QObject>
#include<QThread>
using namespace cv;




///
/// \brief 取图工作类
///
class GetImage:public QObject
{
    Q_OBJECT
signals:
    void resultReady(const QImage &image);
    void msg(const QString &);
public slots:
    void doWork(const QString &);
};



///
/// \brief 线程控制类
///
class Controller:public QObject
{
    Q_OBJECT
          QThread workerThread;
      public:
          Controller() {
              workerThread.setObjectName("sub_getimage");
              GetImage *worker = new GetImage;
              worker->moveToThread(&workerThread);
              connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
              connect(this, &Controller::operate, worker, &GetImage::doWork);
              connect(worker, &GetImage::resultReady, this, &Controller::handleResults);
              connect(worker,&GetImage::msg,this,&Controller::getmsg);
              workerThread.start();
          }
          ~Controller() {
              workerThread.quit();
              workerThread.wait();
          }

      public slots:
          void handleResults(const QImage & );
          void getmsg(const QString &);
      signals:
          void operate(const QString &);
          void image(const QImage &image);
          void msg(const QString &);

};

#endif // GETIMAGE_H
