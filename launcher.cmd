@echo off
set arch=x86_64
set bin=msvcrt
cd /d "%~dp0"
chcp 65001
%1
mode con cols=50 lines=25
title CRCSN Launcher
echo                  CRCSN Launcher
echo                      24w32a
echo     (C) 2023 MaxLHy0424. All Rights Reserved.
echo.
echo 按任意键启动 CRCSN (%arch%, %bin%).
pause > nul
: msHta vbScript:createObject("shell.application").shellExecute("%~s0","goTo:runAs","","runAs",1)(window.close) & goTo:eof
:runAs
.\bin\CRCSN-%arch%-%bin%.exe