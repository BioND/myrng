/**
 * MT19937 implementation
 *
 * @file MTEngine.cpp
 */

#include "MTEngine.h"
#include <cassert>
#include <ctime>

namespace myrng
{

MTEngine::MTEngine()
{
	// Long has to be at least 32 bits!
	assert(sizeof(long) >= 4);
	mti = 624 + 1;
	//   unsigned long mt[624];
	seed((unsigned long) std::time(0));
}

void MTEngine::seed(unsigned long int s)
{
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti < 624; mti++)
	{
		mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
		// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
		// In the previous versions, MSBs of the seed affect
		// only MSBs of the array mt[].
		// 2002/01/09 modified by Makoto Matsumoto
		mt[mti] &= 0xffffffffUL;
		// for >32 bit machines
	}
}

double MTEngine::operator()()
{
	/**
	 * This generator is an implementation of MT19937.
	 * For more information visit
	 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
	 */
	unsigned long y;
	static unsigned long mag01[2] =
	{ 0x0UL, 0x9908b0dfUL };
	// mag01[x] = x * MATRIX_A  for x=0,1

	if (mti >= 624) // generate N words at one time
	{
		int kk;

		for (kk = 0; kk < 624 - 397; kk++)
		{
			y = (mt[kk] & 0x80000000UL) | (mt[kk + 1] & 0x7fffffffUL);
			mt[kk] = mt[kk + 397] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; kk < 624 - 1; kk++)
		{
			y = (mt[kk] & 0x80000000UL) | (mt[kk + 1] & 0x7fffffffUL);
			mt[kk] = mt[kk + (397 - 624)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[624 - 1] & 0x80000000UL) | (mt[0] & 0x7fffffffUL);
		mt[624 - 1] = mt[397 - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

		mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	return (((double) y) + 0.5) * (1.0 / 4294967296.0);
	/* divided by 2^32 */
}

} /* namespace myrng */

