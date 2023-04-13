#include "workerManager.h"

WorkerManager::WorkerManager()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    //文件不存在
    if (!ifs.is_open())
    {
        // cout << "文件不存在" << endl;//测试输出
        this->m_EmpNum = 0;//初始化职工人数
        this->m_EmpArray = NULL;//初始化员工数组指针
        this->m_FileIsEmpty = true;//初始化文件为空
        ifs.close();//关闭文件
        return;
    }

    //文件存在，数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // cout << "文件为空" << endl;//测试输出
        this->m_EmpNum = 0;//初始化职工人数
        this->m_EmpArray = NULL;//初始化员工数组指针
        this->m_FileIsEmpty = true;//初始化文件为空
        ifs.close();//关闭文件
        return;
    }

    //文件存在，数据不为空
    int num = this->get_EmpNum();//获取职工人数
    // cout << "职工人数为：" << num << endl;//测试输出
    this->m_EmpNum = num;//更新成员属性
}

//展示菜单
void WorkerManager::Show_Menu()
{
    cout << "****************************" << endl;
    cout << "****欢迎使用职工管理系统****" << endl;
    cout << "*****  0.退出管理程序  *****" << endl;
    cout << "*****  1.增加职工信息  *****" << endl;
    cout << "*****  2.显示职工信息  *****" << endl;
    cout << "*****  3.删除离职职工  *****" << endl;
    cout << "*****  4.修改职工信息  *****" << endl;
    cout << "*****  5.查找职工信息  *****" << endl;
    cout << "*****  6.按照编号排序  *****" << endl;
    cout << "*****  7.清空所有文档  *****" << endl;
    cout << "****************************" << endl;
    cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
    cout << "请输入添加的职工数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)
    {
        //计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        //开辟新空间
        Worker ** newSpace = new Worker*[newSize];

        //将原有数据复制到新空间
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
            cin >> id;

            cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
            cin >> name;

            cout << "请选择该职工的岗位：" << endl;
            cout << "1.普通员工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
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

            //将新职工添加到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }

        //释放原有空间
        delete[] this->m_EmpArray;

        //更改新空间的指向
        this->m_EmpArray = newSpace;

        //更新新的职工人数
        this->m_EmpNum = newSize;

        //更新文件不为空标志
        this->m_FileIsEmpty = false;

        //提示添加成功
        cout << "成功添加" << addNum << "名新职工！" << endl;

        //保存到文件
        this->save();
    }
    else
    {
        cout << "输入数据有误！" << endl;
    }

    //按任意键继续
    system("pause");
    system("cls");
}

//保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    //写文件
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }

    //关闭文件
    ofs.close();
}

//统计文件中的人数
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
        //记录人数
        num++;
    }

    ifs.close();

    return num;
}

//初始化员工
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
        //根据岗位创建对象
        if (dId == 1)//普通员工
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)//经理
        {
            worker = new Manager(id, name, dId);
        }
        else//老板
        {
            worker = new Boss(id, name, dId);
        }
        //将创建的对象放入数组中
        this->m_EmpArray[index] = worker;
        index++;
    }
}

//显示职工
void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            //利用多态调用接口
            this->m_EmpArray[i]->ShowInfo();
        }
    }

    //按任意键继续
    system("pause");
    system("cls");
}

//按照职工编号判断职工是否存在，若存在返回职工在数组中位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1;

    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            //找到职工
            index = i;

            break;
        }
    }

    return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空"<<endl;
    }
    else
    {
        //按照职工编号删除
        cout<<"请输入想要删除的职工编号："<<endl;
        int id = 0;
        cin >> id;

        int index = this->IsExist(id);
        if (index != -1)//说明职工存在，并且要删除掉index位置上的职工
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                //数据前移
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;//更新数组中记录人员个数
            //数据同步更新到文件中
            this->save();
            
            cout<<"删除成功"<<endl;
        }
        else
        {
            cout<<"删除失败，未找到该职工"<<endl;
        }
    }

    //按任意键继续
    system("pause");
    system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空"<<endl;
    }
    else
    {
        cout<<"请输入想要修改的职工编号："<<endl;
        int id = 0;
        cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1)//说明职工存在
        {
            //根据职工编号找到职工
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout<<"请输入新职工编号："<<endl;
            cin>>newId;

            cout<<"请输入新职工姓名："<<endl;
            cin>>newName;

            cout<<"请选择该职工的岗位："<<endl;
            cout<<"1.普通员工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.老板"<<endl;
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

            //更新数组中的数据
            this->m_EmpArray[ret] = worker;

            //数据同步更新到文件中
            this->save();

            cout<<"修改成功"<<endl;
        }
        else
        {
            cout<<"修改失败，未找到该职工"<<endl;
        }
    }

    //按任意键继续
    system("pause");
    system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空"<<endl;
    }
    else
    {
        cout<<"请输入想要查找的方式："<<endl;
        cout<<"1.按职工编号查找"<<endl;
        cout<<"2.按职工姓名查找"<<endl;

        int select = 0;
        cin>>select;

        if (select == 1)//按职工编号查找
        {
            int id;
            cout<<"请输入职工编号："<<endl;
            cin>>id;

            int index = this->IsExist(id);
            if (index != -1)
            {
                //查找到职工
                this->m_EmpArray[index]->ShowInfo();
            }
            else
            {
                cout<<"查无此人"<<endl;
            }
        }
        else if (select == 2)//按职工姓名查找
        {
            string name;
            cout<<"请输入职工姓名："<<endl;
            cin>>name;

            bool flag = false;//标志是否查找到职工
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    //查找到职工
                    flag = true;
                    this->m_EmpArray[i]->ShowInfo();
                }
            }

            if (flag == false)
            {
                cout<<"查无此人"<<endl;
            }
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
    }

    //按任意键继续
    system("pause");
    system("cls");
}

//排序职工
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者记录为空"<<endl;
    }
    else
    {
        cout<<"请选择排序方式："<<endl;
        cout<<"1.按职工编号升序"<<endl;
        cout<<"2.按职工编号降序"<<endl;

        int select = 0;
        cin>>select;

        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int minOrMax = i;//最小值或最大值的下标
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)//升序
                {
                    if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else//降序
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

        //排序后的结果
        cout<<"排序成功，排序后结果为："<<endl;
        this->save();
        this->Show_Emp();
    }
}

//清空文件
void WorkerManager::Clean_File()
{
    cout<<"确认是否清空？"<<endl;
    cout<<"1.确认"<<endl;
    cout<<"2.返回"<<endl;

    int select = 0;
    cin>>select;

    if (select == 1)
    {
        //打开模式ios::trunc如果文件存在，先删除，再创建
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
        cout<<"清空成功"<<endl;
    }

    //按任意键继续
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