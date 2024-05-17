﻿#include "MUSYNXSavDecode.h"
#include "Functions.h"

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
MUSYNXSavDecode::MUSYNXSavDecode(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    ui.versionLabel->setText(QString("Version %0%1 | Develop by Ginsakura")
        .arg(this->version).arg(
        this->isPreRelease ? QString("pre%0").arg(this->preVersion) : QString("rc%0").arg(this->rcVersion)
    ));
    ui.initFrame->hide();
    qout << "random: " << Random(10, 100);
}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_openRepoBtn_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Ginsakura/MUSYNXSaveCPP"));
}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_flushBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_isGameRunning_linkActivated() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_playedBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_unplayBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_rankEXBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_rankSBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_rankABtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_rankBBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_rankCBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_favoBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_redEXBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_blackEXBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_filterSongsBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_filterKeysBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_filterDifficultsBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_hitDelayBtn_clicked() {
    HitDelay* hitDelayWindow = new HitDelay;
    hitDelayWindow->show();
}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_difficultyScoreAnalyzeBtn_clicked() {
    DifficultyScoreAnalyze* diffSAWindow = new DifficultyScoreAnalyze;
    diffSAWindow->show();
}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
void MUSYNXSavDecode::on_openSaveFileBtn_clicked() {

}

//==================================================================
//函 数 名：
//功能描述：
//输入参数：
//返 回 值：
//==================================================================
MUSYNXSavDecode::~MUSYNXSavDecode() {}
