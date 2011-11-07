/**
 * @file RNGTests.h
 * @date 04.11.2011
 * @author gerd
 */

#ifndef RNGTESTS_H_
#define RNGTESTS_H_

#include <iostream>
#include <iomanip>
#include <ctime>

class RNGTests
{
public:
	template<class RNG>
	static void run(RNG& rng)
	{
		testUniform01<RNG>(rng);
		testFromTo<RNG>(rng);
		testDice<RNG>(rng);
		testIntFromTo<RNG>(rng);
		testChance<RNG>(rng);
		testChoices<RNG>(rng);
		testNormal01Polar<RNG>(rng);
		testGaussianPolar<RNG>(rng);
		testExponential<RNG>(rng);
		testGamma<RNG>(rng);
		testBeta<RNG>(rng);
	}
private:
	template<class RNG>
	static void testUniform01(RNG& rng)
	{
		std::cout << "  Testing Uniform01 --------------------------------\n";
		std::cout << std::setprecision(2);
		unsigned int x[10];
		double largest = 0;
		double smallest = 0;
		for (int i = 0; i < 10; ++i)
			x[i] = 0;
		long t1 = time(0);
		for (int i = 0; i < 1e7; ++i)
		{
			double res = rng.Uniform01();
			if (res > largest)
				largest = res;
			if (res < smallest)
				smallest = res;
			int z = (int) (res * 10.0);
			++x[z];
		}
		long t2 = time(0);
		std::cout << "    Largest value:  " << largest << " [1.00]\n";
		std::cout << "    Smallest value: " << smallest << " [0.00]\n";
		for (int i = 0; i < 10; ++i)
		{
			std::cout << "    " << (i / 10.0) << "..." << ((i + 1) / 10.0)
					<< ": " << (static_cast<double>(x[i]) / 1.0e7 * 100.0)
					<< "% [10.0%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testFromTo(RNG& rng)
	{
		std::cout << "  Testing FROM-TO ----------------------------------\n";
		double from = -rng.Uniform01() * 5;
		double to = rng.Uniform01() * 5;
		std::cout << "    test task: From " << from << " to " << to << "\n";
		double lo = 10;
		double hi = -10;
		int i;
		int x[10];
		for (i = 0; i < 10; i++)
			x[i] = 0;
		long t1 = time(0);
		for (i = 0; i < 1e7; i++)
		{
			double res = rng.FromTo(from, to);
			if (res > hi)
				hi = res;
			if (res < lo)
				lo = res;
			int z = (int) ((res - from) / (to - from) * 10.0);
			x[z]++;
		}
		long t2 = time(0);
		std::cout << "    Largest value:  " << hi << " [" << to << "]\n";
		std::cout << "    Smallest value: " << lo << "[" << from << "]\n";
		for (i = 0; i < 10; i++)
		{
			std::cout << "    " << (from + i * (to - from) / 10.0) << "..."
					<< (from + (i + 1) * (to - from) / 10.0) << ": "
					<< (static_cast<double>(x[i]) / 1e7 * 100.0)
					<< "% [10.0%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testDice(RNG& rng)
	{
		std::cout << "  Testing DICE ------------------------------------\n";
		int x[10];
		int i;
		for (i = 0; i < 10; i++)
			x[i] = 0;
		long t1 = time(0);
		for (i = 0; i < 1e7; i++)
		{
			int q = rng.Dice(10) - 1;
			x[q]++;
		}
		long t2 = time(0);
		for (i = 0; i < 10; i++)
		{
			std::cout << "    " << i + 1 << ": "
					<< (static_cast<double>(x[i]) / 1e7 * 100.0)
					<< "% [10.0%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testIntFromTo(RNG& rng)
	{
		std::cout << "  Testing INTEGER FROM-TO -------------------------\n";
		int x[11];
		int from = -rng.Dice(5);
		int to = rng.Dice(5);
		std::cout << "    Test task: From " << from << " to " << to << "\n";
		int i;
		for (i = 0; i < 11; i++)
			x[i] = 0;
		long t1 = time(0);
		for (i = 0; i < 1e7; i++)
		{
			int q = rng.IntFromTo(from, to);
			q -= from;
			x[q]++;
		}
		long t2 = time(0);
		for (i = 0; i < (to - from) + 1; i++)
		{
			std::cout << "    " << i + from << ": "
					<< (static_cast<double>(x[i]) / 1e7 * 100.0) << "% ["
					<< (100.0 / (to - from + 1)) << "%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testChance(RNG& rng)
	{
		std::cout << std::setprecision(3);
		std::cout << "  Testing CHANCE ----------------------------------\n";
		int x[10];
		double chance[10];
		int i;
		for (i = 0; i < 10; i++)
		{
			x[i] = 0;
			chance[i] = rng.FromTo(0.1, 0.999);
		}
		long t1 = time(0);
		for (int j = 0; j < 10; j++)
		{
			for (i = 0; i < 1e6; i++)
			{
				if (rng.Chance(chance[j]))
					x[j]++;
			}
		}
		long t2 = time(0);
		for (i = 0; i < 10; i++)
		{
			std::cout << "    Chance " << 100.0 * chance[i] << ": Success "
					<< (static_cast<double>(x[i]) / 1e6 * 100.0) << "% ["
					<< 100.0 * chance[i] << "%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testChoices(RNG& rng)
	{
		std::cout << std::setprecision(3);
		std::cout << "  Testing CHOICES ---------------------------------\n";
		int x[9];
		int numchoice = 4 + rng.Dice(5);
		double chance[9];
		int i;
		double sum = 0;
		for (i = 0; i < numchoice; i++)
		{
			x[i] = 0;
			chance[i] = rng.Uniform01() + sum;
			sum += chance[i];
		}
		for (i = 0; i < numchoice; i++)
		{
			chance[i] /= sum;
		}
		long t1 = time(0);
		for (i = 0; i < 1e7; i++)
		{
			int q = rng.Choices(chance, numchoice);
			x[q]++;
		}
		long t2 = time(0);
		for (i = 0; i < numchoice; i++)
		{
			std::cout << "    Choice" << i << " (" << 100.0 * chance[i]
					<< "%): " << (static_cast<double>(x[i]) / 1e7 * 100.0)
					<< "% [" << 100.0 * chance[i] << "%]\n";
		}
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testNormal01Polar(RNG& rng)
	{
		std::cout << std::setprecision(2);
		std::cout << "  Testing Normal 01 Polar Method -------------------\n";
		double erf[11];
		erf[0] = 0.6;
		erf[1] = 1.7;
		erf[2] = 4.4;
		erf[3] = 9.2;
		erf[4] = 15.0;
		erf[5] = 38.3;
		erf[10] = 0.6;
		erf[9] = 1.7;
		erf[8] = 4.4;
		erf[7] = 9.2;
		erf[6] = 15.0;
		unsigned int x[11];
		double sum = 0;
		double sumsq = 0;
		int testset = 10000000;
		int i;
		for (i = 0; i < 11; i++)
			x[i] = 0;
		long t1 = time(0);
		for (i = 0; i < testset; i++)
		{
			double res = rng.Normal01Polar();
			int z = (int) (res * 2.0) + 5;
			if (z < 0)
				z = 0;
			if (z > 10)
				z = 10;
			sum += res;
			sumsq += res * res;
			x[z]++;
		}
		long t2 = time(0);
		double mean = sum / testset;
		double meansq = sumsq / testset;
		double sqmean = mean * mean;
		double var = meansq - sqmean;
		std::cout << "    Mean:     " << mean << " [0.00]\n" << "    Variance: "
				<< var << " [1.00]\n" << "    -inf...-2.5: "
				<< (static_cast<double>(x[0]) / testset * 100.0)
				<< "% [0.6%]\n";
		for (i = 1; i < 10; i++)
		{
			std::cout << "    " << ((i - 5) / 2.0 - 0.5) << "..."
					<< ((i - 5) / 2.0 + 0.5) << ": "
					<< (static_cast<double>(x[i]) / testset * 100.0) << "% ["
					<< erf[i] << "%]\n";
		}
		std::cout << "    +2.5...+inf: "
				<< (static_cast<double>(x[10]) / testset * 100.0)
				<< "% [0.6%]\n";
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testGaussianPolar(RNG& rng)
	{
		std::cout << std::setprecision(2);
		std::cout << "  Testing Gaussian Polar Method --------------------\n";
		double targetmean = rng.FromTo(-10, 10);
		double targetvar = rng.FromTo(0.001, 1);
		std::cout << "    Test task: Mean " << targetmean << ", Variance "
				<< targetvar << "\n";
		double sum = 0;
		double sumsq = 0;
		int testset = 10000000;
		int i;
		long t1 = time(0);
		for (i = 0; i < testset; i++)
		{
			double res = rng.GaussianPolar(targetmean, targetvar);
			sum += res;
			sumsq += res * res;
		}
		long t2 = time(0);
		double mean = sum / testset;
		double meansq = sumsq / testset;
		double sqmean = mean * mean;
		double var = meansq - sqmean;
		std::cout << "    Mean:     " << mean << " [" << targetmean << "]\n"
				<< "    Variance: " << var << " [" << targetvar << "]\n";
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testExponential(RNG& rng)
	{
		std::cout << std::setprecision(2);
		std::cout << "  Testing Exponential --------------------\n";
		double targetmean = rng.FromTo(0.1, 10);
		double targetvar = targetmean * targetmean;
		std::cout << "    Test task: Mean " << targetmean << ", Variance "
				<< targetvar << "\n";
		double sum = 0;
		double sumsq = 0;
		int testset = (int) 1e7;
		int i;
		long t1 = time(0);
		for (i = 0; i < testset; i++)
		{
			double res = rng.Exponential(targetmean);
			sum += res;
			sumsq += res * res;
		}
		long t2 = time(0);
		double mean = sum / testset;
		double meansq = sumsq / testset;
		double sqmean = mean * mean;
		double var = meansq - sqmean;
		std::cout << "    Mean:     " << mean << " [" << targetmean << "]\n"
				<< "    Variance: " << var << " [" << targetvar << "]\n";
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}

	template<class RNG>
	static void testGamma(RNG& rng)
	{
		std::cout << std::setprecision(3);
		double shape;
		double scale;
		std::cout << "  Testing Gamma --------------------\n";
		for (int j = 0; j < 2; j++)
		{
			scale = rng.FromTo(0.1, 2);
			if (j == 0)
				shape = rng.FromTo(0.1, 1);
			if (j == 1)
				shape = rng.FromTo(1, 3);
			double targetmean = scale * shape;
			double targetvar = targetmean * scale;

			if (j == 0)
				std::cout << "    Test task: Mean " << targetmean
						<< ", Variance " << targetvar
						<< " for shape <  1 (shape " << shape << ", scale "
						<< scale << ")\n";
			if (j == 1)
				std::cout << "    Test task: Mean " << targetmean
						<< ", Variance " << targetvar
						<< " for shape >= 1 (shape " << shape << ", scale "
						<< scale << ")\n";

			double sum = 0;
			double sumsq = 0;
			int testset = (int) 1e7;
			long t1 = time(0);
			for (int i = 0; i < testset; i++)
			{
				double res = rng.Gamma(shape, scale);
				sum += res;
				sumsq += res * res;
			}
			long t2 = time(0);
			double mean = sum / testset;
			double meansq = sumsq / testset;
			double sqmean = mean * mean;
			double var = meansq - sqmean;
			std::cout << "    Mean:     " << mean << " [" << targetmean << "]\n"
					<< "    Variance: " << var << " [" << targetvar << "]\n";
			std::cout << "    Time: " << t2 - t1 << "s\n\n";
		}
	}

	template<class RNG>
	static void testBeta(RNG& rng)
	{
		std::cout << std::setprecision(3);
		std::cout << "  Testing Beta --------------------\n";
		double shape1 = rng.FromTo(0.1, 3);
		double shape2 = rng.FromTo(0.1, 3);
		double targetmean = shape1 / (shape2 + shape1);
		double targetvar = (shape1 * shape2)
				/ ((shape1 + shape2) * (shape1 + shape2)
						* (shape1 + shape2 + 1.));
		std::cout << "    Test task: Mean " << targetmean << ", Variance "
				<< targetvar << " (shape1 " << shape1 << ", shape2 " << shape2
				<< ")\n";
		double sum = 0;
		double sumsq = 0;
		int testset = (int) 1e7;
		int i;
		long t1 = time(0);
		for (i = 0; i < testset; i++)
		{
			double res = rng.Beta(shape1, shape2);
			sum += res;
			sumsq += res * res;
		}
		long t2 = time(0);
		double mean = sum / testset;
		double meansq = sumsq / testset;
		double sqmean = mean * mean;
		double var = meansq - sqmean;
		std::cout << "    Mean:     " << mean << " [" << targetmean << "]\n"
				<< "    Variance: " << var << " [" << targetvar << "]\n";
		std::cout << "    Time: " << t2 - t1 << "s\n\n";
	}
};

#endif /* RNGTESTS_H_ */
