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
 *     Memory used: 390 MB
 * 
 *	   BFS execution time: 47 seconds
 */

int main()
{
	StressTest();

	return 0;
}
