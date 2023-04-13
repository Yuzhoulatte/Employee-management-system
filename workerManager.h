#pragma once
#include<iostream>
using namespace std;
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include<fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
    //���캯��
    WorkerManager();

    //չʾ�˵�
    void Show_Menu();

    //�˳�ϵͳ
    void ExitSystem();

    //��¼�ļ�������
    int m_EmpNum;

    //Ա������ָ��
    Worker ** m_EmpArray;

    //���ְ��
    void Add_Emp();

    //�����ļ�
    void save();

    //��־�ļ��Ƿ�Ϊ��
    bool m_FileIsEmpty;

    //ͳ���ļ�������
    int get_EmpNum();

    //��ʼ��Ա��
    void init_Emp();

    //��ʾְ��
    void Show_Emp();

    //����ְ������ж�ְ���Ƿ���ڣ������ڷ���ְ����������λ�ã������ڷ���-1
    int IsExist(int id);

    //ɾ��ְ��
    void Del_Emp();

    //�޸�ְ��
    void Mod_Emp();

    //����ְ��
    void Find_Emp();

    //����ְ��
    void Sort_Emp();

    //����ļ�
    void Clean_File();

    //��������
    ~WorkerManager();
};