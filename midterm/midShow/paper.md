# 基于矩阵的化学方程式配平的编程实现

**内容摘要：**通过对化学方程式配平的数学本质的探讨，设计出相关算法并使用编程语言实现。分析数学算法优劣与算法实现复杂度分析。

**关键词：**矩阵消元法 线性方程组 化学方程式配平 编程

#### 一、绪论

我们知道，化学反应是遵循质量守恒定律的。即在化学反应前后，参加反应的各物质的质量总和等于反应后生成的各物质的质量总和。基于此，我们可以知道，化学反应前后原子种类、原子数目、原子质量、元素种类等等都是不发生改变的，化学方程式两边同一种原子是满足数量相等这样的条件的。根据这一结论，我们可以尝试用”待定系数法“来配平化学方程式。

具体操作中，我们对于方程中的每一项都为其设置一项系数，然后列出方程组求解。例如$NaAlO_2+CO_2+H_2O==Al(OH)_3+Na_2CO_3$（未配平），我们分别将$NaAlO_2,CO_2,H_2O,Al(OH)_3,Na_2CO_3$系数设为$x_1,x_2,x_3,x_4,x_5$，基于上述结论，有如下方程组：
$$
\begin{cases}{x_1=2x_5}(Na原子守恒)\\{x1=x4(Al原子守恒)}\\{2x_1+2x_2+x_3=3x_4+3x_5(O原子守恒)}\\{2x_3=3x_4(H原子守恒)}\end{cases}
$$
但这个方程组中有5个未知数而只有4个方程，无法确定一个确定的解。这是因为化学方程式中这些系数都是成一种固定比例关系（如果方程式确定的话）。因而，我们可以设$x_5=1$，容易解得：
$$
\begin{cases}{x_1=2}\\{x_2=1}\\{x_3=3}\\{x_4=2}\\{x_5=1}\end{cases}
$$
这已经是最简形式。根据化学常识，原方程式确实满足这样的关系。但这个方程式这样的解也算是一种巧合。比如说，如果我们设$x_4=1$，则有：
$$
\begin{cases}{x_1=1}\\{x_2=1/2}\\{x_3=3/2}\\{x_4=1}\\{x_5=1/2}\end{cases}
$$
这就需要我们对每项乘以2将答案化简到最简。

观察这个例子，我们发现对于化学方程式的配平，确实是相当于解一个线性方程组。我们设每项系数分别为$x_1,x_2,x_3,...,x_m$，$a_{i,j}$为第$i$种原子在第$j$个项中的数量。一般的，有：
$$
\begin{cases}{a_{1,1}x_1+a_{1,2}x_2+a_{1,3}x_3+...+a_{1,m}x_m}=0\\ {a_{2,1}x_1+a_{2,2}x_2+a_{2,3}x_3+...+a_{2,m}x_m=0}\\...\\ {a_{n,1}x_1+a_{n,2}x_2+a_{n,3}x_3+...+a_{n,m}x_m=0}\end{cases}
$$
其中，$a_{i,j}$在等号左边时为对应的值，在等号右边时为对应的值的相反数。而化学方程式配平的最终答案就是解得的对应的$x$的值。

既然是线性方程组，那么我们可以借助线性代数中的矩阵的相关知识。将以上方程组写成矩阵形式，那么即为：
$$
\left[
\begin{matrix}
a_{1,1} & a_{1,2} & \cdots & a_{1,m}\\
a_{2,1} & a_{2,2} & \cdots & a_{2,m}\\
\vdots & \vdots & \ddots & \vdots\\
a_{n,1} & a_{n,2} & \cdots & a_{n,m}
\end{matrix}
\right]
\left[
\begin{matrix}
x_{1}\\
x_{2}\\
\vdots\\
x_{n}
\end{matrix}
\right]
=
\left[
\begin{matrix}
0\\
0\\
\vdots\\
0
\end{matrix}
\right]
$$
#### 二、求解算法

##### (一)基本概念介绍

###### 1.矩阵

在数学中，矩阵（Matrix）是一个按照长方阵列排列的复数或实数集合，最早来自于方程组的系数及常数所构成的方阵。这一概念由19世纪英国数学家凯利首先提出。

**定义：**由$n×m$个数$a_{i,j}$排成的$n$行$m$列的数表称为$n$行$m$列的矩阵，简称$n×m$矩阵。记作：
$$
A=
\left[
\begin{matrix}
a_{1,1} & a_{1,2} & \cdots & a_{1,m}\\
a_{2,1} & a_{2,2} & \cdots & a_{2,m}\\
\vdots & \vdots & \ddots & \vdots\\
a_{n,1} & a_{n,2} & \cdots & a_{n,m}
\end{matrix}
\right]
$$
这$n×m$个数称为矩阵$A$的元素，简称为元。数$a_{i,j}$位于矩阵$A$的第$i$行第$j$列，称为矩阵$A$的$(i,j)$元，$n×m$矩阵A也记作$A_{nm}$。

###### 2.消元法

**定义：**消元法是指将许多关系式中的若干个元素通过有限次地变换，消去其中的某些元素，从而使问题获得解决的一种解题方法。简单来说，消元法是将方程组中的一方程的未知数用含有另一未知数的代数式表示，并将其代入到另一方程中，这就消去了一未知数，得到一解；或将方程组中的一方程倍乘某个常数加到另外一方程中去，也可达到消去一未知数的目的。消元法是多种方法的统称。

消元法理论的核心主要如下：

- 两方程互换，解不变；
- 一方程乘以非零数$k$，解不变；
- 一方程乘以数$k$加上另一方程，解不变。

##### (二)高斯消元法

在求解线性方程组中，高斯消元法有着重要地位。其首先将方程的增广矩阵（增广矩阵即将系数矩阵与常数矩阵的增广）利用行初等变换化为行最简形，然后以线性无关为准则对自由未知量赋值，最后列出表达方程组通解。

它主要有五个步骤：

1. 增广矩阵行初等行变换为行最简形；
2. 还原线性方程组；
3. 求解第一个变量；
4. 补充自由未知量；
5. 列表示方程组通解。

我们这边省去举例，读者可自行上网搜索。

依据以上对矩阵及高斯消元法的认识，我们不难得出高斯消元法的算法实现：

1. 将输入的方程式写成增广矩阵形式。

2. 消元：对矩阵进行初等变换，主要包括这些操作：(1)将某行同乘或同除一个非零实数；(2)将某行加到另一行；(3)将任意两行互换；（这些也是消元法的基本内容）。

3. 将消元过后的矩阵变换成上三角矩阵，即主对角线全为1，左下三角矩阵全为0。形式如下：
   $$
   [A' B']=
   \left
   [
   \begin
   {matrix}1 & a_{1,2}^{'} & a_{1,3}^{'} & \cdots & \cdots & a_{1,m}^{'} & b_{1}^{'} \\
   0 & 1 & a_{2,3}^{'} & \cdots & \cdots & a_{2,m}^{'} & b_{2}^{'} \\
   0 & 0 & 1 & \ddots & \cdots & a_{3,m}^{'} & b_{3}^{'} \\
   0 & 0 & 0 & \ddots & \ddots & \vdots & \vdots \\
   \vdots & \vdots & \vdots & \ddots & 1 & a_{n-1,m}^{'} & \vdots \\
   0 & 0 & 0 & \cdots & 0 & 1 & b_{n}^{'} \\
   \end{matrix}
   \right]
   $$

4. 最后回带求解。

这便是高斯消元法的一般过程。

##### （三）实现算法

但因为我们是化学方程式的配平，可以对高斯消元法的一般算法进行改造。

在化学方程式配平中，结合绪论中我们将化学方程式写成的矩阵的形式，我们可以知道：最终的常数矩阵都是0，这也完全不必写入到代码中去。因为化学方程式各项的系数是等比例发生改变的，那么我们可以将某一项的未知数直接设为1，再将它作为常数项进行操作。这样做有这些好处：可以简化运算，少了一个维度的数组的开支；可以有效避免一些高斯消元法里存在的局限。