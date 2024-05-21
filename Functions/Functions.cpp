#include "Functions.h"

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <uiautomation.h>
#include <Windows.h>

#include <QCryptographicHash>
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
	this->configDir = QDir(QDir::currentPath());
	if (!configDir.exists("musynx_data")) {
		configDir.mkdir("musynx_data");
		qout << FGREEN << "Create \"musynx_data\" dir" << RESET;
	}
	configDir.cd("musynx_data");
	if (isFileExists(configDir.filePath("config.json"))) {
		qout << FGREEN << "Config_v2 Exists" << RESET;
		this->load();
	}
	else if (isFileExists(configDir.filePath("ExtraFunction.cfg"))){
		qout << FGREEN << "Config_v1 Exists" << RESET;
		std::cout << FORANGE.toStdString() << "Converting config version..." << ResetColor();
		if (this->FromConfig_v1()) {
			qout << FGREEN << "Success" << RESET;
			this->dump();
		}
	}
	else {
		qout << FORANGE << "Config File not Exists." << RESET;
		this->dump();
	}
}

bool Config::load() {
	std::cout << "Loading settings...";
	QFile configFile(configDir.filePath("config.json"));
	if (!configFile.open(QIODevice::ReadOnly)) {
		qout << FRED << "Failure\n   File open error"<< RESET;
		return false;
	}

	QByteArray configText = configFile.readAll();
	configFile.close();

	QJsonParseError jsonError;
	QJsonObject settings = QJsonDocument::fromJson(configText, &jsonError).object();

	// 判断是否出错
	if (jsonError.error != QJsonParseError::NoError) {
		qout << FRED << "Error: \n" << jsonError.errorString() << RESET;
		return false;
	}
	else {
		// 读取settings对象并赋值
		this->Acc_Sync = settings.value("Acc_Sync").toBool();
		this->AutoCheckUpdate = settings.value("AutoCheckUpdate").toBool();
		this->AnalyzeWhenStarting = settings.value("AnalyzeWhenStarting").toBool();
		this->DLLInjection = settings.value("DLLInjection").toBool();
		this->SystemDPI = settings.value("SystemDPI").toInt();
		this->DonutChartinHitDelay = settings.value("DonutChartinHitDelay").toBool();
		this->DonutChartinAllHitAnalyze = settings.value("DonutChartinAllHitAnalyze").toBool();
		this->PDFofCyanExact = settings.value("PDFofCyanExact").toBool();
		this->NarrowDelayInterval = settings.value("NarrowDelayInterval").toBool();
		this->ChangeConsoleStyle = settings.value("ChangeConsoleStyle").toBool();
		this->ConsoleAlpha = settings.value("ConsoleAlpha").toInt();
		this->ConsoleFont = settings.value("ConsoleFont").toString();
		this->ConsoleFontSize = settings.value("ConsoleFontSize").toInt();
		this->MainExecPath = settings.value("MainExecPath").toString();
		this->DefaultKeys = FunctionsEnum::Keys(settings.value("DefaultKeys").toInt());
		this->DefaultDiffcute = FunctionsEnum::Diffcuty(settings.value("DefaultDiffcute").toInt());
		this->ConfigVersion = settings.value("ConfigVersion").toInt();
		qout << FGREEN << "Success" << RESET;
		return true;
	}
}

bool Config::dump() {
	std::cout << "Dumping settings...";
	QFile configFile(configDir.filePath("config.json"));
	if (!configFile.open(QIODevice::WriteOnly)) {
		qout << FRED << "Failure\n   File open error" << RESET;
		return false;
	}
	// 创建Json Object
	QJsonObject settings;
	// 填入数据
	settings.insert("Acc_Sync", this->Acc_Sync);
	settings.insert("AutoCheckUpdate", this->AutoCheckUpdate);
	settings.insert("AnalyzeWhenStarting", this->AnalyzeWhenStarting);
	settings.insert("DLLInjection", this->DLLInjection);
	settings.insert("SystemDPI", this->SystemDPI);
	settings.insert("DonutChartinHitDelay", this->DonutChartinHitDelay);
	settings.insert("DonutChartinAllHitAnalyze", this->DonutChartinAllHitAnalyze);
	settings.insert("PDFofCyanExact", this->PDFofCyanExact);
	settings.insert("NarrowDelayInterval", this->NarrowDelayInterval);
	settings.insert("ChangeConsoleStyle", this->ChangeConsoleStyle);
	settings.insert("ConsoleAlpha", this->ConsoleAlpha);
	settings.insert("ConsoleFont", this->ConsoleFont);
	settings.insert("ConsoleFontSize", this->ConsoleFontSize);
	settings.insert("MainExecPath", this->MainExecPath);
	settings.insert("DefaultKeys", this->DefaultKeys);
	settings.insert("DefaultDiffcute", this->DefaultDiffcute);
	settings.insert("ConfigVersion", this->ConfigVersion);

	// 创建JsonDocument并添加settings对象
	QJsonDocument document;
	document.setObject(settings);
	// 写出文件
	configFile.write(document.toJson());
	configFile.close();
	qout << FGREEN << "Success" << RESET;
	return true;
}

bool Config::FromConfig_v1() {
	QFile configFile(configDir.filePath("ExtraFunction.cfg"));
	if (!configFile.open(QIODevice::WriteOnly)) {
		qout << FRED << "Failure\n   File open error" << RESET;
		return false;
	}

	QByteArray configText = configFile.readAll();
	configFile.close();

	QJsonParseError jsonError;
	QJsonObject settings = QJsonDocument::fromJson(configText, &jsonError).object();

	// 判断是否出错
	if (jsonError.error != QJsonParseError::NoError) {
		qout << FRED << "Error: \n" << jsonError.errorString() << RESET;
		return false;
	}
	else {
		// 读取settings对象并赋值
		this->Acc_Sync = settings.value("EnableAcc-Sync").toBool();
		this->AutoCheckUpdate = !(settings.value("DisableCheckUpdate").toBool());
		this->AnalyzeWhenStarting = settings.value("EnableAnalyzeWhenStarting").toBool();
		this->DLLInjection = settings.value("EnableDLLInjection").toBool();
		this->SystemDPI = settings.value("SystemDPI").toInt();
		this->DonutChartinHitDelay = settings.value("EnableDonutChartinHitDelay").toBool();
		this->DonutChartinAllHitAnalyze = settings.value("EnableDonutChartinAllHitAnalyze").toBool();
		this->PDFofCyanExact = settings.value("EnablePDFofCyanExact").toBool();
		this->NarrowDelayInterval = settings.value("EnableNarrowDelayInterval").toBool();
		this->ChangeConsoleStyle = settings.value("ChangeConsoleStyle").toBool();
		this->ConsoleAlpha = settings.value("ConsoleAlpha").toInt();
		this->ConsoleFont = settings.value("ConsoleFont").toString();
		this->ConsoleFontSize = settings.value("ConsoleFontSize").toInt();
		this->MainExecPath = settings.value("MainExecPath").toString();
		this->DefaultKeys = FunctionsEnum::Keys(settings.value("DefaultKeys").toInt());
		this->DefaultDiffcute = FunctionsEnum::Diffcuty(settings.value("DefaultDiffcute").toInt());
		this->ConfigVersion = 2;
		qout << FGREEN << "Success" << RESET;
		return true;
	}
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