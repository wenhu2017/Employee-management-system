#pragma once
#include "worker.h"
#include <iostream>
#include <string>
using namespace std;

class Manager :
    public Worker
{
public:

    Manager(int id, string name, int dId);


    // ͨ�� Worker �̳�
    virtual void showInfo() override;

    virtual string getDeptName() override;

};

