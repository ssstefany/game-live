#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <chrono>
#include <unistd.h>

class Environment;
class Agent;


typedef std::vector<Agent*> Neighbors;

struct coord_t {
	uint32_t x;
	uint32_t y;
};

typedef struct coord_t CoordXY;

enum TIME { 
	ACTUAL, 
	FUTURE
};

enum STATE { 
	DEAD,
	LIVE
};

typedef enum STATE State;


#endif
