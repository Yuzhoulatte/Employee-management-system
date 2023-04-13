#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

//普通员工类
class Employee : public Worker
{
public:
    Employee(int id, string name, int dId);

    //显示个人信息
    virtual void ShowInfo();
    //获取岗位名称
    virtual string GetDeptName();
};