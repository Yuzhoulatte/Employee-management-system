#include "workerManager.h"

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //�ļ�������
    if (!ifs.is_open())
    {
        // cout << "�ļ�������" << endl;//�������
        this->m_EmpNum = 0;//��ʼ��ְ������
        this->m_EmpArray = NULL;//��ʼ��Ա������ָ��
        this->m_FileIsEmpty = true;//��ʼ���ļ�Ϊ��
        ifs.close();//�ر��ļ�
        return;
    }

    //�ļ����ڣ�����Ϊ��
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // cout << "�ļ�Ϊ��" << endl;//�������
        this->m_EmpNum = 0;//��ʼ��ְ������
        this->m_EmpArray = NULL;//��ʼ��Ա������ָ��
        this->m_FileIsEmpty = true;//��ʼ���ļ�Ϊ��
        ifs.close();//�ر��ļ�
        return;
    }

    //�ļ����ڣ����ݲ�Ϊ��
    int num = this->get_EmpNum();//��ȡְ������
    // cout << "ְ������Ϊ��" << num << endl;//�������
    this->m_EmpNum = num;//���³�Ա����
}

//չʾ�˵�
void WorkerManager::Show_Menu()
{
    cout << "****************************" << endl;
    cout << "****��ӭʹ��ְ������ϵͳ****" << endl;
    cout << "*****  0.�˳��������  *****" << endl;
    cout << "*****  1.����ְ����Ϣ  *****" << endl;
    cout << "*****  2.��ʾְ����Ϣ  *****" << endl;
    cout << "*****  3.ɾ����ְְ��  *****" << endl;
    cout << "*****  4.�޸�ְ����Ϣ  *****" << endl;
    cout << "*****  5.����ְ����Ϣ  *****" << endl;
    cout << "*****  6.���ձ������  *****" << endl;
    cout << "*****  7.��������ĵ�  *****" << endl;
    cout << "****************************" << endl;
    cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}

//���ְ��
void WorkerManager::Add_Emp()
{
    cout << "��������ӵ�ְ��������" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //�����¿ռ��С
        int newSize = this->m_EmpNum + addNum;

        //�����¿ռ�
        Worker ** newSpace = new Worker*[newSize];

        //��ԭ�����ݸ��Ƶ��¿ռ�
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //����������
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
            cin >> id;

            cout << "�������" << i + 1 << "����ְ��������" << endl;
            cin >> name;

            cout << "��ѡ���ְ���ĸ�λ��" << endl;
            cout << "1.��ͨԱ��" << endl;
            cout << "2.����" << endl;
            cout << "3.�ϰ�" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, dSelect);
                break;
            case 2:
                worker = new Manager(id, name, dSelect);
                break;
            case 3:
                worker = new Boss(id, name, dSelect);
                break;
            default:
                break;
            }

            //����ְ����ӵ�������
            newSpace[this->m_EmpNum + i] = worker;
        }

        //�ͷ�ԭ�пռ�
        delete[] this->m_EmpArray;

        //�����¿ռ��ָ��
        this->m_EmpArray = newSpace;

        //�����µ�ְ������
        this->m_EmpNum = newSize;

        //�����ļ���Ϊ�ձ�־
        this->m_FileIsEmpty = false;

        //��ʾ��ӳɹ�
        cout << "�ɹ����" << addNum << "����ְ����" << endl;

        //���浽�ļ�
        this->save();
    }
    else
    {
        cout << "������������" << endl;
    }

    //�����������
    system("pause");
    system("cls");
}

//�����ļ�
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    //д�ļ�
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    //�ر��ļ�
    ofs.close();
}

//ͳ���ļ��е�����
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        //��¼����
        num++;
    }

    ifs.close();

    return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker * worker = NULL;
        //���ݸ�λ��������
        if (dId == 1)//��ͨԱ��
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)//����
        {
            worker = new Manager(id, name, dId);
        }
        else//�ϰ�
        {
            worker = new Boss(id, name, dId);
        }
        //�������Ķ������������
        this->m_EmpArray[index] = worker;
        index++;
    }
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            //���ö�̬���ýӿ�
            this->m_EmpArray[i]->ShowInfo();
        }
    }

    //�����������
    system("pause");
    system("cls");
}

//����ְ������ж�ְ���Ƿ���ڣ������ڷ���ְ����������λ�ã������ڷ���-1
int WorkerManager::IsExist(int id)
{
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //�ҵ�ְ��
            index = i;

            break;
        }
    }

    return index;
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"�ļ������ڻ��߼�¼Ϊ��"<<endl;
    }
    else
    {
        //����ְ�����ɾ��
        cout<<"��������Ҫɾ����ְ����ţ�"<<endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);
        if (index != -1)//˵��ְ�����ڣ�����Ҫɾ����indexλ���ϵ�ְ��
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                //����ǰ��
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;//���������м�¼��Ա����
            //����ͬ�����µ��ļ���
            this->save();
            
            cout<<"ɾ���ɹ�"<<endl;
        }
        else
        {
            cout<<"ɾ��ʧ�ܣ�δ�ҵ���ְ��"<<endl;
        }
    }

    //�����������
    system("pause");
    system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"�ļ������ڻ��߼�¼Ϊ��"<<endl;
    }
    else
    {
        cout<<"��������Ҫ�޸ĵ�ְ����ţ�"<<endl;
        int id = 0;
        cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1)//˵��ְ������
        {
            //����ְ������ҵ�ְ��
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout<<"��������ְ����ţ�"<<endl;
            cin>>newId;

            cout<<"��������ְ��������"<<endl;
            cin>>newName;

            cout<<"��ѡ���ְ���ĸ�λ��"<<endl;
            cout<<"1.��ͨԱ��"<<endl;
            cout<<"2.����"<<endl;
            cout<<"3.�ϰ�"<<endl;
            cin>>dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }

            //���������е�����
            this->m_EmpArray[ret] = worker;

            //����ͬ�����µ��ļ���
            this->save();

            cout<<"�޸ĳɹ�"<<endl;
        }
        else
        {
            cout<<"�޸�ʧ�ܣ�δ�ҵ���ְ��"<<endl;
        }
    }

    //�����������
    system("pause");
    system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"�ļ������ڻ��߼�¼Ϊ��"<<endl;
    }
    else
    {
        cout<<"��������Ҫ���ҵķ�ʽ��"<<endl;
        cout<<"1.��ְ����Ų���"<<endl;
        cout<<"2.��ְ����������"<<endl;

        int select = 0;
        cin>>select;

        if (select == 1)//��ְ����Ų���
        {
            int id;
            cout<<"������ְ����ţ�"<<endl;
            cin>>id;

            int index = this->IsExist(id);
            if (index != -1)
            {
                //���ҵ�ְ��
                this->m_EmpArray[index]->ShowInfo();
            }
            else
            {
                cout<<"���޴���"<<endl;
            }
        }
        else if (select == 2)//��ְ����������
        {
            string name;
            cout<<"������ְ��������"<<endl;
            cin>>name;

            bool flag = false;//��־�Ƿ���ҵ�ְ��
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    //���ҵ�ְ��
                    flag = true;
                    this->m_EmpArray[i]->ShowInfo();
                }
            }

            if (flag == false)
            {
                cout<<"���޴���"<<endl;
            }
        }
        else
        {
            cout<<"������������������"<<endl;
        }
    }

    //�����������
    system("pause");
    system("cls");
}

//����ְ��
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"�ļ������ڻ��߼�¼Ϊ��"<<endl;
    }
    else
    {
        cout<<"��ѡ������ʽ��"<<endl;
        cout<<"1.��ְ���������"<<endl;
        cout<<"2.��ְ����Ž���"<<endl;

        int select = 0;
        cin>>select;

        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int minOrMax = i;//��Сֵ�����ֵ���±�
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)//����
                {
                    if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else//����
                {
                    if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
            }

            if (i != minOrMax)
            {
                Worker * temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }

        //�����Ľ��
        cout<<"����ɹ����������Ϊ��"<<endl;
        this->save();
        this->Show_Emp();
    }
}

//����ļ�
void WorkerManager::Clean_File()
{
    cout<<"ȷ���Ƿ���գ�"<<endl;
    cout<<"1.ȷ��"<<endl;
    cout<<"2.����"<<endl;

    int select = 0;
    cin>>select;

    if (select == 1)
    {
        //��ģʽios::trunc����ļ����ڣ���ɾ�����ٴ���
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;
        }
        cout<<"��ճɹ�"<<endl;
    }

    //�����������
    system("pause");
    system("cls");
}


WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}