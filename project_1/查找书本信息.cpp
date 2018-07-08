#include <iostream>
#include<string.h> 
#include <string>//新加 
#include <stdio.h>//新加
#include <fstream>
#include <sstream>//新加 
#define IN_PARAM
#define OUT_PARAM
using std::string;
using namespace std;
struct Books_Imformation//书信息
{//此处顺序改变 
	int iBook_Number;//修改为int
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
 void Reverse_Book_Number();//修改书的数量 
 char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);//来自用户操作类，合并时需要 
 void Find_Book();
};

class Infor_Operator
{

};





/*class User_Operator //用户基类
{
public:
	virtual void Run();//调用以下函数
	void Borrow_Book();
	void Return_Book();
	void Search_Book();
	void Cmp_Password();//对比密码
};

class Book_Admin : public User_Operator
{
public:
	void Run();
	void Add_Book();//增加文件里的书
	void Delete_Book();//删除文件里的书
	void Revise_Book();//修改文件里的书
};

class Sys_Admin : public Book_Admin
{
public:
	void Run();
	//用于管理账号密码
	void Add_User(int flag);//增加用户信息
	void Delete_User(int flag);//删除用户信息
	void Revise_User(int flag);//修改用户信息
};

//
void test();*/

void Book_Operator::Find_Book()
{//Book_Operator对书文件的指针定义为file 
    char cLine[100];//存储一行信息
    char cBook_Number[20];//保存从文件读取的书的编号 
    char cBook_Number_In[20];//用户输入的书的编号 
    char cBook_Name[20];//保存从文件读取的书的名字 
    char cBook_Name_In[20];//用户输入的书的名字
    int Method;//查询方式 (1/2)
    fstream file; 
	file.open("Book.csv", ios::in|ios::out);
	if(file.fail())
	{
		cout << "打开书文件失败1" << endl;
		exit(1);
	}
	file.seekg(0);//定位于第一行，开始检索 
	cout << "请问您要采用何种方式查询（1编号/2书名）:" << endl;
	cin >> Method;
	switch (Method)
	{
	case 1://根据编号查询书籍信息 
	file.getline(cLine, 100);
	cout << "请输入编号：";
	cin >> cBook_Number_In;
	while (!file.eof())//当文件未到结尾
	{
		
	    Get_Data(1, cLine,cBook_Number);
		if (strcmp(cBook_Number, cBook_Number_In) != 0)
		{
			file.getline(cLine, 100);
			Get_Data(1, cLine, cBook_Number);
		}  
		else
		{
			break;
		}
	}
	cout << "这本书的信息为(图书编号|图书数量|图书名字|图书价格) " << cLine <<endl;
	system("pause");
		break;
		
	case 2://根据书名查询书籍信息
		file.getline(cLine, 100);
	cout << "请输入书名：";
	cin >> cBook_Name_In;
	while (!file.eof())//当文件未到结尾
	{
		
	    Get_Data(3, cLine,cBook_Name);
		if (strcmp(cBook_Name, cBook_Name_In) != 0)
		{
			file.getline(cLine, 100);
			Get_Data(3, cLine, cBook_Name);
		}  
		else
		{
			break;
		}
	}
	cout << "这本书的信息为(图书编号|图书数量|图书名字|图书价格) " << cLine <<endl;
	system("pause");
		break;
	}
file.close();
}
//传入需要的第几个元素iflag，得到的一行字符串szline，返回第iflag个字符串szData（返回值可以不用管）
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
	Book_Operator e;
	e.Find_Book();
} 
