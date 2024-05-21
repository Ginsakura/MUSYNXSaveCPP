#pragma once

#include "functions_global.h"
#include <string>
#include <QDir>
#include <QString>

#define qout qDebug().noquote().nospace()

#define FRED	QFgColor(0xff,	0x00,	0x00)
#define FORANGE	QFgColor(0xff,	0x7f,	0x00)
#define FYELLOW	QFgColor(0xff,	0xff,	0x00)
#define FGREEN	QFgColor(0x00,	0xff,	0x00)
#define FCYAN	QFgColor(0x00,	0xff,	0xff)
#define FBLUE	QFgColor(0x00,	0x00,	0xff)
#define FPURPLE	QFgColor(0x7f,	0x00,	0xff)

#define BRED	QBgColor(0xff,	0x00,	0x00)
#define BORANGE	QBgColor(0xff,	0x7f,	0x00)
#define BYELLOW	QBgColor(0xff,	0xff,	0x00)
#define BGREEN	QBgColor(0x00,	0xff,	0x00)
#define BCYAN	QBgColor(0x00,	0xff,	0xff)
#define BBLUE	QBgColor(0x00,	0x00,	0xff)
#define BPURPLE	QBgColor(0x7f,	0x00,	0xff)
#define RESET	QResetColor()

// 使用`Disable`和`Enable`代替`false`和`true`
enum Bool {
	Disable = false,
	Enable = true
};
namespace FunctionsEnum {
	// 使用枚举类型代替字符串
	enum Keys { Keys4, Keys6 };
	enum Diffcuty { Easy, Hard, Inferno };
}


static bool isRandomInit = false;

//==================================================================
//函 数 名：SetSeed
//功能描述：初始化随机数种子
//输入参数：
//返 回 值：seed: unsigned
//==================================================================
FUNCTIONS_EXPORT unsigned SetSeed(void);

//==================================================================
//函 数 名：Randint
//功能描述：随机整数
//输入参数：min: int, max: int
//返 回 值：number: int
//==================================================================
FUNCTIONS_EXPORT int Randint(int, int);

//==================================================================
//函 数 名：Random
//功能描述：随机浮点数
//输入参数：min: double, max:double
//返 回 值：number: double
//==================================================================
FUNCTIONS_EXPORT double Random(double, double);

//==================================================================
//函 数 名：FgColor
//功能描述：设定控制台文字前景色(标准输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: string
//==================================================================
FUNCTIONS_EXPORT std::string FgColor(int, int, int);

//==================================================================
//函 数 名：BgColor
//功能描述：设定控制台文字背景色(标准输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: string
//==================================================================
FUNCTIONS_EXPORT std::string BgColor(int, int, int);

//==================================================================
//函 数 名：ResetColor
//功能描述：清除控制台文字前景背景色(标准输出)
//输入参数：
//返 回 值：ANSI: string
//==================================================================
FUNCTIONS_EXPORT std::string ResetColor(void);

//==================================================================
//函 数 名：QFgColor
//功能描述：设定控制台文字前景色(QtDebug输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: QString
//==================================================================
FUNCTIONS_EXPORT QString QFgColor(int r, int g, int b);

//==================================================================
//函 数 名：QBgColor
//功能描述：设定控制台文字背景色(QtDebug输出)
//输入参数：red: int, green: int, blue: int
//返 回 值：ANSI: QString
//==================================================================
FUNCTIONS_EXPORT QString QBgColor(int r, int g, int b);

//==================================================================
//函 数 名：QResetColor
//功能描述：清除控制台文字前景背景色(QtDebug输出)
//输入参数：
//返 回 值：ANSI: QString
//==================================================================
FUNCTIONS_EXPORT QString QResetColor();

class FUNCTIONS_EXPORT Config {
public:
	Config();
	~Config() {};

	//==================================================================
	//函 数 名：LoadConfig
	//功能描述：读取Config.json文件
	//输入参数：
	//返 回 值：state: bool
	//==================================================================
	bool load();

	//==================================================================
	//函 数 名：dump
	//功能描述：将配置信息写出到配置文件
	//输入参数：
	//返 回 值：state: bool
	//==================================================================
	bool dump();

	// Acc-Sync图表
	bool Acc_Sync = Disable;
	// 启动时版本检查
	bool AutoCheckUpdate = Enable;
	// 每次启动时重新扫描存档文件
	bool AnalyzeWhenStarting = Disable;
	// 启用DLL注入
	bool DLLInjection = Disable;
	// 读取系统DPI, 提供DPI窗体修正(未实现)
	int SystemDPI = 100;
	// 是否在单次游玩统计中显示击打延迟环形图
	bool DonutChartinHitDelay = Disable;
	// 是否在全局统计中显示击打延迟环形图
	bool DonutChartinAllHitAnalyze = Disable;
	// 是否在全局统计中显示仅CyanExact的正态分布拟合
	bool PDFofCyanExact = Disable;
	// 是否在单次游玩统计中使用更狭窄的击打区间来计算平均偏移值(Delay)
	// [Enable=45ms,Disable=90ms]
	bool NarrowDelayInterval = Enable;
	// 自定义喵赛克游戏本体控制台窗口样式
	bool ChangeConsoleStyle = Enable;
	// 喵赛克游戏本体控制台窗口的不透明度
	// (取值范围[0,100],100为完全不透明,不建议取值在30以下)
	int ConsoleAlpha = 75;
	// 喵赛克游戏本体控制台窗口的字体
	QString ConsoleFont = "霞鹜文楷等宽";
	// 喵赛克游戏本体控制台窗口的字号
	int ConsoleFontSize = 36;
	// 喵赛克游戏本体主程序所在的路径
	QString MainExecPath = "";
	// '高级功能'中默认'键数'参数
	enum FunctionsEnum::Keys DefaultKeys = FunctionsEnum::Keys4;
	// '高级功能'中默认'难度'参数
	enum FunctionsEnum::Diffcuty DefaultDiffcute = FunctionsEnum::Easy;
private:
	// 配置文件版本
	int ConfigVersion = 2;
	// 配置文件路径
	QDir configDir;

	//==================================================================
	//函 数 名：FromConfig_v1
	//功能描述：读取version 1的配置文件,并转换为version 2
	//输入参数：
	//返 回 值：state: bool
	//==================================================================
	bool FromConfig_v1();
};

//==================================================================
//函 数 名：GetScreenScale
//功能描述：获取系统DPI
//输入参数：
//返 回 值：DPI: double
//==================================================================
FUNCTIONS_EXPORT double GetScreenScale();

//==================================================================
//函 数 名：isFileExists
//功能描述：判断文件是否存在
//输入参数：name: QString
//返 回 值：isExists: bool
//==================================================================
FUNCTIONS_EXPORT bool isFileExists(QString name);

//==================================================================
//函 数 名：SearchMainExecPath
//功能描述：(简单)搜索MUSYNX游戏主程序地址
//输入参数：config: Config*
//返 回 值：filepath: QString
//==================================================================
FUNCTIONS_EXPORT QString SearchMainExecPath(Config* config);

//==================================================================
//函 数 名：FileMD5
//功能描述：计算文件MD5值
//输入参数：filepath: QString
//返 回 值：md5: QString
//==================================================================
FUNCTIONS_EXPORT QString FileMD5(QString name);

//==================================================================
//函 数 名：ChangeConsoleStyle
//功能描述：修改MUSYNX控制台的基础样式
//输入参数：config: Config*
//返 回 值：
//==================================================================
FUNCTIONS_EXPORT void ChangeConsoleStyle(Config* config);
