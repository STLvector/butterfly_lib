#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <random>
#include <chrono>

template<typename int_type>
using uniform_int=std::uniform_int_distribution<int_type>;
template<typename real_type>
using uniform_real=std::uniform_int_distribution<real_type>;

static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
//Randomly choose a number in the range [l,r].
template<typename distrib,typename ret_type>
ret_type random(ret_type l,ret_type r,std::mt19937& gen=gen)
{
	distrib rand(l,r);
	return rand(gen);
}

#endif