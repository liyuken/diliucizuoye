#pragma   once  
#ifndef DANDS_H
#define DANDS_H
#include <sstream>
#include <vector>
using namespace std;
class Student;
int  cminterests(string* inte, string* inte1);
int  cmschedual(string* sche, string* sche1);
int  cmp(float point, string* schedual, string* interests, float point1, string* schedual1, string* interests1);
class Department				//部门
{
private:
	string D_No;				//*部门编号
	string D_Name;				//*部门名称
	int D_Limit;				//*纳新人数限制
	string D_Tags[5];			//*部门标签
	string D_Schedules[5];		//*部门常规活动时间
	float GPA_Limit;			//*最低绩点要求
	string student[16];			//部门招的学生集合  
	int m[16] = { 0 };			//每个学生对应的权值
	int numofstu=0;				//选中学生数

public:
	void Init(string No, string name, int Limit, string* tags, int tags_n, string* schedules, int sch_n, float gpa);
	void print();
	string getNo() { return D_No; }
	string getName() { return D_Name; }
	string get_Tags(int n) { return D_Tags[n]; }
	int get_Tags_Len(int n){ return sizeof(D_Tags[n])/sizeof(string); }
	string get_Time(int n) { return D_Schedules[n]; }
	string* getStudent() { return student; }
	int get_Limit() { return D_Limit; }
	float get_GPA() { return GPA_Limit; }
	void willmatching(Student &);
	bool check();
	void chonsenstudent(Student &);
};
class Student					//学生
{
private:
	string S_No;				//*学号
	string S_Sex;				//*性别
	string S_Name;				//*姓名
	string S_Tags[5];			//*兴趣标签
	string S_Schedules[10];		//*空闲时间
	string S_Choice[5];			//*部门志愿
	float GPA;					//*绩点
	string S_Chosen[5];			//选中部门
	int numofdep=0;				//选中部门数
public:
	void Init(string No, string Name,string sex,string *tags,int tag_num,string *Schedules, int scl_num, string *choice, int ch_num, float mGPA);
	void print();
	string getNo() { return S_No; }
	string getSex() { return S_Sex; }
	string getName() { return S_Name; }
	string get_Tags(int n) { return S_Tags[n]; }
	string get_Time(int n) { return S_Schedules[n]; }
	string get_Choice(int n) { return S_Choice[n]; }
	string* get_Chosen() { return S_Chosen; }
	bool check();
	float get_GPA() { return GPA; }
	friend void Department::willmatching(Student &);
	friend void Department::chonsenstudent(Student &);
};
void ReadJson(Department* &department, Student* &student, int N, int M);//读取json
void Generate_JSON(int N,int M);//产生输入json
void match(Department* &department, Student* &student, int N, int M);//部门与学生匹配
void output(Department* department, Student* student, int N, int M);//输出json
#endif // !DANDS_H
