@echo off
title CRCSN Launcher v1.0.15
cd /d "%~dp0"
%1 %2
: msHta vbScript:createObject("shell.application").shellExecute("%~s0","goTo:runAs","","runAs",1)(window.close) & goTo:eof
:runAs
.\bin\main.exe