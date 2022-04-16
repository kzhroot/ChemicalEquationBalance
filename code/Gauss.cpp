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
const LD _minN=1E-8;
const T _maxN=220;
const T _maxM=220;
const T _mod=1e9+7;

struct Matrix
{
	T _n,_m;
	LD _num[_maxN][_maxM];
	
	inline Matrix operator + (const Matrix& _T) const
	{
		Matrix _result;
		_result._n=_n,_result._m=_m;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_result._num[i][j]=_num[i][j]+_T._num[i][j];
		return _result;
	}
	
	inline Matrix operator - (const Matrix& _T) const
	{
		Matrix _result;
		_result._n=_n,_result._m=_m;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_result._num[i][j]=_num[i][j]-_T._num[i][j];
		return _result;
	}
	
	inline Matrix operator * (T _number) const
	{
		Matrix _result;
		_result._n=_n,_result._m=_m;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_result._num[i][j]=_num[i][j];
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_result._num[i][j]=_result._num[i][j]*_number;
    	return _result;
	}
	
	inline Matrix operator * (const Matrix& _T) const
	{
    	Matrix _result;
    	_result._n=_n,_result._m=_T._m;
    	T _current;
    	for(int i=1;i<=_result._n;i++)
    		for(int j=1;j<=_result._m;j++)
    			_result._num[i][j]=0;
    	for(int i=1;i<=_result._n;i++)
    		for(int k=1;k<=_m;k++)
    		{
    			_current=_num[i][k];
    			for(int j=1;j<=_result._m;j++)
    				_result._num[i][j]+=_T._num[k][j]*_current,
					/*_result._num[i][j]%=_mod*/1;
			}
		return _result;
	}
	
	inline Matrix operator ^ (T _ord) const
	{
		Matrix _result,_temporary;
		_result._n=_n,_result._m=_m;
		_temporary._n=_n,_temporary._m=_m;
		for(int i=1;i<=_n;i++)
			_result._num[i][i]=1;
		for(int i=1;i<=_n;i++)
			for(int j=1;j<=_m;j++)
				_temporary._num[i][j]=_num[i][j];
		while(_ord)
		{
			if(_ord&1)
				_result=_result*_temporary;
			_temporary=_temporary*_temporary;
			_ord>>=1;
		}
    	return _result;
	}
	
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
		for(int i=1;i<=_n;i++,cout<<endl)
			for(int j=1;j<=_m;j++)
				cout<<_num[i][j]<<' ';
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
	return ;
}

Matrix A,B,C;
int n;

signed main()
{
	freopen("1.txt","r",stdin);
	cin>>n;
	A._n=A._m=B._n=n;
	B._m=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cin>>A._num[i][j];
		cin>>B._num[i][1];
	}
	C=A|B;
	
	gauss(C);
	C.print();
	return 0;
}
