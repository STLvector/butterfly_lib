#ifndef GRAPH_H
#define GRAPH_H
#include "random.h"
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <set>

struct Edge{size_t start,end;};
template<typename weight_type>
struct Weighted_Edge{size_t start,end;weight_type weight;};

template<typename weight_type,typename weight_gentype>
std::vector<Weighted_Edge<weight_type>> W_Tree_Father(size_t n,weight_gentype weight_gen,double chain_p=0,double flower_p=0,bool Shuffle=true,std::mt19937& gen=gen)
{
	std::vector<Weighted_Edge<weight_type>> T;
	if(chain_p<0||1<chain_p||flower_p<0||1<flower_p)
		throw std::out_of_range("chain and flower must be between 0 and 1.");
	if(chain_p+flower_p>1)
		throw std::out_of_range("chain plus flower must be smaller 1.");
	size_t flower=(n-1)*flower_p,chain=(n-1)*chain_p;
	if(chain+flower>n-1) chain=n-1-flower;
	for(size_t v=2;v<=chain+1;v++)
		T.push_back({v-1,v,weight_gen()});
	for(size_t v=chain+2;v<=chain+flower+1;v++)
		T.push_back({1,v,weight_gen()});
	for(size_t v=chain+flower+2;v<=n;v++)
		T.push_back({randint<size_t>(1,v-1,gen),v,weight_gen()});
	if(Shuffle)
	{
		std::vector<int> p(n+1);
		std::iota(p.begin(),p.end(),0);
		std::shuffle(p.begin()+1,p.end(),gen);
		for(auto& e:T)
		{
			e.start=p[e.start];
			e.end=p[e.end];
			if(randint(0,1)==1)
				std::swap(e.start,e.end);
		}
		std::shuffle(T.begin(),T.end(),gen);
	}
	return T;
}
//Prufer
//Others

std::vector<Edge> Tree_Father(size_t n,double chain_p=0,double flower_p=0,bool Shuffle=true,std::mt19937& gen=gen)
{
	std::vector<Edge> T;
	if(chain_p<0||1<chain_p||flower_p<0||1<flower_p)
		throw std::out_of_range("chain and flower must be between 0 and 1.");
	if(chain_p+flower_p>1)
		throw std::out_of_range("chain plus flower must be smaller 1.");
	size_t flower=(n-1)*flower_p,chain=(n-1)*chain_p;
	if(chain+flower>n-1) chain=n-1-flower;
	for(size_t v=2;v<=chain+1;v++)
		T.push_back({v-1,v});
	for(size_t v=chain+2;v<=chain+flower+1;v++)
		T.push_back({1,v});
	for(size_t v=chain+flower+2;v<=n;v++)
		T.push_back({randint<size_t>(1,v-1,gen),v});
	if(Shuffle)
	{
		std::vector<int> p(n+1);
		std::iota(p.begin(),p.end(),0);
		std::shuffle(p.begin()+1,p.end(),gen);
		for(auto& e:T)
		{
			e.start=p[e.start];
			e.end=p[e.end];
			if(randint(0,1)==1)
				std::swap(e.start,e.end);
		}
		std::shuffle(T.begin(),T.end(),gen);
	}
	return T;
}

template<typename Tree_gentype>
std::vector<Edge> Graph(size_t n,size_t m,Tree_gentype tree_gen,bool repeat=false,bool self_loop=false,bool connected=true,bool Shuffle=true,std::mt19937& gen=gen)
{
	if(!repeat)
	{
		size_t l=0,r=n*(n-1)/2;
		if(connected) l=n-1;
		if(self_loop) r+=n;
		if(m<l||r<m)
			throw std::out_of_range("The number of edges must between "+std::to_string(l)+" and "+std::to_string(r)+".");
	}
	std::set<std::pair<size_t,size_t>> used;
	std::vector<Edge> G;
	if(connected)
	{
		G=tree_gen(n);
		for(size_t i=0;i<n-1;i++)
		{
			used.insert({G[i].start,G[i].end});
			used.insert({G[i].end,G[i].start});
		}
	}
	for(size_t i=G.size()+1,u,v;i<=m;i++)
	{
		do
		{
			u=randint<size_t>(1,n,gen);
			v=randint<size_t>(1,n,gen);
			if((repeat||!used.count({u,v}))&&(self_loop||u!=v))
				break;
		}while(true);
		G.push_back({u,v});
		used.insert({u,v});
		used.insert({v,u});
	}
	if(Shuffle)
	{
		std::vector<int> p(n+1);
		std::iota(p.begin(),p.end(),0);
		std::shuffle(p.begin()+1,p.end(),gen);
		for(Edge& e:G)
		{
			e.start=p[e.start];
			e.end=p[e.end];
			if(randint(0,1)==1)
				std::swap(e.start,e.end);
		}
	}
	return G;
}

template<typename weight_type,typename weight_gentype,typename WeightedTree_gentype>
std::vector<Weighted_Edge<weight_type>> W_Graph(size_t n,size_t m,weight_gentype weight_gen,WeightedTree_gentype wtree_gen,bool repeat=false,bool self_loop=false,bool connected=true,bool Shuffle=true,std::mt19937& gen=gen)
{
	if(!repeat)
	{
		size_t l=0,r=n*(n-1)/2;
		if(connected) l=n-1;
		if(self_loop) r+=n;
		if(m<l||r<m)
			throw std::out_of_range("The number of edges must between "+std::to_string(l)+" and "+std::to_string(r)+".");
	}
	std::set<std::pair<size_t,size_t>> used;
	std::vector<Weighted_Edge<weight_type>> G;
	if(connected)
	{
		G=wtree_gen(n);
		for(size_t i=0;i<n-1;i++)
		{
			used.insert({G[i].start,G[i].end});
			used.insert({G[i].end,G[i].start});
		}
	}
	for(size_t i=G.size()+1,u,v;i<=m;i++)
	{
		do
		{
			u=randint<size_t>(1,n,gen);
			v=randint<size_t>(1,n,gen);
			if((repeat||!used.count({u,v}))&&(self_loop||u!=v))
				break;
		}while(true);
		G.push_back({u,v,weight_gen()});
		used.insert({u,v});
		used.insert({v,u});
	}
	if(Shuffle)
	{
		std::vector<int> p(n+1);
		std::iota(p.begin(),p.end(),0);
		std::shuffle(p.begin()+1,p.end(),gen);
		for(Weighted_Edge<weight_type>& e:G)
		{
			e.start=p[e.start];
			e.end=p[e.end];
			if(randint(0,1)==1)
				std::swap(e.start,e.end);
		}
	}
	return G;
}
#endif