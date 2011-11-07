/**
 * The MT19937 random number generator
 *
 * @file MTEngine.h
 */

#ifndef MTENGINE_H_
#define MTENGINE_H_

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
	MTEngine();
	/// Sets the seed.
	void seed(unsigned long int s);
	/// Returns the seed.
	unsigned long int getSeed() const
	{
		return seed_;
	}
	/// Returns the name of the random number generator engine;
	const char* getName()
	{
		return "MT19937";
	}

protected:
	~MTEngine()
	{
	}
	/// Produce a random number.
	double operator()();

private:
	unsigned long int seed_; ///< the initial seed
    unsigned long int mt[624]; ///< state vector
    int mti; // mti==625 means mt[] is not initialized

};

} /* namespace myrng */
#endif /* MTENGINE_H_ */
