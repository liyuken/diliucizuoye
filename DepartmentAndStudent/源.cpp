/*#include<iostream>
#include<string>
using namespace std;
class Student;
int  cminterests(string inte, string inte1);
int  cmschedual(string sche, string sche1);
int  cmp(float point, string schedual, string interests, float point1, string schedual1, string interests1);
class Department				//����
{
private:
	string D_No;				//���ű��
	string D_Name;				//��������
	int D_Limit;				//������������
	string D_Tags;			//���ű�ǩ
	string D_Schedules;		//���ų���ʱ��
	float GPA_Limit;			//��ͼ�������
	string  student[16];
	string m[16];
	int numofstu;
public:
	void Init(string No, string name);
	void willmatching(Student &);
	int check();
	string empty_department();
	string matched_delartment();
	void chonsenstudent(Student &);
	
};
class Student					//ѧ��
{
private:
	string S_No;				//ѧ��
	string S_Sex;				//�Ա�
	string S_Name;				//����
	string S_Tags;			//��Ȥ��ǩ
	string S_Schedules;		//����ʱ��
	string S_Choice[5];			//����־Ը
	float GPA;					//����
	string S_Chosen[5];//ѡ�в���
	int numofdep;
public:
	int check();
	void Init(string No, string Name);
	bool isFail();
	friend void Department::willmatching(Student &);
	friend void Department::chonsenstudent(Student &);
	string empty_student();
	string matched_student();
};
void Department::chonsenstudent(Student &s)
{
	int i;
	for (i = 0; i < D_Limit;i++)
	{
		if (student[i] == s.S_No)
		{
			s.S_Chosen[s.numofdep] = D_No;
			s.numofdep = s.numofdep + 1;
			break;
		}
	}
}
string Student::matched_student()
{
	if (check() == 1)
		return S_No;
}

string Student::empty_student()
{
	if (check() == 0)
		return S_No;
}
//���ѧ���Ƿ�ȫ����ѡ
int Student::check()
{
	if (numofdep == 0)
	{
		return 0;
	}
	else return 1;
}
string Department::matched_delartment()
{
	if (check() == 1)
		return D_No;
}
string Department::empty_department()
{
	if (check() == 0)
		return D_No;
}
int Department::check()
{
	if (numofstu == 0)
	{
		return 0;
	}
	else return 1;
}
void Department::willmatching(Student &s)
{ 
	int i,j=numofstu,u;
	for (i = 0; i < 5; i++)
	{
		if (s.S_Choice[i] == D_No)
		{
			if (j < D_Limit)
			{
				student[j] = s.S_No;
				m[j] = cmp(s.GPA, s.S_Schedules, s.S_Tags, GPA_Limit, D_Schedules, D_Tags);
				j = j + 1;
			}
			if (j == D_Limit)
			{
				m[j] = cmp(s.GPA, s.S_Schedules, s.S_Tags, GPA_Limit, D_Schedules, D_Tags);
				for (u = 0; u < D_Limit;u++)
				{
					if (m[j] > m[u])
					{
						m[u] = m[j];
						break;
					}
				}
			}
		}
	}
numofstu=j;	
}
int  cminterests(string inte, string inte1)
{
	int i, j, n = 0, n1 = 0, mark = 0;
	string s1, s2;
	string s[10];
	string d[10];
	s1 = inte;
	s2 = inte1;
	int idx;
	idx = s1.find(",", 0);
	while (idx != string::npos)
	{
		idx = s1.find(",", 0);
		s[n] = s1.substr(0, idx);
		s1.erase(0, idx+1);
		n = n + 1;
	}
	n1 = 0;
	idx = s2.find(",", 0);
	while (idx != string::npos)
	{
		idx = s2.find(",", 0);
		d[n1] = s2.substr(0, idx);
		s2.erase(0, idx + 1);
		n1 = n1 + 1;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n1; j++)
		{
			if (s[i] == d[j])
			{
				mark = mark + 1;
			}
		}
	}
	mark = mark * 4;
	return mark;
}
int  cmschedual(string sche, string sche1)
{
	int i, j, n = 0, n1 = 0, mark = 0;
	string s1, s2;
	string s[10];
	string d[10];
	s1 = sche;
	s2 = sche1;
	int idx;
	idx = s1.find(",", 0);
	while (idx != string::npos)
	{
		idx = s1.find(",", 0);
		s[n] = s1.substr(0, idx);
		s1.erase(0, idx + 1);
		n = n + 1;
	}
	n1 = 0;
	idx = s2.find(",", 0);
	while (idx != string::npos)
	{
		idx = s2.find(",", 0);
		d[n1] = s2.substr(0, idx);
		s2.erase(0, idx + 1);
		n1 = n1 + 1;
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n1; j++)
		{
			if (s[i] == d[j])
			{
				mark = mark + 1;
			}
		}
	}
	mark = mark * 4;
	return mark;
}
int cmpoint(float p1, float p2)
{
	int mark = 0;
	if (p1 >= p2)
	{
		mark = mark + 10;
	}
	return mark;
}
int  cmp(float point, string schedual, string interests, float point1, string schedual1, string interests1)
{
	int mark;
	mark = cminterests(interests, interests1) + cmschedual(schedual, schedual1) + cmpoint(point, point1);
	cout << cminterests(interests, interests1) << " " << cmschedual(schedual, schedual1) << " " << cmpoint(point, point1) << endl;
	return mark;
}
/*int main()
{
	int i,n,m,j;
	cin >> n;
	cin >> m;
	Student s[5000];
	Department d[100];
	for (i = 0; i < n; i++) {
		d->willmatching(s[i]);
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			d[i].chonsenstudent(s[j]);
		}
	}


	return 0;
}*/