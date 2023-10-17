#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empFile.txt"
#include <string>	

class workerManager
{

public:
	// ���캯��
	workerManager();
	
	// ��ʾ�˵�
	void Show_Menu();

	// �˳�ϵͳ
	void exitSystem();

	// ����ְ��
	void add_Emp();

	//�����ļ�
	void save();

	// ��������
	~workerManager();

	//�ļ�������ʱ��ʼ��Ա��
	int init_emp();

	// ��ʾְ����Ϣ
	void show_Emp();

	//ͳ���ļ�������
	int get_empNum();

	// ɾ��ְ��
	void del_Emp();

	// �ж�ְ���Ƿ����
	int  isExist(int id);

	// ����ְ������
	void mod_Emp();

	// ����ְ��
	void find_Emp();

	// ����
	void sort_Emp();

	// �������
	void clear_File();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
	
};

