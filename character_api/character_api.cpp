/**********************************************************
 * 说明: 字符和字符串的相关处理
 * 字符检查类型判断的API接口
 * isalnum 判断是否为字母或数字字符
 * isascii 判断是否为ASCII码
 * isalpha 判断是否为英文字母
 * iscntrl 判断是否为ASCII码的控制字符
 * isdigit 判断字符是否为阿拉伯数字
 * isgraph 判断字符是否可图形显示
 * isprint 判断字符是否可打印
 * islower 判断是否为小写字母
 * isupper 判断是否为大写字母
 * isspace 判断是否为空格字符
 * ispunct 判断是否为标点符号
 * isxdigit 判断是否符合十六进制的字符(0~f)
 * 
 * atof    字符串转double类型
 * atoi    字符串转int类型
 * atol    字符串转长整型
 * 
 * gcvt    浮点型转字符串
 * strtod  字符串转dobule型，带返回终止字符
 * strtol  字符串long型，带返回终止字符
 * strtoll 字符串long long型，带返回终止字符
 * strtoul 字符串unsigned long型，带返回终止字符
 * strtoull 字符串unsigned long long型，带返回终止字符
************************************************************/
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    //check API
    std::cout<<"is alnum:"<<isalnum('a')<<std::endl;   
    std::cout<<"is ascil:"<<isascii('\t')<<std::endl; 
    std::cout<<"is alpha:"<<isalpha('a')<<std::endl;  
    std::cout<<"is cntrl:"<<iscntrl(0x01)<<std::endl; 
    std::cout<<"is digit:"<<isdigit('1')<<std::endl;
    std::cout<<"is graph:"<<isgraph(0x04)<<std::endl;
    std::cout<<"is print:"<<isprint(0x04)<<std::endl;
    std::cout<<"is lower:"<<islower('A')<<std::endl;
    std::cout<<"is upper:"<<isupper('b')<<std::endl;
    std::cout<<"is space:"<<isspace(' ')<<std::endl;
    std::cout<<"is punct:"<<ispunct(',')<<std::endl;
    std::cout<<"is xdigit:"<<isxdigit('f')<<std::endl;

    double val0 = atof("1.02");
    std::cout<<"atof:"<<val0<<std::endl;
    int val1 = atoi("-23");
    std::cout<<"atoi:"<<val1<<std::endl;
    long val2 = atol("231231231312");
    std::cout<<"atol:"<<val2<<std::endl;

    char buffer0[6];
    gcvt(123.25, 5, buffer0);
    std::cout<<"gcvt:"<<buffer0<<std::endl;
    std::cout<<"strtod:"<<strtod("-123.5", NULL)<<std::endl;
    std::cout<<"strtol:"<<strtol("-123", NULL, 10)<<std::endl;
    std::cout<<"strtoll:"<<strtoll("0x16", NULL, 16)<<std::endl;
    std::cout<<"strtoul:"<<strtoul("0x16", NULL, 16)<<std::endl;
    std::cout<<"strtoull:"<<strtoul("0x47", NULL, 16)<<std::endl;
    std::cout<<"toascii:"<<toascii(5)<<std::endl;
    std::cout<<"tolower:"<<tolower('A')<<std::endl;
    std::cout<<"toupper:"<<toupper('a')<<std::endl;

    return 0;
}
