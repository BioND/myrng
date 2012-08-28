#ifndef MTENGINE_H_
#define MTENGINE_H_

#include <cassert>
#include <ctime>

namespace myrng
{

/**
 * The MT19937 random number generator.
 *
 * The Mersenne Twister has a ridiculous high period of 2^19937. If it is
 * seeded with a decent value the probability that the generator hits a bad
 * state during the simulation is quite small. If it hits a "bad state" or is
 * badly initialized it can take several hundred thousand steps to recover,
 * i.e. for several hundred thousand steps the bits of the generated numbers
 * will be dominated by either zeros or ones.
 * But the seed function is written to avoid a bad initialization so this
 * generator can also be used without hesitation.
 *
 * @see http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 * @author Marton Morvai
 * @author Thilo Gross <gross@physics.org>
 *
 * @copyright Algorithm Copyright (c) 1997 - 2002, Makoto Matsumoto and Takuji
 * Nishimura. All rights reserved. Redistribution and use in source and binary
 * forms, with or without modification, are permitted provided that the following
 * conditions are met:
 *   -# Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   -# Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *   -# The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 */
class MTEngine
{
public:
	MTEngine()
	{
		// Long has to be at least 32 bits!
		assert(sizeof(long) >= 4);
		mti = 624 + 1;
		//   unsigned long mt[624];
		seed((unsigned long) std::time(0));
	}
	/**
	 * Set random number generator seed
	 */
	void seed(unsigned long int s)
	{
		mt[0] = s & 0xffffffffUL;
		for (mti = 1; mti < 624; mti++)
		{
			mt[mti] =
					(1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
			// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
			// In the previous versions, MSBs of the seed affect
			// only MSBs of the array mt[].
			// 2002/01/09 modified by Makoto Matsumoto
			mt[mti] &= 0xffffffffUL;
			// for >32 bit machines
		}
	}
	/**
	 * Get random number generator seed
	 */
	unsigned long int getSeed() const
	{
		return seed_;
	}
	/**
	 * Get the name of the random number generator engine
	 */
	const char* getName()
	{
		return "MT19937";
	}

protected:
	~MTEngine()
	{
	}
	/**
	 * Produce a random number.
	 */
	double operator()()
	{
		/*
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

private:
	unsigned long int seed_; ///< the initial seed
	unsigned long int mt[624]; ///< state vector
	int mti; // mti==625 means mt[] is not initialized

};

} /* namespace myrng */
#endif /* MTENGINE_H_ */
