#include"header.hpp"
#include"ui.hpp"
CUI ui;
#include"module.hpp"
auto main(int argc,char* argv[])->int{
    bool errOpt{};
    {
        std::string t;
        if(argc==1){
            goto BEGIN;
        }
        for(int i{1};i<argc;++i){
            t=argv[i];
            if((t.size()>2ull)&&(t.substr(0,2)=="-W")){
                for(uint64_t j{2ull};j<t.size();++j){
                    switch(t[j]){
                        case 'c':{
                            CRCSN::opt.wndCtrls=true;
                            break;
                        }case 'f':{
                            CRCSN::opt.frontShow=true;
                            break;
                        }case 'a':{
                            CRCSN::opt.alphaWnd=true;
                            break;
                        }default:{
                            errOpt=true;
                        }
                    }
                }
            }else if(t=="--sparse-view"){
                CRCSN::opt.sparseView=true;
            }else if(t=="/command"){
                continue;
            }else{
                errOpt=true;
                goto BEGIN;
            }
        }
    BEGIN:
        if(errOpt){
            CRCSN::opt={};
        }
        CRCSN::init(CRCSN::opt.wndCtrls,CRCSN::opt.alphaWnd);
        if(CRCSN::opt.frontShow){
            std::thread(CRCSN::frontShow).detach();
        }
    }
    ui.push("    [ Computer Room Control Software Nemesis ]");
    if(CRCSN::opt.sparseView){
        ui.push("\0");
    }
    ui.push("                  v5.0.0-beta.2");
    ui.push("       https://github.com/MaxLHy0424/CRCSN");
    ui.push("     (C) 2023 MaxLHy0424. All Rights Reserved.\n");
    if(errOpt){
        ui.push(" (!) 存在未知的命令行参数.\n");
    }
    ui.push(" > 退出 ",EXIT);
    if(CRCSN::opt.sparseView){
        ui.push("\0");
    }
    ui.push(" > 命令提示符 ",CRCSN::cmd);
    ui.push("\n[ 破 解 ]\n");
    if(IsUserAnAdmin()){
        ui.push(" > 极域电子教室 ",CRCSN::Crack::mythware);
        if(CRCSN::opt.sparseView){
            ui.push("\0");
        }
        ui.push(" > 联想云教室 ",CRCSN::Crack::lenovo);
    }else{
        ui.push(" (i) 需要管理员权限.");
    }
    ui.push("\n[ 恢 复 ]\n");
    if(IsUserAnAdmin()){
        ui.push(" > 极域电子教室 ",CRCSN::Recovery::mythware);
        if(CRCSN::opt.sparseView){
            ui.push("\0");
        }
        ui.push(" > 联想云教室 ",CRCSN::Recovery::lenovo);
    }else{
        ui.push(" (i) 需要管理员权限.");
    }
    ui.show();
    return 0;
}