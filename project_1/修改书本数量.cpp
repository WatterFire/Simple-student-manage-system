#include <iostream>
#include<cstring> 
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
	char *Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline);

public:
 void Reverse_Book_Number();//�޸�������� 
 char *Get_Data(IN_PARAM int iflag, IN_PARAM char *szLine, OUT_PARAM char *szData);//�����û������࣬�ϲ�ʱ��Ҫ 
 void Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange = NULL, int IN_PARAM iBook = 0);
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

void Book_Operator::Reverse_Book_Number()
{//Book_Operator�����ļ���ָ�붨��Ϊfile 
    fstream file;
    int iBook_Number; //Ҫ��������ı�� 
    int iBook_N;//�޸ĵ�����
    stringstream stream_1;
    stringstream stream_2;
    cout << "��������ı�ţ�";
	cin >> iBook_Number;
	cout << "��Ҫ���ӻ���ٵ�����Ϊ�������٣�����-�ţ���";
	cin >> iBook_N;
    char String_1[15];//��һ��ѭ���ã��洢�ļ��ж�ȡ����ĺ��� 
    int intString_1;
    char String_2[15];
    int intString_2;
	char String_3[15];//�ڶ���ѭ���ã��洢�ļ��ж�ȡ��������� 
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
while( !file.eof() )
{
	Get_Data(1, String_Roll,String_1);
	intString_1 = atoi(String_1);//�� String_1ת��Ϊint�� 
	if(iBook_Number == intString_1)//�����ȣ�ִ�еڶ���ѭ���������������ȡ���޸ģ���д���ļ� 
	{   
	    Get_Data(2, String_Roll, String_2);
		stream_2 << String_2;//�� String_2ת��Ϊint��
	    stream_2 >> intString_2;
		while((intString_2 + iBook_N)<0)
		{
			cout << "���ٵ�������������"<<intString_2+iBook_N<<"��"<<endl;
			cout << "��������Ҫ�����������������٣�����-�ţ���";
			cin >> iBook_N;
		};
	Store_Book_N = (intString_2 + iBook_N);//����������ӻ��߼�ȥ iBook_N�� 
	sprintf(String_3, "%d", Store_Book_N);//�� Store_Book_Nת��Ϊstring3
//iflag =��
	Reset_User(2,String_1,String_3);
	//��String_3д���ļ� 
	
		 break;//����whileѭ�� 
	};//��ִ�����޸���ϣ�break����ѭ�� 
	file.getline(String_Roll, 60);
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

char * Book_Operator::Change_Data(IN_PARAM int iflag, IN_PARAM char * szLine, IN_PARAM char * szChange, OUT_PARAM char * szOutline)
{
	int i_L = 0;//szLineָ��λ��
	int i_O = 0;//Outineָ��λ��
	int i_C = 0;//Changeָ��λ��
	if (NULL == szLine && NULL == szChange)
	{
		cout << "error! fun:Get_Data: the wrong line";
		return 0;
	}
	//�ҵ���iflag-1������,���Ѷ���ǰ������д���ַ���
	while (iflag != 1)
	{
		while (1)//��ת����һ������
		{
			szOutline[i_O] = szLine[i_L];//д������ַ���
			if (*(szLine + i_L) == ',')//������ֶ�����break
			{
				break;
			}
			else if (*(szLine + i_L) == '\0')//��������Ѿ���β�ˣ�˵��iflag����������szline����
			{
				cout << "error! fun:Get_Data: the wrong input str" << endl;
				system("PAUSE");
				return 0;
			}

			i_L++;
			i_O++;
		}
		i_L++;//������ǰ����
		i_O++;
		iflag--;
	}
	//�����Ҫ�޸ĵ��ַ���
	while (szChange[i_C] != '\0')
	{
		szOutline[i_O] = szChange[i_C];
		i_O++;
		i_C++;
		
	}
	//��szLineָ��λ���Ƶ���һ������
	while (1)//��ת����һ������
	{
		if (*(szLine + i_L) == ',')//������ֶ�����break
		{
			break;
		}
		else if (*(szLine + i_L) == '\0')//��������Ѿ���β�ˣ�˵�������һ�����ݣ��������������
		{
			break;
		}
		i_L++;
	}
	//д��֮����ַ�
	while (szLine[i_L] != '\0' && szLine[i_L] != '\n')
	{
		szOutline[i_O] = szLine[i_L];
		i_O++;
		i_L++;
	}
	//���ĩβ�Ļس��ͽ�β
	szOutline[i_O] = '\n';
	szOutline[i_O] = '\0';
	return szOutline;
}

void Book_Operator::Reset_User(IN_PARAM int iflag, IN_PARAM char * szID, IN_PARAM char * szChange, int IN_PARAM iBook)
{
	fstream Old_File("Book.csv", ios::in);
	//���ļ�
	if (Old_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}
	fstream Trans_File("Book_Trans.csv", ios::out);
	if (Trans_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}

	//�ҵ���Ҫ�ҵ����û�,����ǰ����û���Ϣд����ת�ļ�
	Old_File.seekg(0);
	Trans_File.seekp(0);
	char cLine[1024];//�洢һ����Ϣ
	char cStr[40];//�洢�˺�
	int findif = 0;//�ж��Ƿ��ҵ��û�ID
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Get_Data(1, cLine, cStr);
		if (strcmp(cStr, szID) == 0)//����ҵ����û���Ϣ������
		{
			findif = 1;
			break;
		}
		Trans_File << cLine << '\n';
	}

	if (findif == 0)
	{
		cout << "�Ҳ���ID" << endl;
		return;
	}

	//�Եõ���һ�н����޸�
	if (iflag == 0)//ɾ��������Ϣ
	{
		Old_File.getline(cLine, 1024);
	}
	else if (iflag == 3)//�ı������Ϣ
	{
		Get_Data(4, cLine, cStr);//�õ�������Ϣ
		//����δ����
	}
	else//�ı�ָ����Ϣ
	{
		char cLine_changed[1024];//���ڴ洢�ı���cLine
		Change_Data(iflag, cLine, szChange,cLine_changed);//�ı�ָ������
		Trans_File << cLine_changed << '\n';//���뵽��ת�ļ�
		Old_File.getline(cLine, 1024);//��ȡ��һ��
	}

	//��֮����û���Ϣд����ת�ļ�
	Trans_File << cLine << '\n';
	while (!Old_File.eof())
	{
		Old_File.getline(cLine, 1024);
		Trans_File << cLine << '\n';
	}
	Old_File.close();
	Trans_File.close();

	//����ת�ļ�д��ԭ�ļ�
	Old_File.open("Book.csv", ios::out);
	if (Old_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
		system("PAUSE");
		exit(1);
	}
	Trans_File.open("Book_Trans.csv", ios::in);
	if (Trans_File.fail())
	{
		cout << "�ļ���ʧ��!" << endl;
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

