#include<iostream>
using namespace std;
#include"SpeechManger.h"

int main() {

	//���������
	srand((unsigned)time(NULL));

	//չʾ�˵�
	SpeechManger sm;

	////����
	//for (map<int, Speaker>::iterator it = sm.m_Speaker.begin();it != sm.m_Speaker.end();it++) {
	//	cout << "ѡ�ֱ��: " << it->first << "  ѡ������: " << it->second.m_Name << "  ѡ�ֳɼ�: " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;

	while (true) {
		//��ʾ�˵�
		sm.Show_Menu();
		cout << "����ѡ��ѡ��:" << endl;
		cin >> choice;
		switch (choice){
		case 0:
			sm.exitSystem();//�˳�����
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