// Bumenpipei.cpp : 定义控制台应用程序的入口点。
//
#include "json.h"
#include "stdafx.h"
#include"head.h"
using namespace std;
vector <Student > st;
vector <Department > dep;
int main()
{
	
	ifstream fcin;
	ofstream fcout;
	fcin.open(".\\input_data.txt");
	Json::Value root;
	Json::Reader jsonreader;
	Json::Value val;
	if (!jsonreader.parse(fcin, root))
	{
		return -1;
	}
	fcin.close();
	int i;
	int st_count = root["students"].size();
	for (i = 0; i < st_count; i++)
	{
		Student stu;
		stu.st_readin(root,i);
		st.push_back(stu);
	}
	int dep_count = root["departments"].size();
	for (i = 0; i < dep_count; i++)
	{
		Department depa;
		depa.de_readin(root, i);
		dep.push_back(depa);
	}
//	for (unsigned i = 0; i < st.size(); i++)
//		dep[0].println();
	mate();
	print();
	return 0;
}
