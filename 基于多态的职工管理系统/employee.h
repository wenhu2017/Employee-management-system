#pragma once
#include "worker.h"
class Employee : public Worker
{
public:

    // Í¨¹ý worker ¼Ì³Ð
    virtual void showInfo() override;
    virtual string getDeptName() override;

    Employee(int id, string name, int dId);
};

