#ifndef RANDOM_H
#define RANDOM_H
#include <vector>
#include <random>
#include <chrono>

static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
//Randomly choose a interger in the range [l,r].
template<typename int_type,typename distrib=std::uniform_int_distribution<int_type>>
int_type randint(int_type l,int_type r,std::mt19937& gen=gen)
{
	distrib rand(l,r);
	return rand(gen);
}

//Randomly choose a real number in the range [l,r].
template<typename real_type,typename distrib=std::uniform_real_distribution<real_type>>
real_type randreal(real_type l,real_type r,std::mt19937& gen=gen)
{
	distrib rand(l,r);
	return rand(gen);
}

#endif