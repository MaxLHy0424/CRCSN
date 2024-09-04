#include"def.hpp"
#include"ui.hpp"
CUI ui;
#include"mod.hpp"
auto main(i32 argc,cstr argv[])->i32{
    bool optErr{};
    if(argc>1){
        std::string tmp;
        for(i32 i{1};i<argc;++i){
            tmp=argv[i];
            if((tmp.size()>2)?(tmp.substr(0,2)=="-W"):(false)){
                for(const auto &j:tmp.substr(2)){
                    switch(j){
                        case 'f':{
                            opt.frontShow=true;
                            break;
                        }case 'a':{
                            opt.alphaWnd=true;
                            break;
                        }case 's':{
                            opt.wndSizeBox=true;
                            break;
                        }default:{
                            optErr=true;
                            goto INIT;
                        }
                    }
                }
            }else if(tmp=="--large-view"){
                opt.largeView=true;
            }else{
                optErr=true;
                break;
            }
        }
    INIT:
        if(optErr){
            opt={};
        }
    }
    Mod::init();
    if(opt.frontShow){
        std::thread{Mod::frontShow}.detach();
    }
    ui.push("    [ Computer Room Control Software Nemesis ]");
    ui.push("                     v5.3.0");
    ui.push("       https://github.com/MaxLHy0424/CRCSN");
    ui.push("     (C) 2023 MaxLHy0424, All Rights Reserved.\n");
    if(optErr){
        ui.push(" (!) 参数错误.\n");
    }
    ui.push(" > 退出 ",Mod::exit,nullptr,CON_RED_PALE);
    if(opt.largeView){
        ui.push("\0");
    }
    ui.push(" > 命令提示符 ",Mod::cmd);
    ui.push("\n[ 破 解 ]\n");
    if(IsUserAnAdmin()){
        ui.push(" > 极域电子教室 ",Mod::op,new Mod::OpArg{'c',Mod::rule.mythware.exe,Mod::rule.mythware.svc});
        if(opt.largeView){
            ui.push("\0");
        }
        ui.push(" > 联想云教室 ",Mod::op,new Mod::OpArg{'c',Mod::rule.lenovo.exe,Mod::rule.lenovo.svc});
    }else{
        ui.push(" (i) 需要提权.");
    }
    ui.push("\n[ 恢 复 ]\n");
    if(IsUserAnAdmin()){
        ui.push(" > 极域电子教室 ",Mod::op,new Mod::OpArg{'r',Mod::rule.mythware.exe,Mod::rule.mythware.svc});
        if(opt.largeView){
            ui.push("\0");
        }
        ui.push(" > 联想云教室 ",Mod::op,new Mod::OpArg{'r',Mod::rule.lenovo.exe,Mod::rule.lenovo.svc});
    }else{
        ui.push(" (i) 需要提权.");
    }
    ui.show();
    return 0;
}