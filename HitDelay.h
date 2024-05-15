#pragma once

#include <QWidget>
#include "ui_HitDelay.h"

class HitDelay : public QWidget
{
	Q_OBJECT

public:
	HitDelay(QWidget *parent = nullptr);
	~HitDelay();

private:
	Ui::HitDelayClass ui;
};
