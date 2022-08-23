#include<bits/stdc++.h>
#define int long long
typedef long long ll;
using namespace std;
const int maxn=1005;
const ll mod=1e9+7;
string equation,element[maxn];
//equation为读入的未配平的化学方程式，element记的是元素名称，其实没啥用。
int T,mat[maxn][maxn],cnt,num,lst,flg,ion[maxn],l[maxn],r[maxn],ret[maxn],rem[maxn][maxn];
//mat是高斯消元中用的；l,r用来存一个物质在方程式中的位置，方便输出；
//ret是存每个物质的系数的最终答案；cnt为物质个数；num为元素个数；
//flg用来存现在是扫到等号左边还是等号右边，方便转移；
map<string,int>appear;//appear记的是这个元素在前面是否出现过。
stack<int>ct;
//ct是如果有括号的话用来存括号后面的数，就是要将括号内的元素的原子个数乘以几。
bool haveion;//haveion是存是否有离子物质
inline int gcd(int a,int b) {
    return b?gcd(b,a%b):a;
}
inline ll pw(ll a,ll b) {
    ll res=1;
    while(b) {
        if(b&1)
            res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
inline string readelement(int pos) {//读入元素名称
    string res="";
    while(1) {
        if(!islower(equation[pos]))
            break;
        res+=equation[pos];
        pos++;
        if(!islower(equation[pos]))
            break;
    }
    return res;
}
inline int readratio(int pos) {//读入系数
    int res=0;
    if(!isdigit(equation[pos]))
        return 1;
    while(1) {
        res=(res<<3)+(res<<1)+equation[pos]-'0';
        pos++;
        if(!isdigit(equation[pos]))
            break;
    }
    return res;
}
inline int readion(int pos) {//读入带电粒子个数和正负
    int res=0;
    while(1) {
        if(!isdigit(equation[pos]))
            break;
        res=(res<<3)+(res<<1)+equation[pos]-'0';
        pos++;
        if(!isdigit(equation[pos]))
            break;
    }
    if(!res)
        res=1;
    if(equation[pos]=='-')
        res=-res;
    pos++;
    return res;
}
inline void read(int l,int r,int tmp) {//读入l～r这个区间的物质
    for(int i=l;i<=r;i++) {
        if(equation[i]=='[') {
            ion[cnt]=readion(i+1)*flg;
            haveion=1;
        }
        if(equation[i]==')') {
            tmp/=ct.top();
            ct.pop();
        }
        if(equation[i]=='(') {
            int o=1,nw=-1;
            for(int j=i+1;j<=r;j++) {
                if(equation[j]==')')
                    o--;
                else if(equation[j]=='(')
                    o++;
                if(!o) {
                    nw=j+1;
                    break;
                }
            }
            ct.push(readratio(nw));
            tmp*=ct.top();
        }
        if(isupper(equation[i])) {
            string now=equation[i]+readelement(i+1);
            int p=i+1;
            while(islower(equation[p]))
                p++;
            if(!appear[now])
                appear[now]=++num,element[num]=now;
            mat[appear[now]][cnt]+=readratio(p)*flg*tmp;
        }
    }
}
inline bool gauss() {//高斯消元求解，false为无穷多解或无解，true为唯一解
    for(int i=1;i<=num;i++) {
        for(int j=1;j<=cnt;j++) {
            rem[i][j]=mat[i][j];
            ((mat[i][j]%=mod)+=mod)%=mod;
        }
        mat[i][cnt]=(mod-mat[i][cnt])%mod;
    }
    for(int i=1;i<cnt;i++) {
        int pos=i;
        for(int j=i+1;j<=num;j++)
            if(abs(mat[j][i])>abs(mat[pos][i]))
                pos=j;
        for(int j=i;j<=cnt;j++)
            swap(mat[i][j],mat[pos][j]);
        if(!mat[i][i])
            return 0;
        ll inv=pw(mat[i][i],mod-2);
        for(int j=i+1;j<=num;j++) {
            ll tmp=mat[j][i]*inv%mod;
            for(int k=i;k<=cnt;k++)
                (((mat[j][k]-=mat[i][k]*tmp%mod)%=mod)+=mod)%=mod;
        }
    }
    for(int i=cnt-1;i;i--) {
        for(int j=i+1;j<cnt;j++)
            (((mat[i][cnt]-=mat[i][j]*mat[j][cnt]%mod)%=mod)+=mod)%=mod;
        (mat[i][cnt]*=pw(mat[i][i],mod-2))%=mod;
    }
    int res=0;
    for(int i=1;i<=(1<<15);i++) {
        bool sol=1;
        for(int j=1;j<cnt;j++)
            if(mat[j][cnt]*i%mod>(1<<15)) {
                sol=0;
                break;
            }
        if(!sol)
            continue;
        int g=i;
        for(int j=1;j<cnt;j++)
            g=gcd(g,mat[j][cnt]*i%mod);
        if(g==1)
            res++;
    }
    if(res-1)
        return 0;
    for(int i=1;i<=(1<<15);i++) {
        bool sol=1;
        for(int j=1;j<cnt;j++)
            if(mat[j][cnt]*i%mod>(1<<15)) {
                sol=0;
                break;
            }
        if(!sol)
            continue;
        int g=i;
        for(int j=1;j<cnt;j++)
            g=gcd(g,mat[j][cnt]*i%mod);
        if(g==1) {
            for(int j=1;j<cnt;j++)
                ret[j]=mat[j][cnt]*i%mod;
            ret[cnt]=i;
            break;
        }
    }
    for(int i=1;i<=cnt;i++)
        if(!ret[i])
            return 0;
    for(int i=1;i<=num;i++) {
        int mogic=0;
        for(int j=1;j<=cnt;j++)
            mogic+=rem[i][j]*ret[j];
        if(mogic)
            return 0;
    }
    return 1;
}
signed main() {
	freopen("in.txt","r",stdin);
    //scanf("%lld",&T);
    T=1;
    while(T--) {
        appear.clear();
        cin>>equation;
        flg=1;lst=0;cnt=0,num=0;haveion=0;
        memset(mat,0,sizeof mat);
        memset(l,0,sizeof l);
        memset(r,0,sizeof r);
        memset(ret,0,sizeof ret);
        memset(ion,0,sizeof ion);
        for(int i=0;i<equation.length();i++) {
            if(i==equation.length()-1) {
                cnt++;
                read(lst,i,1);
                l[cnt]=lst;
                r[cnt]=i;
            }
            if(equation[i]=='='||(equation[i]=='+'&&equation[i+1]=='(')||(equation[i]=='+'&&isupper(equation[i+1]))) {
                cnt++;
                read(lst,i,1);
                l[cnt]=lst;
                r[cnt]=i;
                lst=i+1;
            }
            if(equation[i]=='=')
                flg=-1;
        }
        if(haveion) {
            ++num;
            for(int i=1;i<=cnt;i++)
                mat[num][i]=ion[i];
        }
        if(!gauss()) {
            puts("-1");
            continue;
        }
        for(int i=1;i<=cnt;i++) {
            if(ret[i]>1)
                printf("%lld",ret[i]);
            cout<<equation.substr(l[i],r[i]-l[i]+1);
        }
        puts("");
    }
}
/*
input:

8
H2O3=H2O+O2
Fe(CN)6[4-]+MnO4[-]+H[+]=Fe[3+]+NO3[-]+CO2+Mn[2+]+H2O
ReCl5+H2O=Re2Cl9[2-]+ReO4[-]+Cl[-]+H[+]
KMnO4+FeSO4+H2SO4=Fe2(SO4)3+MnSO4+K2SO4+H2O
B10H12CNH3+NiCl2+NaOH=Na4(B10H10CNH2)2Ni+NaCl+H2O
Fe36Si5+H3PO4+K2Cr2O7=FePO4+SiO2+K3PO4+CrPO4+H2O
B10H12CNH3+NiCl2+NaOH=Na4(B10H10CNH2)2Ni+NaCl+H2O
K4Fe(CN)6+KMnO4+H2SO4=KHSO4+Fe2(SO4)3+MnSO4+HNO3+CO2+H2

output:

H2O3=H2O+O2
5Fe(CN)6[4-]+61MnO4[-]+188H[+]=5Fe[3+]+30NO3[-]+30CO2+61Mn[2+]+94H2O
7ReCl5+12H2O=2Re2Cl9[2-]+3ReO4[-]+17Cl[-]+24H[+]
2KMnO4+10FeSO4+8H2SO4=5Fe2(SO4)3+2MnSO4+K2SO4+8H2O
2B10H12CNH3+NiCl2+6NaOH=Na4(B10H10CNH2)2Ni+2NaCl+6H2O
9Fe36Si5+836H3PO4+192K2Cr2O7=324FePO4+45SiO2+128K3PO4+384CrPO4+1254H2O
2B10H12CNH3+NiCl2+6NaOH=Na4(B10H10CNH2)2Ni+2NaCl+6H2O
4K4Fe(CN)6+30KMnO4+82H2SO4=46KHSO4+2Fe2(SO4)3+30MnSO4+24HNO3+24CO2+47H2
*/
