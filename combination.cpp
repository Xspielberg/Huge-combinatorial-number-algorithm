#define X 100000000000
#define Y 1000000000
#define Z 10000000
#define p0 9699691
#include<stdio.h>
#include<iostream>
using namespace std;
static long long n,m;
static int size=0,cnt;
static int A[X],B[X];//for high¡ªprecision calculation 
static int primes[Y],totid[Y];//the factors and the index of factors of combination
static int is_P[Z];//prime<=>0
 
void Euler_Sieve(int n){
    for(int i=2;i<=n;i++){
        if(!is_P[i]) primes[cnt++]=i;
        for(int j=0;j<=n/i;j++){
            is_P[primes[j]*i]=1;
            if(i%primes[j]==0) break;
        }
    }
}
 
int toid(int a,int p){
    int res=0;
    while(a){
        res+=a/p;
        a/=p;
    }
    return res;
}//the index of a prime X in a! equals [a/X]+[a/X^2]...+[a/X^n].until X^n>a
 
void mul(int k){
    int t=0,i;
    for(i=0;i<=size||t;i++){
        if(i<=size) t+=k*A[i];
        B[i]=t%10;
        t/=10;
    }
    size=i-1;
    for(int j=0;j<=size;j++) A[j]=B[j];
}//High-Precision Calculation to get the array form of combination

long long pow(long long x,long long y)
{
    if (y==0) return 1;
    long long z=pow(x,y/2)%p0;
    if (y%2==0) return z*z%p0;
    return z*z%p0*x%p0;
}
long long ni(long long x)
{
    return pow(x,p0-2);
}
long long c(int n,int m)
{
    if (m==0) return 1%p0;
    if (n==0) return 0;
    if (n>=p0||m>=p0) return c(n/p0,m/p0)*c(n%p0,m%p0)%p0;//Lucas Law
    long long x=1,y=1;
    for (int i=n;i>=n-m+1;i--) x=x*i%p0;
    for (int i=1;i<=m;i++) y=y*i%p0;
    return x*ni(y)%p0;
}

int main(){
    scanf("%lld%lld",&n,&m);
	if(n<=9699690) {
    Euler_Sieve(n);
 
    for(int i=0;i<cnt;i++){
        int p=primes[i];
        totid[i]=toid(n,p)-toid(m,p)-toid(n-m,p);
    }
 
    A[0]=B[0]=1;
    for(int i=0;i<cnt;i++){
        for(int j=totid[i];j>0;j--){
            mul(primes[i]);
        }
    }
    for(int i=size;i>=0;i--) printf("%d",A[i]);
    return 0;}
    else{cout<<c(n,m);
	}
}

