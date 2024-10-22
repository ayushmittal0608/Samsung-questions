#include<iostream>
using namespace std;
int map[1000][1000], visited[1000][1000];
int row, col, X, Y, L;
struct node{
    int x, y, l;
};
node q[1000000];
int front, back;
void init(){
    front=0, back=0;
}
void push(node temp){
    q[back]=temp;
    back++;
}
node pop(){
    return q[front++];
}
bool isempty(){
    return front==back;
}
bool valid(int x, int y){
    return (x>=0 && x<row && y>=0 && y<col);
}
bool left(int x, int y){
    return map[x][y]==1 || map[x][y]==3 || map[x][y]==6 || map[x][y]==7;
}
bool right(int x, int y){
    return map[x][y]==1 || map[x][y]==3 || map[x][y]==4 || map[x][y]==5;
}
bool up(int x, int y){
    return map[x][y]==1 || map[x][y]==2 || map[x][y]==4 || map[x][y]==7;
}
bool down(int x, int y){
    return map[x][y]==1 || map[x][y]==2 || map[x][y]==5 || map[x][y]==6;
}
int SolveEndo(int x, int y, int l){
    int ans=0;
    push({x, y, l});
    visited[x][y]=1;
    while(!isempty()){
        node cur=pop();
        int x=cur.x;
        int y=cur.y;
        int l=cur.l;
        if(l==0){
            continue;
        }
        ans++;
        if(valid(x, y-1) && left(x, y) && right(x, y-1) && visited[x][y-1]==0){
            push({x, y-1, l-1});
            visited[x][y-1]=1;
        }
        if(valid(x, y+1) && right(x, y) && left(x, y+1) && visited[x][y+1]==0){
            push({x, y+1, l-1});
            visited[x][y+1]=1;
        }
        if(valid(x-1, y) && up(x, y) && down(x-1, y) && visited[x-1][y]==0){
            push({x-1, y, l-1});
            visited[x-1][y]=1;
        }
        if(valid(x+1, y) && down(x, y) && up(x+1, y) && visited[x+1][y]==0){
            push({x+1, y, l-1});
            visited[x+1][y]=1;
        }
    }
    return ans;
}
int main(){
    int t; 
    cin>>t;
    while(t--){
        cin>>row>>col>>X>>Y>>L;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                cin>>map[i][j];
                visited[i][j]=0;
            }
        }
        if(map[X][Y]>0){
            cout<<SolveEndo(X, Y, L)<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }
}