#pragma once
#include <string>
using namespace std;

// ְ���������
class Worker
{
public:
	// ��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;


	int m_Id; // ְ��ID
	string m_Name; // ְ����Ϣ
	int m_DeptId; // ְ�����ڲ������Ʊ��
};

