#include "employee.h"
#include <iostream>
#include <string>
using namespace std;

Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

void Employee::showInfo()
{

    cout << "ְ����ţ�" << this->m_Id
        << "\tְ��������" << this->m_Name
        << "\t��λ��" << this->getDeptName()
        << "\t��λְ����ɾ���ָ�ɵ�����"
        << endl;
}

string Employee::getDeptName()
{
    return string("Ա��");
}





