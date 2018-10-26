#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

extern "C" int  modulo(int, int);
extern "C" int vals_divisible(int);


const size_t tmpsize = 1024;


#define PRINT_BEGIN(test)\
	do {\
		std::cout << __COUNTER__ << " - Running the " << test << " Test, in " << __FUNCTION__\
				  << " : " << __LINE__ << std::endl;\
	} while(0)

int v(int n)
{
	int a = 0;
	for(int i = 1; i <= n; ++i)
		a += ((i % 3) == 0 || (i % 5) == 0) ? 1 : 0;
	return a;
}

template<typename T>
void compare_vals(T first, T second)
{
	std::stringstream result;
 	if(first == second)
 		result << "[*] Success! Values are equal!";
 	else
 		result << "[x] Test Failed! Results are not equal!";
	result << " Expected: " << first << " | Received: " << second << ", In test: " << std::endl;
	std::cout << result.str();
}

template<typename T> 
void compare_vals(T* first, T* second, size_t size)
{
	std::stringstream result;
	std::stringstream contents;
	bool isEqual = true;

	for(int i = 0; i < size; ++i, ++first, ++second) {
 		if(*first == *second) {
 			contents << " Expected: " << *first << " | Received: " << *second << "\t";
 			isEqual &= true;
 		} else {
 			contents << " Expected: " << *first << " | Received: " << *second << "\t";
 			isEqual = false;
 		}
 	}
 	if (isEqual)
 		result << "[*] Success! Values are equal! " << contents.str();
 	else
 		result << "[x] Test Failed! Results are not equal! " << contents.str();

	result << std::endl;
	std::cout << result.str();	
}

template<typename T>
void populate_arrays(T* buf1, T* buf2, size_t size)
{
	if (NULL == buf1 || NULL == buf2)
		return;

	memset(buf1, 0, sizeof(T) * size);
	memset(buf2, 0, sizeof(T) * size);

	for(int i = 0; i < size; ++i) {
		buf1[i] = rand();
		buf2[i] = rand();
		buf1[i] >>= 6;
		buf2[i] >>= 6;
	}

}



void modulo_test()
{
	PRINT_BEGIN("Modulo Test - Case 1");
	compare_vals(0, modulo(50, 10));

	PRINT_BEGIN("Modulo Test - Case 2");
	compare_vals(1, modulo(7, 3));

	PRINT_BEGIN("Modulo Test - Case 3");
	compare_vals(0, modulo(50, 0));

	PRINT_BEGIN("Modulo Test - Case 4");
	compare_vals(3, modulo(33, 10));

	PRINT_BEGIN("Modulo Test - Case 5");
	compare_vals(0, modulo(2, 0));

	PRINT_BEGIN("Modulo Test - Case 6");
	compare_vals(1, modulo(101, 10));
}

void vals_divisible_test()
{
 	PRINT_BEGIN("Vals Divisible Test - Case 1");
 	compare_vals(v(10), vals_divisible(10));
 	PRINT_BEGIN("Vals Divisible Test - Case 2");
 	compare_vals(v(20), vals_divisible(20));
 	PRINT_BEGIN("Vals Divisible Test - Case 3");
 	compare_vals(v(1000), vals_divisible(1000));
 	PRINT_BEGIN("Vals Divisible Test - Case 4");
 	compare_vals(v(100), vals_divisible(100));

}


template<typename T>
T cmin(T* buf, T size)
{
	T current = buf[0];

	if (NULL == buf)
		return -1;

	for(T i = 1; i < size; ++i)
		current = (buf[i] < current) ? buf[i] : current;
	std::cout << current << std::endl;
	return current;
}




int main(int argc, char** argv)
{
	unsigned int a, d;
	asm("rdtsc" : "=a"(a), "=d"(d));
	srand((a | (d << 32)));
    modulo_test();
    vals_divisible_test();
    return 0;
}
