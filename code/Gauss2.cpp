#define debugFun(x) cout<<"debugFunction: "<<__FUNCTION__<<"()"<<"\n"
#define debugFile(x) cout<<"debugFile: "<<__FILE__<<" L"<<__LINE__<<"\n"
#define debugPara(x) cout<<"debugParameter: "<<#x" = "<<(x)<<"\n"
#define dbg(x) cout<<x<<"\n"
#define debug(x) cout<<"debug: "<<__FUNCTION__<<"() @ "<<__TIMESTAMP__<<"\n"\
<<__FILE__<<" L"<<__LINE__<<"\n"<<#x" = "<<(x)<<"\n"
#include <bits/stdc++.h>
#define int long long
using namespace std;

typedef long long LL;
typedef int T;
typedef long double LD;
const long long maxN=2000010;
const LD _minN=1E-10;
const T _maxN=220;
const T _maxM=220;
const T _mod=1e9+7;

int curop=1;
int ans=1;

struct Matrix
{
	T _n,_m;
	LD _num[_maxN][_maxM];
	
	inline Matrix operator | (const Matrix& _T) const
	{
		Matrix _result;
		_result._n=_n;
		_result._m=_m+_T._m;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_result._num[i][j]=_num[i][j];
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_T._m;j++)
				_result._num[i][j+_m]=_T._num[i][j];
		return _result;
	}
	/*
	In fact,extend matrix is between matrix and fixed number.
	*/
	
	inline void scan()
	{
		cin>>_n>>_m;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				cin>>_num[i][j];
		return ;
	}
	
	inline void print()
	{
		cout<<_n<<" "<<_m<<endl;
		for(int i=1;i<=_n;i++,cout<<endl)
			for(int j=1;j<=_m;j++)
				cout<<_num[i][j]<<' ';
		cout<<endl;
		return ;
	}
};

void pri(int **num)
{
	for(int i=1;i<=10;i++,cout<<endl)
	{
		for(int j=1;j<=10;j++)
			cout<<num[i][j]<<' ';
	}
	return ;
}

void gauss(Matrix &_T)
{
	for(int i=1;i<=_T._n;i++)
	{
		int _current=i;
		for(int j=i;j<=_T._n;j++)
			if(fabs(_T._num[j][i])>fabs(_T._num[_current][i]))
				_current=j;
		for(int j=1;j<=_T._m;j++)
			swap(_T._num[i][j],_T._num[_current][j]);
		if(_T._num[i][i]==0)
			continue;
		LD curFir=_T._num[i][i];
		for(int j=1;j<=_T._m;j++)
			_T._num[i][j]/=curFir;
		for(int j=i+1;j<=_T._n;j++)
		{
			LD curSec=_T._num[j][i]/_T._num[i][i];
			for(int k=i;k<=_T._m;k++)
				_T._num[j][k]-=_T._num[i][k]*curSec;
		}
		/*for(int j=i+1;j<=_T._n+1;j++)
			_T._num[i][j]/=_T._num[i][i];
		for(int j=1;j<=_T._n;j++)
			if(i!=j)
				for(int k=i+1;k<=_T._n+1;k++)
					_T._num[j][k]-=_T._num[j][i]*_T._num[i][k];*/
		_T.print();
	}
	/*for(int i=1;i<=_T._n;i++)
	{
		int _current=i;
		for(int j=i;j<=_T._n;j++)
			if(fabs(_T._num[j][i]-_T._num[_current][i])<=_minN)
				_current=j;
		for(int j=1;j<=_T._n+1;j++)
			swap(_T._num[i][j],_T._num[_current][j]);
		if(fabs(_T._num[i][i])<=_minN)
		{
			printf("No Solution\n");
			return ;
		}
		for(int j=i+1;j<=_T._n+1;j++)
			_T._num[i][j]/=_T._num[i][i];
		for(int j=1;j<=_T._n;j++)
			if(i!=j)
				for(int k=i+1;k<=_T._n+1;k++)
					_T._num[j][k]-=_T._num[j][i]*_T._num[i][k];
	}
	for(int i=1;i<=_T._n;i++)
		printf("%.2Lf\n",_T._num[i][_T._n+1]);
	return ;*/
}



void yue1(Matrix &_T)
{
	/*for(int i=1;i<=_T._n;i++)
		_T._num[i][_T._m]=-_T._num[i][_T._m];*/
	for(int i=1;i<=_T._n;i++)
	{
		int _current=i;
		for(int j=i;j<=_T._n;j++)
		{
			if(fabs(_T._num[j][i])>fabs(_T._num[_current][i])&&fabs(fabs(_T._num[j][i])-fabs(_T._num[_current][i]))>=_minN)
				_current=j;
		}
		for(int j=1;j<=_T._m;j++)
			swap(_T._num[i][j],_T._num[_current][j]);
		if(fabs(_T._num[i][i])<=_minN)
			continue;
		LD curFir=_T._num[i][i];
		for(int j=1;j<=_T._m;j++)
			_T._num[i][j]/=curFir;
		for(int j=1;j<=_T._n;j++)
		{
			if(j==i)
				continue;
			LD curSec=_T._num[j][i]/_T._num[i][i];
			for(int k=i;k<=_T._m;k++)
				_T._num[j][k]-=_T._num[i][k]*curSec;
		}
		//_T.print();
	}
}

void yue(Matrix &_T)
{
	/*for(int i=1;i<=_T._n;i++)
		_T._num[i][_T._m]=-_T._num[i][_T._m];*/
	curop=1;
	for(int i=1;i<=_T._n;i++)
	{
		int _current=curop;
		for(int j=curop+1;j<=_T._n;j++)
		{
			if(fabs(_T._num[j][i])>fabs(_T._num[_current][i])&&fabs(fabs(_T._num[j][i])-fabs(_T._num[_current][i]))>=_minN)
				_current=j;
		}
		for(int j=1;j<=_T._m;j++)
			swap(_T._num[curop][j],_T._num[_current][j]);
		if(fabs(_T._num[curop][i])<=_minN)
			continue;
		LD curFir=_T._num[curop][i];
		for(int j=1;j<=_T._m;j++)
			_T._num[curop][j]/=curFir;
		/*for(int j=i+1;j<=_T._n;j++)
		{
			LD curSec=_T._num[j][i]/_T._num[i][i];
			for(int k=i;k<=_T._m;k++)
				_T._num[j][k]-=_T._num[i][k]*curSec;
		}*/
		for(int j=1;j<=_T._n;j++)
		{
			if(j==curop)
				continue;
			LD curSec=_T._num[j][i]/_T._num[curop][i];
			for(int k=i;k<=_T._m;k++)
				_T._num[j][k]-=_T._num[curop][k]*curSec;
		}
		curop++;
		//_T.print();
	}
}

int judge(Matrix &_T)
{
	if(curop<=_T._n)
	{
		while(curop<=_T._n)
		{
			if(fabs(_T._num[curop++][_T._m])!=0)
				return -1;
		}
		return 0;
	}
	return 1;
}

Matrix A,B,C;
int n;

signed main()
{
	freopen("1.txt","r",stdin);
	/*cin>>n;
	A._n=A._m=B._n=n;
	B._m=1;*/
	int curA,curB;
	/*cin>>curA>>curB;*/
	cin>>curA;
	curB=curA+1;
	/*A._n=curA,A._m=curB;
	B._n=curA,B._m=1;
	for(int i=1;i<=A._n;i++)
	{
		for(int j=1;j<=A._m;j++)
			cin>>A._num[i][j];
		cin>>B._num[i][1];
	}*/
	//C=A|B;
	C._n=curA,C._m=curB;
	for(int i=1;i<=C._n;i++)
		for(int j=1;j<=C._m;j++)
			cin>>C._num[i][j];
//	C.print();
	yue(C);
	//C.print();
	int ans=judge(C);
	//cout<<curop<<endl;
	if(ans!=1)
	{
		cout<<ans<<endl;
		return 0;
	}
	for(int i=1;i<=C._n;i++)
		printf("x%d=%.2Lf\n",i,C._num[i][C._m]);

	return 0;
}
