#include <bits/stdc++.h>
#define int long long

using namespace std;

typedef long long LL;
typedef int T;
const long long maxN=2000010;
const T _maxN=110;
const T _maxM=110;
const T _mod=1e9+7;

struct Matrix
{
	T _n,_m;
	T _num[_maxN][_maxM];
	
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
					_result._num[i][j]%=_mod;
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

signed main()
{
	
	return 0;
}
