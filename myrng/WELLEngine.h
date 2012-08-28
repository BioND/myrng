#ifndef WELLENGINE_H_
#define WELLENGINE_H_

#include <cassert>
#include <ctime>

namespace myrng
{

/**
 * The WELL1024a random number generator.
 *
 * The acronym WELL stands for "Well Equidistributed Long-period Linear". It
 * has a period of 2^1024, which should be enough for most simulation
 * tasks. It has better equidistribution properties and it recovers faster
 * from a "bad state", e.g. bad initialization, than the MT19937.
 * For more information see F. Panneton, P. L'Ecuyer, and M. Matsumoto,
 * "Improved Long-Period Generators Based on Linear Recurrences Modulo 2",
 * ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.
 *
 * @author Gerd Zschaler <gzschaler@googlemail.com>
 * @author Marton Morvai
 * @author Thilo Gross <gross@physics.org>
 *
 * @copyright This implementation of the WELL alogrithm is licensed under the
 * Creative Commons Attribution-NonCommercial 3.0 Unported License. To view
 * a copy of this license, visit http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain
 * View, California, 94041, USA.
 */
class WELLEngine
{
public:
	WELLEngine()
	{
		// Long has to be at least 32 bits!
		assert(sizeof(long) >= 4);
		state_i = 0;
		seed((unsigned long) std::time(0));
	}
	/**
	 * Set random number generator seed
	 */
	void seed(unsigned long int s)
	{
		/*
		 * After the engine has been seeded, this function generates 50.000
		 * random numbers to let it recover at least a little bit from a
		 * bad initial state.
		 */
		seed_ = s;
		STATE[0] = s & 0xffffffffUL;
		for (int i = 1; i < 32; ++i)
		{
			STATE[i] =
					(1812433253UL * (STATE[i - 1] ^ (STATE[i - 1] >> 30)) + i);
			STATE[i] &= 0xffffffffUL;
			// for >32 bit machines
		}
		for (int j = 0; j < 10000; ++j)
			(*this)();
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
		return "WELL1024a";
	}

protected:
	~WELLEngine()
	{
	}
	/// Produce a random number.
	double operator()()
	{
		/*
		 * This generator is an Implementation of WELL1024a
		 * (F. Panneton, P. L'Ecuyer, and M. Matsumoto,
		 * "Improved Long-Period Generators Based on Linear Recurrences Modulo 2",
		 * ACM Transactions on Mathematical Software, 32, 1 (2006), 1-16.)
		 */
		z0 = STATE[(state_i + 31) & 0x0000001fU];
		z1 = (STATE[state_i]) ^ STATE[(state_i + 3) & 0x0000001fU];
		z2 = (STATE[(state_i + 24) & 0x0000001fU]
				^ (STATE[(state_i + 24) & 0x0000001fU] << (19)))
				^ (STATE[(state_i + 10) & 0x0000001fU]
						^ (STATE[(state_i + 10) & 0x0000001fU] << (14)));

		STATE[state_i] = z1 ^ z2;
		STATE[(state_i + 31) & 0x0000001fU] = (z0 ^ (z0 << (11)))
				^ (z1 ^ (z1 << (7))) ^ (z2 ^ (z2 << (13)));

		state_i = (state_i + 31) & 0x0000001fUL;
		return ((double) STATE[state_i] * 2.32830643653869628906e-10);
	}

private:
	unsigned long int seed_; ///< the initial seed

	unsigned int z0, z1, z2, state_i;
	unsigned int STATE[32];
};

} /* namespace myrng */
#endif /* WELLENGINE_H_ */
