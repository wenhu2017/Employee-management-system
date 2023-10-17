#include "workerManager.h"

workerManager::workerManager()
{
	// 1. �ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;

		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		return;
	} 
	// 2.�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;

		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		return;
	}
	// �ļ�����,����������
	int num = this->get_empNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	// ���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	// ���ļ����ݷ���ռ�
	this->init_emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}*/
}

void workerManager::Show_Menu()
{
	cout << "****************************" << endl;
	cout << "*** ��ӭʹ��ְ������ϵͳ ***" << endl;
	cout << "****** 0.�˳�������� ******" << endl;
	cout << "****** 1.����ְ����Ϣ ******" << endl;
	cout << "****** 2.��ʾְ����Ϣ ******" << endl;
	cout << "****** 3.ɾ����ְְ�� ******" << endl;
	cout << "****** 4.�޸�ְ����Ϣ ******" << endl;
	cout << "****** 5.����ְ����Ϣ ******" << endl;
	cout << "****** 6.���ձ������ ******" << endl;
	cout << "****** 7.��������ĵ� ******" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

void workerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void workerManager::add_Emp()
{
	cout << "���������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		// ���
		int newSize = this->m_EmpNum + addNum;
		// �����ռ�
		Worker** newSpace = new Worker* [newSize];

		//��ԭ���ռ�������,�������¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// ���������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����Ա����ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����Ա��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//������ְ��,���浽������
			newSpace[this->m_EmpNum + i] = worker;
			
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		//�����¿ռ������
		this->m_EmpNum = newSize;

		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		// �����ļ�
		this->save();

		this->m_FileIsEmpty = false;
	}
	else {
		cout << "��������" << endl;
	}
	//���������, �����ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

int workerManager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int index = 0;
	int id;
	string name;
	int dId;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{

		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
	return index;
}

void workerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "û��ְ����Ϣ" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

int workerManager::get_empNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int num = 0;
	int id;
	string name;
	int dId;
	while (ifs>> id && ifs >> name && ifs>> dId)
	{
		num++;
	}

	ifs.close();
	return num;
}

void workerManager::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "û�м�¼����" << endl;
	}
	else {
		cout << "��������Ҫɾ��ְ���ı�ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			// ��������
			this->m_EmpNum--;
			// �����ļ�
			this->save();
		}
		else {
			cout << "ְ��������" << endl;
		}
	}

	system("pause");
	system("cls");
}

int workerManager::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void workerManager::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼����Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "���ң�" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;
			cout << "��������������" << endl;
			cin >> newName;
			cout << "��ѡ���¸�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			//������ְ��,���浽������
			this->m_EmpArray[index] = worker;
			//��������
			this->save();
		}
		else {
			cout << "ְ��������" << endl;
		}
	}
	

	system("pause");
	system("cls");
}

void workerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼����Ϊ�գ�" << endl;
	}
	else {
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "������ְ����ţ�" << endl;
			int id;
			cin >> id;

			int index = this->isExist(id);
			if (index != -1)
			{
				cout << "��ѯ�ɹ���" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "���޴���" << endl;
			}

		}
		else if (select == 2)
		{
			cout << "������ְ��������" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name) {
					if (!flag)
					{
						cout << "��ѯ�ɹ���" << endl;
					}

					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}

			if (!flag)
			{
				cout << "���޴���" << endl;
			}

		}
		else {
			cout << "��������" << endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼����Ϊ�գ�" << endl;
	}
	else {
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i+1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
					
				}
				else if (select == 2) {
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else {
					cout << "��������" << endl;
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "����ɹ����������Ϊ��" << endl;

		this->save();

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void workerManager::clear_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
			}

			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	

	system("pause");
	system("cls");
}
