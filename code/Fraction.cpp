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
	inline const Frac operator = (const int& tempNum)
	{
		_mole=tempNum,_deno=1;
		return *this;
	}
	inline const Frac operator = (const Frac& tempNum)
	{
		int _nextGcd=_gcd(tempNum._mole,tempNum._deno);
		_mole=tempNum._mole/_nextGcd,_deno=tempNum._deno/_nextGcd;
		return *this;
	}
	inline const Frac operator + (const Frac& tempNum) const
	{
		int _nextMole=_mole*tempNum._deno+_deno*tempNum._mole,
		_nextDeno=_deno*tempNum._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const Frac operator - (const Frac& tempNum) const
	{
		int _nextMole=_mole*tempNum._deno-_deno*tempNum._mole,
		_nextDeno=_deno*tempNum._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const Frac operator * (const Frac& tempNum) const
	{
		int _nextMole=_mole*tempNum._mole,
		_nextDeno=_deno*tempNum._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const Frac operator * (const int& tempNum) const
	{
		int _nextMole=_mole*tempNum,
		_nextDeno=_deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const Frac operator / (const Frac& tempNum) const
	{
		int _nextMole=_mole*tempNum._deno,
		_nextDeno=_deno*tempNum._mole;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const Frac operator / (const int& tempNum) const
	{
		int _nextMole=_mole,
		_nextDeno=_deno*tempNum;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline const bool operator > (const Frac& tempNum) const
	{
		return _mole*tempNum._deno>_deno*tempNum._mole;
	}
	inline const bool operator < (const Frac& tempNum) const
	{
		return _mole*tempNum._deno<_deno*tempNum._mole;
	}
	inline const bool operator <= (const Frac& tempNum) const
	{
		return _mole*tempNum._deno<=_deno*tempNum._mole;
	}
	inline const bool operator == (const Frac& tempNum) const
	{
		return _mole*tempNum._deno==_deno*tempNum._mole;
	}
	inline const Frac abs()
	{
		_mole=fabs(_mole),_deno=fabs(_deno);
		return *this;
	}
	inline void print()
	{
		cout<<_mole<<"/"<<_deno<<" ";
	}
};

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	return 0;
}
