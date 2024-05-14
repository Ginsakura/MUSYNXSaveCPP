#include "MUSYNCSavDecode.h"

MUSYNCSavDecode::MUSYNCSavDecode(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);
}

void MUSYNCSavDecode::on_openRepoBtn_clicked() {
    QDesktopServices::openUrl(QUrl("https://github.com/Ginsakura/MUSYNCSave"));
}


MUSYNCSavDecode::~MUSYNCSavDecode() {}
