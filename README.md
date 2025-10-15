# St. Butterfly Pub Data Generator Library

## 简介

该库为 St. Butterfly Pub 群员共同开发的 C++ 下的随机数据生成库，现支持如下功能：

- 基于 `<random>` 库的随机整数与随机实数
- 基于随机父亲的随机(带权)树
- 随机(无向)(带权)图

## 使用说明

### 随机模块 `lib/random.h`

#### `static std::mt19937 gen;`

全局变量，用于填充绝大多数函数的默认种子参数。

#### `int_type randint(int_type l,int_type r,std::mt19937& gen=gen)`

等概率随机生成一个位于 $[l,r]$，类型为 `int_type` 的整数。

##### 参数说明

- `typename int_type` （模板参数）：指定返回类型
- `int_type l` ：返回值下限
- `int_type r` ：返回值上限
- `std::mt19937& gen = gen` ：用于生成的种子，默认为 `static std::mt19937 gen`

##### 注意事项

- 需要保证 `l` 和 `r` 相同类型且均为整数类型

##### 示例代码

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

#### `real_type randreal(real_type l,real_type r,std::mt19937& gen=gen)`

等概率随机生成一个位于 $[l,r]$，类型为 `real_type` 的实数。

##### 参数说明

- `typename real_type` （模板参数）：指定返回类型
- `real_type l` ：返回值下限
- `real_type r` ：返回值上限
- `std::mt19937& gen = gen` ：用于生成的种子，默认为 `static std::mt19937 gen`

##### 注意事项

- 需要保证 `l` 和 `r` 相同类型且均为实数类型

##### 示例代码

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

### 图论模块 `lib/graph.h`

#### `struct Edge`

用于储存无权边。

##### 成员

- `size_t start` ：边的起点
- `size_t end` ：边的终点

#### `struct Weighted_Edge`

用于储存带权边。

##### 参数与成员

- `typename weight_type`（模板参数）：权值类型
- `size_t start` ：边的起点
- `size_t end` ：边的终点
- `weight_type weight` ：边的权值

#### `std::vector<Weighted_Edge<weight_type>> W_Tree_Father(size_t,weight_gentype,double,double,bool,std::mt19937&)`

以随机父亲的方法生成一个权值类型为 `weight_type` 的有权树，用 `std::vector<Weighted_Edge<weight_type>>` 储存。

##### 参数

- `typename weight_type`（模板参数）：权值类型
- `typename weight_gentype`（模板参数）：权值生成器类型
- `size_t n` ：树的结点个数
- `weight_gentype weight_gen` ：权值生成器
- `double chain_p = 0` ：链的占比，取值范围为 $[0,1]$，默认为 `0.0`
- `double flower_p = 0` ：菊花的占比，取值范围为 $[0,1]$，默认为 `0.0`
- `bool Shuffle = true` ：是否打乱点的顺序和边的顺序，默认为 `true`
- `std::mt19937& gen = gen` ：用于随机点和打乱的种子，默认为 `static std::mt19937 gen`

##### 注意事项

- `chain_p`、`flower_p` 与两者之和都要为 $[0,1]$ 间的实数。
- 一般需要填写模板参数 `typename weight_type`。

##### 示例代码

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