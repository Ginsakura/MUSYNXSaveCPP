#pragma once

#include "sql_global.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QDebug>

// 对数据库操作的第一层封装
class SQL_EXPORT SQLOperat {
public:
	SQLOperat();
	~SQLOperat();

	//==================================================================
	//函 数 名：SelectAll
	//功能描述：传入表名,查询表内`全部行`的`全部字段`
	//          select * from 'table';
	//输入参数：QString table
	//返 回 值：QSqlQuery || nullptr
	//==================================================================
	QSqlQuery SelectAll(QString);

	//==================================================================
	//函 数 名：Select
	//功能描述：通过传入表名、搜索字段和条件,查询`指定行`的`指定字段`
	//          select 'getter' from 'table' where 'condition';
	//输入参数：QString table, QString getter, QString condition
	//返 回 值：QSqlQuery || nullptr
	//==================================================================
	QSqlQuery Select(QString, QString, QString);

	//==================================================================
	//函 数 名：Select
	//功能描述：通过传入表名、搜索字段,查询`全部行`的`指定字段`
	//          select 'getter' from 'table';
	//输入参数：QString table, QString getter = "*"
	//返 回 值：QSqlQuery || nullptr
	//==================================================================
	QSqlQuery Select(QString, QString);

	//==================================================================
	//函 数 名：Insert
	//功能描述：传入表名、字段名和值,向表内插入指定字段的数据
	//          Insert into 'table'('keys') values ('value');
	//输入参数：QString table, QString keys, QString value
	//返 回 值：bool,是否成功执行
	//==================================================================
	bool Insert(QString, QString, QString);

	//==================================================================
	//函 数 名：Insert
	//功能描述：传入表名和值,向表内插入一整行数据
	//          Insert into 'table' values ('value');
	//输入参数：QString table, QString value
	//返 回 值：bool,是否成功执行
	//==================================================================
	bool Insert(QString, QString);

	//==================================================================
	//函 数 名：Update
	//功能描述：通过传入表名、字段、值和条件,更新一个字段的值
	//          Update 'table' set 'keys'='value' where 'condition';
	//输入参数：QString table, QString keys, QString value, QString condition
	//返 回 值：bool,是否成功执行
	//==================================================================
	bool Update(QString, QString, QString, QString);

	//==================================================================
	//函 数 名：Delete
	//功能描述：通过传入表名和条件,以删除指定的数据行
	//          delete from 'table' where 'condition';
	//输入参数：QString table, QString condition
	//返 回 值：bool,是否成功执行
	//==================================================================
	bool Delete(QString, QString);

	//==================================================================
	//函 数 名：Close
	//功能描述：关闭数据库连接,并清空Query
	//输入参数：
	//返 回 值：
	//==================================================================
	void Close();

private:
	QSqlDatabase DB;
	QSqlQuery cursor;
	QSqlQuery tempCur;

	//==================================================================
	//函 数 名：CheckOldSQLite
	//功能描述：检查转换旧版数据库
	//输入参数：
	//返 回 值：bool
	//==================================================================
	bool CheckOldSQLite();

	//==================================================================
	//函 数 名：FromSql_v1
	//功能描述：从version 1数据库转换到version 3
	//输入参数：
	//返 回 值：
	//==================================================================
	void FromSql_v1();

	//==================================================================
	//函 数 名：FromSql_v2
	//功能描述：从version 2数据库转换到version 3
	//输入参数：
	//返 回 值：
	//==================================================================
	void FromSql_v2();

	//==================================================================
	//函 数 名：CreateTable
	//功能描述：创建数据表结构
	//输入参数：
	//返 回 值：
	//==================================================================
	void CreateTable();
};

// 对`HitDelayHistory`进行ORM二次封装
class SQL_EXPORT HitDelayHistory {
public:
	// 无参构造函数, 创建一个空的HitDelayHistoryORM对象
	HitDelayHistory();
	~HitDelayHistory();

	//==================================================================
	//函 数 名：HitDelayHistory
	//功能描述：有参构造函数,通过传入Query对象来初始化HitDelayHistoryORM对象的值
	//输入参数：QSqlQuery cur
	//返 回 值：
	//==================================================================
	HitDelayHistory(QSqlQuery);

	//==================================================================
	//函 数 名：HitDelayHistory
	//功能描述：有参构造函数,通过传入Query对象来初始化HitDelayHistoryORM对象的值并手动传入是否插入
	//输入参数：QSqlQuery cur, bool insert
	//返 回 值：
	//==================================================================
	HitDelayHistory(QSqlQuery cur, bool insert);

	//==================================================================
	//函 数 名：HitDelayHistory
	//功能描述：通过传入每一个参数的值,完成HitDelayHistoryORM对象初始化
	//输入参数：QString songMapName, QString recordTime, QString Keys, QString Diffcuty,
	//	double avgDelay, int allKeys, double avgAcc, QString hitMap
	//返 回 值：
	//==================================================================
	HitDelayHistory(QString, QString, QString, QString, double, int, double, QString);

	QString SongMapName = "";
	QString RecordTime = "";
	QString Keys = "4K";
	QString Diffcuty = "EZ";
	double AvgDelay = 0;
	int AllKeys = 0;
	double AvgAcc = 0;
	QString HitMap = "";

	//==================================================================
	//函 数 名：save
	//功能描述：通过类内私有成员变量isInsert判断执行Insert还是Update
	//输入参数：
	//返 回 值：bool,是否成功执行
	//==================================================================
	bool save();

	// 切换该ORM对象的插入/更新功能
	void change();

private:
	SQLOperat sql;
	QString sqlo;
	bool isInsert = true;
};
