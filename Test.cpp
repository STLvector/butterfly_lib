#include "butterfly.h"
#include <iostream>

int main()
{
	int n=randint(1,10),m=randint(n-1,20);
	double p=randreal(0.0,1.0);
	auto G=U_Graph(n,m,[](int n){return Tree_Father(n);});
	std::cout<<n<<' '<<m<<' '<<p<<'\n';
	for(int i=0;i<m;i++)
		std::cout<<G[i].start<<' '<<G[i].end<<'\n';
	return 0;
}