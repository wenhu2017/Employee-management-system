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


    // Í¨¹ý Worker ¼Ì³Ð
    virtual void showInfo() override;

    virtual string getDeptName() override;

};

