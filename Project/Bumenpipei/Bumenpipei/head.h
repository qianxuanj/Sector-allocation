#ifndef HEAD_HPP
#define HEAD_HPP
#include "json.h"
#include<vector>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include<vector>
#include <time.h> 
using namespace std;
class Student {
public:
	vector <string > free_time;//222222222222
	vector <string > tag;
	vector <string > applications_department;
	string student_no;
	int deps[5];
	int department;//这里还要初始化


	void w_dep() {
		department = 0;
		for (int i = 0; i < 5; i++)
			deps[i] = -1;
	}
	void w_time(string s) {
		string test;
		size_t fi1 = s.find('"', 0);
		size_t fi2 = s.find('"', fi1 + 1);
		test.assign(s.begin() + fi1 + 1, s.begin() + fi2);//1.1111111
														  //	cout << test << endl;
		free_time.push_back(test);
	}
	void w_no(string s) {
		size_t fi1 = s.find(":", 0);
		size_t fi2 = s.find('"', fi1 + 1);
		size_t fi3 = s.find('"', fi2 + 1);
		student_no.assign(s.begin() + fi2 + 1, s.begin() + fi3);
		//	cout << student_no << endl;
	}
	void w_a_dep(string s) {
		string test;
		size_t fi1 = s.find('"', 0);
		size_t fi2 = s.find('"', fi1 + 1);
		test.assign(s.begin() + fi1 + 1, s.begin() + fi2);
		//		cout << test << endl;
		applications_department.push_back(test);
	}
	void w_tag(string s) {
		string test;
		size_t fi1 = s.find('"', 0);
		size_t fi2 = s.find('"', fi1 + 1);
		test.assign(s.begin() + fi1 + 1, s.begin() + fi2);
		//	cout << test << endl;
		tag.push_back(test);
	}
	void println() {
		for (unsigned i = 0; i < free_time.size(); i++)
			cout << free_time[i] << endl;
		for (int i = 0; i < 9; i++)
			cout << student_no[i];
		cout << endl;
		for (unsigned i = 0; i < tag.size(); i++)
			cout << tag[i] << endl;
		for (unsigned i = 0; i < applications_department.size(); i++)
			cout << applications_department[i] << endl;
	}
	void st_readin(Json::Value &root, int x) {
		int i;
		int freetime_count = root["students"][(Json::Value::UInt)x]["free_time"].size();
		for (i = 0; i < freetime_count; i++)
		{
			free_time.push_back(root["students"][(Json::Value::UInt)x]["free_time"][(Json::Value::UInt)i].asString());
		}

		student_no = root["students"][(Json::Value::UInt)x]["student_no"].asString();

		int application_count = root["students"][(Json::Value::UInt)x]["applications_department"].size();
		for (i = 0; i < application_count; i++)
		{
			applications_department.push_back(root["students"][(Json::Value::UInt)x]["applications_department"][(Json::Value::UInt)i].asString());
		}

		int tags_count = root["students"][(Json::Value::UInt)x]["tags"].size();
		for (i = 0; i < tags_count; i++)
		{
			tag.push_back(root["students"][(Json::Value::UInt)x]["tags"][(Json::Value::UInt)i].asString());
		}
		w_dep();
	}
};
class Department {
public:
	vector <string > event_schedules;
	vector <string > tag;
	int member_limit;
	string department_no;
	int *student;
	int students;


	void w_stu() {
		student = new int[member_limit];
		students = 0;
	}
	void w_e_sch(string s) {
		string test;
		size_t fi1 = s.find('"', 0);
		size_t fi2 = s.find('"', fi1 + 1);
		test.assign(s.begin() + fi1 + 1, s.begin() + fi2);
		//		cout << test << endl;
		event_schedules.push_back(test);
	}
	void w_no(string s) {
		size_t fi1 = s.find(":", 0);
		size_t fi2 = s.find('"', fi1 + 1);
		size_t fi3 = s.find('"', fi2 + 1);
		department_no.assign(s.begin() + fi2 + 1, s.begin() + fi3);
		//	cout << department_no << endl;
	}
	void w_me_limit(string s) {
		size_t fi1 = s.find(":", 0);
		member_limit = (s[fi1 + 2] - '0') * 10 + (s[fi1 + 3] - '0');
		//	member_limit = (s[fi1 + 2] - '0') ;
		//	cout << member_limit << endl;
	}
	void w_tag(string s) {
		string test;
		size_t fi1 = s.find('"', 0);
		size_t fi2 = s.find('"', fi1 + 1);
		test.assign(s.begin() + fi1 + 1, s.begin() + fi2);
		//	cout << test << endl;
		tag.push_back(test);
	}
	void de_readin(Json::Value &root, int x)//将Json数据读入到Department类
	{
		int i;
		int schedules_count = root["departments"][(Json::Value::UInt)x]["event_schedules"].size();
		for (i = 0; i < schedules_count; i++)
		{
			event_schedules.push_back(root["departments"][(Json::Value::UInt)x]["event_schedules"][(Json::Value::UInt)i].asString());
		}

		member_limit = root["departments"][(Json::Value::UInt)x]["member_limit"].asInt();

		department_no = root["departments"][(Json::Value::UInt)x]["department_no"].asString();

		int tags_count = root["departments"][(Json::Value::UInt)x]["tags"].size();
		for (i = 0; i < tags_count; i++)
		{
			tag.push_back(root["departments"][(Json::Value::UInt)x]["tags"][(Json::Value::UInt)i].asString());
		}
		w_stu();
	}
	void println() {
		for (unsigned i = 0; i < event_schedules.size(); i++)
			cout << event_schedules[i] << endl;
		cout << department_no << endl;
		cout << member_limit << endl;
		for (unsigned i = 0; i < tag.size(); i++)
			cout << tag[i] << endl;
	}
};
extern vector <Student > st;
extern vector <Department > dep;
int query_tag(int x, int y) {//计算兴趣有多少一样
	int z = 0;
	for (int i = 0; i < st[x].tag.size(); i++) {
		for (int j = 0; j < dep[y].tag.size(); j++) {
			if (st[x].tag[i] == dep[y].tag[j])
				z++;
		}
	}
	return z;
}
void Time_extraction(int* y, int a, int b, int c) {//将空闲时间和活动时间从字符串转化为数组
	if (c == 0) {
		for (int i = dep[a].event_schedules[b].size(), j = 0, k = 0; j <= 10; j++) {
			if (dep[a].event_schedules[b][i - 1 - j] >= 48 && dep[a].event_schedules[b][i - 1 - j] <= 57) {
				y[7 - k] = dep[a].event_schedules[b][i - 1 - j] - '0';
				k++;
			}
			else if (dep[a].event_schedules[b][i - 1 - j] == '~'&&k == 3)
				k++;
		}
	}
	else {
		for (int i = st[a].free_time[b].size(), j = 0, k = 0; j <= 10; j++) {
			if (st[a].free_time[b][i - 1 - j] >= 48 && st[a].free_time[b][i - 1 - j] <= 57) {
				y[7 - k] = st[a].free_time[b][i - 1 - j] - '0';
				k++;
			}
			else if (st[a].free_time[b][i - 1 - j] == '~'&&k == 3)
				k++;
		}
	}
}
int query_time(int x, int y) {//时间匹配算法
	int n = 0;
	for (int i = 0; i < dep[y].event_schedules.size(); i++) {
		for (int j = 0; j < st[x].free_time.size(); j++) {
			string count1, count2;
			size_t fi1 = dep[y].event_schedules[i].find(".", 0);
			count1.assign(dep[y].event_schedules[i].begin(), dep[y].event_schedules[i].begin() + fi1);
			size_t fi2 = st[x].free_time[j].find(".", 0);
			count2.assign(st[x].free_time[j].begin(), st[x].free_time[j].begin() + fi2);
			if (count1 == count2) {
				int a[8] = { 0 }, c = 0;
				int b[8] = { 0 };//这里有问题
				Time_extraction(a, y, i, 0);
				Time_extraction(b, x, j, 1);
				for (int i = 7; i >3; i--) {
					if (b[i] > a[i])
						c = 1;
					else if (b[i] < a[i])
						c = -1;
				}
				if (c == -1)
					break;
				for (int j = 3; j >= 0; j--) {
					if (a[j] > b[j])
						c = 1;
					else if (a[j] < b[j])
						c = -1;
				}
				if (c == 1 || c == 0)
					n++;
			}
		}
	}
	return n;
}
bool clash(int x, int y) {//部门时间冲突计算
	for (int i = 0; i < dep[y].event_schedules.size(); i++) {
		for (int j = 0; j < dep[x].event_schedules.size(); j++) {
			string count1, count2;
			size_t fi1 = dep[y].event_schedules[i].find(".", 0);
			count1.assign(dep[y].event_schedules[i].begin(), dep[y].event_schedules[i].begin() + fi1);
			size_t fi2 = dep[x].event_schedules[j].find(".", 0);
			count2.assign(dep[x].event_schedules[j].begin(), dep[x].event_schedules[j].begin() + fi2);
			if (count1 == count2) {
				int a[8] = { 0 };
				int b[8] = { 0 };
				int n = 0, m = 0, k = 0;
				Time_extraction(a, y, i, 0);
				Time_extraction(b, x, j, 0);
				for (int i = 7; i > 3; i--) {//注意这里的算法 
					if (a[i] > b[i - 4])
						n = 1;
					else if (b[i - 4] > a[i])
						n = -1;
					if (a[i - 4] > b[i])
						m = 1;
					else if (a[i - 4] < b[i])
						m = -1;
				}
				k = n + m;
				if (k == 0)
					return true;
				else
					return false;
			}
		}
	}
}
bool decide(int x, int y) {
	for (int i = 0; i < st[x].department; i++) {
		if (clash(st[x].deps[i], y))
			return false;
	}
	return true;
}
void add(int x, int z) {
	if (st[x].department == 0 || decide(x, z)) {
		if (dep[z].students == 0) {
			dep[z].student[0] = x;
			dep[z].students++;
			st[x].deps[st[x].department] = z;
			st[x].department++;
		}
		else {
			for (int i = dep[z].students; i > 0; i--) {
				if (query_tag(x, z) > query_tag(dep[z].student[i - 1], z)) {
					if (dep[z].students < dep[z].member_limit &&i == dep[z].students) {
						dep[z].student[i] = dep[z].student[i - 1];
						dep[z].student[i - 1] = x;
						dep[z].students++;
						st[x].deps[st[x].department] = z;
						st[x].department++;
					}
					else if ((dep[z].students == dep[z].member_limit&&i != dep[z].member_limit) || (dep[z].students < dep[z].member_limit &&i < dep[z].member_limit)) {
						dep[z].student[i] = dep[z].student[i - 1];
						dep[z].student[i - 1] = x;
					}
					else if (dep[z].students == dep[z].member_limit&&i == dep[z].member_limit) {
						for (int j = 0; j < st[dep[z].student[i - 1]].department; j++) {//注意这里的结构是否正确,这里删除原本的学生的记录
							if (st[dep[z].student[i - 1]].deps[j] == z&&i == (st[dep[z].student[i - 1]].department) - 1)
								st[dep[z].student[i - 1]].deps[j] = st[dep[z].student[i - 1]].deps[j + 1];
							else if (st[dep[z].student[i - 1]].deps[j] == z&&i != (st[dep[z].student[i - 1]].department) - 1)
								swap(st[dep[z].student[i - 1]].deps[j], st[dep[z].student[i - 1]].deps[j + 1]);
						}
						st[dep[z].student[i - 1]].deps[4] = -1;
						st[dep[z].student[i - 1]].department--;
						dep[z].student[i - 1] = x;
					}
				}
				else if (query_tag(x, z) == query_tag(dep[z].student[i - 1], z)) {
					if (query_time(x, z) > query_time(dep[z].student[i - 1], z)) {
						if (dep[z].students < dep[z].member_limit &&i == dep[z].students) {
							dep[z].student[i] = dep[z].student[i - 1];
							dep[z].student[i - 1] = x;
							dep[z].students++;
							st[x].deps[st[x].department] = z;
							st[x].department++;
						}
						else if ((dep[z].students == dep[z].member_limit&&i != dep[z].member_limit) || (dep[z].students < dep[z].member_limit &&i < dep[z].member_limit)) {
							dep[z].student[i] = dep[z].student[i - 1];
							dep[z].student[i - 1] = x;
						}
						else if (dep[z].students == dep[z].member_limit&&i == dep[z].member_limit) {
							for (int j = 0; j < st[dep[z].student[i - 1]].department; j++) {
								if (st[dep[z].student[i - 1]].deps[j] == z&&i == (st[dep[z].student[i - 1]].department) - 1)
									st[dep[z].student[i - 1]].deps[j] = st[dep[z].student[i - 1]].deps[j + 1];
								else if (st[dep[z].student[i - 1]].deps[j] == z&&i != (st[dep[z].student[i - 1]].department) - 1)
									swap(st[dep[z].student[i - 1]].deps[j], st[dep[z].student[i - 1]].deps[j + 1]);
							}
							st[dep[z].student[i - 1]].deps[4] = -1;
							st[dep[z].student[i - 1]].department--;
							dep[z].student[i - 1] = x;
						}
					}
					else if ((dep[z].students < dep[z].member_limit) && (i == dep[z].students)) {
						dep[z].student[dep[z].students] = x;
						dep[z].students++;
						st[x].deps[st[x].department] = z;
						st[x].department++;
						break;
					}
				}
				else if ((dep[z].students < dep[z].member_limit) && (i == dep[z].students)) {
					dep[z].student[dep[z].students] = x;
					dep[z].students++;
					st[x].deps[st[x].department] = z;
					st[x].department++;
					break;
				}
			}
		}
	}
}
void search(int x, int y) {
	for (unsigned i = 0; i < dep.size(); i++) {
		if (st[x].applications_department[y] == dep[i].department_no) {
			add(x, i);
			break;
		}
	}
}
void mate() {
	for (unsigned i = 0; i < st.size(); i++) {
		for (unsigned j = 0; j < st[i].applications_department.size(); j++)
			search(i, j);
	}
}
void print() {
	ofstream outfile("output_data.txt");
	outfile << "{" << endl;
	outfile << "    \"unlucky_student\": [";
	for (unsigned i = 0, j = 0; i < st.size(); i++) {
		if (st[i].department == 0) {
			if (j == 0)
				outfile << endl;
			if (j != 0)
				outfile << "," << endl;
			outfile << "        \"" << st[i].student_no << "\"";
			j++;
		}
		if (i == st.size() - 1 && j != 0)
			outfile << endl << "    ";
	}
	outfile << "]," << endl;
	outfile << "    \"addmitted\": [" << endl;
	for (unsigned i = 0; i < dep.size(); i++) {
		if (i != 0)
			outfile << "," << endl;
		outfile << "        {" << endl;
		outfile << "            \"member\": [";
		for (unsigned j = 0; j < dep[i].students; j++) {
			if (j == 0)
				outfile << endl;
			if (j != 0)
				outfile << "," << endl;
			outfile << "                \"" << st[dep[i].student[j]].student_no << "\"";
			if (j == dep[i].students - 1) {
				outfile << endl;
				outfile << "            ";
			}
		}
		outfile << "]," << endl;
		outfile << "            \"department_no\": " << "\"" << dep[i].department_no << "\"" << endl;
		outfile << "        }";
	}
	outfile << endl;
	outfile << "    ]," << endl;
	outfile << "    \"unlucky_department\": [";
	for (unsigned i = 0; i < dep.size(); i++) {
		if (dep[i].students == 0) {
			if (i == 0)
				outfile << endl;
			if (i != 0)
				outfile << "," << endl;
			outfile << "                \"" << dep[i].department_no << "\"";
			if (i == dep.size() - 1) {
				outfile << endl;
				outfile << "    ";
			}
		}
	}
	outfile << "]" << endl;
	outfile << "}" << endl;
}
#endif