#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include<Qdebug>
#include<QObject>
#include<QSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#pragma execution_character_set("utf-8")

const QString showview="showdata";

class dbConnect{
private:
//    static QString username;
//    static QString psw;

public:
     QString Username(QString uname);
     QString Psw(QString psw);
     QString initshowdata();
     QString sortbyGID();
     QString sortbytime();
     QString sortbyKUL();
     QString unclearsearch(QString &find);
     QString selectCFD();
     QString selectSPNAME(QString sql0);
     QString selectSPID(QString sql0);
     QString insertjinhuo(QString str0, QString str1, QString str2, QString str3, QString str4, QString str5);
     QString showDind();
     QString unclearsearch2(QString &find);
     QString insertHW(QString str0, QString str1, QString str2, QString str3);
     QString selectCFDid(QString str);
     QString updateHW(QString str0, QString str1, QString str2);
     QString selectHWID(QString sql0);
     QString selectHWNAME(QString sql0);
     QString insertCH(QString str0, QString str1, QString str2, QString str3, QString str4);
     QString showCHd();
     QString unclearsearch3(QString &find);
     QString searchflag();
     QString updateHWbyCH(QString str0, QString str1,QString str2);
     bool compare(QString str0,QString str1);
     QString updateflag(QString str0);
};
#endif // DBCONNECTOR_H
