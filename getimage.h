#ifndef GETIMAGE_H
#define GETIMAGE_H
#include<opencv2/opencv.hpp>
#include<QImage>
#include<QObject>
#include<QThread>
using namespace cv;





class GetImage:public QObject
{
    Q_OBJECT
signals:
    void resultReady(const QImage &image);
public slots:
    void doWork(const QString &);
};

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
              workerThread.start();
          }
          ~Controller() {
              workerThread.quit();
              workerThread.wait();
          }

      public slots:
          void handleResults(const QImage & );
      signals:
          void operate(const QString &);
          void image(const QImage &image);

};

#endif // GETIMAGE_H
