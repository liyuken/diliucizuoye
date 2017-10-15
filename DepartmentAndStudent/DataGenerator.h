#pragma once
#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include <sstream>
#include <stdlib.h>
#include "DandS.h"
using namespace std;

const char Character[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
const char Number[10] = { '0','1','2','3','4','5','6','7','8','9' };
const string Sex[2] = { "male","female" };
const string Tags[16] = { "dancing","film","music","painting","programing","reading","running","sports","English","math","swimming","game","hiking","travelling","basketball","document" };
const string Week_Time[7] = { "Mon.","Tue.","Wed.","Thu.","Fri.","Sat.","Sun." };
const string Day_Time[10] = { "9: 00~10: 00","9: 00~10: 00","10: 00~11: 00","13: 00~14: 00","14: 00~15: 00","15: 00~16: 00","16: 00~17: 00",
"19: 00~20: 00","20: 00~21: 00","21: 00~22: 00" };

template <class T>
int getlen(T& array)
{
	int temp = (sizeof(array) / sizeof(array[0]));
	return temp;
}

class DataGenerator
{
public:

	//产生名字（学生/部门）
	string Name_Get()
	{
		stringstream stream;
		stream << Character[rand() % getlen(Character)] << Number[rand() % getlen(Number)] << Number[rand() % getlen(Number)] << Number[rand() % getlen(Number)];
		string Num = stream.str();
		return stream.str();
	}

	//产生标签（学生/部门）
	string* Tags_Get(int n)
	{
		int* random = new int[n];
		string* result = new string[n];
		int count = 0, temp;
		bool flag;
		for (int i = 0; i < n;)
		{
			flag = true;
			temp = rand() % getlen(Tags);
			for (int j = 0; j < i; j++)
			{
				if (random[j] == temp)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				random[i] = temp;
				result[i] = Tags[temp];
				i++;
			}
		}
		return result;
	}

	//产生一周内的时间表（学生/部门）
	string* Time_Get(int n)
	{
		int* x = new int[n];
		int* y = new int[n];
		int temp1, temp2;
		bool flag;
		//cout << n;
		string* result = new string[n];
		for (int i = 0; i < n;)
		{
			flag = true;
			temp1 = rand() % getlen(Week_Time);
			temp2 = rand() % getlen(Day_Time);
			for (int j = 0; j < i; j++)
			{
				if (temp1 == x[j] && temp2 == y[j])
				{
					flag = false;
					//cout << "error" << " ";
					break;
				}
			}
			if (flag)
			{
				x[i] = temp1;
				y[i] = temp2;
				//cout << " (" << temp1 << "," << temp2 << ") ";
				result[i] = Week_Time[temp1] + Day_Time[temp2];
				i++;
			}
		}
		//cout << endl;
		return result;
	}

	//产生性别（学生）
	string Sex_Get()
	{
		return Sex[rand() % getlen(Sex)];
	}

	//产生学号（学生）
	string* SNum_Get(int n)
	{
		int* random = new int[n];
		int temp = 0;
		bool flag;
		string start = "S03150";
		stringstream ss;
		string* result = new string[n];
		for (int i = 0; i < n;)
		{
			ss.clear();
			ss.str("");
			flag = true;
			temp = rand() % 8960 + 1;
			if (temp % 100 == 0 || temp % 100 > 60)continue;
			for (int j = 0; j < i; j++)
			{
				if (random[j] == temp) { flag = false; break; }
			}
			if (flag)
			{
				random[i] = temp;
				ss.fill('0');
				ss.width(4);
				ss << temp;
				result[i] = start + ss.str();
				i++;
			}
		}
		return result;
	}

	//产生志愿(2~5个)（学生）
	string* Choices_Get(int numof_student, int numof_department, string* choices, int numof_chocies)
	{
		string* result = new string[numof_chocies];
		int* random=new int[numof_chocies];
		bool flag;
		for (int i = 0; i < numof_chocies; )
		{
			flag = true;
			int temp = rand() % numof_department;
			for (int j = 0; j < i; j++)
			{
				if (random[j] == temp)
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				random[i] = temp;
				result[i] = choices[temp];
				i++;
			}
		}
		return result;
	}

	//产生绩点（学生）
	float GPA_Get()
	{
		float m = (rand() % 100000);
		float k = m / 100000;
		int n = rand() % 4;
		float result = 1 + n + k;
		return result;
	}

	//产生部门编号（部门）
	string* DNum_Get(int n)
	{
		int* random = new int[n];
		int temp;
		bool flag;
		string start = "D";
		stringstream ss;
		string* result = new string[n];
		for (int i = 0; i < n;)
		{
			ss.clear();
			ss.str("");
			flag = true;
			temp = rand() % 100 + 1;
			for (int j = 0; j < i; j++)
			{
				if (random[j] == temp) { flag = false; break; }
			}
			if (flag)
			{
				random[i] = temp;
				ss.fill('0');
				ss.width(3);
				ss << temp;
				result[i] = start + ss.str();
				i++;
			}
		}
		delete[] random;
		return result;
	}

	//产生部门人数限制(0~15人)（部门）
	int Max_Get()
	{
		return rand() % 15;
	}

	//产生绩点要求(部门)
	float GPA_Min_Get()
	{
		float m = (rand() % 1000);
		float k = m / 1000;
		int n = rand() % 2;
		float result = 1 + n + k;
		return result;
	}

};

Department* generate_department(int N, string* &temp)
{
	DataGenerator DG;
	Department* department = new Department[N];
	string* num = new string[N];
	num = DG.DNum_Get(N);
	temp = num;
	for (int i = 0; i < N; i++)
	{
		int temp1 = rand() % 5 + 3;
		string* tags = new string[temp1];
		tags = DG.Tags_Get(temp1);

		int temp2 = rand() % 5 + 1;
		string* times = new string[temp2];
		times = DG.Time_Get(temp2);

		department[i].Init(num[i], DG.Name_Get(), DG.Max_Get(), tags, temp1, times, temp2, DG.GPA_Min_Get());
	}
	return department;
}

Student* generate_student(int N, int M, string* temp)
{
	DataGenerator DG;
	Student* student = new Student[N];
	string* num = new string[N];
	num = DG.SNum_Get(N);
	for (int i = 0; i < N; i++)
	{

		int temp1 = 2 + (int)4 * rand() / (RAND_MAX + 1);
		string* tags = new string[temp1];
		tags = DG.Tags_Get(temp1);

		int temp2 = 2 + (int)9 * rand() / (RAND_MAX + 1);
		string* times = new string[temp2];
		times = DG.Time_Get(temp2);

		int temp3 = 2 + (int)4 * rand() / (RAND_MAX + 1);
		if (temp3 >= M) temp3 = M;
		string* choices = new string[temp3];
		choices = DG.Choices_Get(N, M, temp, temp3);

		student[i].Init(num[i], DG.Name_Get(), DG.Sex_Get(), tags, temp1, times, temp2, choices, temp3, DG.GPA_Get());
	}
	return student;
}

#endif