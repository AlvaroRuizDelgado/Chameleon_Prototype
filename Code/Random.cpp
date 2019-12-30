#include "Random.h"

void Random::Init()
{
	std::random_device rd;     // only used once to initialise (seed) engine
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed)
{
	s_rng.seed(seed);
}

int Random::GetIntRange(int min, int max)
{
	std::uniform_int_distribution<int> uniformDistribution(min, max);
	return uniformDistribution(s_rng);
}

float Random::GetFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> uniformDistribution(min, max);
	return uniformDistribution(s_rng);
}

// Get float between 0.0f and 1.0f
float Random::GetFloat()
{
	return GetFloatRange(0.f, 1.f);
}

// Declared explicitly for static functions
std::mt19937 Random::s_rng;