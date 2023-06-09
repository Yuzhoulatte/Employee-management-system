#pragma once
#include<iostream>
using namespace std;

//职工抽象基类
class Worker
{
public:
    //显示个人信息
    virtual void ShowInfo() = 0;
    //获取岗位名称
    virtual string GetDeptName() = 0;

    int m_Id; //职工编号
    string m_Name; //职工姓名
    int m_DeptId; //职工所在部门编号
};