#include <bits/stdc++.h>
#include <windows.h>
#define int long long
#define dbg(x) cout<<x<<"\n"
#define dbp(x) cout<<"dbP: "<<#x" = "<<(x)<<"\n"

using namespace std;

const long long maxN=2000010;
typedef long long LL;
typedef long double LD;

int modeMark=0;
int languageMark=0;
int play=1;

int ansLast[200]={0};
map<string,int>elemt;
string equation="";
int noAnsMark=0;
int onlyAns=0;

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

namespace Control
{
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
	
	void init()
	{
	
	}
};
using namespace Control;

namespace Text
{
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
};
using namespace Text;

namespace Struct
{
	int _gcd(int _x,int _y)
	{
		return _y==0?_x:_gcd(_y,_x%_y);
	}
	
	const int _maxN=110;
	const int _maxM=110;
	const int _mod=1e9+7;
	
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

	struct Matrix
	{
		int _n,_m;
		LD _num[_maxN][_maxM];
		
		inline Matrix operator + (const Matrix& tempNum) const
		{
			Matrix _result;
			_result._n=_n,_result._m=_m;
			for(int i=1;i<=_n;i++)
				for(int j=1;j<=_m;j++)
					_result._num[i][j]=_num[i][j]+tempNum._num[i][j];
			return _result;
		}
		
		inline Matrix operator - (const Matrix& tempNum) const
		{
			Matrix _result;
			_result._n=_n,_result._m=_m;
			for(int i=1;i<=_n;i++)
				for(int j=1;j<=_m;j++)
					_result._num[i][j]=_num[i][j]-tempNum._num[i][j];
			return _result;
		}
		
		inline Matrix operator * (const int& _number) const
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
		
		inline Matrix operator * (const Matrix& tempNum) const
		{
	    	Matrix _result;
	    	_result._n=_n,_result._m=tempNum._m;
	    	int _current;
	    	//Frac _current;
	    	for(int i=1;i<=_result._n;i++)
	    		for(int j=1;j<=_result._m;j++)
	    			_result._num[i][j]=0;
	    			//_result._num[i][j]._mole=0,_result._num[i][j]._deno=1;
	    	for(int i=1;i<=_result._n;i++)
	    		for(int k=1;k<=_m;k++)
	    		{
	    			_current=_num[i][k];
	    			for(int j=1;j<=_result._m;j++)
	    				_result._num[i][j]=_result._num[i][j]+tempNum._num[k][j]*_current;
				}
			return _result;
		}
		
		inline Matrix operator ^ (int _ord) const
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
			for(int i=0;i<=_n+1;i++)
				for(int j=0;j<=_m+1;j++)
				{
					_num[i][j]=0;
					//_num[i][j]._mole=0,_num[i][j]._deno=1;
				}
			_n=0,_m=0;
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
			printf("Matrix: %d %d\n",_n,_m);
			for(int i=1;i<=_n;i++,cout<<endl)
				for(int j=1;j<=_m;j++)
					cout<<_num[i][j]<<' ';
			return ;
		}
	};
	ostream &operator << (ostream &tempOut,const Frac &tempNum)
	{
	    tempOut<<tempNum._mole<<"/"<<tempNum._deno;
	    return tempOut;
	}
	ostream &operator << (ostream &tempOut,const Matrix &tempNum)
	{
	    tempOut<<"Matrix: "<<tempNum._n<<" "<<tempNum._m<<endl;
	    for(int i=1;i<=tempNum._n;i++,tempOut<<endl)
			for(int j=1;j<=tempNum._m;j++)
				tempOut<<tempNum._num[i][j]<<' ';
	    return tempOut;
	}
};
using namespace Struct;

Matrix ques;

namespace Test
{
	void pM(Matrix T)
	{
		T.print();
	}
	void pF(Frac T)
	{
		T.print();
	}
};
using namespace Test;

namespace Algorithm
{
	//const Frac _minN={1,1E8};
	const LD _minN=1E-10;
	
	/*void gauss(Matrix &_T)
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
	}*/
	void gauss(Matrix &_T)
	{
		//pM(_T);
		for(int i=1;i<=_T._n;i++)
	        _T._num[i][_T._m]=-_T._num[i][_T._m];
	    for(int i=1;i<_T._m;i++)
		{
	        LD maxN=-1;
			int _current;
	        for(int j=i;j<=_T._n;j++)
	            if(fabs(_T._num[j][i])>maxN)
	                maxN=fabs(_T._num[j][i]),_current=j;
	        if(maxN==0)
	        {
	        	noAnsMark=-1;
	        	return ;
			}
	        for(int j=1;j<=_T._m;j++)
	            swap(_T._num[i][j],_T._num[_current][j]);
	        LD tmp=_T._num[i][i];
	        for(int j=1;j<=_T._m;j++)
	            _T._num[i][j]=_T._num[i][j]/tmp;
	        for(int j=i-1?1:2;j<=_T._n;j++)
			{
	            if(j==i)
					continue;
	            LD tmp=_T._num[j][i];
	            for(int k=1;k<=_T._m;k++)
	                _T._num[j][k]=_T._num[j][k]-tmp*_T._num[i][k];
	        }
	        //pM(_T);
	    }
		return ;
	}
};
using namespace Algorithm;

namespace Solve
{
	void startClear()
	{
		memset(ansLast,0,sizeof(ansLast));
		elemt.clear();
		noAnsMark=0;
		onlyAns=0;
		equation="";
		ques.clear();
		modeMark=0;
		clear();
		return ;
	}
	
	int getNumber(int& i,string str)
	{
		int curCnt=0;
		while('0'<=str[i]&&str[i]<='9')
			curCnt=(curCnt<<3)+(curCnt<<1)+str[i++]-'0';
		return max(curCnt,(int)(1));
	}
	
	string getStr(int& i,string str)
	{
		if(str[i]>'Z'||str[i]<'A')
			return "";
		string curStr="";
		curStr+=str[i++];
		while('a'<=str[i]&&str[i]<='z')
			curStr+=str[i++];
		return curStr;
	}
	
	void input(int leftNum,int rightNum,int flag,string str)
	{
		if(leftNum==rightNum)
			return ;
		int i=leftNum,j=rightNum;
		while(i<rightNum-1&&str[i]!='(')
			i++;
		while(j>leftNum&&str[j]!=')')
			j--;
		if(str[i]=='(')
		{
			input(leftNum,i,flag,str);
			int nextLeftNum=j+1,curFlag=getNumber(nextLeftNum,str);
			input(i+1,j,flag*curFlag,str);
			input(nextLeftNum,rightNum,flag,str);
			return ;
		}
		i=leftNum;
		while(i<rightNum)
		{
			string curStr=getStr(i,str);
			if(!elemt[curStr])
				elemt[curStr]=++ques._n;
			int curHash=elemt[curStr];
			ques._num[curHash][ques._m]=ques._num[curHash][ques._m]+flag*getNumber(i,str);
			//ques._num[hs][ques._m]=ques._num[hs][ques._m]+Frac({f*getNumber(i,str),1});
		}
	}
	
	void getInput(string str)
	{
		int lenth=str.length(),curFlag=1;
		int i=0;
		while(i<lenth)
		{
			int j=i;
			while(str[j]!='+'&&str[j]!='='&&j<lenth)
				j++;
			ques._m++;
			input(i,j,curFlag,str);
			if(str[j]=='=')
				curFlag*=-1;
			i=j+1;
		}
		return ;
	}
	
	void printAns(Matrix& _T,string str)
	{
		//pM(_T);
		cout<<equation<<endl; 
		for(int i=1;i<_T._n;i++)
		{
			if(_T._num[i][_T._m]==0)
			{
				noAnsMark=-1;
				break;
			}
		}
		if(noAnsMark==-1)
		{
			printf("No solution\n");
			getchar(),getchar();
			return ;
		}
		for(int i=1;i<=1000;i++)
		{
			int curFlag=1;
			for(int j=1;j<=_T._n;j++)
			{
				LD cur=LD(i*1.000000*_T._num[j][_T._m]);
				if(LD(cur-LL(cur))>_minN)
					curFlag=0;
			}
			if(curFlag==0)
				continue;
			for(int j=1;j<_T._m;j++)
				ansLast[j]=_T._num[j][_T._m]*i;
			ansLast[_T._m]=i;
			break;
		}
		/*for(int i=1;i<=_T._m;i++)
			cout<<ansLast[i]<<' ';*/
		int lenth=str.length(),cur=1;
		if(ansLast[cur]!=1)
			printf("%d",ansLast[cur]);
		for(int j=0;j<lenth;j++)
		{
			putchar(str[j]);
			if(str[j]=='='||str[j]=='+')
			{
				cur++;
				if(ansLast[cur]!=1)
					printf("%d",ansLast[cur]);
			}
		}
		getchar(),getchar();
	}
	
	void solve()
	{
		cin>>equation;
		getInput(equation);
		gauss(ques);
		printAns(ques,equation);
		return ;
	}
};
using namespace Solve;

namespace UI
{
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
		printf("%s",text[languageMark][11].c_str());
		printLine();
		solve();
		return ;
	}
	
	void userInterface()
	{
		if(modeMark==1)
			userInterfaceFirst();
		else if(modeMark==2)
		{
			userInterfaceSecond();
		}
		else ;
		return ;
	}
};
using namespace UI;

signed main()
{
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//std::ios::sync_with_stdio(false);
	userInterfaceSecond();
	/*while(play)
	{
		startClear();
		welcomeInterface();
		userInterface();
	}*/
	Sleep(100000);
	return 0;
}
