#include <iostream>
#include <stdlib.h>
#include "DandS.h"
#include "DataGenerator.h"
#include <fstream>
#include <string> 
#include <cstdio>  
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"  
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h"

using namespace std;
using namespace rapidjson;

string IntToString(int n)
{
	stringstream temp;
	temp << n;
	string result;
	temp >> result;
	return result;
}
void Student::Init(string No, string Name, string sex, string *tags, int tag_num, string *Schedules, int scl_num, string *choice, int ch_num, float mGPA)
{
	S_No = No;
	S_Sex = sex;
	S_Name = Name;
	for (int i = 0; i < tag_num; i++)
	{
		S_Tags[i] = tags[i];
		//if (i != tag_num - 1)SS_Tags = SS_Tags + tags[i] + ",";
		//else SS_Tags = SS_Tags + tags[i];
	}

	for (int i = 0; i < scl_num; i++)
	{
		S_Schedules[i] = Schedules[i];
		//if (i != scl_num - 1)SS_Schedules = SS_Schedules + Schedules[i] + ",";
		//else SS_Schedules = SS_Schedules + Schedules[i];
	}
	for (int i = 0; i < ch_num; i++)
	{
		S_Choice[i] = choice[i];
	}
	GPA = mGPA;
}
void Department::Init(string No, string name, int Limit, string* tags, int tags_n, string* schedules, int sch_n, float gpa)
{
	D_No = No;
	D_Name = name;
	D_Limit = Limit;
	for (int i = 0; i < tags_n; i++)
	{
		D_Tags[i] = tags[i];
	}
	for (int i = 0; i < sch_n; i++)
	{
		D_Schedules[i] = schedules[i];
	}
	GPA_Limit = gpa;
}
void ReadJson(Department* &department, Student* &student,int N,int M)
{
	//读入json文件
	const string filename = "s" + IntToString(M) + "-d" + IntToString(N) + "-in.json";
	ifstream json_file;
	json_file.open(filename.c_str());
	string json;
	if (!json_file.is_open())
	{
		cout << "Error opening file" << endl;
		exit(1);
	}
	string str;
	string str_in = "";
	while (getline(json_file, str))    //一行一行地读到字符串str_in中  
	{
		str_in = str_in + str + '\n';
	}
	Document doc;
	doc.Parse<0>(str_in.c_str());
	//部门读取
	Value &departments = doc["department"];
	if (departments.IsArray())
	{
		for (unsigned int i = 0; i < departments.Size(); i++)
		{
			string No = departments[i]["Department_No"].GetString();		//读取部门编号
			string Name = departments[i]["Department_Name"].GetString();	//读取部门名称
			int Limit = departments[i]["Limit"].GetInt();					//读取部门人数限制
			float GPA_Limit = departments[i]["GPA_Limit"].GetFloat();		//读取部门绩点限制
			Value &d_tags = departments[i]["Tags"];							//读取部门标签表
			string* tags = new string[5];					
			unsigned int tags_len=0;
			if (d_tags.IsArray())
			{
				for (tags_len = 0; tags_len < d_tags.Size(); tags_len++)
				{
					tags[tags_len] = d_tags[tags_len].GetString();
				}
			}
			Value &d_time = departments[i]["Schedules"];					//读取部门活动时间表
			string* times = new string[10];			
			unsigned int times_len;
			if (d_time.IsArray())
			{
				for (times_len = 0; times_len < d_time.Size(); times_len++)
				{
					times[times_len] = d_time[times_len].GetString();
				}
			}
			department[i].Init(No,Name,Limit, tags, tags_len, times, times_len, GPA_Limit);	//导入部门数据
		}
	}
	//学生读取
	Value &students = doc["student"];
	if (students.IsArray())
	{
		for (unsigned int i = 0; i < students.Size(); i++)
		{
			string No = students[i]["Student_No"].GetString();			//读取学号
			string Name = students[i]["Student_Name"].GetString();		//读取姓名
			string Sex = students[i]["Sex"].GetString();				//读取性别
			float GPA = students[i]["GPA"].GetFloat();					//读取绩点
			Value &s_tags = students[i]["Tags"];						//读取兴趣标签表
			string* tags = new string[5];
			unsigned int tags_len;
			if (s_tags.IsArray())
			{
				for (tags_len = 0; tags_len < s_tags.Size(); tags_len++)
				{
					tags[tags_len] = s_tags[tags_len].GetString();
				}
			}
			Value &s_time = students[i]["Free_Time"];					//读取空闲时间表
			string* free_time = new string[10];
			unsigned int time_len;
			if (s_time.IsArray())
			{
				for (time_len = 0; time_len < s_time.Size(); time_len++)
				{
					free_time[time_len] = s_time[time_len].GetString();
				}
			}
			
			Value &student_choices = students[i]["Choice"];				//读取部门志愿表
			string* choices = new string[5];
			unsigned int choices_len;
			if (student_choices.IsArray())
			{
				for (choices_len = 0; choices_len < student_choices.Size(); choices_len++)
				{
					choices[choices_len] = student_choices[choices_len].GetString();
				}
			}
			student[i].Init(No,Name,Sex,tags,tags_len,free_time,time_len,choices,choices_len,GPA);	//导入学生数据
		}
	}
}
void Generate_JSON(int N,int M)
{
	//随机产生部门、学生信息
	string* D_Num = new string[N];
	Department* department;
	Student* student;
	department = generate_department(N, D_Num);
	student = generate_student(M, N, D_Num);
	//写入json文件
	Document doc;
	doc.SetObject();
	Document::AllocatorType &allocator = doc.GetAllocator(); 
	//部门
	Value department_array(kArrayType);
	for (int i = 0; i < N; i++)
	{
		Value department_object(kObjectType);
		department_object.SetObject();
		Value DepartmentNO;
		DepartmentNO.SetString(StringRef(department[i].getNo().c_str()), allocator);
		department_object.AddMember("Department_No", DepartmentNO, allocator);
		Value DepartmentName;
		DepartmentName.SetString(StringRef(department[i].getName().c_str()), allocator);
		department_object.AddMember("Department_Name", DepartmentName, allocator);
		department_object.AddMember("Limit", department[i].get_Limit(), allocator);
		Value DepartmentGPA;
		DepartmentGPA.SetFloat(department[i].get_GPA());
		department_object.AddMember("GPA_Limit", DepartmentGPA, allocator);
		Value Tags_array(kArrayType);
		for (int t = 0; t<5; t++)
		{
			Value Tags_object(kObjectType);
			string temp = department[i].get_Tags(t);
			if (temp != "")
			{
				Tags_object.SetObject();
				Tags_object.SetString(StringRef(temp.c_str()), allocator);
				Tags_array.PushBack(Tags_object, allocator);
			}
		}
		department_object.AddMember("Tags", Tags_array, allocator);

		Value schedule_array(kArrayType);
		for (int t = 0; t<5; t++)
		{
			Value schedule_object(kObjectType);
			string temp = department[i].get_Time(t);
			if (temp != "")
			{
				schedule_object.SetObject();
				schedule_object.SetString(StringRef(temp.c_str()), allocator);
				schedule_array.PushBack(schedule_object, allocator);
			}
		}
		department_object.AddMember("Schedules", schedule_array, allocator);

		department_array.PushBack(department_object, allocator);
	}
	doc.AddMember("department", department_array, allocator);
	//学生
	Value student_array(kArrayType);
	for (int i = 0; i < M; i++)
	{
		Value Student_object(kObjectType);
		Student_object.SetObject();
		Value StudentNo;
		StudentNo.SetString(StringRef(student[i].getNo().c_str()), allocator);
		Student_object.AddMember("Student_No", StudentNo, allocator);
		Value StudentName;
		StudentName.SetString(StringRef(student[i].getName().c_str()), allocator);
		Student_object.AddMember("Student_Name", StudentName, allocator);
		Value Sex;
		Sex.SetString(StringRef(student[i].getSex().c_str()), allocator);
		Student_object.AddMember("Sex", Sex, allocator);
		Value StudentGPA;
		StudentGPA.SetFloat(student[i].get_GPA());
		Student_object.AddMember("GPA", StudentGPA, allocator);
		Value Tags_array(kArrayType);
		int t;
		for (t = 0; t<5; t++)
		{
			Value Tags_object(kObjectType);
			string temp = student[i].get_Tags(t);
			if (temp != "")
			{
				Tags_object.SetObject();
				Tags_object.SetString(StringRef(temp.c_str()), allocator);
				Tags_array.PushBack(Tags_object, allocator);
			}
		}
		Student_object.AddMember("Tags", Tags_array, allocator);
		//空闲时间
		Value Schedules_array(kArrayType);
		for (t = 0; t<10; t++)
		{
			Value Schedules_object(kObjectType);
			string temp = student[i].get_Time(t);
			if (temp != "")
			{
				Schedules_object.SetObject();
				Schedules_object.SetString(StringRef(temp.c_str()), allocator);
				Schedules_array.PushBack(Schedules_object, allocator);
			}
		}
		Student_object.AddMember("Free_Time", Schedules_array, allocator);

		//志愿
		Value Choices_array(kArrayType);
		for (t = 0; t<5; t++)
		{
			Value Choices_object(kObjectType);
			string temp = student[i].get_Choice(t);
			if (temp != "")
			{
				Choices_object.SetObject();
				Choices_object.SetString(StringRef(temp.c_str()), allocator);
				Choices_array.PushBack(Choices_object, allocator);
			}
		}
		Student_object.AddMember("Choice", Choices_array, allocator);
		student_array.PushBack(Student_object, allocator);
	}
	doc.AddMember("student", student_array, allocator);
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
	doc.Accept(writer);
	ofstream out;
	const string filename = "s" + IntToString(M) + "-d" + IntToString(N) + "-in.json";
	out.open(filename);
	out << buffer.GetString();
	out.close();
}
void Department::chonsenstudent(Student &s)
{
	int i;
	for (i = 0; i < D_Limit; i++)
	{
		if (student[i] == s.S_No)
		{
			s.S_Chosen[s.numofdep] = D_No;
			s.numofdep = s.numofdep + 1;
			break;
		}
	}
}
/*string Student::matched_student()
{
if (check() == 1)
return S_No;
}

string Student::empty_student()
{
if (check() == 0)
return S_No;
}*/
//检测学生是否全部落选
bool Student::check()
{
	if (numofdep == 0)
	{
		return false;
	}
	else return true;
}
/*string Department::matched_delartment()
{
if (check() == 1)
return D_No;
}
string Department::empty_department()
{
if (check() == 0)
return D_No;
}*/
bool Department::check()
{
	if (numofstu == 0)
	{
		return false;
	}
	else return true;
}
void Department::willmatching(Student &s)
{
	if (D_Limit != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (s.S_Choice[i] == D_No)
			{			
				if (numofstu < D_Limit)
				{
					student[numofstu] = s.S_No;
					m[numofstu] = cmp(s.GPA, s.S_Schedules, s.S_Tags, GPA_Limit, D_Schedules, D_Tags);
					numofstu++;
				}
				else if (numofstu > D_Limit)
				{
					m[numofstu] = cmp(s.GPA, s.S_Schedules, s.S_Tags, GPA_Limit, D_Schedules, D_Tags);
					for (int u = 0; u < D_Limit; u++)
					{
						if (m[numofstu] > m[u])
						{							
							m[u] = m[numofstu];
							student[u] = student[numofstu];
							break;
						}
					}
				}
			}
		}
	}
}
int  cminterests(string* s_interest, string* d_interest)
{
	int i, j, n = 0, n1 = 0, mark = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n1; j++)
		{
			if (s_interest[i] == d_interest[j])
			{
				mark = mark + 1;
			}
		}
	}
	mark = mark * 4;
	return mark;
}
int  cmschedual(string* s_che, string* d_che)
{
	int i, j, n = 0, n1 = 0, mark = 0;
	for (i = 0; i < 10; i++)
	{
		if (s_che[i] == "")break;
		for (j = 0; j < 5; j++)
		{
			if (d_che[j] == "")break;
			if (s_che[i] == d_che[j])
			{
				mark = mark + 1;
			}
		}
	}
	mark = mark * 4;
	return mark;
}
int	 cmpoint(float p1, float p2)
{
	int mark = 0;
	if (p1 >= p2)
	{
		mark = mark + 10;
	}
	return mark;
}
int  cmp(float point, string* schedual, string* interests, float point1, string* schedual1, string* interests1)
{
	int mark;
	mark = cminterests(interests, interests1) + cmschedual(schedual, schedual1) + cmpoint(point, point1);
	//cout << cminterests(interests, interests1) << " " << cmschedual(schedual, schedual1) << " " << cmpoint(point, point1) << endl;
	return mark;
}
void match(Department* &department,Student* &student,int N,int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			department[i].willmatching(student[j]);
		}
	}
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < M; j++)
		{
			department[i].chonsenstudent(student[j]);
		}
	}
}
void output(Department* department, Student* student, int N, int M)
{
	Document doc;
	doc.SetObject();
	Document::AllocatorType &allocator = doc.GetAllocator();
	Value matched_department(kArrayType);
	for (int i = 0; i < N; i++)
	{
		string* new_student;
		if (department[i].check())
		{
			Value matched_department_object(kObjectType);
			matched_department_object.SetObject();
			Value Department_NO;
			Department_NO.SetString(StringRef(department[i].getNo().c_str()), allocator);
			matched_department_object.AddMember("department_no", Department_NO, allocator);
			new_student = department[i].getStudent();
			Value New_Array(kArrayType);
			for (int t = 0; t<15; t++)
			{
				Value new_object(kObjectType);
				if (new_student[t] != "")
				{
					new_object.SetObject();
					new_object.SetString(StringRef(new_student[t].c_str()), allocator);
					New_Array.PushBack(new_object, allocator);
				}
			}
			matched_department_object.AddMember("chosen_students", New_Array, allocator);

			matched_department.PushBack(matched_department_object, allocator);
		}
	}
	doc.AddMember("matched_department_view", matched_department, allocator);

	Value matched_student(kArrayType);
	for (int i = 0; i < M; i++)
	{
		string* new_department;
		if (student[i].check())
		{
			Value matched_student_object(kObjectType);
			matched_student_object.SetObject();
			Value Student_NO;
			Student_NO.SetString(StringRef(student[i].getNo().c_str()), allocator);
			matched_student_object.AddMember("department_no", Student_NO, allocator);
			new_department = student[i].get_Chosen();
			Value New_Array(kArrayType);
			for (int t = 0; t<5; t++)
			{
				Value new_object(kObjectType);
				if (new_department[t] != "")
				{
					new_object.SetObject();
					new_object.SetString(StringRef(new_department[t].c_str()), allocator);
					New_Array.PushBack(new_object, allocator);
				}
			}
			matched_student_object.AddMember("chosen_department", New_Array, allocator);
			matched_student.PushBack(matched_student_object, allocator);
		}
	}
	doc.AddMember("matched_student_view", matched_student, allocator);

	Value standalone_departments(kArrayType);
	for (int i = 0; i < N; i++)
	{
		Value temp_object(kObjectType);
		if (!department[i].check())
		{
			Value standalone_departments_object(kObjectType);
			standalone_departments_object.SetObject();
			temp_object.SetString(StringRef(department[i].getNo().c_str()), allocator);
			standalone_departments.PushBack(temp_object, allocator);
		}
	}
	doc.AddMember("standalone_departments", standalone_departments, allocator);

	Value standalone_students(kArrayType);
	for (int i = 0; i < M; i++)
	{
		Value temp_object(kObjectType);
		if (!student[i].check())
		{
			Value standalone_students_object(kObjectType);
			standalone_students_object.SetObject();
			temp_object.SetString(StringRef(student[i].getNo().c_str()), allocator);
			standalone_students.PushBack(temp_object, allocator);
		}
	}
	doc.AddMember("standalone_students", standalone_students, allocator);

	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	doc.Accept(writer);
	//cout << buffer.GetString() << endl;
	ofstream out;
	string filename = "s" + IntToString(M) + "-d" + IntToString(N) + "-out.json";
	out.open(filename);
	out << buffer.GetString();
	out.close();
}
void Department::print()
{
	cout << "部门编号:" << D_No << endl;
	cout << "部门名称:" << D_Name << endl;
	cout << "人数限制:" << D_Limit << endl;
	cout << "绩点限制:" << GPA_Limit << endl << "兴趣标签:";
	for (int i = 0; i < 5; i++)
	{
		cout << D_Tags[i] << " ";
	}
	cout << endl << "部门时间:";
	for (int i = 0; i < 5; i++)
	{
		cout << D_Schedules[i] << " ";
	}
	cout << endl << "---------------------------" << endl;
}
void Student::print()
{
	cout << "学号:" << S_No << endl;
	cout << "姓名:" << S_Name << endl;
	cout << "性别:" << S_Sex << endl;
	cout << "绩点:" << GPA << endl << "兴趣标签:";
	for (int i = 0; i < 5; i++)
	{
		cout << S_Tags[i] << " ";
	}
	cout << endl << "空闲时间:";
	for (int i = 0; i < 10; i++)
	{
		cout << S_Schedules[i] << " ";
	}
	cout << endl << "志愿:";
	for (int i = 0; i < 5; i++)
	{
		cout << S_Choice[i] << " ";
	}
	cout << endl << "---------------------------" << endl;
}