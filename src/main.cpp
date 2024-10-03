#ifdef _WIN32
#include"def.hpp"
#include"ui.hpp"
#include"mod.hpp"
#ifndef _THE_NEXT_UPDATE_
auto main(const i32 argc,const i8 *const args[])->i32{
    if(argc>1){
        std::string k;
        for(i32 i{1};i<argc;++i){
            k=args[i];
            if((k.size()>2)&&(k.substr(0,2)=="-W")){
                for(const auto &ref:k.substr(2,k.size())){
                    switch(ref){
                        case 'f':{
                            settings.wndFrontShow=true;
                            break;
                        }case 'a':{
                            settings.wndAlpha=true;
                            break;
                        }case 'c':{
                            settings.wndCtrls=true;
                            break;
                        }default:{
                            settingsError=true;
                            goto END;
                        }
                    }
                }
            }else{
                settingsError=true;
                break;
            }
        }
    END:
        if(settingsError){
            settings={};
        }
    }
#else
auto main()->i32{
    if(!Mod::IsRunAsAdmin()){
        i8 path[MAX_PATH];
        GetModuleFileNameA(NULL,path,MAX_PATH);
        ShellExecuteA(NULL,"runas",path,NULL,NULL,SW_SHOWNORMAL);
        exit(0);
    }
    Mod::settingsRead();
#endif
    Mod::init();
    if(settings.wndFrontShow){
        std::thread(Mod::frontShow).detach();
    }
    UI ui;
    ui.add("                    < 主  页 >\n\n");
    if(settingsError){
    #ifdef _THE_NEXT_UPDATE_
        ui.add(" (!) 配置项目错误.\n");
    #else
        ui.add(" (!) 参数错误.\n");
    #endif
    }
    ui.add(" > 退出 ",Mod::exit,{},WC_RED)
      .add(" > 信息 ",Mod::info)
    #ifdef _THE_NEXT_UPDATE_
      .add(" > 设置 ",Mod::settingsEdit)
    #endif
      .add(" > 命令提示符 ",Mod::cmd)
      .add("\n[破解]\n")
      .add(" > 极域电子教室 ",Mod::op,Mod::ArgsOp('C',Mod::rule.mythware.exe,Mod::rule.mythware.svc))
      .add(" > 联想云教室 ",Mod::op,Mod::ArgsOp('C',Mod::rule.lenovo.exe,Mod::rule.lenovo.svc))
      .add("\n[恢复]\n")
      .add(" > 极域电子教室 ",Mod::op,Mod::ArgsOp('R',Mod::rule.mythware.exe,Mod::rule.mythware.svc))
      .add(" > 联想云教室 ",Mod::op,Mod::ArgsOp('R',Mod::rule.lenovo.exe,Mod::rule.lenovo.svc))
      .show();
    return 0;
}
#endif