@Echo Off
Title CRCSN Launcher v1.1.3
Echo (C) 2024 MaxLHy0424, All Rights Reserved.
CD /D "%~DP0"
%1 %2
TimeOut /NoBreak /T 3
: MsHta VBScript:CreateObject("Shell.Application").ShellExecute("%~S0","GoTo:RunAs","","RunAs",1)(Window.Close) & GoTo:EOF
:RunAs
.\bin\main.exe -fs
GoTo RunAs