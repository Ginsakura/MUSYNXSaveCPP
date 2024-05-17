#pragma once

#include "sql_global.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QDebug>

#define qout qDebug().noquote().nospace()

class SQL_EXPORT SQLOperat {
public:
	SQLOperat();
	~SQLOperat();
	QSqlQuery SelectAll(QString);
	QSqlQuery Select(QString, QString, QString);
	QSqlQuery Select(QString, QString);
	bool Insert(QString, QString, QString);
	bool Insert(QString, QString);
	bool Update(QString, QString, QString, QString);
	bool Delete(QString, QString);
	void Close();

private:
	QSqlDatabase DB;
	QSqlQuery cursor;
	QSqlQuery tempCur;
};

class SQL_EXPORT HitDelayHistory
{
public:
	HitDelayHistory();
	HitDelayHistory(QSqlQuery);
	HitDelayHistory(QString, QString, double, int, double, QString);
	~HitDelayHistory();
	QString SongMapName = "";
	QString RecordTime = "";
	double AvgDelay = 0;
	int AllKeys = 0;
	double AvgAcc = 0;
	QString HitMap = "";
	bool save();
	void change();

private:
	SQLOperat sql;
	QString sqlo;
	bool isInsert = true;
};
