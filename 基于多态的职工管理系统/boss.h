#pragma once
#include "worker.h"
#include <iostream>
#include <string>
using namespace std;

class Boss :
    public Worker
{
public:
    Boss(int id, string name, int dId);

    // Í¨¹ý Worker ¼Ì³Ð
    virtual void showInfo() override;

    virtual string getDeptName() override;

};

 