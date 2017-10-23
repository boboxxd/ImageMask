#include "logwindow.h"
#include<QTime>
LogWindow::LogWindow(QWidget *parent) : QTextBrowser(parent)
{

}

void LogWindow::ShowMsg(const QString& msg)
{
    append(QString("[%1]: %2").arg(QTime::currentTime().toString("hh:mm:ss:zzz")).arg(msg));
}
