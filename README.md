# St. Butterfly Pub Data Generator Library

## 1 简介

该库为 St. Butterfly Pub 群员共同开发的 C++ 下的随机数据生成库，现支持如下功能：

- 基于 `<random>` 库的随机整数与随机实数；
- 基于随机父亲的随机(带权)树；
- 随机(无向)(带权)图。

## 2 使用说明

###2.1  随机模块 `lib/random.h`

#### 2.1.1 `static std::mt19937 gen;`

全局变量，用于填充绝大多数函数的默认种子参数。

#### 2.1.2 `int_type randint(int_type l,int_type r,std::mt19937& gen=gen)`

等概率随机生成一个位于 $[l,r]$，类型为 `int_type` 的整数。

##### 2.1.2.1 参数说明

- `typename int_type` （模板参数）：指定返回类型；
- `int_type l` ：返回值下限；
- `int_type r` ：返回值上限；
- `std::mt19937& gen = gen` ：用于生成的种子，默认为 `static std::mt19937 gen`。

##### 2.1.2.2 注意事项

- 需要保证 `l` 和 `r` 相同类型且均为整数类型。

##### 2.1.2.3 示例代码

```cpp
#include "lib/random.h"
#include <iostream>
#include <time.h>
#include <random>

int main()
{
	int r1=randint(1,3); //返回一个位于 [1,3] 之间的 int
	long long r2=randint<long long>(1,3); //返回一个位于 [1,3] 之间的 long long
	std::mt19937 my_gen(time(0));
	long long r3=randint(1ll,100ll,my_gen); //以 my_gen 为种子生成一个位于 [1,100] 的 long long
	std::cout<<r1<<' '<<r2<<' '<<r3;
	return 0;
}
```

#### 2.1.3 `real_type randreal(real_type l,real_type r,std::mt19937& gen=gen)`

等概率随机生成一个位于 $[l,r]$，类型为 `real_type` 的实数。

##### 2.1.3.1 参数说明

- `typename real_type` （模板参数）：指定返回类型；
- `real_type l` ：返回值下限；
- `real_type r` ：返回值上限；
- `std::mt19937& gen = gen` ：用于生成的种子，默认为 `static std::mt19937 gen`。

##### 2.1.3.2 注意事项

- 需要保证 `l` 和 `r` 相同类型且均为实数类型。

##### 2.1.3.3 示例代码

```cpp
#include "lib/random.h"
#include <iostream>
#include <time.h>
#include <random>

int main()
{
	double r1=randreal(1.0,3.0); //返回一个位于 [1,3] 之间的 double
	long double r2=randreal<long double>(1,3); //返回一个位于 [1,3] 之间的 long double
	std::mt19937 my_gen(time(0));
	float r3=randreal(1.0f,100.0f,my_gen); //以 my_gen 为种子生成一个位于 [1,100] 的 float
	std::cout<<r1<<' '<<r2<<' '<<r3;
	return 0;
}
```

### 2.2 图论模块 `lib/graph.h`

#### 2.2.1 `struct Edge`

用于储存无权边。

##### 2.2.1.1 成员

- `size_t start` ：边的起点；
- `size_t end` ：边的终点。

#### 2.2.2 `struct Weighted_Edge`

用于储存带权边。

##### 2.2.2.1 参数与成员

- `typename weight_type`（模板参数）：权值类型；
- `size_t start` ：边的起点；
- `size_t end` ：边的终点；
- `weight_type weight` ：边的权值。

#### 2.2.3 `std::vector<Weighted_Edge<weight_type>> W_Tree_Father(size_t,weight_gentype,double,double,bool,std::mt19937&)`

以随机父亲的方法生成一个权值类型为 `weight_type` 的有权树，用 `std::vector<Weighted_Edge<weight_type>>` 储存。

##### 2.2.3.1 参数

- `typename weight_type`（模板参数）：权值类型；
- `typename weight_gentype`（模板参数）：权值生成器类型；
- `size_t n` ：树的结点个数；
- `weight_gentype weight_gen` ：权值生成器；
- `double chain_p = 0` ：链的占比，取值范围为 $[0,1]$，默认为 `0.0`；
- `double flower_p = 0` ：菊花的占比，取值范围为 $[0,1]$，默认为 `0.0`；
- `bool Shuffle = true` ：是否打乱点的顺序和边的顺序，默认为 `true`；
- `std::mt19937& gen = gen` ：用于随机点和打乱的种子，默认为 `static std::mt19937 gen`。

##### 2.2.3.2 注意事项

- `chain_p`、`flower_p` 与两者之和都要为 $[0,1]$ 间的实数；
- 一般需要填写模板参数 `typename weight_type`。

##### 2.2.3.3 示例代码

```cpp
#include "lib/graph.h"
#include <iostream>

int main()
{
	int n=20;
	auto G1=W_Tree_Father<int>(n,[](){return 1;}); //生成一个权值均为1的有n个节点的带权树，权值类型为 int
	auto G2=W_Tree_Father<double>(n,[](){return randreal(1.0,3.0);},0,0.25); //生成一个权值在[1,3]内的有n个节点的带权树，权值类型为 double，有1/4部分为菊花图
	auto G3=W_Tree_Father<long long>(n,[](){return randint(1,1000000);},0,0,false) //生成一个权值在[1,1000000]内的有n个节点的带权树，权值类型为 long long，不打乱点和边的顺序
	return 0;
}
```

#### 2.2.4 `std::vector<Edge> Tree_Father(size_t,double,double,bool,std::mt19937&)`

以随机父亲的方法生成一棵树，用 `std::vector<Edge>` 储存。

##### 2.2.4.1 参数

- `size_t n`：树的结点个数；
- `double chain_p = 0` ：链的占比，取值范围为 $[0,1]$，默认为 `0.0`；
- `double flower_p = 0` ：菊花的占比，取值范围为 $[0,1]$，默认为 `0.0`；
- `bool Shuffle = true` ：是否打乱点的顺序和边的顺序，默认为 `true`；
- `std::mt19937& gen = gen` ：用于随机点和打乱的种子，默认为 `static std::mt19937 gen`。

##### 2.2.4.2 注意事项

- `chain_p`、`flower_p` 与两者之和都要为 $[0,1]$ 间的实数；
- 一般需要填写模板参数 `typename weight_type`。

##### 2.2.4.3 示例代码

```cpp
#include "lib/graph.h"
#include <iostream>

int main()
{
	int n=20;
	auto G1=Tree_Father(n); //生成一个有n个节点的树
	auto G2=Tree_Father(n,0,0.25); //生成一个有n个节点的树，有1/4部分为菊花图
	auto G3=Tree_Father(n,0.5,0,false) //生成一个有n个节点的树，有1/2的部分为链，不打乱点和边的顺序
	return 0;
}
```

#### 2.2.5 `std::vector<Edge> Graph(size_t,size_t,Tree_gentype,bool,bool,bool,bool,std::mt19937&)`

生成一张图，用 `std::vector<Edge>` 储存。需调用 `Tree_gentype` 函数生成一棵树，该函数应支持接受单一参数 `size_t n`。

##### 2.2.5.1 参数

- `typename Tree_gentype`（模板参数）：随机生成树的函数类型；
- `size_t n`：图的点数；
- `size_t m`：图的边数；
- `Tree_gentype tree_gen`：随机数生成函数；
- `bool repeat = false`：是否允许有重边，默认为 `false`；
- `bool self_loop = false`：是否允许有自环，默认为 `false`；
- `bool connected = true`：图是否联通，默认为 `true`；
- `bool Shuffle = true` ：是否打乱点的顺序和边的顺序，默认为 `true`；
- `std::mt19937& gen = gen` ：用于随机点、边和打乱的种子，默认为 `static std::mt19937 gen`。

##### 2.2.5.2 示例代码

```cpp
#include "lib/graph.h"
#include <iostream>

int main()
{
	int n=20,m=30;
  auto G1=Garph(n,m,[](int n){return Tree_Father(n);}); //生成一张有n个结点和m条边的连通简单图
  auto G2=Graph(n,m,[](int n){return Tree_Father(n);},1,1,0,0); //生成一张有n个结点和m条边的不联通、允许出现重边和自环的图，不打乱点和边的顺序
  auto G3=Graph(n,m,[](int n){return Tree_Father(n,1,0);}); //在一条链的基础上生成一张有n个结点和m条边的连通简单图
	return 0;
}
```

#### 2.2.6 `std::vector<Weighted_Edge<weight_type>> W_Graph(size_t,size_t,weight_gentype,WeightedTree_gentype,bool,bool,bool,bool,std::mt19937&)`

生成一张权值类型为 `weight_type` 的带权图。需调用 `Tree_gentype` 函数生成一棵树，该函数应支持接受单一参数 `size_t n`。

##### 2.2.6.1 参数

- `typename weight_type`（模板参数）：权值类型；
- `typename weight_gentype`（模板参数）：权值生成器类型；
- `typename WeightedTree_gentype`（模板参数）：随机生成带权树的函数类型；
- `size_t n`：图的点数；
- `size_t m`：图的边数；
- `Tree_gentype tree_gen`：随机数生成函数；
- `bool repeat = false`：是否允许有重边，默认为 `false`；
- `bool self_loop = false`：是否允许有自环，默认为 `false`；
- `bool connected = true`：图是否联通，默认为 `true`；
- `bool Shuffle = true` ：是否打乱点的顺序和边的顺序，默认为 `true`；
- `std::mt19937& gen = gen` ：用于随机点、边和打乱的种子，默认为 `static std::mt19937 gen`。

#### 2.2.6.2 示例代码

```cpp
#include "lib/graph.h"
#include <iostream>

int main()
{
	int n = 20, m = 30;
  auto G1 = W_Graph<int>(
    n, m,
    []() { return 0; },
    []() { return W_Tree_Father<int>(n, []() { return 0; }); }
  ); //生成一张有n个结点和m条边的连通简单图，权值均为0
  auto G2 = W_Graph<double>(
    n, m,
    []() { return randreal(1.0, 3.0); },
    []() { return W_Tree_Father<double>(n, []() { return ranreal(1.0, 3.0); }); },
    1, 1, 1, 1
  ); //生成一张有n个结点和m条边的连通图，权值均为[1,3]中的实数，允许出现重边和自环，不打乱点和边的顺序
	return 0;
}
```

