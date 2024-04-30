@Echo Off
SetLocal EnableDelayedExpansion
Title CRCSN Launcher
PUSHD %~DP0 & CD /D "%~dp0"
%1 %2
: MsHTA Vbscript:CreateObject("Shell.Application").ShellExecute("%~S0","goto :RunAs","","RunAs",1)(Window.Close)&Goto:EOF
:RunAs
.\bin\main.exe -color=9