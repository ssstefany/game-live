#ifndef _CLOCK_HH_
#define _CLOCK_HH_

#include <time.h>

template<typename LLAMABLE>
float measureTime(LLAMABLE llamable){
    clock_t start, finish;
    start = clock();
	llamable();
	finish = clock();
    return((float(finish-start)/CLOCKS_PER_SEC)*1000);
}

#endif