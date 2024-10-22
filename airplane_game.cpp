#include <iostream>
#include <algorithm>
using namespace std;
const int N=15;
const int M=5;
int a[N][M];
int b[N][M];
void detonate(int row){
    for(int i=row; i>max(0, row-4); i--){
        for(int j=0; j<5; j++){
            b[i][j]=a[i][j];
            if(a[i][j]==2){
                a[i][j]=0;
            }
        }
    }
}
void findMax(int pos, int n, int coins, int& maxcoins){
    if(pos<0 || pos>4 || coins<0){
        return;
    }
    if(a[n-1][pos]==1){
        coins+=1;
    }
    if(a[n-1][pos]==2){
        coins-=1;
    }
    if(n==1){
        maxcoins=max(coins, maxcoins);
        return;
    }
    else{
        findMax(pos-1, n-1, coins, maxcoins);
        findMax(pos+1, n-1, coins, maxcoins);
        findMax(pos, n-1, coins, maxcoins);
    }
}
void undetonate(int row){
    for(int i=row; i>max(0, row-4); i--){
        for(int j=0; j<5; j++){
            a[i][j]=b[i][j];
        }
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++){
                cin>>a[i][j];
            }
        }
        for(int j=0; j<5; j++){
            a[n][j]=0;
        }
        a[n][2]=3;
        int globalMax=-1, localMax;
        for(int j=n-1; j>0; j--){
            detonate(j);
            localMax=-1;
            findMax(2, n, 0, localMax);
            globalMax=max(globalMax, localMax);
            undetonate(j);
        }
        cout<<globalMax<<endl;
    }
    return 0;
}