#include <bits/stdc++.h>

using namespace std;

const long long maxN=2000010;
typedef long long LL;

int modeMark=0;
int languageMark=0;//a mark of language.
int play=1;//a flag of running.
int numReactant=0,numProduct=0;

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
	numReactant=0,numProduct=0;
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
