#include "workerManager.h"

workerManager::workerManager()
{
	// 1. 文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		return;
	} 
	// 2.文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;

		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		return;
	}
	// 文件存在,并且有数据
	int num = this->get_empNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	// 开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	// 把文件数据放入空间
	this->init_emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		this->m_EmpArray[i]->showInfo();
	}*/
}

void workerManager::Show_Menu()
{
	cout << "****************************" << endl;
	cout << "*** 欢迎使用职工管理系统 ***" << endl;
	cout << "****** 0.退出管理程序 ******" << endl;
	cout << "****** 1.增加职工信息 ******" << endl;
	cout << "****** 2.显示职工信息 ******" << endl;
	cout << "****** 3.删除离职职工 ******" << endl;
	cout << "****** 4.修改职工信息 ******" << endl;
	cout << "****** 5.查找职工信息 ******" << endl;
	cout << "****** 6.按照编号排序 ******" << endl;
	cout << "****** 7.清空所有文档 ******" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

void workerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void workerManager::add_Emp()
{
	cout << "请输入添加职工数量：" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		// 添加
		int newSize = this->m_EmpNum + addNum;
		// 创建空间
		Worker** newSpace = new Worker* [newSize];

		//将原来空间下数据,拷贝到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// 添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新员工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新员工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//将创建职工,保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
			
		}
		//释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;
		//更新新空间的人数
		this->m_EmpNum = newSize;

		cout << "成功添加" << addNum << "名新职工" << endl;
		// 保存文件
		this->save();

		this->m_FileIsEmpty = false;
	}
	else {
		cout << "输入有误" << endl;
	}
	//按任意键后, 清屏回到上级目录
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
		cout << "没有职工信息" << endl;
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
		cout << "没有记录数据" << endl;
	}
	else {
		cout << "请输入需要删除职工的编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			// 更新数据
			this->m_EmpNum--;
			// 保存文件
			this->save();
		}
		else {
			cout << "职工不存在" << endl;
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
		cout << "记录数据为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;
		int index = this->isExist(id);
		if (index != -1)
		{
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查找：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请选择新岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//将创建职工,保存到数组中
			this->m_EmpArray[index] = worker;
			//保存数据
			this->save();
		}
		else {
			cout << "职工不存在" << endl;
		}
	}
	

	system("pause");
	system("cls");
}

void workerManager::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录数据为空！" << endl;
	}
	else {
		cout << "请选择查找方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "请输入职工编号：" << endl;
			int id;
			cin >> id;

			int index = this->isExist(id);
			if (index != -1)
			{
				cout << "查询成功：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
				cout << "查无此人" << endl;
			}

		}
		else if (select == 2)
		{
			cout << "请输入职工姓名：" << endl;
			string name;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name) {
					if (!flag)
					{
						cout << "查询成功：" << endl;
					}

					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}

			if (!flag)
			{
				cout << "查无此人" << endl;
			}

		}
		else {
			cout << "输入有误" << endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录数据为空！" << endl;
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

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
					cout << "输入有误！" << endl;
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}
		}

		cout << "排序成功，排序后结果为：" << endl;

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
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

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
		cout << "清空成功！" << endl;
	}
	

	system("pause");
	system("cls");
}
