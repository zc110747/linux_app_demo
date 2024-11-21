﻿/**********************************************************
 * 说明: 用于处理系统时间的相关接口
 * time 获取系统的日历时间，以1970-1-1, 00:00:00开始
 * gmtime/gmtime_r 根据日历时间获取GMT时间的函数
 * localtime/localtime_r 获取本地时间的函数
 * asctime/asctime_r 根据本地时间生成时间字符串
 * ctime/ctime_r 根据日历时间生成时间字符串
 * mktime 将带时区的时间转换成秒数
 * gettimeofday/settimeofday 获取/设置当前的精确时间， tz用于保存时区结果
************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
    time_t tim, tim_cur;
    struct tm tm_val, *ptm_val;
    char *pString;
    char buf[256];

    time(&tim);
    
    //获取当前的时间，以标准时间为准
    ptm_val = gmtime(&tim);
    printf("utc time %d:%d:%d\n", ptm_val->tm_hour, ptm_val->tm_min, ptm_val->tm_sec);
    ptm_val = gmtime_r(&tim, &tm_val);
    printf("utc time %d:%d:%d\n", ptm_val->tm_hour, ptm_val->tm_min, ptm_val->tm_sec);

    //获取本地时间，带时区相关
    ptm_val = localtime(&tim);
    printf("local time %d:%d:%d\n", ptm_val->tm_hour, ptm_val->tm_min, ptm_val->tm_sec);
    ptm_val = localtime_r(&tim, &tm_val);
    printf("local time %d:%d:%d\n", ptm_val->tm_hour, ptm_val->tm_min, ptm_val->tm_sec); 
    pString = asctime(ptm_val);
    printf("asctime:%s", pString);
    pString = asctime_r(ptm_val, buf);
    printf("asctime_r:%s", pString);
    pString = ctime(&tim);
    printf("ctime:%s", pString);
    pString = ctime_r(&tim, buf);
    printf("ctime_r:%s", pString);

    //将计算好的time转换为秒数 -- 带时区
    tim_cur = mktime(ptm_val);
    printf("time:%ld, %ld\n", tim, tim_cur);

    struct timeval cur_tv;
    struct timezone cur_tz;
    
    //读取当前的时间(每天中的时分秒)
    gettimeofday(&cur_tv, &cur_tz);
    printf("sec:%ld, usec:%ld\r\n", cur_tv.tv_sec, cur_tv.tv_usec);
    printf("minuteswest:%d, dsttime:%d\r\n", cur_tz.tz_minuteswest, cur_tz.tz_dsttime); 
    settimeofday(&cur_tv, &cur_tz);
}   
