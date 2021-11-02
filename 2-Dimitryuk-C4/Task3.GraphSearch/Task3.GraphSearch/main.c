#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BreadthFirstSearch.h"

/**
 * CPU: Intel(R) Core(TM) i5-8300H CPU 2.30GHz
 * RAM: Single-Channel 1200 MHz 17-17-17-39
 * SSD: NVMe 4x 8 GT/s
 * 
 * Vertecies amount: 5000
 * 
 * Stress Test results:
 *     Memory used: 295.48 MB
 * 
 *     Total programm execution time: 42 minutes and 2 seconds or 2522 seconds
 *	   First breakpoint in the begginig of BFS algorithm: 38 minutes and 39 seconds or 2319 seconds
 *	   Second breakpoint in the end of BFS algorithm: 42 minutes and 02 seconds or 2522 seconds
 * 
 *	   BFS execution time: 203 seconds
 */

int main()
{
	StressTest();

	return 0;
}
