#pragma once

#include <QWidget>
#include "ui_HitDelay.h"

class HitDelay : public QWidget
{
	Q_OBJECT

public:
	HitDelay(QWidget *parent = nullptr);
	~HitDelay();

public slots:
	void on_accSyncBtn_clicked();
	void on_diffcuteBtn_clicked();
	void on_deleteHistoryBtn_clicked();
	void on_updateHistoryBtn_clicked();
	void on_hitAnalyzeBtn_clicked();
	void on_keysBtn_clicked();
	void on_loggerBtn_clicked();

private:
	Ui::HitDelayClass ui;
};
