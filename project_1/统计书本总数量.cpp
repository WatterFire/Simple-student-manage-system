#include <iostream>
#include <string>//�¼� 
#include <stdio.h>//�¼�
#include <fstream>
#include <sstream>//�¼� 
#define IN_PARAM
#define OUT_PARAM
using namespace std;
struct Books_Imformation//����Ϣ
{//�˴�˳��ı� 
	int iBook_Number;//�޸�Ϊint
	int iBook_N;//����������
	char cBook_Name[40];
	int iBook_Price;
};

struct Stu_Imformation//ѧ����Ϣ
{
	char cStudent_Number[20];
	char cStudent_Password[20];
	int iStudent_Rent;//��������
	char *szStudent_Book[10];//��������
};

struct Tea_Imformation//��ʦ��Ϣ
{
	char cTeacher_Number[20];
	char cTeacher_Password[20];
	int iTeacher_Rent;//��������
	int iStudent_Book[30];//�������
};

struct Admin_Imformation//����Ա��Ϣ
{
	char cAdmin_Number[20];
	char cAdmin_Password[20];
	int iAdmin_Rent;//��������
	int iAdmin_Book[30];//�������
};


class Book_Operator
{
public:
 char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);//�����û������࣬�ϲ�ʱ��Ҫ 
 void Get_Total_Number();// ��ȡ��������� 
};

class Infor_Operator
{

};





/*class User_Operator //�û�����
{
public:
	virtual void Run();//�������º���
	void Borrow_Book();
	void Return_Book();
	void Search_Book();
	void Cmp_Password();//�Ա�����
};

class Book_Admin : public User_Operator
{
public:
	void Run();
	void Add_Book();//�����ļ������
	void Delete_Book();//ɾ���ļ������
	void Revise_Book();//�޸��ļ������
};

class Sys_Admin : public Book_Admin
{
public:
	void Run();
	//���ڹ����˺�����
	void Add_User(int flag);//�����û���Ϣ
	void Delete_User(int flag);//ɾ���û���Ϣ
	void Revise_User(int flag);//�޸��û���Ϣ
};

//
void test();*/

void Book_Operator::Get_Total_Number()
{//Book_Operator�����ļ���ָ�붨��Ϊfile 
    fstream file;
    char String_1[15];//�洢�ļ��ж�ȡ����ĺ��� 
    int intString_1;// String_1ת��Ϊ��int�ͳ��� 
	char String_Roll[60];//getline�ã������� 
	int Store_Book_N;//���ļ���ȡʱ�������������ڴ� 
	
	file.open("Book.csv", ios::in|ios::out);
	if( file.fail() )
	{
		cout << "�����ļ�ʧ��1" << endl;
		exit(1);
	}
	
	file.seekg(0);//��λ�ڵ�һ�У���ʼ���� 
    file.getline(String_Roll, 60);
while(!file.eof())
{
	Get_Data(2, String_Roll, String_1);
	intString_1 = atoi(String_1);//�� String_1ת��Ϊint�� 
	Store_Book_N += intString_1;//�ۼ� 
    file.getline(String_Roll, 60);
}
file.close();

cout << "���������Ϊ��" << Store_Book_N << endl;
system( "pause" );
}
//������Ҫ�ĵڼ���Ԫ��iflag���õ���һ���ַ���szline�����ص�iflag���ַ���szData������ֵ���Բ��ùܣ�
char * Book_Operator::Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData)
{
	int i = 0;
	//�ҵ���iflag-1������
	if (NULL == szLine && NULL == szData)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	while (iflag != 1)
	{
		while (1)//��ת����һ������
		{
			if (*(szLine + i) == ',')//������ֶ�����break
			{
				break;
			}
			else if (*(szLine + i) == '\0')//��������Ѿ���β�ˣ�˵��iflag����������szline����
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}
			i++;
		}
		i++;//������ǰ����
		iflag--;
	}
	int j = 0;
	//������������֮������ݵ�szData��
	while (*(szLine + i) != ',' && *(szLine + i) != '\0')
	{
		*(szData + j) = *(szLine + i);
		i++;
		j++;
	}
	*(szData + j) = '\0';//����ַ�����β����
	return szData;
}

int main(void){
	Book_Operator e;
	e.Get_Total_Number();
} 
