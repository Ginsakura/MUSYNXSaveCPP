#pragma once

#include <QtCharts>
#include <QDebug>
#include <QDesktopServices>
#include <QMainWindow>
#include <QUrl>
#include "ui_MUSYNCSavDecode.h"
#include "functions.h"
#include "DifficultyScoreAnalyze.h"

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
    const bool isPreRelease = true;
    const QString version = "0.0.2";
    const int rcVersion = 1;
    const int preVersion = 1;
};
