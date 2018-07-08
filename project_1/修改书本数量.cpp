#include <iostream>
#include<cstring> 
#include <string>//新加 
#include <stdio.h>//新加
#include <fstream>
#include <sstream>//新加 
#define IN_PARAM
#define OUT_PARAM
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
	char *Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline);

public:
 void Reverse_Book_Number();//修改书的数量 
 char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);//来自用户操作类，合并时需要 
 void Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange = NULL, int IN_PARAM iBook = 0);
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

void Book_Operator::Reverse_Book_Number()
{//Book_Operator对书文件的指针定义为file 
    fstream file;
    int iBook_Number; //要检索的书的编号 
    int iBook_N;//修改的数量
    stringstream stream_1;
    stringstream stream_2;
    cout << "请输入书的编号：";
	cin >> iBook_Number;
	cout << "您要增加或减少的数量为（若减少，请输-号）：";
	cin >> iBook_N;
    char String_1[15];//第一重循环用，存储文件中读取的书的号码 
    int intString_1;
    char String_2[15];
    int intString_2;
	char String_3[15];//第二重循环用，存储文件中读取的书的数量 
	char String_Roll[60];//getline用，无意义 
	int Store_Book_N;//从文件读取时，书的数量存放于此 
	file.open("Book.csv", ios::in|ios::out);
	if( file.fail() )
	{
		cout << "打开书文件失败1" << endl;
		exit(1);
	}
	file.seekg(0);//定位于第一行，开始检索 
    file.getline(String_Roll, 60);
while( !file.eof() )
{
	Get_Data(1, String_Roll,String_1);
	intString_1 = atoi(String_1);//将 String_1转化为int型 
	if(iBook_Number == intString_1)//如果相等，执行第二重循环，将书的数量读取，修改，再写入文件 
	{   
	    Get_Data(2, String_Roll, String_2);
		stream_2 << String_2;//将 String_2转化为int型
	    stream_2 >> intString_2;
		while((intString_2 + iBook_N)<0)
		{
			cout << "减少的数量超过下限"<<intString_2+iBook_N<<"个"<<endl;
			cout << "请重输您要增减的数量（若减少，请输-号）：";
			cin >> iBook_N;
		};
	Store_Book_N = (intString_2 + iBook_N);//将书的数量加或者减去 iBook_N个 
	sprintf(String_3, "%d", Store_Book_N);//将 Store_Book_N转化为string3
//iflag =：
	Reset_User(2,String_1,String_3);
	//将String_3写入文件 
	
		 break;//跳出while循环 
	};//当执行完修改完毕，break跳出循环 
	file.getline(String_Roll, 60);
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

char * Book_Operator::Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline)
{
	int i_L = 0;//szLine指针位置
	int i_O = 0;//Outine指针位置
	int i_C = 0;//Change指针位置
	if (NULL == szLine && NULL == szChange)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	//找到第iflag-1个逗号,并把逗号前的内容写入字符串
	while (iflag != 1)
	{
		while (1)//跳转到下一个逗号
		{
			szOutline[i_O] = szLine[i_L];//写入输出字符串
			if (*(szLine + i_L) == ',')//如果发现逗号则break
			{
				break;
			}
			else if (*(szLine + i_L) == '\0')//如果发现已经结尾了，说明iflag输入错误或者szline出错
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}

			i_L++;
			i_O++;
		}
		i_L++;//跳过当前逗号
		i_O++;
		iflag--;
	}
	//添加想要修改的字符串
	while (szChange[i_C] != '\0')
	{
		szOutline[i_O] = szChange[i_C];
		i_O++;
		i_C++;
		
	}
	//把szLine指针位置移到下一个逗号
	while (1)//跳转到下一个逗号
	{
		if (*(szLine + i_L) == ',')//如果发现逗号则break
		{
			break;
		}
		else if (*(szLine + i_L) == '\0')//如果发现已经结尾了，说明是最后一个数据，后面无须再添加
		{
			break;
		}
		i_L++;
	}
	//写入之后的字符
	while (szLine[i_L] != '\0' && szLine[i_L] != '\n')
	{
		szOutline[i_O] = szLine[i_L];
		i_O++;
		i_L++;
	}
	//添加末尾的回车和结尾
	szOutline[i_O] = '\n';
	szOutline[i_O] = '\0';
	return szOutline;
}

void Book_Operator::Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange, int IN_PARAM iBook)
{
	fstream Old_File("Book.csv", ios::in);
	//打开文件
	if (Old_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	fstream Trans_File("Book_Trans.csv", ios::out);
	if (Trans_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}

	//找到想要找到的用户,并把前面的用户信息写入中转文件
	Old_File.seekg(0);
	Trans_File.seekp(0);
	char cLine[1024];//存储一行信息
	char cStr[40];//存储账号
	int findif = 0;//判断是否找到用户ID
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)//如果找到该用户信息，跳出
		{
			findif = 1;
			break;
		}
		Trans_File << cLine << '\n';
	}

	if (findif == 0)
	{
		cout << "找不到ID" << endl;
		return;
	}

	//对得到的一行进行修改
	if (iflag == 0)//删除整行信息
	{
		Old_File.getline(cLine, 1024);
	}
	else if (iflag == 3)//改变书的信息
	{
		Get_Data(4, cLine, cStr);//得到借书信息
		//这里未完善
	}
	else//改变指定信息
	{
		char cLine_changed[1024];//用于存储改变后的cLine
		Change_Data(iflag, cLine, szChange,cLine_changed);//改变指定数据
		Trans_File << cLine_changed << '\n';//输入到中转文件
		Old_File.getline(cLine, 1024);//读取下一行
	}

	//把之后的用户信息写入中转文件
	Trans_File << cLine << '\n';
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Trans_File << cLine << '\n';
	}
	Old_File.close();
	Trans_File.close();

	//从中转文件写入原文件
	Old_File.open("Book.csv", ios::out);
	if (Old_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	Trans_File.open("Book_Trans.csv", ios::in);
	if (Trans_File.fail())
	{
		cout << "文件打开失败!" << endl;
		system("PAUSE");
		exit(1);
	}
	Old_File.seekp(0);
	Trans_File.seekg(0);
	while (!Trans_File.eof())
	{
		Trans_File.getline(cLine, 1024);
		Old_File << cLine << '\n';
	}
	Trans_File.close();
	Old_File.close();
}

int main(void){
	Book_Operator e;
	e.Reverse_Book_Number();
} 

