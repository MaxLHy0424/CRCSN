@Echo Off
SetLocal EnableDelayedExpansion
Title CRCSN Launcher
PUSHD %~DP0 & CD /D "%~dp0"
%1 %2
: 如果需要以管理员权限运行, 请将下一行的前的": "去掉.
: MsHTA Vbscript:CreateObject("Shell.Application").ShellExecute("%~S0","goto :RunAs","","RunAs",1)(Window.Close)&Goto:EOF
:RunAs
.\bin\main.exe -color=9 -beta