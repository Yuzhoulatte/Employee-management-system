#include "employee.h"

Employee::Employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
}

//��ʾ������Ϣ
void Employee::ShowInfo()
{
    cout << "ְ����ţ�" << this->m_Id
        << "\tְ��������" << this->m_Name
        << "\t��λ��" << this->GetDeptName()
        << "\t��λְ����ɾ�������������" << endl;
}

//��ȡ��λ����
string Employee::GetDeptName()
{
    return string("��ͨԱ��");
}