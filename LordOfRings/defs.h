#if !defined _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <vector>

using namespace std;

struct eventList 
{
	long nEventCode; 
	eventList* pNext;
};


bool checkSCC (int N, eventList* pEventList);
int travel (int N, eventList* pEventList);

#endif 