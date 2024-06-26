#ifndef MENU_HPP
#define MENU_HPP
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
void hidecursor() {
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
// ��ʾ�����
void showcursor() {
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
	CursorInfo.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
// �Ƴ�����̨����
void removeAttributes() {
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;	//�Ƴ����ٱ༭ģʽ
	mode &= ~ENABLE_INSERT_MODE;		//�Ƴ�����ģʽ
	mode |= ENABLE_MOUSE_INPUT;			//����������
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
}
// ��ӿ���̨����
void addAttributes() {
	DWORD mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
	mode |= ENABLE_QUICK_EDIT_MODE;		//��ӿ��ٱ༭ģʽ
	mode |= ENABLE_INSERT_MODE;     	//��Ӳ���ģʽ
	mode |= ENABLE_MOUSE_INPUT;			//����������
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
}

// ������йصĺ���
// ��ȡ���λ��
COORD getcursor() {
	CONSOLE_SCREEN_BUFFER_INFO temp;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
	return temp.dwCursorPosition;
}
// �������λ��
void setcursor(const COORD &temp = {0, 0}) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
}
// �ȴ�����¼����¼���������ƶ�����������ֹ�����һ�������������¼�
MOUSE_EVENT_RECORD waitMouseEvent(bool move = true) {
	INPUT_RECORD record; //�����¼�
	DWORD reg;           //��ʱ�Ĵ�
	while (true) {
		Sleep(10);
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &record, 1, &reg);                                  //�������¼�����record
		if (record.EventType == MOUSE_EVENT and (move | (record.Event.MouseEvent.dwEventFlags != MOUSE_MOVED))) //������¼� && �ƶ��¼���ģʽ��Ӧ
			return record.Event.MouseEvent;
	}
}
// ���Դ��룬�������COORD��������ӡ���λ��
ostream &operator<<(ostream &pout, const COORD &temp) {
	pout.setf(ios_base::fixed);
	pout << "[Cursor Position] X: " << std::setw(2) << temp.X << "  Y: " << std::setw(2) << temp.Y;
	return pout;
}

// �����̨�ı���ɫ�йص���
// һЩ������ɫ��ϵĶ���
#define BlackWhite 0x07
#define BlackCyan 0x0b
#define YellowBlue 0xe9
struct Color {
	short Default;		// Ĭ����ɫ���
	short Highlight;	// �ı�������ɫ���
	short lastcolor;	// ����ʵ���л���ɫ��ϣ����ڸ�������

	// ��ʼ��
	Color() : Default(BlackWhite), Highlight(BlackCyan), lastcolor(BlackWhite) {}
	Color(short Default = BlackWhite, short Highlight = BlackCyan) : Default(Default), Highlight(Highlight), lastcolor(BlackWhite) {}

	// ���ı���ɫ����ΪDefault���
	void setDefault() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Default);
		lastcolor = Default;
	}
	// ���ı���ɫ����ΪHighlight���
	void setHighlight() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Highlight);
		lastcolor = Highlight;
	}
};

// Menu���ǰ��������Parameter����ʹ��
class Menu;
// ����Parameter��Ա����״̬
// buttonState����ֵ�Ķ���
#define mouseLeftButton FROM_LEFT_1ST_BUTTON_PRESSED	// ���
#define mouseMiddleButton FROM_LEFT_2ND_BUTTON_PRESSED	// �м�
#define mouseRightButton RIGHTMOST_BUTTON_PRESSED		// �Ҽ�
// eventFlag����ֵ�Ķ���
#define mouseClick 0x0					// ��갴�����»��ɿ�ʱ����
#define mouseMove MOUSE_MOVED			// ����ƶ�ʱ����
#define mouseDoubleClick DOUBLE_CLICK	// ���ڶ��ΰ���ʱ�������������¼�ǰһ���ᴥ�� mouseClick �¼�
#define mouseWheel MOUSE_WHEELED		// �����ֹ���ʱ����
// *****Parameter�������Ϊ�ص�������������*****
struct Parameter {
	DWORD buttonState;		// ��갴����¼
	DWORD controlkeyState;	// ���ư���״̬
	DWORD eventFlag;		// ����¼���¼
	Menu *menu;				// Menu��ָ�룬����ԭ�˵�

	// ��ʼ��
	Parameter() : buttonState(mouseLeftButton), controlkeyState(0), eventFlag(0), menu(nullptr) {}
	Parameter(MOUSE_EVENT_RECORD mouseEvent, Menu *menu) : buttonState(mouseEvent.dwButtonState), controlkeyState(mouseEvent.dwControlKeyState), eventFlag(mouseEvent.dwEventFlags), menu(menu) {}
};
// ����ص���������callback
typedef bool(*callback)(Parameter);

// �˵����ı��࣬ÿ��Text�ͱ���������˵��е�һ��
struct Text {
	string text;		// �ı�����
	Color color;		// ��ɫ����
	COORD position;		// �ı�λ��
	callback function;	// �ص�����

	// ��ʼ��
	Text() : text(""), color(Color(0, 0)), position({0, 0}), function(nullptr) {}
	Text(string text, Color color, callback function) : text(text), color(color), position({0, 0}), function(function) {}

	// �ж���������Ƿ����ı�λ���غ�
	bool operator== (const COORD &mousePosition) const {
		if (position.Y == mousePosition.Y and position.X <= mousePosition.X and mousePosition.X < position.X + (short)text.length()) {
			return true;
		}
		return false;
	}
	// �ж���������Ƿ����ı�λ���غ�
	bool operator!= (const COORD &mousePosition) const {
		return !operator==(mousePosition);
	}
};

// *****�˵���*****
class Menu {
	private:
		long sleepTime;						// ѭ���еȴ�ʱ��
		short consoleHeight, consoleWidth;	// ����̨����������
		vector<Text> linedata;				// ��Ų˵�ÿ�е���Ϣ
	protected:
		// ��ȡ����̨��С
		void getconsoleSize() {
			CONSOLE_SCREEN_BUFFER_INFO temp;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
			consoleHeight = temp.dwSize.Y;	// ��ֵ
			consoleWidth = temp.dwSize.X;	// ��ֵ
		}
		// ����
		void clearScreen() {
			getconsoleSize();
			setcursor({0, 0});
			for (short i = 0; i < consoleHeight; ++i) {
				for (short j = 0; j < consoleWidth; ++j) {
					cout << " ";
				}
			}
			setcursor({0, 0});
		}
		// ���
		void write(string text, bool isEndl = false) {
			printf("%s", text.c_str());
			if (isEndl) {
				printf("\n");
			}
		}
		// ���и������
		void rewrite(Text data) {
			setcursor({0, data.position.Y});
			// ��վ�����
			for (short j = 0; j < data.position.X; ++j) {
				write(" ");
			}
			setcursor({0, data.position.Y});
			// ���������
			write(data.text);
			setcursor({0, data.position.Y});
		}
		// ����˵�������linedata��position��Ա������ʼ��
		void initializePosition() {
			clearScreen();
			for (auto &data : linedata) {
				data.position = getcursor();
				data.color.setDefault();
				write(data.text, true);
			}
		}
		// ˢ�²˵�
		void refresh(COORD hangPosition) {
			for (auto &data : linedata) {
				// ������λ��%data%��ť�� ���� %data%��ť�����ڸ���
				if (data == hangPosition and data.color.lastcolor != data.color.Highlight) {
					data.color.setHighlight();	// ����Ϊ������ɫ
					rewrite(data);
				}
				// �����겻λ��%data%��ť�� ���� %data%��ť���ڸ���
				if (data != hangPosition and data.color.lastcolor != data.color.Default) {
					data.color.setDefault();	// ����ΪĬ����ɫ
					rewrite(data);
				}
			}
		}
		// �Զ����ûص�����
		bool implement(MOUSE_EVENT_RECORD mouseEvent) {
			bool isExit = false;	// ����ص��������صĽ������ʾ�Ƿ�Ҫ�˳��˵�
			for (auto &data : linedata) {
				if (data == mouseEvent.dwMousePosition) {
					if (data.function != nullptr) {
						clearScreen();
						data.color.setDefault();
						addAttributes();
						showcursor();
						isExit = data.function(Parameter(mouseEvent, this));
						removeAttributes();
						hidecursor();
						initializePosition();
					}
					break;
				}
			}
			return isExit;
		}
	public:
		// ���캯��
		Menu() : sleepTime(50), consoleHeight(0), consoleWidth(0) {}
		~Menu() {}

		// ��˵�β�����һ��
		Menu &push_back(string text = "", callback function = nullptr, short colorDefault = BlackWhite, short colorHighlight = BlackCyan) {
			if (function == nullptr) {
				linedata.push_back(Text(text, Color(colorDefault, colorDefault), function));
			} else {
				linedata.push_back(Text(text, Color(colorDefault, colorHighlight), function));
			}
			return *this;
		}
		// �Ӳ˵�β������һ��
		Menu &pop_back() {
			linedata.pop_back();
			return *this;
		}
		// ��ղ˵�
		Menu &clear() {
			linedata.clear();
			return *this;
		}
		void showMenu() {
			removeAttributes();
			hidecursor();
			MOUSE_EVENT_RECORD mouseEvent;
			Sleep(100);
			initializePosition();
			bool isExit = false;
			while (!isExit) {
				Sleep(sleepTime);
				mouseEvent = waitMouseEvent();
				switch (mouseEvent.dwEventFlags) {
					case mouseMove: {
						refresh(mouseEvent.dwMousePosition);
						break;
					}
					case mouseClick: {
						if (mouseEvent.dwButtonState and mouseEvent.dwButtonState != mouseWheel) {
							isExit = implement(mouseEvent);
						}
						break;
					}
				}
			}
			clearScreen();
			Sleep(100);
		}
};
// exitMenu�����Ե����ص�����ʹ�ã����Զ�����true���˳��˵�
bool _exitMenu(Parameter) {
	return true;
}
#define exitMenu _exitMenu
#endif
