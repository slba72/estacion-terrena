#ifndef _TIME_H_
#define _TIME_H_

#define TIME_SEC 1 // 60 -> 1 segundo
#define INCREASE_TIME(time) ++time;
#define CHECK_TIME() \
if (time == TIME_SEC)\
time = 0;

extern unsigned char time;

#endif // _TIME_H_