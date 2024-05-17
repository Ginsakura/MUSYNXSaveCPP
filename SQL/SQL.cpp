#include "stdafx.h"
#include "SQL.h"
#include "Functions.h"

SQLOperat::SQLOperat() {
	// 加载驱动
	DB = QSqlDatabase::addDatabase("QSQLITE");
	// 连接数据库
	DB.setDatabaseName("HitDelayHistory_v2.db");
	// 检验数据库连接
	if (DB.open()) {
		// 创建游标并连接到数据库
		cursor = QSqlQuery(DB);
		bool create = false, tableNotExists = true;
		// 查询表结构
		while (Select("sqlite_master", "name", "type='table'").next()) {
			QString tab = tempCur.value(0).toString();
			if (tab == "HitDelayHistory") tableNotExists = false;
		}
		// 表不存在时创建表
		if (tableNotExists) {
			cursor.prepare("CREATE TABLE if not exists \"HitDelayHistory\" ("
				"\"SongMapName\" text NOT NULL,"
				"\"RecordTime\" TEXT,"
				"\"AvgDelay\" float,"
				"\"AllKeys\" int,"
				"\"AvgAcc\" float,"
				"\"HitMap\" text,"
				"PRIMARY KEY(\"SongMapName\", \"RecordTime\")"
				");");
			create = cursor.exec();
			if (create) {
				qout << QFgColor(0, 0xff, 0) << QString::fromLocal8Bit("HitDelayHistory表创建成功或已存在") << QResetColor();
			}
			else {
				qout << QFgColor(0xff, 0, 0) << QString::fromLocal8Bit("HitDelayHistory表创建失败: ") << QResetColor() << cursor.lastError();
			}
		}
	}
	qout << QFgColor(0xff, 0, 0) << QString::fromLocal8Bit("打开失败") << QResetColor();
}

//==================================================================
//函 数 名：SelectAll
//功能描述：传入表名,查询表内`全部行`的`全部字段`
//          select * from 'table';
//输入参数：QString table
//返 回 值：QSqlQuery || nullptr
//==================================================================
QSqlQuery SQLOperat::SelectAll(const QString table) {
	QSqlQuery cur = QSqlQuery(DB);
	cur.prepare(QString("SELECT * from %0").arg(table));
	bool state = cur.exec();
	if (state) {
		return cur;
	}
	else {
		qout << QFgColor(0xff, 0, 0) << "select error: " << QResetColor() << cur.lastError();
	}
}

//==================================================================
//函 数 名：Select
//功能描述：通过传入表名、搜索字段和条件,查询`指定行`的`指定字段`
//          select 'getter' from 'table' where 'condition';
//输入参数：QString table, QString getter, QString condition
//返 回 值：QSqlQuery || nullptr
//==================================================================
QSqlQuery SQLOperat::Select(const QString table, const QString getter, const QString condition) {
	QSqlQuery cur = QSqlQuery(DB);
	cur.prepare(QString("select %0 from %1 where %2").arg(getter).arg(table).arg(condition));
	bool state = cur.exec();
	if (state) {
		return cur;
	}
	else {
		qout << QFgColor(0xff, 0, 0) << "select error: " << QResetColor() << cur.lastError();
	}
}

//==================================================================
//函 数 名：Select
//功能描述：通过传入表名、搜索字段,查询`全部行`的`指定字段`
//          select 'getter' from 'table';
//输入参数：QString table, QString getter = "*"
//返 回 值：QSqlQuery || nullptr
//==================================================================
QSqlQuery SQLOperat::Select(const QString table, const QString getter = "*") {
	QSqlQuery cur = QSqlQuery(DB);
	cursor.prepare(QString("select %0 from %1").arg(getter).arg(table));
	bool state = cursor.exec();
	if (state) {
		return cur;
	}
	else {
		qout << QFgColor(0xff, 0, 0) << "select error: " << QResetColor() << cur.lastError();
	}
}

//==================================================================
//函 数 名：Insert
//功能描述：传入表名、字段名和值,向表内插入指定字段的数据
//          Insert into 'table'('keys') values ('value');
//输入参数：QString table, QString keys, QString value
//返 回 值：bool,是否成功执行
//==================================================================
bool SQLOperat::Insert(const QString table, const QString keys, const QString value) {
	cursor.prepare(QString("Insert into %0(%1) values (%2);").arg(table).arg(keys).arg(value));
	bool state = cursor.exec();
	if (!state) {
		qout << QFgColor(0xff, 0, 0) << "Insert to " << table << " error: " << QResetColor() << cursor.lastError();
	}
	return state;
}

//==================================================================
//函 数 名：Insert
//功能描述：传入表名和值,向表内插入一整行数据
//          Insert into 'table' values ('value');
//输入参数：QString table, QString value
//返 回 值：bool,是否成功执行
//==================================================================
bool SQLOperat::Insert(const QString table, const QString value) {
	cursor.prepare(QString("Insert into %0 values (%1)").arg(table).arg(value));
	bool state = cursor.exec();
	if (!state) {
		qout << QFgColor(0xff, 0, 0) << "Insert to" << table << " error: " << QResetColor() << cursor.lastError();
	}
	return state;
}

//==================================================================
//函 数 名：Update
//功能描述：通过传入表名、字段、值和条件,更新一个字段的值
//          Update 'table' set 'keys'='value' where 'condition';
//输入参数：QString table, QString keys, QString value, QString condition
//返 回 值：bool,是否成功执行
//==================================================================
bool SQLOperat::Update(const QString table, const QString keys, const QString value, const QString condition) {
	//qout << QString("Update %1 set '%2'='%3' where %4").arg(table).arg(keys).arg(value).arg(condition);
	cursor.prepare(QString("Update %0 set '%1'='%2' where %3").arg(table).arg(keys).arg(value).arg(condition));
	bool state = cursor.exec();
	if (!state) {
		qout << QFgColor(0xff, 0, 0) << "Update to " << table << " error: " << QResetColor() << cursor.lastError();
	}
	return state;
}

//==================================================================
//函 数 名：Delete
//功能描述：通过传入表名和条件,以删除指定的数据行
//          delete from 'table' where 'condition';
//输入参数：QString table, QString condition
//返 回 值：bool,是否成功执行
//==================================================================
bool SQLOperat::Delete(QString table, QString condition) {
	cursor.prepare(QString("delete from %0 where %1").arg(table).arg(condition));
	bool state = cursor.exec();
	if (!state) {
		qout << QFgColor(0xff, 0, 0) << "Update to " << table << " error: " << QResetColor() << cursor.lastError();
	}
	return state;
}

//==================================================================
//函 数 名：Close
//功能描述：关闭数据库连接,并清空Query
//输入参数：
//返 回 值：
//==================================================================
void SQLOperat::Close() {
	cursor.clear();
	DB.close();
}

SQLOperat::~SQLOperat() {
	cursor.clear();
}

//==================================================================
//函 数 名：HitDelayHistory
//功能描述：无参构造函数,创建一个空的HitDelayHistoryORM对象
//输入参数：QSqlQuery cur
//返 回 值：
//==================================================================
HitDelayHistory::HitDelayHistory() {}

//==================================================================
//函 数 名：HitDelayHistory
//功能描述：有参构造函数,通过传入Query对象来初始化HitDelayHistoryORM对象的值
//输入参数：QSqlQuery cur
//返 回 值：
//==================================================================
HitDelayHistory::HitDelayHistory(QSqlQuery cur) {
	this->SongMapName = cur.value(0).toString();
	this->RecordTime = cur.value(1).toString();
	this->AvgDelay = cur.value(2).toDouble();
	this->AllKeys = cur.value(3).toInt();
	this->AvgAcc = cur.value(4).toDouble();
	this->HitMap = cur.value(5).toString();
	isInsert = false;
}

//==================================================================
//函 数 名：HitDelayHistory
//功能描述：通过传入每一个参数的值,完成HitDelayHistoryORM对象初始化
//输入参数：QString songMapName, QString recordTime, double avgDelay, int allKeys, double avgAcc, QString hitMap
//返 回 值：
//==================================================================
HitDelayHistory::HitDelayHistory(QString songMapName, QString recordTime,
	double avgDelay, int allKeys, double avgAcc, QString hitMap) {
	this->SongMapName = songMapName;
	this->RecordTime = recordTime;
	this->AvgDelay = avgDelay;
	this->AllKeys = allKeys;
	this->AvgAcc = avgAcc;
	this->HitMap = hitMap;
}

//==================================================================
//函 数 名：save
//功能描述：通过类内私有成员变量isInsert判断执行Insert还是Update
//输入参数：
//返 回 值：bool,是否成功执行
//==================================================================
bool HitDelayHistory::save() {
	if (this->RecordTime == "") {
		qout << QFgColor(0xff, 0, 0) << "Record is Null." << QResetColor();
		return false;
	}
	if (isInsert) {
		sqlo = QString("\"%0\",\"%1\",%2,%3,%4,\"%5\"")
			.arg(this->SongMapName).arg(this->RecordTime).arg(this->AvgDelay)
			.arg(this->AllKeys).arg(this->AvgAcc).arg(this->HitMap);
		sql.Insert("HitDelayHistory", sqlo);
		return true;
	}
	else {
		sqlo = QString("RecordTime=\"%1\"").arg(this->RecordTime);
		sql.Update("HitDelayHistory", "SongMapName", this->SongMapName, sqlo);
		return true;
	}
}

//==================================================================
//函 数 名：change
//功能描述：切换该ORM对象的插入/更新功能
//输入参数：
//返 回 值：
//==================================================================
void HitDelayHistory::change() {
	this->isInsert = !this->isInsert;
}

HitDelayHistory::~HitDelayHistory() {}