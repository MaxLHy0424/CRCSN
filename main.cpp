#include"extern.hpp"
void About(){
    puts("| ~ / 关于 |\n");
    puts("   [软件名称] Computer Room Controlling Software Nemesis");
    puts("   [项目作者] MaxLHy0424");
    puts("   [软件版本] v5.0.0-dev2");
    puts("   [项目仓库] https://github.com/MaxLHy0424/CRCSN\n");
    puts("   (C) 2023- MaxLHy0424, 保留所有权利.\n");
    puts("========================================\n");
    puts("按任意键返回.\n");
    system("Pause");
    return;
}
void Cracker(){
BEGIN:
    puts("| ~ / 破解 |\n");
    puts("   [0] 返回");
    puts("   [1] 极域电子教室");
    puts("   [2] 联想云教室\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Code[0]);
        if((Code[0]=='0'||Code[0]=='1'||Code[0]=='2')&&(Code[1]==0)){
            break;
        }
        printf("输入错误, 请重新输入: ");
    }
    if(Code[0]=='0'){
        return;
    }
    printf("已%s用 [高级破解], ",((IsUserAnAdmin())?("启"):("禁")));
    if(Confirm()==true){
        system("Cls");
        puts("| ~ / 破解 / 执行操作 |\n");
        switch(Code[0]){
            case '1':{
                system("TaskKill /F /T /IM StudentMain.exe");
                system("TaskKill /F /T /IM DispcapHelper.exe");
                system("TaskKill /F /T /IM InstHelpApp.exe");
                system("TaskKill /F /T /IM GATESRV.exe");
                system("TaskKill /F /T /IM ProcHelper64.exe");
                system("TaskKill /F /T /IM MasterHelper.exe");
                if(IsUserAnAdmin()){
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\StudentMain.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DispcapHelper.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\VRCwPlayer.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp64.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\TDOvrSet.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\GATESRV.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ProcHelper64.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\MasterHelper.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Net Stop TDNetFilter /Y");
                    system("Net Stop TDFileFilter /Y");
                    system("Net Stop STUDSRV /Y");
                }
                break;
            }case '2':{
                system("TaskKill /F /T /IM vncviewer.exe");
                system("TaskKill /F /T /IM tvnserver32.exe");
                system("TaskKill /F /T /IM WfbsPnpInstall.exe");
                system("TaskKill /F /T /IM WFBSMon.exe");
                system("TaskKill /F /T /IM WFBSMlogon.exe");
                system("TaskKill /F /T /IM WFBSSvrLogShow.exe");
                system("TaskKill /F /T /IM ResetIp.exe");
                system("TaskKill /F /T /IM Fireware.exe");
                system("TaskKill /F /T /IM BCDBootCopy.exe");
                system("TaskKill /F /T /IM refreship.exe");
                system("TaskKill /F /T /IM LenovoLockScreen.exe");
                system("TaskKill /F /T /IM PortControl64.exe");
                system("TaskKill /F /T /IM DesktopCheck.exe");
                system("TaskKill /F /T /IM DeploymentManager.exe");
                system("TaskKill /F /T /IM DeploymentAgent.exe");
                system("TaskKill /F /T /IM XYNTService.exe");
                if(IsUserAnAdmin()){
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\vncviewer.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tvnserver32.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WfbsPnpInstall.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMon.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMlogon.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSSvrLogShow.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ResetIp.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\FuncForWIN64.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\CertMgr.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Fireware.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\BCDBootCopy.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\refreship.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\LenovoLockScreen.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\PortControl64.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DesktopCheck.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentManager.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentAgent.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\XYNTService.exe\" /F /T REG_SZ /V debugger /D \"BLOCK\"");
                    system("Net Stop tvnserver /Y");
                    system("Net Stop BSAgentSvr /Y");
                    system("Net Stop WFBSMlogon /Y");
                }
                break;
            }
        }
        puts("========================================\n");
        puts("按任意键返回.\n");
        system("Pause");
    }
    system("Cls");
    goto BEGIN;
}
void Recoverer(){
BEGIN:
    puts("| ~ / 恢复 |\n");
    if(!IsUserAnAdmin()){
        puts("基本会话下不可用.\n");
        puts("========================================\n");
        puts("按任意键返回.\n");
        system("Pause");
        return;
    }
    puts("   [0] 返回");
    puts("   [1] 极域电子教室");
    puts("   [2] 联想云教室\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Code[0]);
        if((Code[0]=='0'||Code[0]=='1'||Code[0]=='2')&&(Code[1]==0)){
            break;
        }
        printf("输入错误, 请重新输入: ");
    }
    if(Code[0]=='0'){
        return;
    }
    if(Confirm()==true){
        system("Cls");
        puts("| ~ / 恢复 / 执行操作 |\n");
        switch(Code[0]){
            case '1':{
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\StudentMain.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DispcapHelper.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\VRCwPlayer.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp64.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\TDOvrSet.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\GATESRV.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ProcHelper64.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\MasterHelper.exe\" /F");
                system("Net Start TDNetFilter");
                system("Net Start TDFileFilter");
                system("Net Start STUDSRV");
                break;
            }case '2':{
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\vncviewer.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tvnserver32.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WfbsPnpInstall.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMon.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMlogon.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSSvrLogShow.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ResetIp.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\FuncForWIN64.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\CertMgr.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Fireware.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\BCDBootCopy.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\refreship.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\LenovoLockScreen.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\PortControl64.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DesktopCheck.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentManager.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentAgent.exe\" /F");
                system("Reg Delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\XYNTService.exe\" /F");
                system("Net Start tvnserver");
                system("Net Start BSAgentSvr");
                system("Net Start WFBSMlogon");
                break;
            }
        }
        puts("========================================\n");
        puts("按任意键返回.\n");
        system("Pause");
    }
    system("Cls");
    goto BEGIN;
}
void Toolkit(){
BEGIN:
    puts("| ~ / 工具箱 |\n");
    if(!IsUserAnAdmin()){
        puts("基本会话下不可用.\n");
        puts("========================================\n");
        puts("按任意键返回.\n");
        system("Pause");
        return;
    }
    puts("   [0] 返回");
    puts("   [/] 命令提示符");
    puts("   [1] 系统修复");
    puts("   [2] 磁盘清理");
    puts("   [3] 高级启动\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Code[0]);
        if((Code[0]=='0'||Code[0]=='/'||Code[0]=='1'||Code[0]=='2'||Code[0]=='3')&&(Code[1]==0)){
            break;
        }
        printf("输入错误, 请重新输入: ");
    }
    system("Cls");
    switch(Code[0]){
        case '0':{
            return;
        }case '/':{
            puts("| ~ / 工具箱 / 命令提示符 |\n");
            puts("执行 \"Exit\" 退出.\n");
            system("Cmd");
            break;
        }case '1':{
            puts("| ~ / 工具箱 / 系统修复 |\n");
            if(Confirm()==false){
                system("Cls");
                goto BEGIN;
            }
            if(KernalVersion()>=62UL){
                system("DISM /Online /Cleanup-Image /RestoreHealth");
            }
            system("SFC /ScanNow");
            break;
        }case '2':{
            puts("| ~ / 工具箱 / 垃圾清理 |\n");
            if(Confirm()==false){
                goto END;
            }
            system("Del /F /S /Q %TEMP%");
            if(KernalVersion()>=100UL){
                system("DISM /Online /Set-ReservedStorageState /State:Disabled");
            }
            break;
        }case '3':{
            puts("| ~ / 工具箱 / 高级启动 |\n");
            if(KernalVersion()<62UL){
                puts("仅支持 Windows 8+.\n");
                break;
            }
            if(Confirm()==false){
                goto END;
            }
            puts("\n");
            system("Pause");
            system("Shutdown /R /O /T 0");
            break;
        }
    }
    puts("\n========================================\n");
    puts("按任意键返回.\n");
    system("Pause");
END:
    system("Cls");
    goto BEGIN;
}
int main(int argc,char* argv[]){
    if(IsUserAnAdmin()){
        system("Title [增强会话] CRCSN");
    }else{
        system("Title [基本会话] CRCSN");
    }
    system("Color 9");
    if(argc==1){
        goto BEGIN;
    }
    {
        bool lock[2]{false,false};
        for(int i{1};i<argc;++i){
            std::string opt{argv[i]};
            if((opt.substr(0,5)=="-clr=")&&(lock[0]==false)){
                lock[0]=true;
                opt.erase(0,5);
                opt="Color "+opt;
                system(opt.c_str());
            }else if((opt=="-dev")&&(lock[1]==false)){
                lock[1]=true;
                std::thread(ForceShow).detach();
            }else{
                puts("参数错误.\n");
                puts("========================================\n");
                puts("按任意键退出.\n");
                system("Pause");
                return 0;
            }
        }
    }
BEGIN:
    puts("| ~ |\n");
    puts("   [?] 关于");
    puts("   [1] 破解");
    puts("   [2] 恢复");
    puts("   [3] 工具箱\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Code[0]);
        if((Code[0]=='?'||Code[0]=='1'||Code[0]=='2'||Code[0]=='3')&&(Code[1]==0)){
            break;
        }
        printf("输入错误, 请重新输入: ");
    }
    system("Cls");
    switch(Code[0]){
        case '?':{
            About();
            break;
        }case '1':{
            Cracker();
            break;
        }case '2':{
            Recoverer();
            break;
        }case '3':{
            Toolkit();
            break;
        }
    }
    system("Cls");
    goto BEGIN;
}