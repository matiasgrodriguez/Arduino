
#ifndef __base_h__
#define __base_h__

//Using types from avr
#include <avr/common.h>

// for malloc and free
#include <stdlib.h> 

void* operator new(size_t size) { 
  return malloc(size); 
}

void operator delete(void* ptr) { 
  free(ptr); 
} 

#endif


