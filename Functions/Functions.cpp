#include "Functions.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <uiautomation.h>
#include <Windows.h>

#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QSettings>
#include <QThread>

unsigned SetSeed() {
	LARGE_INTEGER frequency;
	LARGE_INTEGER time;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time);
	std::cout << "Random Engine Init...\n";
	std::cout << "Freq: " << frequency.QuadPart << " Hz, Time: " << time.QuadPart << " Cycle\n\n";
	isRandomInit = true;
	return (unsigned int)(time.QuadPart * 1000 / frequency.QuadPart);
}

int Randint(int min = 0, int max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return rand() % (max - min) + min;
}

double Random(double min = 0, double max = RAND_MAX) {
	if (!isRandomInit) srand(SetSeed());
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

std::string FgColor(int r, int g, int b) {
	return std::format("\033[38;2;{};{};{}m", r, g, b);
}

std::string BgColor(int r, int g, int b) {
	return std::format("\033[48;2;{};{};{}m", r, g, b);
}

std::string ResetColor() {
	return "\033[m";
}

QString QFgColor(int r, int g, int b) {
	return QString("\033[38;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

QString QBgColor(int r, int g, int b) {
	return QString("\033[48;2;%0;%1;%2m").arg(r).arg(g).arg(b);
}

QString QResetColor() {
	return QString("\033[m");
}

double GetScreenScale() {
	int screenW = ::GetSystemMetrics(SM_CXSCREEN);
	int screenH = ::GetSystemMetrics(SM_CYSCREEN);
	//std::cout << "screenW =" << screenW << "screenH=" << screenH << std::endl;
	//HWND hwd = ::GetDesktopWindow();
	HDC hdc = ::GetDC(::GetDesktopWindow());
	int width = ::GetDeviceCaps(hdc, DESKTOPHORZRES);
	int height = ::GetDeviceCaps(hdc, DESKTOPVERTRES);
	//std::cout << "width=" << width << "height=" << height << std::endl;
	double scale = (double)width / screenW;
	return scale;
}

bool isFileExists(QString name) {
	std::ifstream ifs(name.toStdString().c_str());
	return ifs.good();
}

QString FileMD5(QString name) {
	QFile file(name);
	if (file.open(QIODevice::ReadOnly)) {
		//QByteArray content = file.readAll();
		// 生成文件的md5值，当然也提供的加密方式
		QByteArray md5 = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
		file.close();
		return md5.toHex();
	}
	return QString("Get MD5 Failure.");
}

QString SearchMainExecPath(Config* config) {
	QString saveFilePath = "";
	//replace(saveFilePath.begin(), saveFilePath.end(), '\\', '_');
	for (char i : "DEFCGHIJKLMNOPQRSTUVWXYZAB") {
		if (isFileExists(QString("%0:/Program Files/steam/steamapps/common/MUSYNX/MUSYNX.exe").arg(i))) {
			saveFilePath = QString("%0:/Program Files/steam/steamapps/common/MUSYNX/").arg(i);
			break;
		}
		else if (isFileExists(QString("%0:/SteamLibrary/steamapps/common/MUSYNX/MUSYNX.exe").arg(i))) {
			saveFilePath = QString("%0:/SteamLibrary/steamapps/common/MUSYNX/MUSYNX.exe").arg(i);
			break;
		}
		else if (isFileExists(QString("%0:/steam/steamapps/common/MUSYNX/MUSYNX.exe").arg(i))) {
			saveFilePath = QString("%0:/steam/steamapps/common/MUSYNX/MUSYNX.exe").arg(i);
			break;
		}
	}
	if (saveFilePath != "") {
		QFile file("./musynx_data/SaveFilePath.sfp");
		if (file.open(QIODevice::WriteOnly)) {
			file.write(saveFilePath.toStdString().c_str());
		}
		config->MainExecPath = saveFilePath;
		config->dump();
	}
	return saveFilePath;
}

Config::Config() {
	if (!isFileExists(QDir::homePath() + "/musynx_data/config.json")) {

	}
}

bool Config::load() {
	std::cout << "Loading settings...";
	QDir dir(QDir::currentPath());
	if (!dir.exists("musynx_data")) {
		dir.mkdir("musynx_data");
		qout << FGGREEN << "Create \"musynx_data\" dir" << RESET;
	}
	dir.cd("musynx_data");
	QFile configFile(dir.filePath("config.json"));
	if (!configFile.open(QIODevice::ReadOnly)) {
		qout << FGRED << "Failure\n   File open error"<< RESET;
		return false;
	}
	if (configFile.size() == 0) {
		qout << FGBLUE << "Created" << RESET;
		this->dump();
		return true;
	}
	QByteArray configText = configFile.readAll();
	configFile.close();

	QJsonParseError jsonError;
	QJsonObject settings = QJsonDocument::fromJson(configText, &jsonError).object();

	this->Acc_Sync					 = settings.value("Acc_Sync"					).toBool();
	this->AutoCheckUpdate			 = settings.value("AutoCheckUpdate"				).toBool();
	this->AnalyzeWhenStarting		 = settings.value("AnalyzeWhenStarting"			).toBool();
	this->DLLInjection				 = settings.value("DLLInjection"				).toBool();
	this->SystemDPI					 = settings.value("SystemDPI"					).toInt();
	this->DonutChartinHitDelay		 = settings.value("DonutChartinHitDelay"		).toBool();
	this->DonutChartinAllHitAnalyze	 = settings.value("DonutChartinAllHitAnalyze"	).toBool();
	this->PDFofCyanExact			 = settings.value("PDFofCyanExact"				).toBool();
	this->NarrowDelayInterval		 = settings.value("NarrowDelayInterval"			).toBool();
	this->ChangeConsoleStyle		 = settings.value("ChangeConsoleStyle"			).toBool();
	this->ConsoleAlpha				 = settings.value("ConsoleAlpha"				).toInt();
	this->ConsoleFont				 = settings.value("ConsoleFont"					).toString();
	this->ConsoleFontSize			 = settings.value("ConsoleFontSize"				).toInt();
	this->MainExecPath				 = settings.value("MainExecPath"				).toString();
	this->DefaultKeys				 = settings.value("DefaultKeys"					).toInt();
	this->DefaultDiffcute			 = settings.value("DefaultDiffcute"				).toInt();

	qout << FGGREEN << "Success" << RESET;
	return true;
}

bool Config::dump() {
	std::cout << "Dumping settings...";
	QDir dir(QDir::currentPath() + "/musynx_data/");
	QFile configFile(dir.filePath("config.json"));
	QFile configFile(QDir::homePath() + "/musynx_data/config.json");
	if (!configFile.open(QIODevice::WriteOnly)) {
		qout << FGRED << "Failure\n   File open error" << RESET;
		return false;
	}
	QJsonParseError jsonError;
	// 创建Json Object
	QJsonObject settings;
	settings.insert("Acc_Sync",						this->Acc_Sync					);
	settings.insert("AutoCheckUpdate",				this->AutoCheckUpdate			);
	settings.insert("AnalyzeWhenStarting",			this->AnalyzeWhenStarting		);
	settings.insert("DLLInjection",					this->DLLInjection				);
	settings.insert("SystemDPI",					this->SystemDPI					);
	settings.insert("DonutChartinHitDelay",			this->DonutChartinHitDelay		);
	settings.insert("DonutChartinAllHitAnalyze",	this->DonutChartinAllHitAnalyze	);
	settings.insert("PDFofCyanExact",				this->PDFofCyanExact			);
	settings.insert("NarrowDelayInterval",			this->NarrowDelayInterval		);
	settings.insert("ChangeConsoleStyle",			this->ChangeConsoleStyle		);
	settings.insert("ConsoleAlpha",					this->ConsoleAlpha				);
	settings.insert("ConsoleFont",					this->ConsoleFont				);
	settings.insert("ConsoleFontSize",				this->ConsoleFontSize			);
	settings.insert("MainExecPath",					this->MainExecPath				);
	settings.insert("DefaultKeys",					this->DefaultKeys				);
	settings.insert("DefaultDiffcute",				this->DefaultDiffcute			);

	QJsonDocument document;
	document.setObject(settings);
	configFile.write(document.toJson());
	configFile.close();
	qout << FGGREEN << "Success" << RESET;
	return true;
}

void ChangeConsoleStyle(Config* config) {
	// 打开注册表项: "HKEY_CURRENT_USER\\Console\\musynx.exe"
	QSettings setting(QString("HKEY_CURRENT_USER\\Console\\musynx.exe"), QSettings::NativeFormat);
	// 写入注册表键值对
	setting.setValue("CodePage", 65001);
	setting.setValue("WindowSize", 262174);
	setting.setValue("WindowAlpha", (config->ConsoleAlpha * 255 / 100));
	setting.setValue("FaceName", config->ConsoleFont);
	setting.setValue("FontSize", config->ConsoleFontSize);
	setting.setValue("CursorSize", 32);
	//setting.remove("delete");
}

void getConsoleOutput() {
}