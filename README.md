![Logo](logo.png)\
**机房控制软件克星 (Computer Room Control Software Nemesis): 轻松破解机房控制.**\
*©️ 2024 MaxLHy0424, 保留所有权利.*

# 使用方式

> 适用于 v4.2.0 及以上版本.

**CRCSN 涉及到修改注册表等高危操作, 使用时建议关闭防病毒软件. 如 CRCSN 被报为恶意软件, 请添加排除项.**

## 1 破解

以管理员权限运行软件, 依次输入`1 1 Y`, 开始破解.

不起作用的话, 请检查是否有保护进程, 或在上一步所在的页面依次输入`1 2 0 Y`, 重复破解.

## 2 恢复

以管理员权限运行软件, 依次输入`2 Y`, 开始恢复.

## 3 编辑配置

打开软件目录下的`config.ini`, 根据说明修改配置.

接下来运行软件查看效果. 如果此时软件已经运行, 需要在主菜单输入`0`重载配置.

> 如果配置存在错误, 软件也不会进行提示. 如发现配置效果不合预期, 请检查配置文件是否正确.

接下来是配置项的详细介绍.

### 3-1 背景和文字的颜色

设置控制台背景和文字的颜色.

如果你经常使用命令提示符, 应该知道`Color`命令. 这个选项在软件内部的实现方式, 就是在所填配置的前面加上`Color `, 然后去执行来实现的.

举个例子, 配置选项为`F9`, 就相当于在命令提示符中执行`Color F9`, 就是在亮白色背景上显示蓝色文字.

具体配置详见`Color`命令帮助.

### 3-2 会话模式显示

设置是否在标题栏中显示当前的会话模式.

配置为`1`, 将会根据当前软件的权限, 在窗口标题最前面显示`[基本会话]`或`[增强会话]`. 否则, 将不会显示.

建议将此项保持默认.

### 3-3 主菜单文本

设置在主菜单显示的额外文本.

如将此项配置为`UNDEFINED`, 则不会显示额外文本, 否则将会显示所配置的文本. 文本将会显示在导航栏和选项之间.

此项请根据使用情况自行配置. 此处就抛砖引玉, 举几个例子, 供参考:
````MarkDown
1. 欢迎使用 CRCSN!
2. 夏莱的老师, 是来破解控制, 启动什亭之匣吗?
3. 勇者, 破掉这层枷锁, 去探索新的天地吧!
````

### 3-4 自定义命令

设置 "工具箱" 内 "自定义命令" 执行的命令.

如果将此项配置为`UNDEFINED`, 将视为配置 (即默认配置), 否则将会执行所配置的命令.

此项请根据使用情况自行配置. 此处就抛砖引玉, 列出几个常用的命令, 供参考:
````Batch
PowerShell #1
TaskKill /F /IM Explorer.exe #2
Shutdown /S /T 600 #3
````

> 仅支持传统命令. 如需使用 CmdLet 命令, 可以用英文半角双引号包住命令, 并在开头加上`PowerShell `.

# 注意事项

1. 软件优先适配 Windows 8.x/10/11, Windows 7 及以下的 Windows 操作系统的适配可能会延后.
2. 请勿在执行操作时关闭窗口, 否则可能会影响最终效果.
3. 请在遵守许可证的情况下使用软件.

# 常见问题

## 1 GitHub 在中国大陆地区难以访问, 获取软件非常不方便.

目前已经在网盘上传最新版本, 可以从[这里](https://www.123pan.com/s/HmR8jv-tZLN.html)下载.

## 2 运行软件时控制台总是输出 "命令提示符已被管理员禁用", 无法正常使用.

可以试试运行注册表编辑器, 定位到`HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\System`下, 看看有没有一个叫`DisableCMD`的`DWORD`值, 有的话就删掉, 再运行试试.

## 3 软件无法在 32 位 Windows 系统中使用.

可以克隆软件仓库, 使用 MinGW 编译源代码文件. 编译命令如下:
````Batch
g++ main.cpp -Ofast -Os -o main.exe -Wextra -lm -static -fexec-charset=GBK -std=c++11
````
编译完毕后, 运行生成的`main.exe`, 正常使用即可.

## 4 破解后一些软件运行时提示 "找不到文件" 之类的错误, 而运行的软件并没有损坏.

在不影响软件正常运行的情况下, 可以试试给软件文件修改一个名称, 再运行试试. 或者打开注册表编辑器, 定位到`HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\`, 找到和要运行的软件的文件名称相同的项, 删除即可.

## 5 软件目录下存在`config.ini`, 但软件提示无法读取.

请检查`config.ini`的属性 (右键`config.ini` > 属性 > 安全), 点击 "编辑", 依次点击上方列出的所有用户, 将下方的 "允许" 一栏全部勾选, "拒绝" 一栏全部取消勾选 (每栏的最后一个选项 "特殊权限" 可能无法 (取消) 勾选, 但并不影响), 再重载配置试试.

# 鸣谢

所有的测试人员, 所有提出建议的网友, 以及我的老师.