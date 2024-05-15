#include "MUSYNCSavDecode.h"

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
    QDesktopServices::openUrl(QUrl("https://github.com/Ginsakura/MUSYNCSave"));
}


MUSYNCSavDecode::~MUSYNCSavDecode() {}
