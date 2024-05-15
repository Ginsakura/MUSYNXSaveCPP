#pragma once
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QDebug>

#define qout qDebug().noquote().nospace()

class SQLOperat {
public:
	SQLOperat(QSqlDatabase);
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

class HitDelayHistory
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

private:
	SQLOperat sql;
	QString sqlo;
	bool isInsert = true;
};
