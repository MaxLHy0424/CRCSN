# 简介

你是否因为无法脱离机房的控制, 而无法欢快使用机房的电脑?

这个软件可以帮到你!

机房控制软件克星 (Computer Room Control Software Nemesis, 简称 CRCSN), 可以帮助你通过简单的操作快速脱离控制!

# 使用方式

>最后更新于 2024/01/27
>适用于 CRCSN v3.0 及以上版本

CRCSN 大多数选项都有提示, 可以跟着提示一起看

建议先关闭 / 退出操作系统上已安装的所有反病毒软件, 以免干扰软件执行操作.

## 破解

以管理员权限运行软件, 依次输入 `1 1 Y`, 开始破解.

然后等个几十秒关闭软件即可.

## 恢复

以管理员权限运行软件, 依次输入 `2 Y`, 开始恢复.

接着根据提示, 手动打开两个控制软件的安装目录, 分别找到每个软件, 以管理员权限运每个软件.

接着关闭软件即可.

# 注意事项

此软件仅可用于 Windows 平台.

此软件仅用于学习交流, 禁止用于商业用途.

此软件按照 MIT 协议开源, 请在遵守 MIT 协议的情况下使用.

(C) Copyright 2023-2024 MaxLHy0424, All Rights Reserved.

# 常见问题

Q1: 运行软件时控制台界面总是输出 "命令提示符已被管理员禁用" 之类的提示, 无法正常使用, 如何解决?

A1: 这说明 CMD 已被禁用. 可以试试打开注册表编辑器, 定位到 `HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\System` 下, 看看有没有一个叫 `DisableCMD` 的 DWORD 值, 有的话就删掉. 再次打开软件看看是否能成功. (如果还是打不开, 那我也不知道了 awa)

Q2: 软件无法在 32 位 Windows 系统中使用, 有什么办法吗?

A2: 软件暂无计划发布 32 位版本. 可以先下载软件源代码, 使用 MinGW-w32 编译源代码文件, 正常使用即可.

Q3: 破解后一些软件打开提示 "找不到文件" 之类的错误, 并且打开的软件本身并没有损坏, 是什么情况?

A3: CRCSN v3.0 添加了通过注册表劫持控制软件, 间接达到禁止启动控制软件的效果, 但弊端是和控制软件的文件名一样的软件文件也无法打开了. 在不影响软件正常运行的情况下, 可以试试给软件文件修改一个名称, 再打开试试. 实在不行就打开注册表编辑器, 定位到 `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\` 下, 找到和要运行的软件的文件名称相同的项, 删除项即可.

# 公告

CRCSN v3.0 功能更新列表:
1. 全新的映像劫持功能
2. 更加全面的进程处理规则, 更加全面的服务处理规则
3. 统一的返回操作
4. 方便的 "受限模式"
5. 更深度的优化

# 鸣谢

所有辛苦的测试人员, 所有提出宝贵建议的网友, 以及我的老师.