//negative number!!! 
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const long long maxN=2000010; 

inline int _read()
{
	int _num=0,_sign=1;
	char _c=getchar();
	for(;!isdigit(_c);_c=getchar())
		if(_c=='-')
			_sign*=-1;
	for(;isdigit(_c);_c=getchar())
		_num=(_num<<3)+(_num<<1)+_c-'0';
	return _num*_sign;
}

int _gcd(int _x,int _y)
{
	return _y==0?:_gcd(_y,_x%_y);
}
	
struct Frac
{
	int _mole,_deno;
	inline Frac operator = (const int& _num) const
	{
		return (Frac){_num,1};
	}
	inline Frac operator = (const Frac& _T) const
	{
		int _nextGcd=_gcd(_T._mole,_T._deno);
		return (Frac){_T._mole/_nextGcd,_T._deno/_nextGcd};
	}
	inline Frac operator + (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno+_deno*_mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator - (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno-_deno*_mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator * (const Frac& _T) const
	{
		int _nextMole=_mole*_T._mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator / (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno,
		_nextDeno=_deno*_T._mole;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline bool operator > (const Frac& _T) const
	{
		return _mole*_T._deno>_deno*_mole;
	}
	inline bool operator < (const Frac& _T) const
	{
		return _mole*_T._deno<_deno*_mole;
	}
	inline bool operator == (const Frac& _T) const
	{
		return _mole*_T._deno==_deno*_mole;
	}
	inline Frac abs() const
	{
		if(_mole>0&&_deno>0)
			return (Frac){_mole,_deno};
		if(_mole<0&&_deno<0)
			return (Frac){-_mole,-_deno};
		return _mole<0?(Frac){_mole,_deno}:(Frac){-_mole,-_deno};
	}
};

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	return 0;
}
