#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QObject>
#include <QWidget>
#include<QTextBrowser>

class LogWindow : public QTextBrowser
{
    Q_OBJECT
public:
    explicit LogWindow(QWidget *parent = 0);

signals:

public slots:
    void ShowMsg(const QString&);
};

#endif // LOGWINDOW_H
