#pragma once

#include "hitdelay_global.h"
#include <QWidget>
#include "ui_HitDelay.h"

class HITDELAY_EXPORT HitDelay : public QWidget
{
	Q_OBJECT

public:
	//==================================================================
	//函 数 名：
	//功能描述：
	//输入参数：
	//返 回 值：
	//==================================================================
	HitDelay(QWidget* parent = nullptr);
	~HitDelay();

public slots:
	//==================================================================
	//函 数 名：
	//功能描述：
	//输入参数：
	//返 回 值：
	//==================================================================
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
