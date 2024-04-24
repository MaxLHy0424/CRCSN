#pragma once
#include<stdio.h>
#include<fstream>
#include<ShlObj.h>
#include<thread>
char Code[3]{};
std::string CfgDt[3]{"","NUL",""};
DWORD KernalVersion(){
    DWORD version{GetVersion()};
    DWORD major{(DWORD)(LOBYTE(LOWORD(version)))},minor{(DWORD)(HIBYTE(LOWORD(version)))};
    return major*10UL+minor;
}
bool Confirm(){
    printf("是否继续? (Y/N): ");
    for(;;){
        scanf("%s",&Code[1]);
        if((Code[1]=='Y'||Code[1]=='y'||Code[1]=='N'||Code[1]=='n')&&(Code[2]==0)){
            break;
        }
        printf("输入有误, 请重试: ");
    }
    return (Code[1]=='Y'||Code[1]=='y');
}
void ForceShow(){
    HWND ForeWnd{GetForegroundWindow()};
    DWORD ForeID{GetWindowThreadProcessId(ForeWnd,NULL)};
    DWORD CurID{GetCurrentThreadId()};
    for(;;){
        if(CfgDt[2]!="1"){
            SetWindowPos(ForeWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
            return;
        }
        AttachThreadInput(CurID,ForeID,TRUE);
        ShowWindow(ForeWnd,SW_SHOWNORMAL);
        SetWindowPos(ForeWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
        SetWindowPos(ForeWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
        SetForegroundWindow(ForeWnd);
        AttachThreadInput(CurID,ForeID,FALSE);
        SetWindowPos(ForeWnd,HWND_TOPMOST,0,0,100,100,SWP_NOMOVE|SWP_NOSIZE);
        Sleep(500UL);
    }
}