#pragma once
#include "worker.h"
class Employee : public Worker
{
public:

    // ͨ�� worker �̳�
    virtual void showInfo() override;
    virtual string getDeptName() override;

    Employee(int id, string name, int dId);
};

