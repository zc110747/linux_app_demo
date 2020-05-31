#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    int array[5] = {14, 2, 1, 3, 5};

    //容器的初始化
    vector<int> v0(array, array+5);
    vector<int> v1(v0);
    vector<int> v2{5, 2, 1, 3, 1}; //列表初始化 C++11支持

    //向量容器的push和pop方法
    v0.push_back(7);
    v1.pop_back();

    //输出容器的长度
    cout<<"size v0:"<<v0.size()<<" ";
    cout<<"size v1:"<<v1.size()<<endl;

    //容量 容器是否为空
    cout<<"capacity v2:"<<v2.capacity()<<endl;
    cout<<"v2 is empty:"<<v2.empty()<<endl;
    v2.clear();
    cout<<"capacity v2:"<<v2.capacity()<<endl;
    cout<<"v2 is empty:"<<v2.empty()<<endl;

    //输出向量的首值和末尾值
    cout<<"vector front:"<<v1.front()<<" ";
    cout<<"vector end:"<<v1.back()<<endl;

    //迭代器输出
    cout<<"iterator："<<endl;
    for(vector<int>::iterator iter0=v1.begin(); iter0 != v1.end(); iter0++)
    {
        cout<<*iter0<<" ";
    }
    cout<<endl;

    //自动推导变量auto
    cout<<"auto："<<endl;
    for(auto iter1=v1.begin(); iter1 != v1.end(); iter1++)
    {
        cout<<*iter1<<" ";
    }
    cout<<endl;
    
    //运算符重载
    cout<<"overload: "<<endl;
    for(auto index =0; index < v1.size(); index++)
    {
        cout<<v1[index]<<" ";
    }
    cout<<endl;

    //foreach和lambda
    cout<<"foreach and lambda: "<<endl;
    for_each(v1.begin(), v1.end(), [](int &value){
        cout<<value<<" ";
    });
    cout<<endl;

    //sort， foreach和lambda
    cout<<"sort foreach and lambda: "<<endl;
    sort(v1.begin(), v1.end(), [](int &t1, int &t2)->bool{
        if(t1<t2)
             return true;
        return false;
    });
    for_each(v1.begin(), v1.end(), [](int &value){
        cout<<value<<" ";
    });
    cout<<endl;
}
