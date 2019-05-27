#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

int fx[4]= {0,0,1,-1};
int fy[4]= {1,-1,0,0};

int num[150][150];
int match[150*150];
int vis[150*150];

vector<int >mp[150*150];
int n,m;


void Getmap(){
    for(int i=1; i<=n; i++)    {
        for(int j=1; j<=m; j++)        {
            if(num[i][j]!=-1)
                num[i][j]=(i-1)*m+j;
        }
    }
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            for(int k=0; k<4; k++){
                int xx=i+fx[k];
                int yy=j+fy[k];
                if(xx>=1&&xx<=n&&yy>=1&&yy<=m){
                    mp[num[i][j]].push_back(num[xx][yy]);
                }
            }
        }
    }
}

int find(int u){
    for(int i = 0; i < mp[u].size();i++) {
        int v = mp[u][i];
        if(vis[v]==0) {
            vis[v]=1;
            if(match[v]==-1||find(match[v])){
                //match[u]=v;
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

void Match(){
    
    int output=0;
    memset(match,-1,sizeof(match));
    
    for(int i=1;i<=n*m;i++){
        memset(vis,0,sizeof(vis));
        if(find(i))output++;
    }
    
    printf("%d\n", output/2);
    
    for(int i=1;i<=n*m;i++){
        if(match[i]==-1) continue;
        int x = i/m; if(i%m!=0) x++;
        int y = i%m;
        if(y==0)y = m;
        int xx=match[i]/m; if(match[i]%m!=0)xx++;
        int yy=match[i]%m;
        if(yy==0)yy=m;
        if(num[x][y]!=-1&&num[xx][yy]!=-1)
        {
            num[x][y]=-1;num[xx][yy]=-1;
            printf("(%d,%d)--(%d,%d)\n",x,y,xx,yy);
        }
    }
}
int main(){
    while(~scanf("%d%d",&n,&m)){
        if(n==0||m==0)break;
        int z;
        scanf("%d",&z);
        memset(num, 0, sizeof(num));
        
        for(int i=1;i<=n*m;i++) 
            mp[i].clear();
        
        for(int i=0; i<z; i++){
            int x,y;
            scanf("%d%d",&x,&y);
            num[x][y]=-1;
        }
        
        Getmap();
        Match();
    }
}
