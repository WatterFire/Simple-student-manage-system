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
struct Books_Imformation//����Ϣ
{
	int iBook_Number;
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
	void Add_Book();
	char * Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);
};

void Book_Operator::Add_Book()
	{
		char String_Roll[50];//������
		char String_1[15];//�洢ͼ��ı��
		int intString_1;//ͼ����ת��Ϊint�������洢�ڴ�
	    char cBook_Name[40];
	    int iBook_N;
	    int iBook_Price;
	Books_Information New_Book;
		cout << "����������" << endl;
		cin >> cBook_Name;
		cout << "����������" << endl;
		cin >> iBook_N;
		cout << "������۸�" << endl;
		cin >> iBook_Price;
		//��ѯ���
		fstream file;
		file.open("Book.csv", ios::in | ios::app);
		if(file.fail())
		{
			cout<<"�ļ���ʧ��"<<endl;
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
		cout<<"���һ�еı��Ϊ��"<<intString_1 <<endl;
		file.close();
};
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
	Book_Operator b;
	b.Add_Book();
	system("pause");
	return 0;
}
