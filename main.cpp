#include<stdio.h>
#include<string>
#include<ShlObj.h>
#include<thread>
#define NtKernel (((DWORD)(LOBYTE(LOWORD(GetVersion()))))*10UL+((DWORD)(HIBYTE(LOWORD(GetVersion())))))
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
    system("pause");
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
                system("taskKill /f /im StudentMain.exe");
                system("taskKill /f /im DispcapHelper.exe");
                system("taskKill /f /im InstHelpApp.exe");
                system("taskKill /f /im GATESRV.exe");
                system("taskKill /f /im ProcHelper64.exe");
                system("taskKill /f /im MasterHelper.exe");
                if(IsUserAnAdmin()){
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\StudentMain.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DispcapHelper.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\VRCwPlayer.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp64.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\TDOvrSet.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\GATESRV.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ProcHelper64.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\MasterHelper.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("net stop TDNetFilter /y");
                    system("net stop TDFileFilter /y");
                    system("net stop STUDSRV /y");
                }
                break;
            }case '2':{
                system("taskKill /f /im vncviewer.exe");
                system("taskKill /f /im tvnserver32.exe");
                system("taskKill /f /im WfbsPnpInstall.exe");
                system("taskKill /f /im WFBSMon.exe");
                system("taskKill /f /im WFBSMlogon.exe");
                system("taskKill /f /im WFBSSvrLogShow.exe");
                system("taskKill /f /im ResetIp.exe");
                system("taskKill /f /im Fireware.exe");
                system("taskKill /f /im BCDBootCopy.exe");
                system("taskKill /f /im refreship.exe");
                system("taskKill /f /im LenovoLockScreen.exe");
                system("taskKill /f /im PortControl64.exe");
                system("taskKill /f /im DesktopCheck.exe");
                system("taskKill /f /im DeploymentManager.exe");
                system("taskKill /f /im DeploymentAgent.exe");
                system("taskKill /f /im XYNTService.exe");
                if(IsUserAnAdmin()){
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\vncviewer.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tvnserver32.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WfbsPnpInstall.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMon.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMlogon.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSSvrLogShow.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ResetIp.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\FuncForWIN64.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\CertMgr.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Fireware.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\BCDBootCopy.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\refreship.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\LenovoLockScreen.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\PortControl64.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DesktopCheck.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentManager.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentAgent.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\XYNTService.exe\" /f /t reg_sz /v debugger /d \"hjk\"");
                    system("net stop tvnserver /y");
                    system("net stop BSAgentSvr /y");
                    system("net stop WFBSMlogon /y");
                }
                break;
            }
        }
        puts("\n----------------------------------------\n");
        system("pause");
    }
    system("cls");
    goto BEGIN;
}
void Recovery(){
BEGIN:
    puts("[恢复]\n");
    if(!IsUserAnAdmin()){
        puts("User 权限下不可用.\n");
        puts("--------------------\n");
        system("pause");
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
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\StudentMain.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DispcapHelper.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\VRCwPlayer.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\InstHelpApp64.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\TDOvrSet.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\GATESRV.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ProcHelper64.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\MasterHelper.exe\" /f");
                system("net start TDNetFilter");
                system("net start TDFileFilter");
                system("net start STUDSRV");
                break;
            }case '2':{
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\vncviewer.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\tvnserver32.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WfbsPnpInstall.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMon.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSMlogon.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\WFBSSvrLogShow.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\ResetIp.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\FuncForWIN64.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\CertMgr.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\Fireware.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\BCDBootCopy.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\refreship.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\LenovoLockScreen.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\PortControl64.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DesktopCheck.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentManager.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\DeploymentAgent.exe\" /f");
                system("reg delete \"HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options\\XYNTService.exe\" /f");
                system("net start tvnserver");
                system("net start BSAgentSvr");
                system("net start WFBSMlogon");
                break;
            }
        }
        puts("----------------------------------------\n");
        system("pause");
    }
    system("cls");
    goto BEGIN;
}
void Terminal(){
    puts("[终端]\n");
    puts("执行 \"exit\" 退出.\n");
    puts("---------------------------------------------\n");
    system("cmd");
    return;
}
int main(int argc,char* argv[]){
    system("title CRCSN");
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
                system("pause");
                goto BEGIN;
            }
        }
        system(opt[0].c_str());
        if(opt[1]=="1"){
            std::thread(ForceShow).detach();
        }
    }
BEGIN:
    system("cls");
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
    system("cls");
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