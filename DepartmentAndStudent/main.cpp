#include <iostream>
#include <stdlib.h>
#include <cstdio>  
#include <time.h>
#include <string>
#include <fstream>
#include "DandS.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"  
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h"
using namespace std;
using namespace rapidjson;
void testprint(Department* department, Student* student, int N, int M);
int main()
{	
	
	srand((unsigned)time(NULL));
	int N, M;
	//cin >> N >> M;
	//Generate_JSON(N,M);
	N = 50;
	M = 1000;
	Department* department = new Department[N];
	Student* student = new Student[M];
	ReadJson(department, student, N, M);
	match(department, student, N, M);
	output(department, student, N, M);
	//testprint(department,student,N,M);
	system("pause");
	return 0;
}

void testprint(Department* department,Student* student,int N,int M)
{
	for (int i = 0; i < N; i++)
	{
		department[i].print();
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < M; i++)
		student[i].print();
}

