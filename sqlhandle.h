#ifndef SQLHANDLE_H
#define SQLHANDLE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class SqlHandle:public QObject
{
    Q_OBJECT
public:
    SqlHandle();
    ~SqlHandle()=default;
    //connect  the database
    bool connect(const QString& databasename,const QString& host,int port,const QString& username,const QString& passward);
    //create table
    bool CreateTable(const QString &cmd);
    //add
    bool Insert(const QString &cmd);
    //change
    bool Modify(const QString &cmd);
    //delete
    bool Drop(const QString &cmd);
    //query
    bool Querry(const QString &cmd);
public slots:

signals:

private:
   QSqlDatabase database;
   QSqlQuery sql_query;
};

#endif // SQLHANDLE_H
