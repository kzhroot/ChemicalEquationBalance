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

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	return 0;
}
