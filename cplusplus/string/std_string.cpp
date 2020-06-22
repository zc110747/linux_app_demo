/**********************************************************
 * 说明: string 用于处理字符串的标准库
 * 运算符重载 +, =, ==
 * append 用于字符串的添加
 * size, max_size 当前字符串长度/最大长度
 * capacity 字符串的容量
 * c_str, data 获取内部的字符串指针,只读
 * empty 判断字符串是否为空
 * clear 清除字符串内部数据，只影响size，不影响capacity
 * resize 重新分配字符串空间，不满足的空间用指定字符补足
 * at 返回指定地址的字符
 * front, pack 返回首位的字符
 * push_back, pop_back 增加和删除末尾字符
 * assign, swap 将字符串复制/移动到另一个字符串
 * insert 在字符串中插入另一个字符串
 * find/find_first_of/rfind 在字符串中找寻另一个字符串
 * replace 替换字符串中的部分变量
************************************************************/
#include <string>
#include <iostream>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    std::string sBuf0{"String Buffer 0"};
    std::string sBuf1(sBuf0);

    //字符串输出和比较, 运算符重载, append方法
    cout<<sBuf0<<" "<<sBuf1<<endl;
    if(sBuf0 == sBuf1)
    {
        cout<<"String Equal"<<endl;
    }
    sBuf0 += " test";
    cout<<"operator +:"<<sBuf0<<endl;
    sBuf0.append(" success");
    cout<<"append +:"<<sBuf0<<endl;

    //获取内部的字符串指针，只读属性
    //size和max_size
    //c_str和data
    cout<<"c_str: ";
    const char *pStr = sBuf1.c_str();
    for(int index=0; index<sBuf1.size(); index++)
    {
        cout<<*(pStr+index)<<" "<<sBuf1[index]<<" ";
    }
    cout<<endl;
    cout<<"data: ";
    pStr = sBuf1.data();
    for(int index=0; index<sBuf1.size(); index++)
    {
        cout<<*(pStr+index)<<" "<<sBuf1[index]<<" ";
    }
    cout<<endl;

    //方法 empty和clear
    cout<<"sBuf1 Empty:"<<sBuf1.empty()<<endl;
    sBuf1.clear();
    cout<<"sBuf1 Empty:"<<sBuf1.empty()<<endl;
    cout<<"sBuf1 Capacity:"<<sBuf1.capacity()<<endl;
    cout<<"sBuf1 size:"<<sBuf1.size()<<" sBuf1 Max Size:"<<sBuf1.max_size()<<endl;

    //方法 resize
    sBuf1.resize(10, 'a');
    cout<<"sBuf1 Resize:"<<sBuf1<<endl;

    //方法 at, front, back
    cout<<"sBuf0 at:"<<sBuf0.at(1)<<endl;
    cout<<"sBuf0 front:"<<sBuf0.front()<<endl;
    cout<<"sBuf0 back:"<<sBuf0.back()<<endl;

    //方法 pop_back, push_back
    sBuf0.pop_back();
    sBuf0.push_back('c');
    cout<<"pop and push:"<<sBuf0<<endl;

    //方法 assign和swap
    std::string sBuf2;
    sBuf2.assign(sBuf0);
    cout<<"assign:"<<sBuf2<<"; default size:"<<sBuf0.size()<<endl;
    std::string sBuf3;
    sBuf3.swap(sBuf2);
    cout<<"swap:"<<sBuf3<<"; default size:"<<sBuf2.size()<<endl;

    //常用的字符串遍历方法
    for(auto str:sBuf3)
    {
        cout<<str<<" ";
    }
    cout<<endl;
    for(string::iterator iter=sBuf3.begin(); iter!=sBuf3.end(); iter++)
    {
        cout<<*iter<<" ";
    }
    cout<<endl;
    for_each(sBuf3.begin(), sBuf3.end(), [](const char &buf){
        cout<<buf<<" ";
    });
    cout<<endl;

    //insert方法
    sBuf3.insert(0, 2, 'a'); //位置，长度, 字符
    sBuf3.insert(0, "hello~ "); //位置，字符串
    sBuf3.insert(0, "My World ", 3); //位置，字符串，字符串中的长度
    cout<<sBuf3<<endl;

    //find, rfind方法
    string::size_type position;
    position = sBuf3.find("he");
    if(position != sBuf3.npos)
    {
        cout<<"find position"<<position<<endl;
    }
    cout<<"find first of:"<<sBuf3.find_first_of("he")<<endl; //返回子串中字符串首次出现的地点
    cout<<"find index:"<<sBuf3.find("he", 3)<<endl; //从指定字段开始返回子串中字符串首次出现的地点
    cout<<"rfind:"<<sBuf3.rfind("he")<<endl;

    //replace方法
    string sBuf4 = "";
    sBuf4 += "!$$$test";
    sBuf4.replace(sBuf4.find('$'), 1, "*"); //从起始地址替换指定长度的数据 
    cout<<"replace:"<<sBuf4<<endl;
    sBuf4.replace(sBuf4.begin(), sBuf4.begin()+6, "test!"); //替换迭代器的范围值
    cout<<"replace:"<<sBuf4<<endl;
}
