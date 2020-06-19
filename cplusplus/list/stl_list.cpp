/**********************************************************
 * 说明: list 列表容器
 * 列表容器要求内部变量的类型一致,且与模板定义的一致
 * list每次插入和删除元素，都会配置和释放空间，运用更精准
 * list常用方法
 * size, reserve 获取容量和容器大小调整
 * push_back, push_front    在列表的首尾插入数据
 * pop_front, pop_back      删除列表的首尾数据
 * erase, remove, clear     删除某个迭代器，值或全部元素
 * unique   去除容器内相邻的重复元素
 * splice   剪切后一个List，插入到前List中, 剪切后后一个列表被释放
 * merge    两个列表的合并, 合并后后一个列表被释放
 * sort     排序
************************************************************/
#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

template<class T>
int show_list(list<T> &list_val)
{
    for_each(list_val.begin(), list_val.end(), [](T &value){
        cout<<value<<" ";
    });
    cout<<endl;
}

int main(int argc, char* argv[])
{
    int array[] = {8, 2, 1, 4, 3, 4, 5};

    //列表容器的初始化
    list<int> List0(array, array+7);
    list<int> List1(List0);
    list<string> List2{"11", "21", "14", "21", "23", "11", "15"}; //列表初始化 C++11支持

    //状态信息
    cout<<"list0 size: "<<List0.size()<<endl;
    List0.clear(); //和vector不同,clear会释放所有空间
    List0.resize(10, 3);
    cout<<"list0 size: "<<List0.size()<<endl;

    //push_back, push_front, pop_back, pop_front
    List0 = List1;
    List0.push_back(6);
    List0.push_front(4);
    cout<<"list0 size: "<<List0.size()<<endl;
    cout<<"push val: ";
    show_list<int>(List0);
    cout<<"pop val: ";
    List0.pop_back();
    List0.pop_front();
    show_list<int>(List0);

    //remove和erase，分别删除值和迭代器
    cout<<"del iterator: ";
    for(auto iterList = List0.begin(); iterList != List0.end();)
    {
        if(*iterList == 4){
            iterList = List0.erase(iterList); //列表内迭代器删除,同时将后一个迭代器赋值用于后续的遍历
        }
        else{
            iterList++;
        }  
    }
    show_list<int>(List0); 
    cout<<"del val: ";
    List0.remove(1);
    show_list<int>(List0); 

    //迭代器和运算符重载数据输出
    cout<<"iterator: ";
    for(std::list<int>::iterator list_iter = List1.begin(); list_iter != List1.end(); list_iter++)
    {
        cout<<*list_iter<<" ";
    }
    cout<<endl;

    //算法sort排序，并通过输出
    cout<<"sort and for_each: ";
    //List2.sort();                //从小到大排序
    List2.sort(greater<string>());  //从大到小排序
    for_each(List2.begin(), List2.end(), [](string &value){
        cout<<value<<" ";
    });
    cout<<endl;
    List2.unique();
    cout<<"unique List2: ";
    show_list<string>(List2);

    //列表的合并
    List1.merge(List0);
    cout<<"merge List1: ";
    show_list<int>(List1);
    cout<<"merge List0: ";
    show_list<int>(List0);

    //列表的剪切组合
    list<string> ListString0{"12", "34", "56", "78"};
    list<string> ListString1{"11", "22", "33"};

    auto ListIterator = ListString0.begin();
    ListIterator++;
    ListString0.splice(ListIterator, ListString1);
    cout<<"splice string0: ";
    show_list<string>(ListString0);
    cout<<"splice string1: ";
    show_list<string>(ListString1);
}
