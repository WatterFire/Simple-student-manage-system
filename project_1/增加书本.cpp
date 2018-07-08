#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<sstream>
#define IN_PARAM
#define OUT_PARAM
using namespace std;
struct Books_Information
{
	int iBook_Number;
	int iBook_N;
	char cBook_Name[40];
	int iBook_Price;
};

#include<iostream>
#include<fstream>
#include<sstream>
#define IN_PARAM
#define OUT_PARAM
using namespace std;
struct Books_Imformation//书信息
{
	int iBook_Number;
	int iBook_N;//该类书数量
	char cBook_Name[40];
	int iBook_Price;
};

struct Stu_Imformation//学生信息
{
	char cStudent_Number[20];
	char cStudent_Password[20];
	int iStudent_Rent;//借书数量
	char *szStudent_Book[10];//借书名字
};

struct Tea_Imformation//教师信息
{
	char cTeacher_Number[20];
	char cTeacher_Password[20];
	int iTeacher_Rent;//借书数量
	int iStudent_Book[30];//借书序号
};

struct Admin_Imformation//管理员信息
{
	char cAdmin_Number[20];
	char cAdmin_Password[20];
	int iAdmin_Rent;//借书数量
	int iAdmin_Book[30];//借书序号
};




class Book_Operator
{
	public:
	void Add_Book();
	char * Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);
};

void Book_Operator::Add_Book()
	{
		char String_Roll[50];//无意义
		char String_1[15];//存储图书的编号
		int intString_1;//图书编号转化为int型整数存储于此
	    char cBook_Name[40];
	    int iBook_N;
	    int iBook_Price;
	Books_Information New_Book;
		cout << "请输入书名" << endl;
		cin >> cBook_Name;
		cout << "请输入数量" << endl;
		cin >> iBook_N;
		cout << "请输入价格" << endl;
		cin >> iBook_Price;
		//查询编号
		fstream file;
		file.open("Book.csv", ios::in | ios::app);
		if(file.fail())
		{
			cout<<"文件打开失败"<<endl;
			exit(1); 
		}
		file.getline(String_Roll, 100);
		while (!file.eof())
		{
			
			Get_Data(1, String_Roll, String_1);
			intString_1 = atoi(String_1);
			file.getline(String_Roll, 100);
		}
		intString_1++;
		cout<<"\n"<<intString_1<<","<<iBook_N<<","<<cBook_Name<<","<<iBook_Price;
		file.seekp(ios::end);
		file<<intString_1<<","<<iBook_N<<","<<cBook_Name<<","<<iBook_Price;
		cout<<"最后一行的编号为："<<intString_1 <<endl;
		file.close();
};
char * Book_Operator::Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData)
	{
		int i = 0;
		//找到第iflag-1个逗号
		if (NULL == szLine && NULL == szData)
		{
			cout << "error! fun:Get_Data: the wrong line";
			return 0;
		}
		while (iflag != 1)
		{
			while (1)//跳转到下一个逗号
			{
				if (*(szLine + i) == ',')//如果发现逗号则break
				{
					break;
				}
				else if (*(szLine + i) == '\0')//如果发现已经结尾了，说明iflag输入错误或者szline出错
				{
					cout << "error! fun:Get_Data: the wrong input str" << endl;
					system("PAUSE");
					return 0;
				}
				i++;
			}
			i++;//跳过当前逗号
			iflag--;
		}
		int j = 0;
		//复制两个逗号之间的内容到szData中
		while (*(szLine + i) != ',' && *(szLine + i) != '\0')
		{
			*(szData + j) = *(szLine + i);
			i++;
			j++;
		}
		*(szData + j) = '\0';//添加字符串结尾符号
		return szData;
	}
int main(void){
	Book_Operator b;
	b.Add_Book();
	system("pause");
	return 0;
}
