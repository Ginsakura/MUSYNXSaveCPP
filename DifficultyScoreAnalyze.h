#pragma once

#include <QChart>
#include <QChartGlobal>
#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include "ui_DifficultyScoreAnalyze.h"

#define qout qDebug().noquote().nospace()
using namespace QtCharts;

class DifficultyScoreAnalyze : public QWidget
{
	Q_OBJECT

public:
	DifficultyScoreAnalyze(QWidget *parent = nullptr);
	~DifficultyScoreAnalyze();

private:
	Ui::DifficultyScoreAnalyzeClass DSAui;
};
