#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

//��ͨԱ����
class Employee : public Worker
{
public:
    Employee(int id, string name, int dId);

    //��ʾ������Ϣ
    virtual void ShowInfo();
    //��ȡ��λ����
    virtual string GetDeptName();
};