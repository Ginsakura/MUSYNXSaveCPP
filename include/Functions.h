#pragma once

#include <functions_global.h>
#include <QString>

// 使用`Disable`和`Enable`代替`false`和`true`
enum Bool {
	Disable = false,
	Enable = true
};

// 使用枚举类型代替字符串
enum Keys { Keys4, Keys6 };
enum DiffcutyString { Easy, Hard, Inferno };


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
	Config() {};
	~Config() {};
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
	int DefaultKeys = Keys4;
	// '高级功能'中默认'难度'参数
	int DefaultDiffcute = Easy;
private:
	// 配置文件版本
	int ConfigVersion = 2;
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
//输入参数：name: string
//返 回 值：isExists: bool
//==================================================================
FUNCTIONS_EXPORT bool isFileExists(std::string& name);

//==================================================================
//函 数 名：SearchMainExecPath
//功能描述：(简单)搜索MUSYNX游戏主程序地址
//输入参数：
//返 回 值：DPI: double
//==================================================================
FUNCTIONS_EXPORT std::string SearchMainExecPath();

//==================================================================
//函 数 名：LoadConfig
//功能描述：读取Config.json文件,返回Config对象指针(堆内存)
//输入参数：
//返 回 值：config: Config*
//==================================================================
FUNCTIONS_EXPORT Config* LoadConfig();

//==================================================================
//函 数 名：WriteConfig
//功能描述：将Config对象写出到Config.json文件
//输入参数：config: Config*
//返 回 值：state: bool
//==================================================================
FUNCTIONS_EXPORT bool WriteConfig(Config* config);

//==================================================================
//函 数 名：ChangeConsoleStyle
//功能描述：修改MUSYNX控制台的基础样式
//输入参数：config: Config*
//返 回 值：
//==================================================================
FUNCTIONS_EXPORT void ChangeConsoleStyle(Config* config);
