#include "MUSYNCSavDecode.h"
#include "HitDelay.h"
#include "DifficultyScoreAnalyze.h"

MUSYNCSavDecode::MUSYNCSavDecode(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
    ui.versionLabel->setText(QString("Version %0%1 | Develop by Ginsakura")
        .arg(this->version).arg(
        this->isPreRelease ? QString("pre%0").arg(this->preVersion) : QString("rc%0").arg(this->rcVersion)
    ));
    ui.initFrame->hide();
}

void MUSYNCSavDecode::on_openRepoBtn_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Ginsakura/MUSYNCSaveCPP"));
}

void MUSYNCSavDecode::on_flushBtn_clicked() {

}

void MUSYNCSavDecode::on_isGameRunning_linkActivated() {

}

void MUSYNCSavDecode::on_playedBtn_clicked() {

}

void MUSYNCSavDecode::on_unplayBtn_clicked() {

}

void MUSYNCSavDecode::on_rankEXBtn_clicked() {

}

void MUSYNCSavDecode::on_rankSBtn_clicked() {

}

void MUSYNCSavDecode::on_rankABtn_clicked() {

}

void MUSYNCSavDecode::on_rankBBtn_clicked() {

}

void MUSYNCSavDecode::on_rankCBtn_clicked() {

}

void MUSYNCSavDecode::on_favoBtn_clicked() {

}

void MUSYNCSavDecode::on_redEXBtn_clicked() {

}

void MUSYNCSavDecode::on_blackEXBtn_clicked() {

}

void MUSYNCSavDecode::on_filterSongsBtn_clicked() {

}

void MUSYNCSavDecode::on_filterKeysBtn_clicked() {

}

void MUSYNCSavDecode::on_filterDifficultsBtn_clicked() {

}

void MUSYNCSavDecode::on_hitDelayBtn_clicked() {
    HitDelay* hitDelayWindow = new HitDelay;
    hitDelayWindow->show();
}

void MUSYNCSavDecode::on_difficultyScoreAnalyzeBtn_clicked() {
    DifficultyScoreAnalyze* diffSAWindow = new DifficultyScoreAnalyze;
    diffSAWindow->show();
}

void MUSYNCSavDecode::on_openSaveFileBtn_clicked() {

}

MUSYNCSavDecode::~MUSYNCSavDecode() {}
