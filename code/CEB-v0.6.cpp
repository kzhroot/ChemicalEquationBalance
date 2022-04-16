#include <bits/stdc++.h>

using namespace std;

const long long maxN=2000010;
typedef long long LL;

int modeMark=0;
int languageMark=0;//a mark of language.
int play=1;//a flag of running.
int numReactant=0,numProduct=0;
int numKind=0;//the number of kinds of yuansu.

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

typedef int T;
const T _maxN=110;
const T _maxM=110;
const T _mod=1e9+7;

struct Matrix
{
	T _n,_m;
	Frac _num[_maxN][_maxM];
	
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
    	Frac _current;
    	for(int i=1;i<=_result._n;i++)
    		for(int j=1;j<=_result._m;j++)
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

void userInterfaceSecond()
{
	int temporaryNum=0;
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
	ques._n=numKind,ques._m=numReactant+numProduct;
}

void userInterface()
{
	if(modeMark==1)
		userInterfaceFirst();
	else if(modeMark==2)
		userInterfaceSecond();
	else ;
	return ;
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//std::ios::sync_with_stdio(false);
	while(play)
	{
		startClear();
		welcomeInterface();
		userInterface();
	}
	return 0;
}
