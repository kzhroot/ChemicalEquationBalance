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

LD ansLast[200]={0};
map<string,int>elemt;
int exis[maxN][10]={0};
string equation="";

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
	
	void startClear()
	{
		modeMark=0;
		languageMark=0;
		play=1;
		modeMark=0;
		clear();
		return ;
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
		"3.Use the program all the time;",//10
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
		
		inline void clear()
		{
			for(int i=0;i<=_n+1;i++)
				for(int j=0;j<=_m+1;j++)
					_num[i][j]=0;
					//_num[i][j]._mole=0,_num[i][j]._deno=1;
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
				{
					if(_num[i][j]==-0)
						_num[i][j]=0;
					cout<<_num[i][j]<<' ';
				}
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
	void gauss(Matrix &_T)
	{
		for(int i=1;i<=_T._n;i++)
			_T._num[i][_T._m]=-_T._num[i][_T._m];
		int nowLine=1;
		for(int i=1;i<=_T._m&&nowLine<=_T._n;i++)
		{
			//_T.print();
			int _current=nowLine;
			for(int j=nowLine+1;j<=_T._n;j++)
				if(fabs(_T._num[j][i])>fabs(_T._num[_current][i])&&fabs(fabs(_T._num[j][i])-fabs(_T._num[_current][i]))>=_minN)
					_current=j;
			for(int j=1;j<=_T._m;j++)
				swap(_T._num[nowLine][j],_T._num[_current][j]);
			if(fabs(_T._num[nowLine][i])<=_minN)
				continue;
			LD curFir=_T._num[nowLine][i];
			for(int j=1;j<=_T._m;j++)
				_T._num[nowLine][j]/=curFir;
			/*for(int j=i+1;j<=_T._n;j++)
			{
				LD curSec=_T._num[j][i]/_T._num[i][i];
				for(int k=i;k<=_T._m;k++)
					_T._num[j][k]-=_T._num[i][k]*curSec;
			}*/
			for(int j=1;j<=_T._n;j++)
			{
				if(j==nowLine)
					continue;
				LD curSec=_T._num[j][i]/_T._num[nowLine][i];
				for(int k=i;k<=_T._m;k++)
					_T._num[j][k]-=_T._num[nowLine][k]*curSec;
			}
			nowLine++;
		}
		_T._num[0][0]=nowLine;
	}
	
	int ansJudge(Matrix &_T)
	{
		int nowLine=_T._num[0][0],curFlagNo=0;
		for(int i=1;i<=_T._m;i++)
			if(exis[i][1]+exis[i][0]!=0)
				return -1;
		/*if(nowLine<=_T._n)
		{
			while(nowLine<=_T._n)
				if(fabs(_T._num[nowLine++][_T._m])!=0)
					return -1;
			return 1;
		}*/
		for(int i=1;i<=_T._n;i++)
		{
			int curFlag=0,curCnt=0;
			if(_T._num[i][_T._m]>_minN)
				curFlag=1;
			for(int j=i;j<_T._m;j++)
				curCnt+=(fabs(_T._num[i][j])>_minN);
			curFlagNo+=(curCnt>1);
			_T._num[i][0]=curCnt;
			if(curCnt==1&&curFlag==0||curCnt==0&&curFlag==1)
				return -1;
		}
		if(curFlagNo)
			return 1;
		return 0;
	}
	
	void bringBackOne(int line,Matrix &_T)
	{
		int pos=0;
		for(int j=line;j<_T._m&&pos==0;j++)
			if(_T._num[line][j])
				pos=j;
		ansLast[pos]=_T._num[line][_T._m]/_T._num[line][pos];
		for(int i=1;i<=_T._n;i++)
		{
			if(_T._num[i][pos]==0)
				continue;
			_T._num[i][_T._m]-=_T._num[i][pos]*ansLast[pos];
			_T._num[i][pos]=0,_T._num[i][0]--;
			if(_T._num[i][0]==1)
				bringBackOne(i,_T);
		}
		return ;
	}
	
	void bringBack(Matrix &_T)
	{
		int minLine=1;
		for(int i=1;i<=_T._n;i++)
			if(_T._num[i][0]<=_T._num[minLine][0]&&_T._num[i][0]>0)
				minLine=i;
		for(int i=_T._m-1;i>=1&&_T._num[minLine][0]>1;i--)
		{
			if(_T._num[minLine][i]==0)
				continue;
			LD randNum=0;
			int curFlag=1;
			for(LD j=0.001;j<=100&&randNum==0;j+=0.001)
			{
				curFlag=1;
				for(int k=1;k<=_T._n&&curFlag;k++)
				{
					if(_T._num[k][i]==0||_T._num[k][0]!=2)
						continue;
					if(_T._num[k][_T._m]-_T._num[k][i]*j<=_minN)
						curFlag=0;
				}
				if(curFlag)
					randNum=j;
			}
			/*LD curNumOne=0,curNumTwo=0;
			for(LD j=1;j>=0.001&&curNumOne==0;j-=0.001)
			{
				curFlag=1;
				for(int k=1;k<=_T._n&&curFlag;k++)
				{
					if(_T._num[k][i]==0||_T._num[k][0]!=2)
						continue;
					if(_T._num[k][_T._m]-_T._num[k][i]*j<=0)
						curFlag=0;
				}
				if(curFlag)
					curNumOne=j;
			}
			for(LD j=1;j<=100&&curNumTwo==0;j+=0.001)
			{
				curFlag=1;
				for(int k=1;k<=_T._n&&curFlag;k++)
				{
					if(_T._num[k][i]==0||_T._num[k][0]!=2)
						continue;
					if(_T._num[k][_T._m]-_T._num[k][i]*j<=0)
						curFlag=0;
				}
				if(curFlag)
					curNumTwo=j;
			}
			if(curNumOne==0)
				randNum=curNumTwo;
			else if(curNumTwo==0)
				randNum=curNumOne;
			else
				randNum=(fabs(curNumOne-1)<fabs(curNumTwo-1)?curNumOne:curNumTwo);*/
			ansLast[i]=randNum;
			for(int j=1;j<=_T._n;j++)
			{
				if(_T._num[j][i]==0)
					continue;
				_T._num[j][_T._m]-=_T._num[j][i]*ansLast[i];
				_T._num[j][i]=0,_T._num[j][0]--;
				if(_T._num[j][0]==1)
					bringBackOne(j,_T);
			}
		}
		return ;
	}
	
	void getAns(int type,Matrix &_T)
	{
		if(type==0)
		{
			for(int i=1;i<=_T._n;i++)
				ansLast[i]=_T._num[i][_T._m];
			ansLast[_T._m]=1;
		}
		else if(type==1)
		{
			for(int i=1;i<=_T._n;i++)
			{
				if(_T._num[i][0]!=1)
					continue;
				bringBackOne(i,_T);
			}
			bringBack(_T);
			ansLast[_T._m]=1;
		}
		else ;
	}
	
	void dealAns(Matrix _T)
	{
		for(int i=1;i<=10000;i++)
		{
			int curFlag=1;
			for(int j=1;j<=_T._m;j++)
			{
				LD cur=LD(i*1.000000*ansLast[j]);
				if(fabs(LD(cur-(LD)round(cur)))>_minN)
					curFlag=0;
			}
			if(curFlag==0)
				continue;
			for(int j=1;j<=_T._m;j++)
				ansLast[j]=(LD)(ansLast[j]*i);
			break;
		}
	}
};
using namespace Algorithm;

namespace Solve
{
	void init()
	{
		memset(ansLast,0,sizeof(ansLast));
		memset(exis,0,sizeof(exis));
		elemt.clear();
		equation="";
		ques.clear();
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
		int i=leftNum,j;
		while(i<rightNum-1&&str[i]!='(')
			i++;
		if(str[i]=='(')
		{
			int curCnt=1;
			input(leftNum,i,flag,str);
			for(j=i+1;j<rightNum&&curCnt;j++)
				if(str[j+1]=='(')
					curCnt++;
				else if(str[j+1]==')')
					curCnt--;
				else ;
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
			if(flag>0)
				exis[curHash][1]=1;
			else
				exis[curHash][0]=-1;
			ques._num[curHash][ques._m]=ques._num[curHash][ques._m]+flag*getNumber(i,str);
			//ques._num[hs][ques._m]=ques._num[hs][ques._m]+Frac({f*getNumber(i,str),1});
		}
		/*while(i<rightNum-1&&str[i]!='(')
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
		}*/
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
			if(str[j]=='='&&curFlag!=-1)
				curFlag*=-1;
			i=j+1;
		}
		return ;
	}
	
	void printAns(Matrix& _T,string str)
	{
		//_T.print();
		//cout<<equation<<endl;
		int ansRes=ansJudge(_T);
		if(ansRes==1)
		{
			printf("Not only solution.\n");
			//getchar(),getchar();
		}
		else if(ansRes==-1)
		{
			printf("No solution.\n");
			//getchar(),getchar();
			return ;
		}
		else if(ansRes==0);
		else ;
		getAns(ansRes,_T);
		dealAns(_T);
		/*for(int i=1;i<=_T._m;i++)
			cout<<ansLast[i]<<' ';
		cout<<endl;*/
		int lenth=str.length(),cur=1;
		if(fabs(ansLast[cur]-1)>_minN)
			//printf("%d",ansLast[cur]);
			printf("%.0Lf",ansLast[cur]);
		for(int j=0;j<lenth;j++)
		{
			putchar(str[j]);
			if(str[j]=='='||str[j]=='+')
				if(fabs(ansLast[++cur]-1)>_minN)
					//printf("%d",ansLast[cur]);
					printf("%.0Lf",ansLast[cur]);
		}
		printLine();
		//getchar(),getchar();
	}
	
	void solve()
	{
		init();
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
		printf("%s",text[languageMark][10].c_str());
			printLine();
		int temporaryMark=0;
		while(!modeMark)
		{
			printf("%s",text[languageMark][5].c_str());
			scanf("%d",&temporaryMark);
			if(temporaryMark>3||temporaryMark<1)
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
		getchar();getchar();
		return ;
	}
	
	void userInterfaceSecond()
	{
		printf("%s",text[languageMark][11].c_str());
		printLine();
		solve();
		getchar();getchar();
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
		else if(modeMark==3)
		{
			while(1)
			{
				//startClear();
				userInterfaceSecond();
			}
		}
		else ;
		return ;
	}
};
using namespace UI;

signed main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//std::ios::sync_with_stdio(false);
	//userInterfaceSecond();
	while(play)
	{
		startClear();
		welcomeInterface();
		userInterface();
	}
	//Sleep(100000);
	return 0;
}
