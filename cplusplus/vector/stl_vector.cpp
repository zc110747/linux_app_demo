/**********************************************************
 * 说明: vector 向量容器
 * 向量容器要求内部变量的类型一致,且与模板定义的一致
 * 与数组的操作类似，较大的区别是vector对于空间的运用更加灵活
 * vector常用方法
 * size, push_back, pop_back, size, insert
 * erase, clear         只清除变量，不释放空间
 * capacity, resize,
 * reserve
************************************************************/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    int array[5] = {8, 2, 1, 3, 5};

    //容器的初始化
    vector<int> v0(array, array+5);
    vector<int> v1(v0);
    vector<int> v2{5, 2, 1, 3, 1}; //列表初始化 C++11支持

    //向量容器的push, pop和resize方法
    v0.push_back(7);
    v1.pop_back();
    v1.resize(8, 6); //扩展空间为8位,并以6赋值
    
    //输出容器的长度
    cout<<"size v0:"<<v0.size()<<endl;
    cout<<"size v0:"<<v1.size()<<endl;

    //容量 容器是否为空
    cout<<"capacity v2:"<<v2.capacity()<<endl;
    cout<<"v2 is empty:"<<v2.empty()<<endl;
    v2.clear(); 
    v2.reserve(1);
    cout<<"capacity v2:"<<v2.capacity()<<endl;
    cout<<"v2 is empty:"<<v2.empty()<<endl;

    //输出向量的首值和末尾值
    cout<<"vector front:"<<v1.front()<<" ";
    cout<<"vector end:"<<v1.back()<<endl;

    //迭代器输出
    cout<<"iterator：";
    for(vector<int>::iterator iter0=v1.begin(); iter0 != v1.end(); iter0++)
    {
        cout<<*iter0<<" ";
    }
    cout<<endl;

    //自动推导变量auto和重载
    cout<<"auto and *overload：";
    for(auto iter1=v1.begin(); iter1 != v1.end(); iter1++)
    {
        cout<<*iter1<<" ";
    }
    cout<<endl;

    //foreach和lambda
    cout<<"foreach and lambda: ";
    for_each(v1.begin(), v1.end(), [](int &value){
        cout<<value<<" ";
    });
    cout<<endl;

    //sort， foreach和lambda
    cout<<"sort foreach and lambda: ";
    sort(v1.begin(), v1.end(), [](int &t1, int &t2)->bool{
        if(t1<t2)
             return true;
        return false;
    });
    sort(v0.begin(), v1.begin());
    for_each(v1.begin(), v1.end(), [](int &value){
        cout<<value<<" ";
    });
    cout<<endl;
}
