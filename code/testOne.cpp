#include<bits/stdc++.h>
#define dbg(x) cout<<x<<"\n"
#define dbp(x) cout<<"dbP: "<<#x" = "<<(x)<<"\n"

using namespace std;

typedef long long LL;
typedef long double LD;
const long long maxN=2000010; 
const LD eps=1e-10;
int n,m,hash[1<<20]={0};
LD a[205][205];
char z[205];
int _ans,now;

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

int getNumber(int& i)
{
	int s=0;
	while('0'<=z[i]&&z[i]<='9')
		s=(s<<3)+(s<<1)+z[i++]-'0';
	return max(s,1);
}

int getStr(int& i)
{
	if(z[i]>'Z'||z[i]<'A')
		return -1;
	int s=z[i++];
	while('a'<=z[i]&&z[i]<='z')
		s=s*10007+z[i++];
	return s&((1<<20)-1);
}

void countt(int l,int r,int f)
{
	if(l==r)
		return ;
	int i=l,j=r;
	while(i<r-1&&z[i]!='(')
		i++;
	while(j>l&&z[j]!=')')
		j--;
	if(z[i]=='(')
	{
		countt(l,i,f);
		
		int w=j+1,s=getNumber(w);
	//	dbg(10);
		countt(i+1,j,f*s);
		//dbg(11);
		countt(w,r,f);
		//dbg(12);
		return ;
	}
	//dbg(1231);
	for(i=l;i<r;)
	{//dbg(15);
		//dbg(14);
		//dbp(i);
		//dbp(r);
		int str=getStr(i);
		//cout<<str<<endl;
		if(!hash[str])
			hash[str]=++n;
		int hs=hash[str];
		a[hs][m]+=f*getNumber(i);
	}
//	dbg(15);
}

void init()
{
	scanf("%s",&z);
	int l=strlen(z),f=1;
	for(int i=0;i<l;i++)
		putchar(z[i]);
	cout<<endl;
	z[l]='#';
	//dbg(4);
	for(int i=0;i<l;)
	{
		//dbg(5);
		//dbp(i);
		int j=i;
		while(z[j]!='+'&&z[j]!='='&&z[j]!='#'&&j<l)
			j++;
		//dbg(6);
		m++;
		//dbp(j);
		countt(i,j,f);
		if(z[j]=='=')
			f*=-1;
		i=j+1;//something wrong
		//dbp(i);
	}
	//dbg(3);
	/*for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}*/
	return ;
}

void pM()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void gs()
{
	
	for(int j=1,i;j<m;j++)
	{
		for(i=now+1;fabs(a[i][j])<eps&&i<=n;i++);
		if(i>n)
		{
			_ans=-1;
			continue;
		}
		now++;
		dbp(now);
		for(int k=1;k<=m;k++)
			swap(a[i][k],a[now][k]);
		LD ss=a[now][j];
		for(int k=1;k<=m;k++)
			a[now][k]/=ss;
		for(i=1;i<=n;i++)
			if(fabs(a[i][j])>eps&&i!=now)
			{
				LD s=a[i][j];
				for(int k=1;k<=m;k++)
					a[i][k]-=a[now][k]*s;
			}
	}
}

int ans[205];



void solve()
{
	for(int i=now+1;i<=n;i++)
		if(fabs(a[i][m])<=eps)
		{
			printf("No solution\n");
			return ;
		}
	if(_ans==-1)
		printf("Solution not unique\n");
	for(int i=1;i<=1000;i++)
	{
		//dbp(i);
		int p=1;
		for(int j=1;j<m;j++)
		{
			//dbp(a[j][m]);
		//	dbp(fabs(int(a[j][m]*i*-1+0.5)-a[j][m]*i*-1));
			if(fabs(int(a[j][m]*i*-1+0.5)-a[j][m]*i*-1)>eps)
				p=0;
		}
		if(p==0)
			continue;
		for(int j=1;j<m;j++)
			ans[j]=int(a[j][m]*i*-1+0.5);
		ans[m]=i;
		if(ans[1]!=1)
			printf("%d",ans[1]);
		int l=strlen(z),k=1;
		for(int j=0;j<l-1;j++)
		{
			putchar(z[j]);
			if(z[j]=='='||z[j]=='+')
				printf("%d",ans[++k]);
		}
		break;
	}
}

int main()
{
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//dbg(1);
	init();
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++)
			cout<<a[i][j]<<" ";
	//dbg(2);
	gs();
	//dbg(899);
	/*for(int i=1;i<=20;i++,cout<<endl)
		for(int j=1;j<=20;j++)
			cout<<a[i][j]<<" ";
	*/
	//cout<<"fuck"<<endl;
	for(int i=0;i<=m;i++)
		cout<<a[i][m]<<endl;
	solve();
	return 0;
}
