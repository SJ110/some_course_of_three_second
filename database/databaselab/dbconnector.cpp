#include"dbconnector.h"


static bool connectDB(){  //for connect db
    QString dbDriver="QMYSQL";
    QString dbName="sql_lab";
    QString UserName="sqllab";
    QString UserPwd="123";
    QString HostName="localhost";
    int hostPort=3306;
    QSqlDatabase db= QSqlDatabase::addDatabase(dbDriver);
    db.setHostName(HostName);
    db.setDatabaseName(dbName);
    db.setUserName(UserName);
    db.setPassword(UserPwd);
    db.setPort(hostPort);
    if(!db.open()){
        qDebug()<<"can not connect mysql,please check your servece.";
        return false;
    }
    return true;
}


 QString dbConnect:: Username(QString uname){

    QSqlQuery query;
    query.exec("select * from ADMIN where ROOT='"+uname+"'");
    query.next();
  //  qDebug()<<query.value(0).toString();
    return query.value(0).toString();
}
 QString dbConnect:: Psw(QString psw){
     QSqlQuery query;
    query.exec("select * from ADMIN where ROOT='"+psw+"'");
    query.next();
    query.value(1).toString();
  //  qDebug()<<query.value(1).toString();
    return query.value(1).toString();
 }

QString dbConnect::initshowdata()
 {
    QString sql="select HW_XX.GID as 编号,GNAME as 名称,CFD as 存放地,SCC as 生产场地, KUL as 库存量,"
                "time as 修改日期"
                " from HW_XX,SP_XX,CF_XX"
                " where HW_XX.GID=SP_XX.GID and HW_XX.CFD_ID=CF_XX.CFD_ID";
    return sql;
 }

QString dbConnect::sortbyGID(){
    QString sql=initshowdata()+" order by HW_XX.GID";
    return sql;
}

QString dbConnect::sortbytime(){
    QString sql= initshowdata()+" order by time";
    return sql;
}

QString dbConnect::sortbyKUL(){
    QString sql=initshowdata()+" order by KUL";
    return sql;
}

QString dbConnect::unclearsearch(QString& find){
    QString sql;
    QSqlQuery query;
    if(find[0]>='0'&&find[0]<='9'){
        sql= initshowdata() +" and HW_XX.GID like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
           sql= initshowdata() +" and HW_XX.GID like '%"+find+"'";
        query.exec(sql);
        if(!query.next())
            sql= initshowdata() +" and HW_XX.GID like '"+find+"%'";
    }
    else {
        sql= initshowdata() +" and GNAME like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= initshowdata() +" and GNAME like '"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= initshowdata() +" and GNAME like '%"+find+"'";
    }
    return sql;
}

QString dbConnect::selectSPID(QString sql0){
    QString sql="select GID from SP_XX";
    if(sql0.size()!=0)
        sql=sql+" where GNAME='"+sql0+"'";//最后这个单引号很重要 别问我为什么知道（
    return sql;
}

QString dbConnect::selectSPNAME(QString sql0){
    QString sql="select GNAME from SP_XX";
    if(sql0.size()!=0)
        sql=sql+" where GID='"+sql0+"'";
    return sql;
}

QString dbConnect::selectCFD(){
    QString sql="select CFD from CF_XX";
    return sql;
}

QString dbConnect::insertjinhuo(QString str0,QString str1,QString str2,QString str3,QString str4,QString str5){
    QString sql="insert into JH_XX values('"+str0+ "','" + str1+ "','" + str2+ "','" +str3+ "','" + str4+"','" +str5+"',0)";
    return sql;
}

QString dbConnect::showDind(){
    QString sql= "select ID as 订单号, GID as 编号, GNAME as 商品名称, JHSL as 进货数量, CFD as 存放地,TIME as 进货时间"
                 " from JH_XX";
    return sql;
}

QString dbConnect::showCHd(){
    QString sql= "select ID as 出货单号, GID as 编号, GNAME as 商品名称, JHSL as 出货数量, TIME as 出货时间 "
                 "from CH_XX";
    return sql;
}
QString dbConnect::unclearsearch2(QString& find){
    QString sql;
    QSqlQuery query;
    if(find[0]>='0'&&find[0]<='9'){
        sql= showDind() +" where ID like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
           sql= showDind() +" where ID like '%"+find+"'";
        query.exec(sql);
        if(!query.next())
            sql= showDind() +"  where ID like '"+find+"%'";
    }
    else {
        sql= showDind()+" where GNAME like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= showDind()+" where GNAME like '"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= showDind() +" where GNAME like '%"+find+"'";
    }
    return sql;
}

QString dbConnect::unclearsearch3(QString& find){
    QString sql;
    QSqlQuery query;
    if(find[0]>='0'&&find[0]<='9'){
        sql= showCHd() +" where ID like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
           sql= showCHd() +" where ID like '%"+find+"'";
        query.exec(sql);
        if(!query.next())
            sql= showCHd() +"  where ID like '"+find+"%'";
    }
    else {
        sql= showCHd() +" where GNAME like '%"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= showCHd() +" where GNAME like '"+find+"%'";
        query.exec(sql);
        if(!query.next())
            sql= showCHd() +" where GNAME like '%"+find+"'";
    }
    return sql;
}

QString dbConnect::selectCFDid(QString str){
    return "select CFD_ID from CF_XX where CFD='"+str+"'";
}

QString dbConnect::insertHW(QString str0,QString str1,QString str2,QString str3){
    return "insert into HW_XX values('"+str0+"','"+str1+"','"+str2+"','"+str3+"')";
}

QString dbConnect::updateHW(QString str0,QString str1,QString str2){
    return "update HW_XX set KUL=KUL+"+str0+",time='"+str1+"' where GID="+str2;
}

QString dbConnect::selectHWID(QString sql0){
    QString sql="select HW_XX.GID from HW_XX";
    if(sql0.size()!=0)
        sql=sql+",SP_XX where HW_XX.GID=SP_XX.GID and GNAME='"+sql0+"'";//最后这个单引号很重要 别问我为什么知道（
    return sql;
}

QString dbConnect::selectHWNAME(QString sql0){
    QString sql="select GNAME from SP_XX,HW_XX where SP_XX.GID=HW_XX.GID";
    if(sql0.size()!=0)
        sql=sql+" and HW_XX.GID='"+sql0+"'";
    return sql;
}

QString dbConnect::insertCH(QString str0,QString str1,QString str2,QString str3,QString str4){
    QString sql="insert into CH_XX values('"+str0+ "','" + str1+ "','" + str2+ "','" +str3+ "','" + str4+"',0)";
    return sql;
}

QString dbConnect::searchflag(){
    return "select * from CH_XX where flag=0 order by time";
}

bool dbConnect::compare(QString str0,QString str1){
    QSqlQuery query;
    query.exec("select KUL from HW_XX where HW_XX.GID="+str0);
    if( query.next()==false)
        return false;  //仓库无数据
    int str=query.value(0).toInt(); //位数不同无法判断嗷
    int tmp=str1.toInt();
    if(str<tmp) //数量不足
        return false;  //数量不足
    return true; //ok
}

QString dbConnect::updateHWbyCH(QString str0,QString str1,QString str2){
    QString sql= "update HW_XX set KUL=KUL-"+ str0 +",time='"+str2+"' where GID="+str1;
    return sql;
}

QString dbConnect::updateflag( QString str0){
    return "update CH_XX set flag=1 where ID="+str0;
}

//bool dbConnect::jinhuoret(QStringList list){
//      QString sql= "insert into ";
//}
