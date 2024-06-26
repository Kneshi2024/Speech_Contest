#include"SpeechManger.h"

SpeechManger::SpeechManger() {
	//��ʼ����Ա����
	this->initSpeech();
	//����������Ա
	this->creatSpeaker();
	//���������¼
	this->loadRceord();
}

//��ʾ�˵�����
void SpeechManger::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "************  ��ӭ�μ��ݽ�����  ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�����
void SpeechManger::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������������
void SpeechManger::initSpeech() {
	//�������
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//�ִ���Ϊ1
	this->m_Index = 1;
	this->m_Record.clear();
}

//����12��ѡ��
void SpeechManger::creatSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameseed.size();i++) {
		string name = "ѡ��";
		name += nameseed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0;j < 2;j++) {
			sp.m_Score[j] = 0;
		}
		//��ѡ�ֱ�ŷ���v1��
		v1.push_back(i + 1001);

		//��ѡ����Ϣ����map��
		this->m_Speaker.insert(make_pair(i + 1001, sp));//make_pair
	}
}

//��������
void SpeechManger::startSpeech() {
	//��һ�ֱ���
	//��ǩ
	SpeechDraw();
	//��ʾ��ǩ���
	speechContest();
	//��ʾ�������
	ShowSpeech();
	//�ڶ��ֱ���
	this->m_Index++;
	//��ǩ
	SpeechDraw();
	//��ʾ��ǩ���
	speechContest();
	//��ʾ���ս��
	ShowSpeech();
	//�������ս��
	saveRecord();
	//���ñ���
	this->initSpeech();
	this->creatSpeaker();
	this->loadRceord();


	cout << "�������ȫ����ɣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ����
void SpeechManger::SpeechDraw() {
	cout << "��" << this->m_Index << "��ѡ�ֲμӳ�ǩ" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "��ǩ���Ϊ: " << endl;
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

//����
void SpeechManger::speechContest() {
	multimap<double, int,greater<double>> groupScore;
	cout << "-------------��" << this->m_Index << "�ֱ�����ʽ��ʼ-------------" << endl;
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
		for (int i = 0;i < 10;i++) {//10����ί���
			double score = (rand() % 401 + 600) / 10.f;//ȡ�����
			//cout << score << " ";  ����
			d.push_back(score);
		}
		//cout << endl;  ����
		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_back();
		d.pop_front();//ɾ�������Сֵ
		double sum = accumulate(d.begin(), d.end(), 0);//���
		double val = sum / (double)d.size();//��ƽ��ֵ
		//cout << "����: " << this->m_Speaker[*it].m_Name << " ���: " << *it << " ����ƽ����: " << val << endl;  ����
		this->m_Speaker[*it].m_Score[this->m_Index-1] = val;//��ƽ���ַ��������
		groupScore.insert(make_pair(val, *it));//��ƽ���ֺͱ�Ų�����ʱ����
		if (num % 6 == 0) {
			cout << "��" << num/6 << "�������Ϊ: " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();it++) {
				cout << "����: " << this->m_Speaker[it->second].m_Name << "  ���: " << it->second << "  ����: " << it->first << endl;
			}
			//ȡ��ǰ����
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
	cout << "-------------��" << this->m_Index << "�ֱ���ȫ������-------------" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManger::ShowSpeech() {
	cout << endl;
	cout << "--------��" << this->m_Index << "�ֽ���ѡ�ֳɼ�����:--------" << endl;
	cout << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++) {
		cout << "����: " << this->m_Speaker[*it].m_Name << "  ���: " << *it << "  �ɼ�: " << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
	}
	cout << endl;
	cout << "--------��" << this->m_Index << "�ֽ���ѡ�ֳɼ�����:--------" << endl;

	system("pause");
	system("cls");
	Show_Menu();
}

//���������¼���ļ�
void SpeechManger::saveRecord() {
	fstream ofs;
	ofs.open("record.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�Ѿ��������" << endl;
	this->fileIsEmpty = false;
}

//��ȡ�ļ��е�����
void SpeechManger::loadRceord() {
	ifstream ifs("record.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char chr;
	ifs >> chr;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	string data;
	ifs.putback(chr);
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		//��ȡ�ļ����ַ���
		vector<string>v;//��������ַ�������
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//û���ҵ������
				break;
			}
			else {
				string temp = data.substr(start, pos - start);//�ض��ַ����õ��Ӵ�
				//cout << temp << endl;
				v.push_back(temp);
			}
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));//indexΪ����
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin();it != this->m_Record.end();it++) {
		cout << "��" << it->first + 1 << "��ھ����Ϊ: " << it->second[0] << "  �ɼ�Ϊ: " << it->second[1] << endl;
	}*/
}

//չʾ��¼������ǰ�����ɼ�
void SpeechManger::ShowRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ�Ϊ�ջ��ļ�������!" << endl;
	}
	else {
		for (map<int, vector<string>>::iterator it = this->m_Record.begin();it != this->m_Record.end();it++) {
			cout << "��" << it->first + 1 << "��ǰ�����ɼ�����:" << endl;
			cout << "�ھ����Ϊ: " << it->second[0] << "  �ɼ�: " << it->second[1] << " "
				<< "�Ǿ����Ϊ: " << it->second[2] << "  �ɼ�: " << it->second[3] << " "
				<< "�������Ϊ: " << it->second[4] << "  �ɼ�: " << it->second[5] << " "
				<< endl;
		}
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManger::cleanRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ��!" << endl;
	}
	else {
		cout << "�Ƿ�Ҫ��ռ�¼��" << endl;
		cout << "1--���" << endl;
		cout << "2--����" << endl;
		int select=0;
		cin >> select;
		switch (select) {
		case 1: {
			ofstream ofs("record.csv", ios::trunc);
			ofs.close();
			//��ʼ����Ա����
			this->initSpeech();
			//����������Ա
			this->creatSpeaker();
			//���������¼
			this->loadRceord();
			cout << "��¼��ȫ����գ�" << endl;
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