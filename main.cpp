#include<stdio.h>
#include<string>
#include<ShlObj.h>
#include<thread>
char Data[3]{};
void ForceShow(){
    HWND ForeWnd{GetForegroundWindow()};
    DWORD ForeID{GetWindowThreadProcessId(ForeWnd,NULL)};
    DWORD CurID{GetCurrentThreadId()};
    for(;;){
        AttachThreadInput(CurID,ForeID,TRUE);
        ShowWindow(ForeWnd,SW_SHOWNORMAL);
        SetWindowPos(ForeWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
        SetWindowPos(ForeWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
        SetForegroundWindow(ForeWnd);
        AttachThreadInput(CurID,ForeID,FALSE);
        SetWindowPos(ForeWnd,HWND_TOPMOST,0,0,100,100,SWP_NOMOVE|SWP_NOSIZE);
        Sleep(100UL);
    }
}
bool Continue(){
    printf("是否继续? (Y/N): ");
    for(;;){
        scanf("%s",&Data[1]);
        if((Data[1]=='Y'||Data[1]=='y'||Data[1]=='N'||Data[1]=='n')&&(Data[2]==0)){
            break;
        }
        printf("输入错误, 请重试: ");
    }
    return (Data[1]=='Y'||Data[1]=='y');
}
void About(){
    puts("[关于]\n");
    puts("  Computer Room Control Software Nemesis");
    puts("\t\tv5.0.0_Dev1\n");
    puts("  https://github.com/MaxLHy0424/CRCSN");
    puts("  (C) 2024 MaxLHy0424, All Rights Reserved.\n");
    puts("---------------------------------------------\n");
    system("Pause");
    return;
}
void Crack(){
BEGIN:
    puts("[破解]\n");
    puts("  0 返回");
    puts("  1 极域电子教室");
    puts("  2 联想云教室\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Data[0]);
        if((Data[0]=='0'||Data[0]=='1'||Data[0]=='2')&&(Data[1]==0)){
            break;
        }
        printf("输入错误, 请重试: ");
    }
    if(Data[0]=='0'){
        return;
    }
    if(Continue()){
        puts("\n----------------------------------------\n");
        switch(Data[0]){
            case '1':{
                system("TaskKill /F /IM StudentMain.exe");
                system("TaskKill /F /IM DispcapHelper.exe");
                system("TaskKill /F /IM InstHelpApp.exe");
                system("TaskKill /F /IM GATESRV.exe");
                system("TaskKill /F /IM ProcHelper64.exe");
                system("TaskKill /F /IM MasterHelper.exe");
                if(IsUserAnAdmin()){
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\StudentMain.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DispcapHelper.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\VRCwPlayer.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp64.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\TDOvrSet.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\GATESRV.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ProcHelper64.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\MasterHelper.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Net Stop TDNetFilter /Y");
                    system("Net Stop TDFileFilter /Y");
                    system("Net Stop STUDSRV /Y");
                }
                break;
            }case '2':{
                system("TaskKill /F /IM vncviewer.exe");
                system("TaskKill /F /IM tvnserver32.exe");
                system("TaskKill /F /IM WfbsPnpInstall.exe");
                system("TaskKill /F /IM WFBSMon.exe");
                system("TaskKill /F /IM WFBSMlogon.exe");
                system("TaskKill /F /IM WFBSSvrLogShow.exe");
                system("TaskKill /F /IM ResetIp.exe");
                system("TaskKill /F /IM Fireware.exe");
                system("TaskKill /F /IM BCDBootCopy.exe");
                system("TaskKill /F /IM refreship.exe");
                system("TaskKill /F /IM LenovoLockScreen.exe");
                system("TaskKill /F /IM PortControl64.exe");
                system("TaskKill /F /IM DesktopCheck.exe");
                system("TaskKill /F /IM DeploymentManager.exe");
                system("TaskKill /F /IM DeploymentAgent.exe");
                system("TaskKill /F /IM XYNTService.exe");
                if(IsUserAnAdmin()){
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\vncviewer.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tvnserver32.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WfbsPnpInstall.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMon.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMlogon.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSSvrLogShow.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ResetIp.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\FuncForWIN64.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\CertMgr.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Fireware.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\BCDBootCopy.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\refreship.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\LenovoLockScreen.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\PortControl64.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DesktopCheck.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentManager.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentAgent.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Reg Add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\XYNTService.exe\" /F /T Reg_SZ /V debugger /D \"?\"");
                    system("Net Stop tvnserver /Y");
                    system("Net Stop BSAgentSvr /Y");
                    system("Net Stop WFBSMlogon /Y");
                }
                break;
            }
        }
        puts("\n----------------------------------------\n");
        system("Pause");
    }
    system("CLS");
    goto BEGIN;
}
void Recovery(){
BEGIN:
    puts("[恢复]\n");
    if(!IsUserAnAdmin()){
        puts("User 权限下不可用.\n");
        puts("--------------------\n");
        system("Pause");
        return;
    }
    puts("  0 返回");
    puts("  1 极域电子教室");
    puts("  2 联想云教室\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Data[0]);
        if((Data[0]=='0'||Data[0]=='1'||Data[0]=='2')&&(Data[1]==0)){
            break;
        }
        printf("输入错误, 请重试: ");
    }
    if(Data[0]=='0'){
        return;
    }
    if(Continue()){
        puts("\n----------------------------------------\n");
        switch(Data[0]){
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
        puts("----------------------------------------\n");
        system("Pause");
    }
    system("CLS");
    goto BEGIN;
}
void Terminal(){
    puts("[终端]\n");
    puts("执行 \"Exit\" 退出.\n");
    puts("---------------------------------------------\n");
    system("CMD");
    return;
}
int main(int argc,char* argv[]){
    system("Title CRCSN");
    if(argc==1){
        goto BEGIN;
    }
    {
        std::string opt[argc-1]{},tmp{};
        for(unsigned short i{1};i<argc;++i){
            tmp=argv[i];
            if((opt[0]=="")&&(tmp.length()>=5)&&(tmp.substr(0,5)=="-clr=")){
                tmp.erase(0,5);
                opt[0]="color "+tmp;
            }else if((opt[1]=="")&&(tmp=="-fs")){
                opt[1]="1";
            }
            else{
                puts("参数错误.\n");
                puts("--------------------\n");
                system("Pause");
                goto BEGIN;
            }
        }
        system(opt[0].c_str());
        if(opt[1]=="1"){
            std::thread(ForceShow).detach();
        }
    }
BEGIN:
    system("CLS");
    puts("[主页]\n");
    puts("  ? 关于");
    puts("  1 破解");
    puts("  2 恢复");
    puts("  3 终端\n");
    printf("请输入: ");
    for(;;){
        scanf("%s",&Data[0]);
        if((Data[0]=='?'||Data[0]=='1'||Data[0]=='2'||Data[0]=='3')&&(Data[1]==0)){
            break;
        }
        printf("输入错误, 请重试: ");
    }
    system("CLS");
    switch(Data[0]){
        case '?':{
            About();
            break;
        }case '1':{
            Crack();
            break;
        }case '2':{
            Recovery();
            break;
        }case '3':{
            Terminal();
            break;
        }
    }
    goto BEGIN;
}