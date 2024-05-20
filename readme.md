# 同步音律喵赛克 Steam端 存档解析工具 C++重构版
MUSYNX Steam Client Savefile Decode & Analyze Tool C++ Version

[down_svg]: https://img.shields.io/github/downloads/ginsakura/MUSYNXSaveCPP/total?label=All%20Downloads
[all_release]: https://github.com/Ginsakura/MUSYNXSaveCPP/releases
[commit_svg]: https://img.shields.io/github/commit-activity/t/ginsakura/MUSYNXSaveCPP?label=All%20Commits
[commit]: https://github.com/Ginsakura/MUSYNXSaveCPP/commits
[license_svg]: https://img.shields.io/github/license/ginsakura/MUSYNXSaveCPP?label=License
[![All releases][down_svg]][all_release]
[![All commit activity (branch)][commit_svg]][commit]
[![License][license_svg]](./LICENSE)

[latest_prerelease_svg]: https://img.shields.io/github/v/release/ginsakura/MUSYNXSaveCPP?display_name=release&label=Latest%20PreRelease&include_prereleases
[all_tags]: https://github.com/Ginsakura/MUSYNXSaveCPP/tags
[![Latest tag][latest_prerelease_svg]][all_tags]

[latest_release_svg]: https://img.shields.io/github/v/release/ginsakura/MUSYNXSaveCPP?display_name=release&label=Latest%20Release
[release]: https://github.com/Ginsakura/MUSYNXSaveCPP/releases/latest
[![latest release][latest_release_svg]][release]

## How to use

1. [English (English, `en-us`) v1.2.6 rc2](How_to_use.en.md)
2. [简体中文 (Simplified Chinese, `zh-Hans`) v1.2.6 rc2](How_to_use.zh.md)

## 界面展示

<details>
<summary>界面展示</summary>

![主页面](./ReadmeResources/main.png "主页面")
![score-diff页面](./ReadmeResources/score-diff.png "score-diff页面")
![HitDelay页面](./ReadmeResources/HitDelay.png "HitDelay页面")
![HitAnalyze-Pie&Bar页面](./ReadmeResources/HitAnalyze-Pie&Bar.png "HitAnalyze-Pie&Bar页面")
![HitAnalyze-Line页面](./ReadmeResources/HitAnalyze-Line.png "HitAnalyze-Line页面")
![AllHitAnalyze-Pie页面](./ReadmeResources/AllHitAnalyze.png "AllHitAnalyze页面")
![AvgAcc-SYNC.Rate回归分析页面](./ReadmeResources/AvgAcc-SYNC.Rate.png "AvgAcc-SYNC.Rate回归分析")

</details>

## 计划
### 未来的计划
- [ ] 提供全球排行榜显示功能 (需要调用SteamAPI)
- [ ] 将提供一个文档来演示使用方法 (在写了,咕咕咕)
- [ ] 使用文件夹内指定文件名的方式自定义美化UI
### 已完成的计划
- [x] 一键获取上次谱面游玩结果
- [x] 使用GitHub Action workflow实现自动分发
- [x] 重排版SongName.json
- [x] 滑动条在重加载后保持位置不变
- [x] 隐藏cmd窗口
- [x] 将像Windows资源管理器一样使用列标题栏进行排序
- [x] 将高级功能整合为`ExtraFunction.cfg`配置文件

## Release版本说明
NoConsole版本为没有命令提示符界面，适合正常使用

WithConsole版本为带命令提示符界面，适合出现bug时快速定位错误发生地点以及原因

## 功能控制模块
<details>
<summary>控制参数详解</summary>

于`./musynx_data/ExtraFunction.cfg`文件中启用/禁用对应功能

|               配置项              |     默认值    | 值类型 |                                配置说明                                |
|-----------------------------------|---------------|--------|------------------------------------------------------------------------|
| `EnableAcc-Sync`                  |false          |boolean |是否启用Acc-Synx图表                                                    |
| `DisableCheckUpdate`              |false          |boolean |是否禁用更新检测                                                        |
| `EnableAnalyzeWhenStarting`       |false          |boolean |是否启用每次启动时重新扫描存档文件                                      |
| `EnableDLLInjection`              |false          |boolean |是否启用DLL注入以开启`高级功能`                                         |
| `SystemDPI`                       |`自动获取`     |string  |读取系统DPI, 提供DPI窗体修正(未实现)                                    |
| `EnableDonutChartinHitDelay`      |false          |boolean |是否在单次游玩统计中显示击打延迟环形图                                  |
| `EnableDonutChartinAllHitAnalyze` |false          |boolean |是否在全局统计中显示击打延迟环形图                                      |
| `EnablePDFofCyanExact`            |false          |boolean |是否在全局统计中显示仅CyanExact的正态分布拟合                           |
| `EnableNarrowDelayInterval`       |true           |boolean |是否在单次游玩统计中使用更狭窄的击打区间来计算平均偏移值(Delay)<br>[true=45ms,false=90ms]|
| `ConsoleAlpha`                    |75             |int     |喵赛克游戏本体控制台窗口的不透明度<br>(取值范围[0,100],100为完全不透明,不建议取值在30以下)|
| `ConsoleFont`                     |'霞鹜文楷等宽' |string  |喵赛克游戏本体控制台窗口的字体                                          |
| `ConsoleFontSize`                 |36             |int     |喵赛克游戏本体控制台窗口的字号                                          |
| `MainExecPath`                    |`自动获取`     |string  |喵赛克游戏本体主程序所在的路径                                          |
| `ChangeConsoleStyle`              |false          |boolean |是否启用自定义喵赛克游戏本体控制台窗口样式                              |
| `EnableFramelessWindow`           |false          |boolean |是否启用无边框窗口样式(未完成)                                          |
| `TransparentColor`                |'#FFFFFF'      |string<br>boolean |设置透明色(仅限新样式)<br>设置为false即为关闭透明色           |
| `DefaultKeys`                     |false          |boolean |`高级功能`中默认`键数`参数                                              |
| `DefaultDiffcute`                 |0              |int     |`高级功能`中默认`难度`参数                                              |

</details>

### 高级功能简介
下列组件对游戏客户端有修改,请谨慎使用

*** $\color{Red}{ 注意备份 注意备份 注意备份 }$ ***

$\color{Red}{请自行决定是否使用,使用过程中出现任何意外}$
$\color{Red}{后果自负,开发者概不负责}$

HitDelay模块用法:启用DLL注入后,在本次游戏进行首次谱面游玩时会打开一个cmd窗口 $\color{Red}{请勿关闭该窗口}$

- `HitDelayFix.dll` 被精心修改过的客户端文件,原始文件为`./MUSYNX_Data/Managed/Assembly-CSharp.dll`.
- `HitDelayLine.py` 用于读取`./musynx_data/HitDelay.log`中的击打信息生成可视化数据表,标题栏提供三个统计信息.
    - `AvgDelay` 平均击打延迟,即所有击打的平均值,能够一定程度上提示游戏延迟应该调整的数值(可能有较大偏差,仅供参考).
    比如游戏内判定补偿是+010ms,AvgDelay数值为-5ms,那么就应将游戏内判定补偿减少5ms,但是具体需要调整多少请多次测试.
    - `AllKeys` 谱面中存在note的数目.
    - `AvgAcc` 平均击打偏差,即所有击打的绝对值的平均值,该值总为正数.
    该值反应了您当前谱面本次游玩击打Key的时机的精准度,该值与您本次游玩的结算成绩有一定的关联:

    该值越小,就说明您击打的越精准,(在该值小于45ms时,您的)分值就会越高.

## 更新日志
<!--
### Version 
#### PreRelease 
1. 更新
    1. xxx
2. 修复
    1. xxx
3. 优化
    1. xxx
-->

## 初始化项目(尚未达到可用标准)
### Version 0.0.8
1. 修改函数参数类型 `isFileExists(std::string&)` -> `isFileExists(QString)`
2. 编写函数 `FileMD5()`
3. 编写函数 `SearchMainExecPath()`
4. 创建构造函数 `Config::Config()`
5. 重写函数 `LoadConfig()` -> `Config::load()`
5. 重写函数 `WriteConfig()` -> `Config::dump()`
7. 添加默认色彩宏,分别为`FGRED`,`BGRED`,`FGGREEN`,`BGGREEN`,`FGBLUE`,`BGBLUE`,`RESET`
### Version 0.0.7
1. 创建数据库表结构
    #### HitDelayHistory
    |     字段    | 类型 | 备注 |
    |-------------|------|------|
    | SongMapName | text | PMK  |
    | Keys        | int  |      |
    | Diffcuty    | text |      |
    | RecordTime  | text | PMK  |
    | AvgDelay    | real |      |
    | AllKeys     | int  |      |
    | AvgAcc      | real |      |
    | HitMap      | text |      |
2. 增加数据库连接确认
1. 修改项目名: `MUSYNXSavDecode` -> `MUSYNXSavDecodeCPP`
2. 修改数据库名: `HitDelayHistory_v2.db` -> `data.db`
3. 修改数据库表名: `HitDelayHistory` -> `HitDelayHistory_v3`
4. 修改`HitDelay.ui`中的表格布局
5. 把函数注释从实现(.cpp)移动到声明(.h)
6. 添加配置类用于在程序中存储配置数据
7. 新增多个工具函数
### Version 0.0.6
1. 删除`stdafx`预编译头
2. 修改moc目录
3. 修改uic目录
4. 添加引用树
5. 删除`HitDelay`、`DifficultyScoreAnalyze`头文件中的`Q_DECL_IMPORT`
6. 修复主界面头文件引用
7. 使用前向声明的方式解决`Q_OBJECT`与`Q_DECL_IMPORT`冲突的问题
### Version 0.0.5
1. 添加注释
2. 对HitDelayHistoryORM添加切换Insert/Update函数
3. 将全局的`MUSYNC`替换为`MUSYNX`
4. 将`Functions`分离为DLL文件
5. 筛选`musynx_data`目录中的文件
6. 将`HitDelay`页面分离为DLL文件
7. 将`SQL`封装分离为DLL文件
8. 将`DifficultyScoreAnalyze`页面分离为DLL文件
9. 将所有`GBK`编码转换为`UTF-8-BOM`编码
### Version 0.0.4
1. 将所有`GBK`编码转换为`UTF-8-BOM`编码
2. 将所有`UTF-8`编码转换为`UTF-8-BOM`编码
3. 对所有UI添加基础信号槽函数
4. 调整UI部件命名
5. 微调UI布局
6. 关联多个窗口
7. 修复Repo链接指向的Python版仓库而不是cpp版仓库的错误
8. 将筛选转换为枚举类型
### Version 0.0.3
1. 从Python项目添加资源文件
2. 微调UI布局
3. 添加HitDelay窗口
4. 主窗口添加版本显示
5. 主窗口移除SQL相关库
6. 主窗口添加版本信息
7. 初步完成SQL封装
### Version 0.0.2
1. 添加获取系统DPI函数
2. 微调UI
### Version 0.0.1
1. 初始化项目,搭建框架

## 声明：妾身`不会`对存档文件进行`写`操作