#pragma once

#include <QtCharts>
#include <QDebug>
#include <QDesktopServices>
#include <QMainWindow>
#include <QUrl>
#include "ui_MUSYNXSavDecode.h"

#define qout qDebug().noquote().nospace()

typedef enum Filter {
    NoFilter = 0,
    Played,
    Unplay,
    RankEx,
    RankS,
    RankA,
    RankB,
    RankC,
    Favo,
    RedEx,
    BlackEx,
} Filter;

typedef enum SongsFilter {
    AllSongs = 0,
    FreeSongs,
    DLCSongs,
} SongsFilter;

typedef enum KeysFilter {
    AllKeys = 0,
    Key4,
    Key6,
} KeysFilter;

typedef enum DiffcuteFilter {
    AllDiff = 0,
    Easy,
    Hard,
    Inferno,
} DiffcuteFilter;

class MUSYNXSavDecode : public QMainWindow
{
    Q_OBJECT

public:
    MUSYNXSavDecode(QWidget* parent = nullptr);
    ~MUSYNXSavDecode();

private slots:
    void on_flushBtn_clicked();
    void on_isGameRunning_linkActivated();
    void on_playedBtn_clicked();
    void on_unplayBtn_clicked();
    void on_rankEXBtn_clicked();
    void on_rankSBtn_clicked();
    void on_rankABtn_clicked();
    void on_rankBBtn_clicked();
    void on_rankCBtn_clicked();
    void on_favoBtn_clicked();
    void on_redEXBtn_clicked();
    void on_blackEXBtn_clicked();
    void on_filterSongsBtn_clicked();
    void on_filterKeysBtn_clicked();
    void on_filterDifficultsBtn_clicked();
    void on_hitDelayBtn_clicked();
    void on_difficultyScoreAnalyzeBtn_clicked();
    void on_openSaveFileBtn_clicked();
    void on_openRepoBtn_clicked();

private:
    Ui::MUSYNXSavDecodeClass ui;
    Filter filter = NoFilter;
    SongsFilter songsFilter = AllSongs;
    KeysFilter keysFilter = AllKeys;
    DiffcuteFilter diffcuteFilter = AllDiff;

    const bool isPreRelease = true;
    const QString version = "0.0.2";
    const int rcVersion = 1;
    const int preVersion = 1;
};
