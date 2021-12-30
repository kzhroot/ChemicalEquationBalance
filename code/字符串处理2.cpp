#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const long long maxN=20010; 

map<string,int>mapping;
string current="";
int wei;

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

int cSTI(string a)
{
	int temp=0;
	for(int i=0;i<a.length();i++)
		temp*=10,temp+=a[i]-'0';
	return temp; 
}

int main()
{
	freopen("10.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(1)
	{
		cin>>current;
		if(current=="END_OF_FIRST_PART")
			break;
		cin>>wei;
		mapping[current]=wei;
	}
	for(map<string,int>::iterator it=mapping.begin();it!=mapping.end();it++)
		cout<<it->first<<' '<<it->second<<endl;
	while(cin>>current)
	{
		if(current=="0")
			break;
		queue<string>tempP;
		map<string,int>tempMap;
		int ans=0;
		int cnt=0;
		int tempNum[maxN]={0};
		for(int i=0;i<current.length();i++)
		{
			if(current[i]==')')
			{
				tempP.push(")");
				if(!isdigit(current[i+1]))
					tempP.push("1");
					//tempP.push({"1"});
				else
				{
					string tempN="";
					while(isdigit(current[i+1]))
					{
						tempN+=current[i+1];
						i++;
					}
					tempP.push(tempN);
					//tempP.push({tempN});
				}
			}
			else if(current[i]=='(')
				tempP.push("(");
				//tempP.push({"("});
			else if(current[i]>='A'&&current[i]<='Z')
			{
				string tempEle="";
				tempEle+=current[i];
				if(current[i+1]>='a'&&current[i+1]<='z')
					tempEle+=current[++i];
				tempP.push(tempEle);
				if(mapping[tempEle]==0)
				{
					cout<<"UNKNOWN"<<endl;
					break;
				}
				//tempP.push({tempEle});
			}
			else if(isdigit(current[i]))
			{
				string tempN="";
				tempN+=current[i];
				while(isdigit(current[i+1]))
				{
					tempN+=current[i+1];
					i++;
				}
				tempP.push(tempN);
				//tempP.push({tempN});
			}
			else ;
			if(!isdigit(tempP.back()[0])&&tempP.back()!="("&&!isdigit(current[i+1]))
				tempP.push("1");
				//tempP.push({"1"});
		}
		//for(queue<element>::iterator it=tempP.front();it!=tempP.back();it++)
		//	cout<<it->first<<' '<<it->second<<endl;
		/*while(!tempP.empty())
		{
			cout<<tempP.front()<<' ';
			tempP.pop();
		}
		cout<<endl;*/
		stack<string>tempQ;
		while(!tempP.empty())
		{
			tempQ.push(tempP.front());
			tempP.pop();
			if(tempQ.top()==")")
			{
				tempQ.pop();
				int bei=cSTI(tempP.front());
				while(tempQ.top()!="(")
				{
					int tempBei=cSTI(tempQ.top());
					tempQ.pop();
					string elem=tempQ.top();
					tempQ.pop();
					/*if(tempMap[elem]==0)
						tempMap[elem]=++cnt;
					tempNum[tempMap[elem]]=tempBei;
					tempNum[tempMap[elem]]*=bei;
					ans+=tempNum[tempMap[elem]]*mapping[elem];*/
					ans+=tempBei*bei*mapping[elem];
				}
				tempQ.pop();
			}
		}
		cout<<ans<<endl;
		/*stack q;
		for(int i=0;i<current.length();i++)
		{
			int tempNum=1;
			q.push(current[i]);
			queue p;
			if(current[i]==')')
			{
				int j=i+1;
				while(isdigit(current[j]))
				{
					if(tempNum==1)
						tempNum=current[j]-'0';
					else
						tempNum*=10,tempNum+=current[j]-'0';
					j++;
				}
				
			}
		}*/
		/*int weight=0;
		int cnt=0;
		for(int i=0;i<current.length();i++)
		{
			string temporary="";
			if(current[i]=='(')
			{
				stack q;
				int temp;
				for(int j=i;;j++)
				{
					if(current[j]==')')
					{
						
					}
					q.push(current[j]);
				}
				
			}
			if(current[i]>='A'&&current[i]<='Z')
			{
				temporary+=current[i];
				if(current[i+1]>='a'&&current[i+1]<='z')
					temporary+=current[++i];
				if(mapping[temporary]==0)
				{
					cout<<"UNKNOWN"<<endl;
					break;
				}
			}
		}*/
	}
	return 0;
}
