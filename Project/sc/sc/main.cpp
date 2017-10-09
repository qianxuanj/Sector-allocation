

#include<iostream>
#include<map>
#include<queue>
#include<time.h>
#include<fstream>
#include"json.h"
#include<stdlib.h>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<string>


using namespace std;
Json::Value All; // Json
const int maxn = 300;
string depId[21]; // ��¼20�����ŵı��
string day[7] = { "Mon", "Tues", "Wed", "Thur","Fri", "Sat", "Sun"};  
string hour[24] = { "08","09","10","11","12","13", "14", "15", "16","17", "18","19", "20","21","22"};
string tags[10] = { "basketball","dance","chess","English","film","football","music","programming","reading","study" };
map<string, bool>id; // ������Ƿ��ظ�
bool flag[7][20]; //����ʱ���������
bool used_d[maxn]; // ��¼��ʹ�õĲ��ű��
bool used[maxn]; // ��¼��ʹ�õı�ǩ

// --------------------- �������Ψһ��ѧ�� SXXXXXX ------------------
string getId(string x)
{
	string s_id = x;
	do 
	{
		for (int i = 0; i < 6; i++) 
		{
			s_id = s_id + to_string(rand() % 10) ;
		}
	} while (id[s_id]);
	id[s_id] = true;
	return s_id;
}

// --------------------- ������ɳ���ʱ�� ----------------------------------
string getTime(int &d, int &h1)
{
	
	do
	{
		d = rand() % 7;
		h1 = rand() % 13;
	} while (flag[d][h1] || flag[d][h1+1] || flag[d][h1+2]);
	string res = day[d] + "." + hour[h1] + ":00" + "~" + hour[h1+2] + ":00";
	return res;
}
// --------------------- ����D001-D020��ʼ�����ű�� ----------------------------------
void init() 
{                            
	for (int i = 1; i <= 20; i++)
	{
		if (i<10)
			 depId[i] = "D00" + to_string(i);
		else
			depId[i] = "D0" + to_string(i);
	}
}


// --------------------- ���� -----------------------------------------------
void information_dep(int n)
{
	id.clear(); // ��ʼ�� �� ���
	Json::Value Item;

	int tgn, i, j;

	for (i = 0; i < n; ++i)
	{
		memset(used, false, sizeof(used));
		memset(flag, false, sizeof(flag));

		// ���� ����ʱ�� 
		int s = rand() % 4 + 2;
		for (j = 0; j < s; ++j)
		{
			string tmp;
			int d, h1;
			tmp = getTime(d, h1);
			flag[d][h1] = flag[d][h1 + 1] = flag[d][h1 + 2] = true;
			Item["event_schedules"].append(tmp);
			
		}

		// ���ɲ��ű��

		Item["department_no"] = depId[i + 1];
		// ���ɲ�����������
		Item["member_limit"] = rand() % 10 + 5;

		// ���ɱ�ǩ
		tgn = rand() % 8 + 2;
		//cout << tgn << endl;
		for (j = 0; j < tgn; ++j)
		{
			int inx;
			do 
			{
				inx = rand() % 10;
			} while (used[inx]);
			//de(i); de(inx);
			used[inx] = true;
			// ��������ǩ������ʹ�ù�
			used_d[inx] = true;
			Item["tags"].append(tags[inx]);
			
		}
		All["departments"].append(Item);
		Item.clear();
	}

	return;
}

// ------------------------- ѧ�� -----------------------------
void information_stu(int n)
{
	Json::Value Item;
	int i, j;
	id.clear();
	bool p[10];            //�ж�־Ը�Ƿ��ظ�
	for (i = 0; i < n; ++i) 
	{
		memset(used, false, sizeof(used));
		memset(flag, false, sizeof(flag));
		memset(p, false, sizeof(p));


		// �������ѧ�����
		Item["student_no"] = getId("S");

		// ������ɿ���ʱ��
		int free = rand() % 8 + 3;
		for (j = 0; j < free; ++j)
		{
			string tmp;
			int d, h1, h2;
			tmp = getTime(d, h1);
			flag[d][h1] = flag[d][h1 + 1] = flag[d][h1 + 2] = true;
			Item["free_time"].append(tmp);
			
		}

		// ���Ѵ����Ĳ�����������<=5������ 
		int deps = rand() % 5 + 1;  //ѧ������ϲ��һ�����ţ����ȼ��Ͱ����ɵ�˳��
		for (j = 0; j < deps; ++j)
		{
			int inx;
			do 
			{
				inx = rand() % 20;
			} while (p[inx]);
			Item["applications_department"].append(depId[inx]);
			p[inx] = true;
		
		}

		// ������Ѿ���������ʹ�ù��ı�ǩ�г��tgn����ǩ
		int tgn = rand() % 5 + 2;
		for (j = 0; j < tgn; ++j)
		{
			int inx;
			do 
			{
				inx = rand() % 10;
			} while (used[inx]||!used_d[inx] );
			used[inx] = true;
			Item["tags"].append(tags[inx]);
		
		}
		
		All["students"].append(Item);
		Item.clear();
	}
	return;
}


// ----------------------------------------------------------------------

int main() 
{
	init();
	information_dep(20); // ����
	information_stu(300); // ѧ��

	Json::StyledWriter writer;
	string str = writer.write(All);
	std::ofstream out;
	out.open("input_data.txt");
	out << str;
	out.close();
	system("pause");
}
