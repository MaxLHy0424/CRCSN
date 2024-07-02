#ifndef MENU_HPP
#define MENU_HP
void HideTheCursor(){
    CONSOLE_CURSOR_INFO TheCursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&TheCursorInfo);
    TheCursorInfo.bVisible=false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&TheCursorInfo);
}
void ShowTheCursor(){
    CONSOLE_CURSOR_INFO TheCursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&TheCursorInfo);
    TheCursorInfo.bVisible=true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&TheCursorInfo);
}
void RemoveAttributes(){
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
    mode&=~ENABLE_QUICK_EDIT_MODE;
    mode&=~ENABLE_INSERT_MODE;
    mode|=ENABLE_MOUSE_INPUT;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
}
void AddAttributes(){
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode);
    mode|=ENABLE_QUICK_EDIT_MODE;
    mode|=ENABLE_INSERT_MODE;
    mode|=ENABLE_MOUSE_INPUT;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),mode);
}
COORD GetTheTheCursor(){
    CONSOLE_SCREEN_BUFFER_INFO tmp;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&tmp);
    return tmp.dwCursorPosition;
}
void SetTheCursor(const COORD&tmp={0,0}){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),tmp);
}
MOUSE_EVENT_RECORD WaitMouseEvent(bool move=true){
    INPUT_RECORD record;
    DWORD reg;
    while(true){
        Sleep(10UL);
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&record,1,&reg);
        if(record.EventType==MOUSE_EVENT&&(move|(record.Event.MouseEvent.dwEventFlags!=MOUSE_MOVED))){
            return record.Event.MouseEvent;
        }
    }
}
#define BlackWhite 0x07
#define BlackBlue 0x03
#define YellowBlue 0xe9
struct Color{
    short Default,highlight,lastColor;
    Color():Default(BlackWhite),highlight(BlackBlue),lastColor(BlackWhite){}
    Color(short Default=BlackWhite,short highlight=BlackBlue):Default(Default),highlight(highlight),lastColor(BlackWhite){}
    void SetDefault(){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),Default);
        lastColor=Default;
    }
    void SetHighlight(){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highlight);
        lastColor=highlight;
    }
};
class Menu;
#define MouseLeftButton FROM_LEFT_1ST_BUTTON_PRESSED
#define MouseMiddleButton FROM_LEFT_2ND_BUTTON_PRESSED
#define MouseRightButton RIGHTMOST_BUTTON_PRESSED
#define MouseClick 0x0
#define MouseMove MOUSE_MOVED
#define MouseDoubleClick DOUBLE_CLICK
#define MouseWheel MOUSE_WHEELED
struct Parameter{
    DWORD buttonState,controlKeyState,eventFlag;
    Menu *menu;
    Parameter():buttonState(MouseLeftButton),controlKeyState(0),eventFlag(0),menu(nullptr){}
    Parameter(MOUSE_EVENT_RECORD mouseEvent,Menu *menu):buttonState(mouseEvent.dwButtonState),controlKeyState(mouseEvent.dwControlKeyState),eventFlag(mouseEvent.dwEventFlags),menu(menu){}
};
typedef bool(*callback)(Parameter);
struct Text{
    std::string text;
    Color color;
    COORD position;
    callback function;
    Text():text(""),color(Color(0,0)),position({0,0}),function(nullptr){}
    Text(std::string text,Color color,callback function):text(text),color(color),position({0,0}),function(function){}
    bool operator==(const COORD&mousePosition)const{
        if((position.Y==mousePosition.Y)&&(position.X<=mousePosition.X)&&(mousePosition.X<(position.X+(short)text.length()))){
            return true;
        }
        return false;
    }
    bool operator!=(const COORD&mousePosition)const{
        return !operator==(mousePosition);
    }
};
class Menu{
    private:
        unsigned long sleepTime;
        short consoleHeight,consoleWidth;
        std::vector<Text>lineData;
    protected:
        void GetConsoleSize(){
            CONSOLE_SCREEN_BUFFER_INFO tmp;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&tmp);
            consoleHeight=tmp.dwSize.Y;
            consoleWidth=tmp.dwSize.X;
        }
        void ClearScreen(){
            GetConsoleSize();
            SetTheCursor({0,0});
            for(short i{};i<consoleHeight;++i){
                for(short j{};j<consoleWidth;++j){
                    printf(" ");
                }
            }
            SetTheCursor({0,0});
        }
        void Write(std::string text,bool isEndl=false){
            printf("%s",text.c_str());
            if(isEndl){
                printf("\n");
            }
        }
        void ReWrite(Text data){
            SetTheCursor({0,data.position.Y});
            for(short j{};j<data.position.X;++j){
                Write(" ");
            }
            SetTheCursor({0,data.position.Y});
            Write(data.text);
            SetTheCursor({0,data.position.Y});
        }
        void InitPosition(){
            ClearScreen();
            for(auto&data:lineData){
                data.position=GetTheTheCursor();
                data.color.SetDefault();
                Write(data.text,true);
            }
        }
        void Refresh(COORD hangPosition){
            for(auto&data:lineData){
                if(data==hangPosition&&data.color.lastColor!=data.color.highlight){
                    data.color.SetHighlight();
                    ReWrite(data);
                }
                if(data!=hangPosition&&data.color.lastColor!=data.color.Default){
                    data.color.SetDefault();
                    ReWrite(data);
                }
            }
        }
        bool implement(MOUSE_EVENT_RECORD mouseEvent){
            bool isExit=false;
            for(auto&data:lineData){
                if(data==mouseEvent.dwMousePosition){
                    if(data.function!=nullptr){
                        ClearScreen();
                        data.color.SetDefault();
                        AddAttributes();
                        ShowTheCursor();
                        isExit=data.function(Parameter(mouseEvent,this));
                        RemoveAttributes();
                        HideTheCursor();
                        InitPosition();
                    }
                    break;
                }
            }
            return isExit;
        }
    public:
        Menu():sleepTime(50),consoleHeight(0),consoleWidth(0){}
        ~Menu(){}
        Menu&PushBack(std::string text="",callback function=nullptr,short colorHighlight=BlackBlue,short colorDefault=BlackWhite){
            if(function==nullptr){
                lineData.push_back(Text(text,Color(colorDefault,colorDefault),function));
            }else{
                lineData.push_back(Text(text,Color(colorDefault,colorHighlight),function));
            }
            return *this;
        }
        Menu&PopBack(){
            lineData.pop_back();
            return *this;
        }
        Menu&Clear(){
            lineData.clear();
            return *this;
        }
        void ShowMenu(){
            RemoveAttributes();
            HideTheCursor();
            MOUSE_EVENT_RECORD mouseEvent;
            Sleep(100UL);
            InitPosition();
            bool isExit=false;
            while(!isExit){
                Sleep(sleepTime);
                mouseEvent=WaitMouseEvent();
                switch(mouseEvent.dwEventFlags){
                    case MouseMove:{
                        Refresh(mouseEvent.dwMousePosition);
                        break;
                    }case MouseClick:{
                        if(mouseEvent.dwButtonState&&mouseEvent.dwButtonState!=MouseWheel){
                            isExit=implement(mouseEvent);
                        }
                        break;
                    }
                }
            }
            ClearScreen();
            Sleep(100UL);
        }
};
bool _ExitProc(Parameter){
    exit(0);
    return true;
}
#define ExitProc _ExitProc
#endif