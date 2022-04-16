#include <bits/stdc++.h>
#define int long long
#define T long long
#define dbg(x) cout<<x<<"\n"
#define dbp(x) cout<<"dbP: "<<#x" = "<<(x)<<"\n"
#define debug(x) cout<<"debug: "<<__FUNCTION__<<"() @ "<<__TIMESTAMP__<<"\n"\
<<__FILE__<<" L"<<__LINE__<<"\n"<<#x" = "<<(x)<<"\n"
using namespace std;

const long long maxN=2000010;
typedef long long LL;
typedef long double LD;

const long double eps=1E-8;

int hash[1<<20]={0};
int modeMark=0;
int languageMark=0;//a mark of language.
int play=1;//a flag of running.
int numReactant=0,numProduct=0;
int numKind=0;//the number of kinds of yuansu.
//const LD _minN=1E-8;
int _flag=0;
int _ans[200]={0};
string equation="";

map<string,int>elemt;


inline LL _read()
{
	LL _num=0,_symbol=1;
	char _c=getchar();
	for(;!isdigit(_c);_c=getchar())
		if(_c=='-')
			_symbol*=-1;
	for(;isdigit(_c);_c=getchar())
		_num=(_num<<3)+(_num<<1)+_c-'0';
	return _num*_symbol;
}

string text[10][30]=
{
	"Warning:Wrong Input!",//0
	"Welcome to use Chemical Equation Balance!",//1
	"Please choose the next step:",
	"1.Describe of the program;",
	"2.Use the program;",
	"Please type a number:",
	"Please type the number of reactant:",//6
	"Please type the number of product:",
	"Please type the reactant:",
	"Please type the product:",
	"",//10
	"Please type the Equation:",
};

string textDescribe[10][30]=
{
	"",
	"This is a program to solve the problem which happens on balancing chemical equation,",
	"it based on cmd User Interface.",
	"In the program,we use Gauss and Matrix to solve this proble,",
	"the mass you can see in the document.",
	"We think our works afforts,",
	"and we hope that the program will help you!",
	"Waiting...",
};

int _gcd(int _x,int _y)
{
	return _y==0?_x:_gcd(_y,_x%_y);
}
	
struct Frac
{
	int _mole,_deno;
	/*inline Frac operator = (const int& _num) const
	{
		return (Frac){_num,1};
	}
	inline Frac operator = (const Frac& _T) const
	{
		int _nextGcd=_gcd(_T._mole,_T._deno);
		return (Frac){_T._mole/_nextGcd,_T._deno/_nextGcd};
	}*/
	inline Frac operator + (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno+_deno*_T._mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator - (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno-_deno*_T._mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		//cout<<_nextMole/_nextGcd<<" _nextDeno/_nextGcd "<<_nextDeno/_nextGcd<<" ";
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator * (const Frac& _T) const
	{
		int _nextMole=_mole*_T._mole,
		_nextDeno=_deno*_T._deno;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}
	inline Frac operator * (const int& _T) const
	{
		int _nextMole=_mole*_T,
		_nextDeno=_deno;
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
	/*inline Frac operator /= (const Frac& _T) const
	{
		int _nextMole=_mole*_T._deno,
		_nextDeno=_deno*_T._mole;
		int _nextGcd=_gcd(_nextMole,_nextDeno);
		return (Frac){_nextMole/_nextGcd,_nextDeno/_nextGcd};
	}*/
	inline bool operator > (const Frac& _T) const
	{
		return _mole*_T._deno>_deno*_T._mole;
	}
	inline bool operator < (const Frac& _T) const
	{
		return _mole*_T._deno<_deno*_T._mole;
	}
	inline bool operator <= (const Frac& _T) const
	{
		return _mole*_T._deno<=_deno*_T._mole;
	}
	inline bool operator == (const Frac& _T) const
	{
		return _mole*_T._deno==_deno*_T._mole;
	}
	inline void abs() const
	{
		/*if(_mole>0&&_deno>0)
			return (Frac){_mole,_deno};
		if(_mole<0&&_deno<0)
			return (Frac){-_mole,-_deno};
		return _mole<0?(Frac){_mole,_deno}:(Frac){-_mole,-_deno};*/
		//_mole=fabs(_mole),_deno=fabs(_deno);
		
	}
	inline void print()
	{
		cout<<_mole<<"/"<<_deno<<" ";
	}
};

//typedef int T;
const T _maxN=110;
const T _maxM=110;
const T _mod=1e9+7;
//Frac _minN={1,1E8};
LD _minN=1E-10;


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
    	//Frac _current;
    	int _current;
    	for(int i=1;i<=_result._n;i++)
    		for(int j=1;j<=_result._m;j++)
    			//_result._num[i][j]._mole=0,_result._num[i][j]._deno=1;
    			_result._num[i][j]=0;
    	for(int i=1;i<=_result._n;i++)
    		for(int k=1;k<=_m;k++)
    		{
    			_current=_num[i][k];
    			for(int j=1;j<=_result._m;j++)
    				_result._num[i][j]=_result._num[i][j]+_T._num[k][j]*_current;
					//_result._num[i][j]%=_mod;
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
			//_result._num[i][i]._mole=1,_result._num[i][i]._deno=1;
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
	
	inline void clear()
	{
		_n=0,_m=0;
		for(int i=0;i<=numReactant+numProduct+1;i++)
			for(int j=0;j<=numKind+1;j++)
			{
				_num[i][j]=0;
				//_num[i][j]._mole=0,_num[i][j]._deno=1;
			}
	}
	/*inline void scan()
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
	}*/
};

Matrix ques;

Frac fabs(Frac _T)
{
	return ((Frac){fabs(_T._mole),fabs(_T._deno)});
}

void swap(Frac& a,Frac& b)
{
	Frac t=a;
	a=b;
	b=t;
}


void pM(Matrix &_T)
{
	for(int i=1;i<=_T._n;i++)
	{
		for(int j=1;j<=_T._m;j++)
			//cout<<_T._num[i][j]._mole<<"/"<<_T._num[i][j]._deno<<" ";
			cout<<_T._num[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

/*void gauss(Matrix &_T)
{
	pM(_T);
	for(int i=1;i<=_T._n;i++)
	{
		int _current=i;
		for(int j=i;j<=_T._n+1;j++)
		{
			//_T._num[j][i].print(),_T._num[_current][i].print();
			//fabs(_T._num[j][i]-_T._num[_current][i]).print();
			//_minN.print();
			if(fabs(_T._num[j][i]-_T._num[_current][i])<=eps)
				_current=j/*,dbg(4)*/;
	/*	}
		//dbp(_current);
		for(int j=1;j<=_T._n+1;j++)
		{
			/*_T._num[i][j].print(),_T._num[_current][j].print();
			cout<<endl;*/
		/*	swap(_T._num[i][j],_T._num[_current][j])/*,dbg(3)*/;
			/*Frac _temp=_T._num[i][j];
			_T._num[i][j]=_T._num[_current][j];
			_T._num[_current][j]=_temp;*/
	/*	}
		//cout<<"fuck";
		/*for(int i=1;i<=_T._n;i++)
		{
			for(int j=1;j<=_T._m;j++)
				cout<<_T._num[i][j]._mole<<"/"<<_T._num[i][j]._deno<<" ";
			cout<<endl;
		}*/
	/*	if(fabs(_T._num[i][i])<=eps)
		{
			_flag=-1;
			pM(_T);
			cout<<"fuck"<<endl;
			//printf("No Solution\n");
			return ;
		}
		for(int j=i+1;j<=_T._n+1;j++)
			//_T._num[i][j]/=_T._num[i][i];
			_T._num[i][j]=_T._num[i][j]/_T._num[i][i]/*,dbg(2)*/;
	/*	for(int j=1;j<=_T._n;j++)
			if(i!=j)
				for(int k=i+1;k<=_T._n+1;k++)
					//_T._num[j][k]-=_T._num[j][i]*_T._num[i][k];
					_T._num[j][k]=_T._num[j][k]-_T._num[j][i]*_T._num[i][k];
		/*dbg(1);
		cout<<i<<" ";
			for(int i=1;i<=_T._n;i++)
		{
			for(int j=1;j<=_T._m;j++)
				cout<<_T._num[i][j]._mole<<"/"<<_T._num[i][j]._deno<<" ";
			cout<<endl;
		}*/
//	}

	/*for(int i=1;i<=_T._m;i++)
	{
		_T._num[i][_T._n+1].print();
		cout<<endl;
	}*/
		//cout<<_T._num[i][_T._n+1]._mole/_T._num[i][_T._n+1]._deno<<endl;
		//printf("%.2Lf\n",(LD)_T._num[i][_T._n+1]._mole/_T._num[i][_T._n+1]._deno);
/*	return ;
}*/

/*void gauss(Matrix &_T)
{
	//pM(_T);
	for(int i=1;i<=_T._n;i++)
	{
		pM(_T);
		
		int _current=i;
		for(int j=i;j<=_T._n;j++)
		{
			//cout<<_T._num[j][i]<<" "<<_T._num[_current][i]<<" "<<fabs(_T._num[j][i]-_T._num[_current][i])<<endl;
			if(fabs(_T._num[j][i]-_T._num[_current][i])<=_minN)
				_current=j;
		}
		dbp(_current);
		//dbp(_current);
		for(int j=1;j<=_T._n+1;j++)
		{
			//cout<<_T._num[i][j]<<" "<<_T._num[_current][j]<<endl;
			swap(_T._num[i][j],_T._num[_current][j]);
		}
			
		//cout<<"fuck";
		//_T.print();
		
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
		//dbg(1);
		//cout<<i<<" ",_T.print();
	}
	
	for(int i=1;i<=_T._n;i++)
		cout<<_T._num[i][_T._n+1]<<endl;
		//printf("%.2Lf\n",_T._num[i][_T._n+1]);
	return ;
}

*/
void gauss(Matrix& _T)
{
	int _current=0;
	for(int j=1,i;j<_T._m;j++)
	{
		pM(_T);
		
		for(i=_current+1;fabs(_T._num[i][j])<_minN&&i<=_T._n;i++);
		if(i>_T._n)
		{
			_flag=-1;
			continue;
		}
		_current++;
		dbp(_current);
		for(int k=1;k<=_T._m;k++)
		{
			dbg(123),dbp(k),dbp(_current),dbp(i);
			swap(_T._num[i][k],_T._num[_current][k]);
			//dbg(124),dbp(_T._num[i][k]),dbp(_T._num[_current][k]);
		}
			//swap(_T._num[i][k],_T._num[_current][k]);
		dbg(1),pM(_T);
		LD ss=_T._num[_current][j];
		dbp(j);
		dbp(ss);
		for(int k=1;k<=_T._m;k++)
			_T._num[_current][k]/=ss;
		for(i=1;i<=_T._n;i++)
			if(fabs(_T._num[i][j])>_minN&&i!=_current)
			{
				LD s=_T._num[i][j];
				for(int k=1;k<=_T._m;k++)
					_T._num[i][k]-=_T._num[_current][k]*s;
			}
	}
}

void clear()
{
	system("cls");
	return ;
}

void null()
{
	return ;
}

void printLine()
{
	printf("\n");
	return ;
}

void startClear()
{
	memset(hash,0,sizeof(hash));
	_flag=0;
	memset(_ans,0,sizeof(_ans));
	equation="";
	ques._m=ques._n=0;
	for(int i=0;i<=100;i++)
	{
		for(int j=0;j<=100;j++)
		{
			//ques._num[i][j]._mole=0,ques._num[i][j]._deno=1;
			ques._num[i][j]=0;
		}
	}
	numReactant=0,numProduct=0,numKind=0;
	modeMark=0;
	
	clear();
}

void welcomeInterface()
{
	for(int i=1;i<=4;i++)
	{
		printf("%s",text[languageMark][i].c_str());
		printLine();
	}
	int temporaryMark=0;
	while(!modeMark)
	{
		printf("%s",text[languageMark][5].c_str());
		scanf("%d",&temporaryMark);
		if(temporaryMark>2||temporaryMark<1)
		{
			printf("%s",text[languageMark][0].c_str());
			printLine();
		}
		else
			modeMark=temporaryMark;
	}
	return ;
}


void userInterfaceFirst()
{
	clear();
	for(int i=1;i<=6;i&1?null():printLine(),i++)
		printf("%s",textDescribe[languageMark][i].c_str());
	printf("%s",textDescribe[languageMark][7].c_str());
	getchar();
	getchar();
	return ;
}

int getNumber(int& i,string z)
{
	int s=0;
	while('0'<=z[i]&&z[i]<='9')
		s=(s<<3)+(s<<1)+z[i++]-'0';
	return max(s,(int)(1));
}

int getStr(int& i,string z)
{
	dbp(i);
	if(z[i]>'Z'||z[i]<'A')
		return -1;
	int s=z[i++];
	while('a'<=z[i]&&z[i]<='z')
		s=s*10007+z[i++];
	return s&((1<<20)-1);
}

void countt(int l,int r,int f,string z)
{
	if(l==r)
		return ;
	int i=l,j=r;
	while(i<r-1&&z[i]!='(')
		i++;
	while(j>l&&z[j]!=')')
		j--;
	//dbg(123);
	if(z[i]=='(')
	{
		
		countt(l,i,f,z);
		
		int w=j+1,s=getNumber(w,z);
		countt(i+1,j,f*s,z);
		countt(w,r,f,z);
		return ;
	}
	debug(1231);
	for(i=l;i<r;)
	{
		dbg(13);
		int str=getStr(i,z);
		//cout<<str<<endl;
		if(!hash[str])
			hash[str]=++ques._n;
		int hs=hash[str];
		//ques._num[hs][ques._m]=ques._num[hs][ques._m]+Frac({f*getNumber(i,z),1});
		ques._num[hs][ques._m]=ques._num[hs][ques._m]+f*getNumber(i,z);
	}
	dbg(15);
	//gauss(ques);
}

void printAns(Matrix &_T,string z)
{
	//cout<<z<<endl;
	/*if(_flag==-1)
	{
		printf("No solution.\n");
		return ;
	}
	for(int i=1;i<=1000;i++)
	{
		int p=1;
		for(int j=1;j<_T._m;j++)
		{
			if(fabs((int)(_T._num[j][_T._m]._mole/_T._num[j][_T._m]._deno*i*-1+0.5)-_T._num[j][_T._m]._mole/_T._num[j][_T._m]._deno*i*-1)>eps)
				p=0;
		}
		if(p==0)
			continue;
		for(int j=1;j<_T._m;j++)//
			_ans[j]=(int)(_T._num[j][_T._m]._mole*i/_T._num[j][_T._m]._deno-1+0.5);
		_ans[_T._m]=i;
		if(_ans[1]!=1)
			printf("%d",_ans[1]);
		int l=z.length(),k=1;
		for(int j=0;j<l-1;j++)
		{
			putchar(z[j]);
			if(z[j]=='='||z[j]=='+')
				printf("%d",_ans[++k]);
		}
		break;
	}*/
	//dbg(123);
	if(_flag==-1)
	{
		printf("No solution\n");
		return ;
	}
	for(int i=1;i<=1000;i++)
	{
		//dbp(i);
		int p=1;
		for(int j=1;j<_T._m;j++)
		{
			//LD cur=LD(1.000000*_T._num[j][_T._m]._mole/_T._num[j][_T._m]._deno);
			LD cur=LD(1.000000*_T._num[j][_T._m]);
			//dbp(cur);
			//dbp(fabs((int)(cur*i*-1+0.5)-cur*i*-1));
			if(fabs((int)(cur*i*-1+0.5)-cur*i*-1)>eps)
				p=0;
		}
		//dbp(i),dbp(p);
		if(p==0)
			continue;
		for(int j=1;j<_T._m;j++)
			_ans[j]=(int)(i*-1*_T._num[j][_T._m]+0.5);
		_ans[_T._m]=i;
		if(_ans[1]!=1)
			printf("%d",_ans[1]);
		int l=z.length(),k=1;
		for(int j=0;j<l;j++)
		{
			putchar(z[j]);
			if(z[j]=='='||z[j]=='+')
				printf("%d",_ans[++k]);
		}
		
		break;
	}
}

void init()
{
	
}

void userInterfaceSecond()
{
	/*int temporaryNum=0;
	while(!numReactant)
	{
		printf("%s",text[languageMark][6].c_str());
		scanf("%d",&temporaryNum);
		if(temporaryNum<1)
		{
			printf("%s",text[languageMark][0].c_str());
			printLine();
		}
		else
			numReactant=temporaryNum;
	}
	for(int i=1;i<=numReactant;i++)
	{
		
	}
	temporaryNum=0;
	while(!numProduct)
	{
		printf("%s",text[languageMark][7].c_str());
		scanf("%d",&temporaryNum);
		if(temporaryNum<1)
		{
			printf("%s",text[languageMark][0].c_str());
			printLine();
		}
		else
			numProduct=temporaryNum;
	}
	for(int i=1;i<=numProduct;i++)
	{
		
	}
	ques._n=numKind,ques._m=numReactant+numProduct;*/
	
	printf("%s",text[languageMark][11].c_str());
	printLine();
	//scanf("%s",&equation);
	cin>>equation;
	//dbg(2);
	//printf("%s",equation.c_str());
	//getchar();getchar();
	int l=equation.length(),f=1;
	for(int i=0;i<l;i++)
		putchar(equation[i]);
	cout<<endl;
	equation[l]='#';
	//dbg(10);
	for(int i=0;i<l;)
	{
		int j=i;
		
		while(equation[j]!='+'&&equation[j]!='='&&equation[j]!='#')
			j++;
		//dbp(j);
		ques._m++;
		countt(i,j,f,equation);
		if(equation[j]=='=')
			f*=-1;
		i=j+1;
		//dbg(11);
	}
	//dbg(1);
	/*for(int i=1;i<=ques._n;i++)
	{
		for(int j=1;j<=ques._m;j++)
		{
			ques._num[i][j].print();
		}
		cout<<endl;
	}*/
	return ;
}

void userInterface()
{
	if(modeMark==1)
		userInterfaceFirst();
	else if(modeMark==2)
	{
		userInterfaceSecond();
		gauss(ques);
		printAns(ques,equation);
		getchar();
		getchar();
	}
		
	else ;
	return ;
}

signed main()
{
	//freopen("in1.txt","r",stdin);
	//freopen(".out","w",stdout);
	//std::ios::sync_with_stdio(false);
	//cout<<_minN._mole<<"/"<<_minN._deno<<endl;
	//cout<<_gcd(0,1)<<endl;
	/*for(int i=0;i<=100;i++)
	{
		for(int j=0;j<=100;j++)
		{
			ques._num[i][j]._mole=0,ques._num[i][j]._deno=1;
		}
	}*/
	//dbg(4);
	/*cin>>ques._n;
	ques._m=ques._n+1;
	for(int i=0;i<=ques._n+1;i++)
	{
		for(int j=0;j<=ques._m+1;j++)
		{
			ques._num[i][j]._mole=0,ques._num[i][j]._deno=1;
		}
	}*/
	/*for(int i=1;i<=ques._n;i++)
	{
		for(int j=1;j<=ques._m;j++)
		{
			cout<<ques._num[i][j]._mole<<"/"<<ques._num[i][j]._deno<<" ";
		}
		cout<<endl;
	}*/
	/*for(int i=1;i<=ques._n;i++)
	{
		for(int j=1;j<=ques._m;j++)
		{
			//cout<<i<<" "<<j<<" ";
			int a;
			cin>>a;
			//dbp(a);
			//Frac b=Frac({a,1});
			//cout<<b._mole<<"/"<<b._deno<<" ";
			ques._num[i][j]._mole=a,ques._num[i][j]._deno=1;
		//	cout<<Frac({a,1})._mole<<"/"<<Frac({a,1})._deno<<" ";
			//cout<<ques._num[i][j]._mole<<"/"<<ques._num[i][j]._deno<<" ";
		}
		//cout<<endl;
	}
	/*for(int i=1;i<=ques._n;i++)
	{
		for(int j=1;j<=ques._m;j++)
		{
			cout<<ques._num[i][j]._mole<<"/"<<ques._num[i][j]._deno<<" ";
		}
		cout<<endl;
	}*/
	//swap(ques._num[1][2],ques._num[2][1]);
	/*Frac fuckT=ques._num[1][2];
	ques._num[1][2]=ques._num[2][1];
	ques._num[2][1]=fuckT;*/
	
	/*dbg(123);
		for(int i=1;i<=ques._n;i++)
	{
		for(int j=1;j<=ques._m;j++)
		{
			cout<<ques._num[i][j]._mole<<"/"<<ques._num[i][j]._deno<<" ";
		}
		cout<<endl;
	}*/
	//gauss(ques);
	//dbg(3);
	userInterfaceSecond();
	/*gauss(ques);
	cout<<equation<<endl;
	printAns(ques,equation);*/
	/*while(play)
	{
		startClear();
		welcomeInterface();
		userInterface();
		return 0;
	}*/
	return 0;
}
