#include <iostream>
#include<string.h> 
#include <string>//�¼� 
#include <stdio.h>//�¼�
#include <fstream>
#include <sstream>//�¼� 
#define IN_PARAM
#define OUT_PARAM
using std::string;
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
 void Reverse_Book_Number();//�޸�������� 
 char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);//�����û������࣬�ϲ�ʱ��Ҫ 
 void Find_Book();
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

void Book_Operator::Find_Book()
{//Book_Operator�����ļ���ָ�붨��Ϊfile 
    char cLine[100];//�洢һ����Ϣ
    char cBook_Number[20];//������ļ���ȡ����ı�� 
    char cBook_Number_In[20];//�û��������ı�� 
    char cBook_Name[20];//������ļ���ȡ��������� 
    char cBook_Name_In[20];//�û�������������
    int Method;//��ѯ��ʽ (1/2)
    fstream file; 
	file.open("Book.csv", ios::in|ios::out);
	if(file.fail())
	{
		cout << "�����ļ�ʧ��1" << endl;
		exit(1);
	}
	file.seekg(0);//��λ�ڵ�һ�У���ʼ���� 
	cout << "������Ҫ���ú��ַ�ʽ��ѯ��1���/2������:" << endl;
	cin >> Method;
	switch (Method)
	{
	case 1://���ݱ�Ų�ѯ�鼮��Ϣ 
	file.getline(cLine, 100);
	cout << "�������ţ�";
	cin >> cBook_Number_In;
	while (!file.eof())//���ļ�δ����β
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
	cout << "�Ȿ�����ϢΪ(ͼ����|ͼ������|ͼ������|ͼ��۸�) " << cLine <<endl;
	system("pause");
		break;
		
	case 2://����������ѯ�鼮��Ϣ
		file.getline(cLine, 100);
	cout << "������������";
	cin >> cBook_Name_In;
	while (!file.eof())//���ļ�δ����β
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
	cout << "�Ȿ�����ϢΪ(ͼ����|ͼ������|ͼ������|ͼ��۸�) " << cLine <<endl;
	system("pause");
		break;
	}
file.close();
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
	e.Find_Book();
} 
