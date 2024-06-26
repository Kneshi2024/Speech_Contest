#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"
#include<algorithm>//sort��random_shuffle
#include<deque>
#include<functional>//greater
#include<numeric>//accualute
#include<fstream>

class SpeechManger {
public:
	//���캯��
	SpeechManger();

	//չʾ�˵�
	void Show_Menu();

	//�˳�����
	void exitSystem();

	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void creatSpeaker();

	//��������
	void startSpeech();

	//��ǩ����
	void SpeechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void ShowSpeech();

	//���������¼���ļ�
	void saveRecord();

	//��ȡ�ļ��е�����
	void loadRceord();

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//չʾ��¼������ǰ�����ɼ�
	void ShowRecord();

	//��ռ�¼
	void cleanRecord();

	//��������
	~SpeechManger();

	//��Ա����
	vector<int>v1;//��һ�ֱ�������

	vector<int>v2;//�ڶ��ֱ�������

	vector<int>vVictory;//���һ�ֱ�������

	map<int, Speaker>m_Speaker;//������Ա��Ϣ��Ӧ

	int m_Index;//��¼�����ִ�

	map<int, vector<string>>m_Record;//��������¼������

};