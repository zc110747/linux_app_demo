/**********************************************************
 * 说明: map 关联容器，提供映射的处理关系
 * size 获取map的当前大小
 * max_size 容器的最大大小
 * empty 判断容器是否为空
 * swap 交换两个map内的信息，另外一个map将会被清空
 * erase clear 容器删除数据
 * insert 容器插入数据
 * lower_bound 返回非递减序列中的第一个大于等于值val的迭代器(上限闭合)
 * upper_bound 返回非递减序列中第一个大于值val的位置(下限闭合)
************************************************************/
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <vector>

using namespace std;

template<class T0, class T1>
void show_map(map<T0, T1> &map_val)
{
    for_each(map_val.begin(), map_val.end(), [](const pair<T0, T1> &map_ref){
        cout<<map_ref.first<<":"<<map_ref.second<<endl;
    });
    cout<<endl;
}

int main(int argc, char* argv[])
{
    map<string, int> MapVal = {
        {"first", 1},
        {"second", 2},
        {"third", 3}
    };
    map<string, string> MapString = {
        {"val0", "0"},
        {"val1", "1"},
    };
    map<int, int> MapInt = {
        {10, 500},
        {20, 600},
        {30, 900}
    };

    cout<<"show map:"<<endl;
    show_map<string, int>(MapVal);

    //Map方法size, clear， erase
    cout<<"MapString size:"<<MapString.size()<<endl;
    MapString.clear();
    cout<<"MapString size:"<<MapString.size()<<endl;
    cout<<"MapString max size:"<<MapString.max_size()<<endl;
    cout<<"MapString is empty:"<<MapString.empty()<<endl;
    MapString["first"] = "0";
    MapString["second"] = "1";
    MapString["third"] = "1";
    for(auto iter=MapString.begin();iter!=MapString.end();)
    {
        if(iter->second == "1")
        {
            iter = MapString.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    show_map<string, string>(MapString);
    
    //Map方法lower_bound, upper_bound, swap方法
    auto map_iterator = MapInt.lower_bound(9);
    cout<<"lower bound:"<<map_iterator->first<<":"<<map_iterator->second<<endl;
    map_iterator = MapInt.upper_bound(21);
    cout<<"upper bound:"<<map_iterator->first<<":"<<map_iterator->second<<endl;
    cout<<"show mapInt0:"<<endl;
    show_map<int, int>(MapInt);
    map<int, int> MapInt1;
    MapInt1.swap(MapInt);
    cout<<"show mapInt1:"<<endl;
    show_map<int, int>(MapInt1);
    cout<<"MapInt size:"<<MapInt.size()<<endl;

    //map insert方法
    MapVal.insert(pair<string, int>("four", 4));
    MapVal.insert(make_pair<string, int>("five", 5));
    MapVal.insert(map<string, int>::value_type("six", 6));
    MapVal["Seven"] = 7;
    cout<<"show insert:"<<endl;
    show_map<string, int>(MapVal);
    
    //auto :
    cout<<"show auto:"<<endl;
    for(auto val:MapVal)
    {
        cout<<val.first<<":"<<val.second<<endl;
    }
    cout<<endl;

    //auto iterator
    cout<<"show iterator:"<<endl;
    for(auto iteartor_val=MapVal.begin(); iteartor_val!=MapVal.end(); iteartor_val++)
    {
        cout<<iteartor_val->first<<":"<<iteartor_val->second<<endl;
    }
    cout<<endl;

    //find语法
    map<string, int>::iterator iter = MapVal.find(string("second"));
    if(iter != MapVal.end())
        cout<<iter->first<<":"<<iter->second<<endl;
    cout<<endl;

    //map排序 sort算法默认只支持vector
    cout<<"show sort:"<<endl;
    vector<pair<string, int>>  vec_pair;
    for(auto val:MapVal)
    {
        vec_pair.push_back(pair<string, int>(val.first, val.second));
    }
    sort(vec_pair.begin(), vec_pair.end(), [](pair<string, int> &map_ref0, pair<string, int> &map_ref1)->bool{
        return map_ref0.second < map_ref1.second;
    });
    for(auto val:vec_pair)
    {
        cout<<val.first<<":"<<val.second<<endl;
    }
    cout<<endl;
    return 0;
}
