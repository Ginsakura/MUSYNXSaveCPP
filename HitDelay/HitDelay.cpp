﻿#include "HitDelay.h"
#include "../SQL/SQL.h"

HitDelay::HitDelay(QWidget* parent): QWidget(parent) {
	ui.setupUi(this);
}

void HitDelay::on_accSyncBtn_clicked() {

}

void HitDelay::on_diffcuteBtn_clicked() {
	if (ui.diffcuteBtn->text() == "") {
		ui.diffcuteBtn->setText("");
	}
}

void HitDelay::on_deleteHistoryBtn_clicked() {

}

void HitDelay::on_updateHistoryBtn_clicked() {

}

void HitDelay::on_hitAnalyzeBtn_clicked() {

}

void HitDelay::on_keysBtn_clicked() {

}

void HitDelay::on_loggerBtn_clicked() {

}

HitDelay::~HitDelay() {}
