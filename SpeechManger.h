#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"
#include<algorithm>//sort、random_shuffle
#include<deque>
#include<functional>//greater
#include<numeric>//accualute
#include<fstream>

class SpeechManger {
public:
	//构造函数
	SpeechManger();

	//展示菜单
	void Show_Menu();

	//退出程序
	void exitSystem();

	//初始化容器与属性
	void initSpeech();

	//创建12名选手
	void creatSpeaker();

	//比赛流程
	void startSpeech();

	//抽签程序
	void SpeechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void ShowSpeech();

	//保存比赛记录到文件
	void saveRecord();

	//读取文件中的数据
	void loadRceord();

	//判断文件是否为空
	bool fileIsEmpty;

	//展示记录的往届前三名成绩
	void ShowRecord();

	//清空记录
	void cleanRecord();

	//析构函数
	~SpeechManger();

	//成员属性
	vector<int>v1;//第一轮比赛容器

	vector<int>v2;//第二轮比赛容器

	vector<int>vVictory;//最后一轮比赛容器

	map<int, Speaker>m_Speaker;//比赛成员信息对应

	int m_Index;//记录比赛轮次

	map<int, vector<string>>m_Record;//存放往届记录的容器

};