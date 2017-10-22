#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QObject>
#include <QWidget>

class LogWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LogWindow(QWidget *parent = 0);

signals:

public slots:
};

#endif // LOGWINDOW_H