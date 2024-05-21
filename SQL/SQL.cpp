#include "SQL.h"
#include "../Functions/Functions.h"
#include <iostream>

SQLOperat::SQLOperat() {
	this->CheckOldSQLite();
	// 检查数据库连接是否已经创建过
	if (QSqlDatabase::contains("SQLiteLink"))
	{
		DB = QSqlDatabase::database("SQLiteLink");
	}
	// 创建数据库连接
	else {
		// 加载驱动
		DB = QSqlDatabase::addDatabase("QSQLITE", "SQLiteLink");
		// 连接数据库
		DB.setDatabaseName("HitDelayHistory_v3.db");
	}
	// 检验数据库连接
	if (DB.open()) {
		// 创建游标并连接到数据库
		cursor = QSqlQuery(DB);
		// 表创建结果状态
		bool createResult = false;
		// 表存在状态
		bool tablesNotExists = true;
		// 查询表结构
		tempCur = Select("sqlite_master", "name", "type='table'");
		while (tempCur.next()) {
			QString tab = tempCur.value(0).toString();
			if (tab == "HitDelayHistory") tablesNotExists = false;
		}
		// 表不存在时创建表
		if (tablesNotExists) {
			cursor.prepare("CREATE TABLE if not exists \"HitDelayHistory\" ("
				"\"SongMapName\" text not null,"
				"\"Keys\" int not null,"
				"\"Diffcuty\" text not null,"
				"\"RecordTime\" text,"
				"\"AvgDelay\" float,"
				"\"AllKeys\" int,"
				"\"AvgAcc\" float,"
				"\"HitMap\" text,"
				"PRIMARY KEY(\"SongMapName\", \"RecordTime\")"
				");");
			createResult = cursor.exec();
			if (createResult) {
				qout << FGREEN << QString::fromLocal8Bit("HitDelayHistory_v3表创建成功或已存在") << RESET;
			}
			else {
				qout << FRED << QString::fromLocal8Bit("HitDelayHistory_v3表创建失败: ") << RESET << cursor.lastError();
			}
		}
	}
	qout << FRED << QString::fromLocal8Bit("打开失败") << RESET;
}

bool SQLOperat::CheckOldSQLite() {
	if (!isFileExists(QDir::currentPath() + "/musynx_data/HitDelayHistory_v3.db")) {
		qout << FRED << "Database versions 3 not Exists" << RESET;
		if (isFileExists(QDir::currentPath() + "/musynx_data/HitDelayHistory_v2.db")) {
			qout << BYELLOW << "Database versions 2 Exists." << RESET;
			std::cout << FORANGE.toStdString() << "Transing database version..." << ResetColor();
			this->FromSql_v2();
			return true;
		}
		else if (isFileExists(QDir::currentPath() + "/musynx_data/HitDelayHistory.db")) {
			qout << BYELLOW << "Database versions 1 Exists." << RESET;
			std::cout << FORANGE.toStdString() << "Transing database version..." << ResetColor();
			this->FromSql_v1();
			return true;
		}
		else {
			qout << FRED << "All database versions does not exist" << RESET;
		}
	}
	return false;
}

void SQLOperat::FromSql_v1() {
	QSqlDatabase oldDB = QSqlDatabase::addDatabase("QSQLITE", "SQLiteLink_v1");
	oldDB.setDatabaseName("HitDelayHistory.db");
	QSqlDatabase newDB = QSqlDatabase::addDatabase("QSQLITE", "SQLiteLink");
	newDB.setDatabaseName("HitDelayHistory_v3.db");
	QSqlQuery oldcur;
	if (oldDB.open()) {
		oldcur = QSqlQuery(oldDB);
		bool createResult = false;
		QSqlQuery tmpcur = Select("sqlite_master", "name", "type='table'");
		tmpcur.next();
		if (tmpcur.value(0).toString() != "HitDelayHistory") {
		}
	}
	if (newDB.open()) {
		cursor = QSqlQuery(newDB);
	}
	qout << FGREEN << "Success" << RESET;
	qout << FRED << "Failure" << RESET;
}
void SQLOperat::FromSql_v2() {
	QSqlDatabase oldDB = QSqlDatabase::addDatabase("QSQLITE", "SQLiteLink_v2");
	oldDB.setDatabaseName("HitDelayHistory_v2.db");
	QSqlDatabase newDB = QSqlDatabase::addDatabase("QSQLITE", "SQLiteLink");
	newDB.setDatabaseName("HitDelayHistory_v3.db");
	QSqlQuery oldcur;
	if (oldDB.open()) {
		oldcur = QSqlQuery(oldDB);
		bool createResult = false;
		QSqlQuery tmpcur = Select("sqlite_master", "name", "type='table'");
		tmpcur.next();
		if (tmpcur.value(0).toString() != "HitDelayHistory") {
		}
	}
	if (newDB.open()) {
		cursor = QSqlQuery(newDB);
	}
	qout << FGREEN << "Success" << RESET;
	qout << FRED << "Failure" << RESET;
}

QSqlQuery SQLOperat::SelectAll(const QString table) {
	QSqlQuery cur = QSqlQuery(DB);
	cur.prepare(QString("SELECT * from %0").arg(table));
	bool state = cur.exec();
	if (state) {
		return cur;
	}
	else {
		qout << FRED << "select error: " << RESET << cur.lastError();
		return;
	}
}

QSqlQuery SQLOperat::Select(const QString table, const QString getter, const QString condition) {
	QSqlQuery cur = QSqlQuery(DB);
	cur.prepare(QString("select %0 from %1 where %2").arg(getter).arg(table).arg(condition));
	bool state = cur.exec();
	if (state) {
		return cur;
	}
	else {
		qout << FRED << "select error: " << RESET << cur.lastError();
		return;
	}
}

QSqlQuery SQLOperat::Select(const QString table, const QString getter = "*") {
	QSqlQuery cur = QSqlQuery(DB);
	cursor.prepare(QString("select %0 from %1").arg(getter).arg(table));
	bool state = cursor.exec();
	if (state) {
		return cur;
	}
	else {
		qout << FRED << "select error: " << RESET << cur.lastError();
		return;
	}
}

bool SQLOperat::Insert(const QString table, const QString keys, const QString value) {
	cursor.prepare(QString("Insert into %0(%1) values (%2);").arg(table).arg(keys).arg(value));
	bool state = cursor.exec();
	if (!state) {
		qout << FRED << "Insert to " << table << " error: " << RESET << cursor.lastError();
	}
	return state;
}

bool SQLOperat::Insert(const QString table, const QString value) {
	cursor.prepare(QString("Insert into %0 values (%1)").arg(table).arg(value));
	bool state = cursor.exec();
	if (!state) {
		qout << FRED << "Insert to" << table << " error: " << RESET << cursor.lastError();
	}
	return state;
}

bool SQLOperat::Update(const QString table, const QString keys, const QString value, const QString condition) {
	//qout << QString("Update %1 set '%2'='%3' where %4").arg(table).arg(keys).arg(value).arg(condition);
	cursor.prepare(QString("Update %0 set '%1'='%2' where %3").arg(table).arg(keys).arg(value).arg(condition));
	bool state = cursor.exec();
	if (!state) {
		qout << FRED << "Update to " << table << " error: " << RESET << cursor.lastError();
	}
	return state;
}

bool SQLOperat::Delete(QString table, QString condition) {
	cursor.prepare(QString("delete from %0 where %1").arg(table).arg(condition));
	bool state = cursor.exec();
	if (!state) {
		qout << FRED << "Update to " << table << " error: " << RESET << cursor.lastError();
	}
	return state;
}

void SQLOperat::Close() {
	cursor.clear();
	DB.close();
}

SQLOperat::~SQLOperat() {
	cursor.clear();
}

HitDelayHistory::HitDelayHistory() {}

HitDelayHistory::HitDelayHistory(QSqlQuery cur) {
	this->SongMapName = cur.value(0).toString();
	this->RecordTime = cur.value(1).toString();
	this->AvgDelay = cur.value(2).toDouble();
	this->AllKeys = cur.value(3).toInt();
	this->AvgAcc = cur.value(4).toDouble();
	this->HitMap = cur.value(5).toString();
	isInsert = false;
}

HitDelayHistory::HitDelayHistory(QString songMapName, QString recordTime,
	double avgDelay, int allKeys, double avgAcc, QString hitMap) {
	this->SongMapName = songMapName;
	this->RecordTime = recordTime;
	this->AvgDelay = avgDelay;
	this->AllKeys = allKeys;
	this->AvgAcc = avgAcc;
	this->HitMap = hitMap;
}

bool HitDelayHistory::save() {
	if (this->RecordTime == "") {
		qout << FRED << "Record is Null." << RESET;
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

void HitDelayHistory::change() {
	this->isInsert = !this->isInsert;
}

HitDelayHistory::~HitDelayHistory() {}