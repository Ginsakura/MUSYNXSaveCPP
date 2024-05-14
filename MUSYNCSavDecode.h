#pragma once

#include <QtCharts>
#include <QDebug>
#include <QDesktopServices>
#include <QList>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QUrl>
#include "ui_MUSYNCSavDecode.h"
#include "functions.h"

#define qout qDebug().noquote().nospace()

class MUSYNCSavDecode : public QMainWindow
{
    Q_OBJECT

public:
    MUSYNCSavDecode(QWidget *parent = nullptr);
    ~MUSYNCSavDecode();

private slots:
    void on_openRepoBtn_clicked();

private:
    Ui::MUSYNCSavDecodeClass ui;
};
