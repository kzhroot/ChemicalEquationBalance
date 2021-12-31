#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const long long maxN=20010; 

map<string,int>_map;
int _sum[maxN]={0};

void solve(string _num)
{
	int _cnt=0;
	string _curS="";
	memset(_sum,0,sizeof(_sum));
	for(int i=0;i<_num.length();i++)
	{
		if(_num[i]>='A'&&_num[i]<='Z')
		{
			_curS=_num[i];
			if(_num[i+1]>='a'&&_num[i+1]<='z')
				_curS+=_num[++i];
			if(!_map[_curS])
			{
				cout<<"UNKNOWN"<<endl;
				return ;
			}
			_sum[_cnt]+=_map[_curS];
		}
		else if(isdigit(_num[i]))
		{
			int _curN=0;
			while(isdigit(_num[i]))
				_curN*=10,_curN+=_num[i++]-'0';
			i--;
			_sum[_cnt]+=(_curN-1)*_map[_curS];
		}
		else if(_num[i]=='(')
			_cnt++;
		else if(_num[i]==')')
		{
			int _curN=0;
			while(isdigit(_num[++i]))
				_curN*=10,_curN+=_num[i]-'0';
			i--;
			_sum[_cnt-1]+=_curN*_sum[_cnt];
			_sum[_cnt--]=0;
		}
		else ;
	}
	cout<<_sum[0]<<endl;
	return ;
}

int main()
{
	string _curS;
	int _curWei;
	while(1)
	{
		cin>>_curS;
		if(_curS=="END_OF_FIRST_PART")
			break;
		cin>>_curWei;
		_map[_curS]=_curWei;
	}
	while(1)
	{	
		cin>>_curS;
		if(_curS=="0")
			break;
		solve(_curS);
	}
	return 0;
}
