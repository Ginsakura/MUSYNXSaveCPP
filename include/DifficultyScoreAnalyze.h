#pragma once
#include "difficultyscoreanalyze_global.h"
#include <QChart>
#include <QChartGlobal>
#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include "ui_DifficultyScoreAnalyze.h"

#define qout qDebug().noquote().nospace()
using namespace QtCharts;

class DIFFICULTYSCOREANALYZE_EXPORT DifficultyScoreAnalyze : public QWidget
{
	Q_OBJECT

public:
	DifficultyScoreAnalyze(QWidget* parent = nullptr);
	~DifficultyScoreAnalyze();

private:
	Ui::DifficultyScoreAnalyzeClass DSAui;
};
