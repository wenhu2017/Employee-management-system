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
	// 构造函数
	workerManager();
	
	// 显示菜单
	void Show_Menu();

	// 退出系统
	void exitSystem();

	// 增加职工
	void add_Emp();

	//保存文件
	void save();

	// 析构函数
	~workerManager();

	//文件有数据时初始化员工
	int init_emp();

	// 显示职工信息
	void show_Emp();

	//统计文件中人数
	int get_empNum();

	// 删除职工
	void del_Emp();

	// 判断职工是否存在
	int  isExist(int id);

	// 更新职工数据
	void mod_Emp();

	// 查找职工
	void find_Emp();

	// 排序
	void sort_Emp();

	// 清空数据
	void clear_File();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//标志文件是否为空
	bool m_FileIsEmpty;
	
};

