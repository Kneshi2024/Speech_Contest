#include<iostream>
using namespace std;
#include"SpeechManger.h"

int main() {

	//真正随机数
	srand((unsigned)time(NULL));

	//展示菜单
	SpeechManger sm;

	////测试
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it++) {
	//	cout << "选手编号: " << it->first << "  选手姓名: " << it->second.m_Name << "  选手成绩: " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;

	while (true) {
		//显示菜单
		sm.Show_Menu();
		cout << "请您选择选项:" << endl;
		cin >> choice;
		switch (choice){
		case 0:
			sm.exitSystem();//退出程序
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.ShowRecord();
			break;
		case 3:
			sm.cleanRecord();
			break;
		default:
			system("cls");
			break;
		}
	}
	

	system("pause");
	return(0);
}