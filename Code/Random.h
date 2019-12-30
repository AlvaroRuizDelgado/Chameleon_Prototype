#pragma once
#include <random>

class Random
{
public:
	static void Init();
	static void Seed(unsigned int seed);

	static int GetIntRange(int min, int max);
	static float GetFloatRange(float min, float max);
	// Get float between 0.0f and 1.0f
	static float GetFloat();

private:
	// Random-number engine used (Mersenne-Twister for guaranteed unbiased)
	static std::mt19937 s_rng;
};