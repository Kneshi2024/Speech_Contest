#include"SpeechManger.h"

SpeechManger::SpeechManger() {
	//初始化成员属性
	this->initSpeech();
	//创建参赛人员
	this->creatSpeaker();
	//加载往届记录
	this->loadRceord();
}

//显示菜单程序
void SpeechManger::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "************  欢迎参加演讲比赛  ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出程序
void SpeechManger::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化容器与属性
void SpeechManger::initSpeech() {
	//容器清空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//轮次置为1
	this->m_Index = 1;
	this->m_Record.clear();
}

//创建12名选手
void SpeechManger::creatSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameseed.size();i++) {
		string name = "选手";
		name += nameseed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++) {
			sp.m_Score[j] = 0;
		}
		//将选手编号放入v1中
		v1.push_back(i + 1001);

		//将选手信息放入map中
		this->m_Speaker.insert(make_pair(i + 1001, sp));//make_pair
	}
}

//比赛流程
void SpeechManger::startSpeech() {
	//第一轮比赛
	//抽签
	SpeechDraw();
	//显示抽签结果
	speechContest();
	//显示晋级结果
	ShowSpeech();
	//第二轮比赛
	this->m_Index++;
	//抽签
	SpeechDraw();
	//显示抽签结果
	speechContest();
	//显示最终结果
	ShowSpeech();
	//保存最终结果
	saveRecord();
	//重置比赛
	this->initSpeech();
	this->creatSpeaker();
	this->loadRceord();


	cout << "本届比赛全部完成！" << endl;
	system("pause");
	system("cls");
}

//抽签程序
void SpeechManger::SpeechDraw() {
	cout << "第" << this->m_Index << "轮选手参加抽签" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "抽签结果为: " << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();it++) {
			cout << *it<<" ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();it != v2.end();it++) {
			cout << *it<<" ";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------------------" << endl;
	system("pause" );
}

//比赛
void SpeechManger::speechContest() {
	multimap<double, int,greater<double>> groupScore;
	cout << "-------------第" << this->m_Index << "轮比赛正式开始-------------" << endl;
	cout << endl;
	vector<int>m_Scr;
	int num = 0;
	if (this->m_Index == 1) {
		m_Scr = v1;
	}
	else {
		m_Scr = v2;
	}
	for (vector<int>::iterator it = m_Scr.begin();it != m_Scr.end();it++) {
		num++;
		deque<double>d;
		for (int i = 0;i < 10;i++) {//10个评委打分
			double score = (rand() % 401 + 600) / 10.f;//取随机数
			//cout << score << " ";  测试
			d.push_back(score);
		}
		//cout << endl;  测试
		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_back();
		d.pop_front();//删除最大最小值
		double sum = accumulate(d.begin(), d.end(), 0);//求和
		double val = sum / (double)d.size();//求平均值
		//cout << "姓名: " << this->m_Speaker[*it].m_Name << " 编号: " << *it << " 所得平均分: " << val << endl;  测试
		this->m_Speaker[*it].m_Score[this->m_Index-1] = val;//将平均分放入分数中
		groupScore.insert(make_pair(val, *it));//将平均分和编号插入临时数组
		if (num % 6 == 0) {
			cout << "第" << num/6 << "组的名次为: " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++) {
				cout << "姓名: " << this->m_Speaker[it->second].m_Name << "  编号: " << it->second << "  分数: " << it->first << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end() && count < 3;it++, count++) {
				if (this->m_Index == 1) {
					v2.push_back(it->second);
				}
				else {
					vVictory.push_back(it->second);
				}
			}
			cout << endl;
			groupScore.clear();
		}
	}
	cout << "-------------第" << this->m_Index << "轮比赛全部结束-------------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManger::ShowSpeech() {
	cout << endl;
	cout << "--------第" << this->m_Index << "轮晋级选手成绩如下:--------" << endl;
	cout << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++) {
		cout << "姓名: " << this->m_Speaker[*it].m_Name << "  编号: " << *it << "  成绩: " << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;
	cout << "--------第" << this->m_Index << "轮晋级选手成绩如上:--------" << endl;

	system("pause");
	system("cls");
	Show_Menu();
}

//保存比赛记录到文件
void SpeechManger::saveRecord() {
	fstream ofs;
	ofs.open("record.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "已经保存完毕" << endl;
	this->fileIsEmpty = false;
}

//读取文件中的数据
void SpeechManger::loadRceord() {
	ifstream ifs("record.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char chr;
	ifs >> chr;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	string data;
	ifs.putback(chr);
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		//获取文件中字符串
		vector<string>v;//创建存放字符的容器
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//没有找到的情况
				break;
			}
			else {
				string temp = data.substr(start, pos - start);//截断字符串得到子串
				//cout << temp << endl;
				v.push_back(temp);
			}
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));//index为届数
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin();it != this->m_Record.end();it++) {
		cout << "第" << it->first + 1 << "届冠军编号为: " << it->second[0] << "  成绩为: " << it->second[1] << endl;
	}*/
}

//展示记录的往届前三名成绩
void SpeechManger::ShowRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空或文件不存在!" << endl;
	}
	else {
		for (map<int, vector<string>>::iterator it = this->m_Record.begin();it != this->m_Record.end();it++) {
			cout << "第" << it->first + 1 << "届前三名成绩如下:" << endl;
			cout << "冠军编号为: " << it->second[0] << "  成绩: " << it->second[1] << " "
				<< "亚军编号为: " << it->second[2] << "  成绩: " << it->second[3] << " "
				<< "季军编号为: " << it->second[4] << "  成绩: " << it->second[5] << " "
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManger::cleanRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在或者文件为空!" << endl;
	}
	else {
		cout << "是否要清空记录？" << endl;
		cout << "1--清空" << endl;
		cout << "2--返回" << endl;
		int select=0;
		cin >> select;
		switch (select) {
		case 1: {
			ofstream ofs("record.csv", ios::trunc);
			ofs.close();
			//初始化成员属性
			this->initSpeech();
			//创建参赛人员
			this->creatSpeaker();
			//加载往届记录
			this->loadRceord();
			cout << "记录已全部清空！" << endl;
			break;
		}
		default:
			break;
		}
	}
	system("pause");
	system("cls");
}

SpeechManger::~SpeechManger() {

}