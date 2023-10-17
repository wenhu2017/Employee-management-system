#include <iostream>
#include <string>
using namespace std;

#include "workerManager.h";
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

class Person
{

};

void testA()
{

    
    // 测试代码
    Worker* worker = NULL;
    worker = new Employee(1, "张三", 1);
    /*worker->showInfo();
    delete worker;
    worker = new Manager(2, "李四", 2);
    worker->showInfo();
    delete worker;
    worker = new Boss(3, "王五", 3);
    worker->showInfo();*/
}

int main()
{
    //testA();
    // 示例化管理者对象
    workerManager wm;
    int choice = 0;

    while (true)
    {
        //显示菜单
        wm.Show_Menu();
        cout << "请输入您的选择：" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: // 退出系统
            wm.exitSystem(); 
            break;
        case 1: // 增加职工
            wm.add_Emp();
            break;
        case 2: // 显示职工
            wm.show_Emp();
            break;
        case 3: // 删除职工
            wm.del_Emp();
            break;
        case 4: // 修改职工
            wm.mod_Emp();
            break;
        case 5: // 查找职工
            wm.find_Emp();
            break;
        case 6: // 排序职工
            wm.sort_Emp();
            break;
        case 7: // 清空文档
            wm.clear_File();
            break;
        default:
            system("cls"); //清空屏幕
            break;
        }
    }
    
    return 0;
}


