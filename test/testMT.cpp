/*
 * ==========================================================================
 *
 *       Filename:  testMT.cpp
 *    Description:  Generates 1 Billion random numbers with MT. And runs all
 *                  tests.
 *                  Takes app. 50 seconds on Intel(R) Pentium(R) M processor 
 *                  1.86GHz.
 *        Version:  1.0 
 *        Created:  15.12.2007 13:00:54 CEST
 *       Revision:  
 *       Compiler:  gcc
 *
 *         Author:  Márton Morvai (mm), marton@morvai.de
 *        Company:  
 *
 * ==========================================================================
 */
#include <iostream>
#include <ctime>
#include "../src/myrngMT.h"
#include "RNGTests.h"

int main(int argc, char *argv[])
{
	int mytime;
	int n = 1E09;
	int genTime;
	int testTime;

	// Generating 1 Billion uniformly distributed numbers
	mytime = time(0);
	for (unsigned long i = 0; i < n; ++i)
	{
		rng.Uniform01();
	}
	genTime = time(0) - mytime;

	// Running all tests
	mytime = time(0);

	RNGTests::run(rng);
	testTime = time(0) - mytime;

	// Summary
	std::cout << "Used " << rng.getName() << ".\n"
			<< "Generated 1 Billion numbers in " << genTime << ".\n"
			<< "AllTests() runtime: " << testTime << ".\n";
}

