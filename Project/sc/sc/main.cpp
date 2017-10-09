

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
string depId[21]; // 记录20个部门的编号
string day[7] = { "Mon", "Tues", "Wed", "Thur","Fri", "Sat", "Sun"};  
string hour[24] = { "08","09","10","11","12","13", "14", "15", "16","17", "18","19", "20","21","22"};
string tags[10] = { "basketball","dance","chess","English","film","football","music","programming","reading","study" };
map<string, bool>id; // 检查编号是否重复
bool flag[7][20]; //避免时间产生交集
bool used_d[maxn]; // 记录被使用的部门编号
bool used[maxn]; // 记录被使用的标签

// --------------------- 随机生成唯一的学号 SXXXXXX ------------------
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

// --------------------- 随机生成常规时间 ----------------------------------
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
// --------------------- 按照D001-D020初始化部门编号 ----------------------------------
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


// --------------------- 部门 -----------------------------------------------
void information_dep(int n)
{
	id.clear(); // 初始化 ， 清空
	Json::Value Item;

	int tgn, i, j;

	for (i = 0; i < n; ++i)
	{
		memset(used, false, sizeof(used));
		memset(flag, false, sizeof(flag));

		// 生成 常规活动时间 
		int s = rand() % 4 + 2;
		for (j = 0; j < s; ++j)
		{
			string tmp;
			int d, h1;
			tmp = getTime(d, h1);
			flag[d][h1] = flag[d][h1 + 1] = flag[d][h1 + 2] = true;
			Item["event_schedules"].append(tmp);
			
		}

		// 生成部门编号

		Item["department_no"] = depId[i + 1];
		// 生成部门纳新人数
		Item["member_limit"] = rand() % 10 + 5;

		// 生成标签
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
			// 标记这个标签被部门使用过
			used_d[inx] = true;
			Item["tags"].append(tags[inx]);
			
		}
		All["departments"].append(Item);
		Item.clear();
	}

	return;
}

// ------------------------- 学生 -----------------------------
void information_stu(int n)
{
	Json::Value Item;
	int i, j;
	id.clear();
	bool p[10];            //判断志愿是否重复
	for (i = 0; i < n; ++i) 
	{
		memset(used, false, sizeof(used));
		memset(flag, false, sizeof(flag));
		memset(p, false, sizeof(p));


		// 随机生成学生编号
		Item["student_no"] = getId("S");

		// 随机生成空余时间
		int free = rand() % 8 + 3;
		for (j = 0; j < free; ++j)
		{
			string tmp;
			int d, h1, h2;
			tmp = getTime(d, h1);
			flag[d][h1] = flag[d][h1 + 1] = flag[d][h1 + 2] = true;
			Item["free_time"].append(tmp);
			
		}

		// 从已创建的部门中随机抽出<=5个部门 
		int deps = rand() % 5 + 1;  //学生至少喜欢一个部门，优先级就按生成的顺序
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

		// 随机从已经被部门所使用过的标签中抽出tgn个标签
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
	information_dep(20); // 部门
	information_stu(300); // 学生

	Json::StyledWriter writer;
	string str = writer.write(All);
	std::ofstream out;
	out.open("input_data.txt");
	out << str;
	out.close();
	system("pause");
}
