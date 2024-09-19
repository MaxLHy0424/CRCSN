#pragma once
#include"def.hpp"
#include"ui.hpp"
struct{
    bool wndFrontShow,wndAlpha,wndCtrls;
}opt{};
namespace Mod{
    auto init(){
        SetConsoleTitle(WINDOW_TITLE);
        if(!opt.wndCtrls){
            SetWindowLongPtr(
                GetConsoleWindow(),GWL_STYLE,
                GetWindowLongPtr(GetConsoleWindow(),GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX
            );
        }
        system("mode con cols=50 lines=25");
        SetLayeredWindowAttributes(GetConsoleWindow(),0,(opt.wndAlpha)?(204):(255),LWA_ALPHA);
    }
    auto frontShow(){
        HWND foreWnd{GetConsoleWindow()};
        DWORD foreId{GetWindowThreadProcessId(foreWnd,nullptr)},curId{GetCurrentThreadId()};
        while(true){
            AttachThreadInput(curId,foreId,TRUE);
            ShowWindow(foreWnd,SW_SHOWNORMAL);
            SetWindowPos(foreWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
            SetWindowPos(foreWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
            SetForegroundWindow(foreWnd);
            AttachThreadInput(curId,foreId,FALSE);
            SetWindowPos(foreWnd,HWND_TOPMOST,0,0,100,100,SWP_NOMOVE|SWP_NOSIZE);
            Sleep(100);
        }
    }
    auto exit(Data){
        return true;
    }
    auto info(Data){
        CUI ui;
        ui.add("                    | 关  于 |\n\n")
          .add(" > 返回 ",Mod::exit,nullptr,CON_RED_PALE)
          .add("\n[名称]\n")
          .add(" Computer Room Control Software Nemesis")
          .add("\n[版本]\n")
          .add(" " VERSION_INFO)
          .add("\n[仓库]\n")
          .add(" https://github.com/MaxLHy0424/CRCSN")
          .add("\n[许可证]\n")
          .add(" MIT License")
          .add(" (C) 2023 MaxLHy0424. All rights reserved.")
          .show();
        return false;
    }
    auto cmd(Data){
        system("cmd");
        return false;
    }
    struct{
        struct{
            std::vector<const i8*> exe,svc;
        }mythware;
        struct{
            std::vector<const i8*> exe,svc;
        }lenovo;
    }rule{
        {
            {
                "StudentMain","DispcapHelper","VRCwPlayer",
                "InstHelpApp","InstHelpApp64","TDOvrSet",
                "GATESRV","ProcHelper64","MasterHelper"
            },{
                "STUDSRV","TDNetFilter","TDFileFilter"
            }
        },{
            {
                "vncviewer","tvnserver32","WfbsPnpInstall",
                "WFBSMon","WFBSMlogon","WFBSSvrLogShow",
                "ResetIp","FuncForWIN64","CertMgr",
                "Fireware","BCDBootCopy","refreship",
                "lenovoLockScreen","PortControl64","DesktopCheck",
                "DeploymentManager","DeploymentAgent","XYNTService"
            },{
                "BSAgentSvr","tvnserver","WFBSMlogon"
            }
        }
    };
    struct ArgsOp final{
        i8 f;
        std::vector<const i8*> &exe,&svc;
    };
    auto op(Data data){
        std::string cmd;
        switch(((ArgsOp*)data.args)->f){
            case 'c':{
                for(const auto &ref:((ArgsOp*)data.args)->exe){
                    cmd="reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution options\\"
                        +(std::string)ref+".exe\" /f /t reg_sz /v debugger /d ?";
                    system(cmd.c_str());
                    cmd="taskKill /f /im "+(std::string)ref+".exe";
                    system(cmd.c_str());
                }
                for(const auto &ref:((ArgsOp*)data.args)->svc){
                    cmd="net stop "+(std::string)ref+" /y";
                    system(cmd.c_str());
                }
                break;
            }case 'r':{
                for(const auto &ref:((ArgsOp*)data.args)->exe){
                    cmd="reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution options\\"
                        +(std::string)ref+".exe\" /f";
                    system(cmd.c_str());
                }
                for(const auto &ref:((ArgsOp*)data.args)->svc){
                    cmd="net start "+(std::string)ref;
                    system(cmd.c_str());
                }
                break;
            }
        }
        return false;
    }
}