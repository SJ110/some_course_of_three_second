#include<iostream>
#include<vector>
#include<sstream>

// # include "akari.h"

using namespace std;

// namespace aka{
//请在命名空间内编写代码，否则后果自负
//           上 下 左 右
int a[4] = {-1, 1, 0, 1};
int b[4] = {0, 0, -1, 0};
vector<vector<int>> ret; //最后返回的答案
bool issame(vector<vector<int>> &s1, vector<vector<int>> &s2);
void boarderAndmark(vector<vector<int>>&s,int row,int col,vector<vector<int>>&islight);
void putlight(vector<vector<int>> &g, vector<vector<int>> &islight, vector<pair<int, int>>& save, int x, int y);
void DFSwhite(vector<vector<int>> &g, vector<vector<int>> &islight, vector<pair<int, int>> &white, int i);
void DFS1(int x, int y, vector<vector<int>> &g, vector<vector<int>> &islight);
void DFS2(int x, int y, vector<vector<int>> &g, vector<vector<int>> &islight);
void DFS3(int x, int y, vector<vector<int>> &g, vector<vector<int>> &islight);
vector<vector<int>> solveAkari(vector<vector<int>> &g);
void findway(vector<vector<int>> &g, int row, int col, vector<vector<int>> &islight);

bool  issame(vector<vector<int>>& s1,vector<vector<int>>& s2){
    for (int i = 0; i < s1.size();i++){
        for (int j = 0; j < s1[0].size();j++){
            if(s1[i][j]!=s2[i][j])
                return false;
        }
    }
    return true;
}
void boarderAndmark(vector<vector<int>>&s,int row,int col,vector<vector<int>>&islight){
    int count = 0;
    vector<int> ismark(4, 0); //1 修改为对应值，0 不修改
    if(row-1>=0 && (s[row-1][col]==-2 ||s[row-1][col]==5) ) //表示此处可以电灯，或者已经电灯
     { //上
         ismark[0] = 1;  
         count++;
     }  
    if(row+1<s.size()&&(s[row+1][col]==-2 || s[row+1][col]==5))
        {//下
            ismark[1] = 1;
            count++;
        }
    if(col-1>=0 &&(s[row][col-1]==-2 || s[row][col-1]==5))
      { //左
          count++;
          ismark[2] = 1;
      }  
    if(col+1<s.size()&&(s[row][col+1]==-2 || s[row][col+1]==5))
    {//右
          count++;
          ismark[3] = 1;
      }  
    if(count==s[row][col]){ //无回溯
        for (int j = 0; j < 4;j++){
            if(ismark[j]==1){
                switch(j){
                    case 0:
                        s[row - 1][col] = 5; //对该位置上左右进行标记
                        islight[row - 1][col] = 5; //点亮
                        for (int i = row - 2; i >= 0;i--){ //此行往上
                            if(s[i][col]==-2){
                                s[i][col] = -3;//设置不可用灯
                                islight[i][col] = 6; //设置此处被点亮
                            }else if(s[i][col]==5 || s[i][col]==-3){
                                if(s[i][col]==-3)
                                    islight[i][col] = 6;
                            } //已经放灯或者标记不可放灯  
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        // for (int i = row + 2;i<s.size();i++){ //往下
                        //     if(s[i][col]==-2){
                        //         s[i][col] = -3;//设置不可用灯
                        //         islight[i][col] = 6; //设置此处被点亮
                        //     }else if(s[i][col]==5 || s[i][col]==-3)
                        //         continue; //s已经点亮 islight 已经点亮
                        //         else 
                        //             break; //遇到墙 ，之后不可亮
                        // }
                        for (int i = col - 1; i >= 0;i--){ //往左
                            if(s[row-1][i]==-2){
                                s[row-1][i] = -3;
                                islight[row-1][i] = 6;
                            }else if(s[row-1][i]==5 || s[row-1][i]==-3){
                                if(s[row-1][i]==-3)
                                    islight[row-1][i] = 6;
                            }
                                else
                                    break;
                        }
                        for (int i = col + 1;i<s[0].size();i++){//往右
                            if(s[row-1][i]==-2){
                                s[row-1][i] = -3;
                                islight[row-1][i] = 6;
                            }else if(s[row-1][i]==5 || s[row-1][i]==-3){
                                if(s[row-1][i]==-3)
                                    islight[row-1][i] = 6;
                            }
                                else
                                    break;
                            }
                         break;
                    case 1:
                        s[row + 1][col] = 5; //对该位置下左右进行标记
                        islight[row + 1][col] = 5; //点亮
                        // for (int i = row - 2; i >= 0;i--){ //此行往上
                        //     if(s[i][col]==-2){
                        //         s[i][col] = -3;//设置不可用灯
                        //         islight[i][col] = 6; //设置此处被点亮
                        //     }else if(s[i][col]==5 || s[i][col]==-3) //已经放灯或者标记不可放灯  
                        //         continue; //s已经点亮 islight 已经点亮
                        //         else 
                        //             break; //遇到墙 ，之后不可亮
                        // }
                        for (int i = row + 2;i<s.size();i++){ //往下
                            if(s[i][col]==-2){
                                s[i][col] = -3;//设置不可用灯
                                islight[i][col] = 6; //设置此处被点亮
                            }else if(s[i][col]==5 || s[i][col]==-3){
                                if(s[i][col]==-3)
                                    islight[i][col] = 6;
                            }
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        for (int i = col - 1; i >= 0;i--){ //往左
                            if(s[row+1][i]==-2){
                                s[row+1][i] = -3;
                                islight[row+1][i] = 6;
                            }else if(s[row+1][i]==5 || s[row+1][i]==-3){
                                if(s[row+1][i]==-3)
                                    islight[row+1][i] = 6;
                            }
                                else
                                    break;
                        }
                        for (int i = col + 1;i<s[0].size();i++){//往右
                            if(s[row+1][i]==-2){
                                s[row+1][i] = -3;
                                islight[row+1][i] = 6;
                            }else if(s[row+1][i]==5 || s[row+1][i]==-3){
                                if(s[row+1][i]==-3)
                                    islight[row+1][i] = 6;
                            }
                                else
                                    break;
                            }                       
                        break;
                    case 2:
                        s[row ][col-1] = 5; //对该位置上下左进行标记
                        islight[row][col-1] = 5; //点亮
                        for (int i = row-1; i >= 0;i--){ //此行往上
                            if(s[i][col-1]==-2){
                                s[i][col-1] = -3;//设置不可用灯
                                islight[i][col-1] = 6; //设置此处被点亮
                            }else if(s[i][col-1]==5 || s[i][col-1]==-3){
                                if(s[i][col-1]==-3)
                                    islight[i][col-1] = 6;
                            } //已经放灯或者标记不可放灯  
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        for (int i = row+1;i<s.size();i++){ //往下
                            if(s[i][col-1]==-2){
                                s[i][col-1] = -3;//设置不可用灯
                                islight[i][col-1] = 6; //设置此处被点亮
                            }else if(s[i][col-1]==5 || s[i][col-1]==-3){
                                if(s[i][col-1]==-3)
                                    islight[i][col-1] = 6;
                            }
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        for (int i = col - 2; i >= 0;i--){ //往左
                            if(s[row][i]==-2){
                                s[row][i] = -3;
                                islight[row][i] = 6;
                            }else if(s[row][i]==5 || s[row][i]==-3){
                                if(s[row][i]==-3)
                                    islight[row][i] = 6;
                            }
                                else
                                    break;
                        }
                        // for (int i = col + 1;i<s[0].size();i++){//往右
                        //     if(s[row+1][i]==-2){
                        //         s[row+1][i] = -3;
                        //         islight[row+1][i] = 6;
                        //     }else if(s[row+1][i]==5 || s[row+1][i]==-3)
                        //         continue;
                        //         else
                        //             break;
                        //     }                          
                        break;
                    case 3:
                        s[row][col+1] = 5; //对该位置上下右设置标记
                        islight[row][col+1] = 5; //点亮
                        for (int i = row-1; i >= 0;i--){ //此行往上
                            if(s[i][col+1]==-2){
                                s[i][col+1] = -3;//设置不可用灯
                                islight[i][col+1] = 6; //设置此处被点亮
                            }else if(s[i][col+1]==5 || s[i][col+1]==-3){
                                 if(s[i][col+1]==-3)
                                    islight[i][col+1] = 6;
                            } //已经放灯或者标记不可放灯  
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        for (int i = row+1;i<s.size();i++){ //往下
                            if(s[i][col+1]==-2){
                                s[i][col+1] = -3;//设置不可用灯
                                islight[i][col+1] = 6; //设置此处被点亮
                            }else if(s[i][col+1]==5 || s[i][col+1]==-3){
                                if(s[row][i]==-3)
                                    islight[i][col+1] = 6;
                            }
                                else 
                                    break; //遇到墙 ，之后不可亮
                        }
                        // for (int i = col - 2; i >= 0;i--){ //往左
                        //     if(s[row][i]==-2){
                        //         s[row][i] = -3;
                        //         islight[row][i] = 6;
                        //     }else if(s[row][i]==5 || s[row][i]==-3)
                        //         continue;
                        //         else
                        //             break;
                        // }
                        for (int i = col + 2;i<s[0].size();i++){//往右
                            if(s[row][i]==-2){
                                s[row][i] = -3;
                                islight[row][i] = 6;
                            }else if(s[row][i]==5 || s[row][i]==-3){
                                if(s[row][i]==-3)
                                    islight[row][i] = 6;
                            }
                                else
                                    break;
                            }                           
                        break;
                     }
                }
            }
        }

    }


void putlight(vector<vector<int>>& g,vector<vector<int>>&islight,vector<pair<int, int>>& save,int x,int y){
    for (int i = x; i >= 0;i--){ //上
        if(g[i][y]>=-1 && g[i][y]<=4)
            break;
        else if(g[i][y]==-2){
            g[i][y] = -3;//设置不可放灯
            islight[i][y] = 6;//设置点亮
            save.push_back({i, y}); //保存修改的点
        }
    }

    for (int i = x;i<g.size();i++){ //下
        if(g[i][y]>=-1 && g[i][y]<=4)
            break;
        else if(g[i][y]==-2){
            g[i][y] = -3;//设置不可放灯
            islight[i][y] = 6;//设置点亮
            save.push_back({i, y}); //保存修改的点
        }
    }
    for (int j = y; j >= 0;j--){//左
        if(g[x][j]>=-1 && g[x][j]<=4)
            break;
        else if(g[x][j]==-2){
            g[x][j]=-3;
            islight[x][j] = 6;
            save.push_back({x, j});
        }
    }
    for (int j = y; j <g.size() ;j++){//右
        if(g[x][j]>=-1 && g[x][j]<=4)
            break;
        else if(g[x][j]==-2){
            g[x][j]=-3;
            islight[x][j] = 6;
            save.push_back({x, j});
        }
    }
    return;
}


void DFSwhite(vector<vector<int>>& g,vector<vector<int>>& islight,vector<pair<int,int>>&white,int i){
    if(i==white.size()){
        for (int i = 0; i < islight.size();i++){
            for(int j=0;j<islight[0].size();j++){
                if(islight[i][j]==-2){
                    return; //未成功的递归
                }
             }
        }

         for (int i = 0; i < islight.size();i++){
            for(int j=0;j<islight[0].size();j++){
            if(islight[i][j]==6){
                islight[i][j] = -2;
            }
         }
        }
        ret=islight;  //结果
        return;
    }

    for(int x=i;x<white.size();x++){
        if(g[white[x].first][white[x].second]==-2 && islight[white[x].first][white[x].second]==-2){
            vector<pair<int, int>> save;
            g[white[x].first][white[x].second]=5;
            islight[white[x].first][white[x].second] = 5;
            putlight(g, islight, save, white[x].first,white[x].second );
            DFSwhite(g, islight, white, x + 1);  //递归
            //回溯
            g[white[x].first][white[x].second]=-2;
            islight[white[x].first][white[x].second] = -2;
            for (auto it = save.begin();it!=save.end();it++)
            {
                g[it->first][it->second] = -2;//回溯
                islight[it->first][it->second] = -2;
            }     
        }
    }
}



void DFS1(int x,int y,vector<vector<int>>& g,vector<vector<int>>&islight){
    //空位与所需灯数相同，直接点亮
    for (int k = 0; k < 4;k++){
        
        if(g[x+a[k]][y+b[k]]==-2){
            vector<pair<int, int>> save;
             g[x + a[k]][y + b[k]] = 5;
             islight[x + a[k]][y + b[k]]=5;
             putlight(g, islight, save, x + a[k], y + b[k]);
             for (int i = 0; i < 4; i++)
            {
                if(g[x+a[i]][y+b[i]]==-2){
                    g[x + a[i]][y + b[i]] = -3;
                    islight[x + a[i]][y + b[i]] = -2;
                } 
            }
            findway(g, x,y + 1, islight);
            for(int i=0;i<4;i++){
                if((g[x+a[i]][y+b[i]]==5 && islight[x+a[i]][y+b[i]]==5) || ( g[x+a[i]][y+b[i]]==-3 && islight[x+a[i]][y+b[i]]==-2 )){
                    g[x + a[i]][y + b[i]] = -2;
                    islight[x + a[i]][y + b[i]] = -2;
                }
             } 
            for (auto it = save.begin();it!=save.end();it++)
            {
                g[it->first][it->second] = -2;//回溯
                islight[it->first][it->second] = -2;
            }        
        }
           
    }
}

void DFS2(int x,int y,vector<vector<int>>& g,vector<vector<int>>&islight){

    for (int k = 0;k<4;k++){
        vector<pair<int, int>> save0;
        if (g[x + a[k]][y + b[k]] == -2 && islight[x + a[k]][y + b[k]] != -2){
            g[x + a[k]][y + b[k]] = 5;
            islight[x + a[k]][y + b[k]] = 5;
            putlight(g, islight, save0, x + a[k], y + b[k]);
            for (int t = k + 1; t < 4; t++){
                vector<pair<int, int>> save1;
                if (g[x + a[t]][y + b[t]] == -2 && islight[x + a[t]][y + b[t]] != -2){
                    g[x + a[t]][y + b[t]] = 5;
                    islight[x + a[t]][y + b[t]] = 5;//然后需要把没放灯的位置设置不能放灯
                    putlight(g, islight,save1, x + a[t], y + b[t]);
                    for (int i = 0; i < 4; i++)
                    {
                        if(g[x+a[i]][y+b[i]]==-2){
                            g[x + a[i]][y + b[i]] = -3;
                            islight[x + a[i]][y + b[i]] = -2;
                        }   
                    }
                    findway(g, x, y + 1, islight);
                    for(int i=0;i<4;i++){
                         if((g[x+a[i]][y+b[i]]==5 && islight[x+a[i]][y+b[i]]==5) || ( g[x+a[i]][y+b[i]]==-3 && islight[x+a[i]][y+b[i]]==-2 )){
                            g[x + a[i]][y + b[i]] = -2;
                            islight[x + a[i]][y + b[i]] = -2;
                     }
                    }
                    for (auto it = save1.begin();it!=save1.end();it++)
                    {
                        g[it->first][it->second] = -2;//回溯
                        islight[it->first][it->second] = -2;
                    }
                }
            }
             for (auto it = save0.begin();it!=save0.end();it++)
                {
                    g[it->first][it->second] = -2;//回溯
                    islight[it->first][it->second] = -2;
                }
        }
    }
}
       

void DFS3(int x,int y,vector<vector<int>>& g,vector<vector<int>>&islight){
    for (int k = 0;k<4;k++){
         vector<pair<int, int>> save0;
         if(g[x+a[k]][y+b[k]]==-2 && islight[x+a[k]][y+b[k]]!=-2){
            g[x + a[k]][y + b[k]] = 5;
            islight[x + a[k]][y + b[k]] = 5;
            putlight(g, islight, save0,x+a[k],y+b[k]);
            for (int t = k + 1;t<4;t++){
                vector<pair<int, int>> save1;
                if(g[x+a[t]][y+b[t]]==-2 && islight[x+a[t]][y+b[t]]!=-2){
                     g[x + a[t]][y + b[t]] = 5;
                    islight[x + a[t]][y + b[t]] = 5;
                    putlight(g, islight, save1,x+a[t],y+b[t]);
                    for (int p = k + 1; p < 4;p++){
                        vector<pair<int, int>> save2;
                        if(g[x+a[p]][y+b[p]]==-2 && islight[x+a[p]][y+b[p]]!=-2){
                            g[x + a[p]][y + b[p]] = 5;
                            islight[x + a[p]][y + b[p]] = 5;
                            putlight(g, islight, save2,x+a[p],y+b[p]);
                            for (int i = 0; i < 4; i++)
                            {
                                if(g[x+a[i]][y+b[i]]==-2){
                                    g[x + a[i]][y + b[i]] = -3;
                                    islight[x + a[i]][y + b[i]] = -2;
                                }
                                    
                            }
                            findway(g, x, y + 1, islight);
                             for(int i=0;i<4;i++){
                                if((g[x+a[i]][y+b[i]]==5 && islight[x+a[i]][y+b[i]]==5) || ( g[x+a[i]][y+b[i]]==-3 && islight[x+a[i]][y+b[i]]==-2 )){
                                    g[x + a[i]][y + b[i]] = -2;
                                    islight[x + a[i]][y + b[i]] = -2;
                                }
                            }
                             for (auto it = save2.begin();it!=save2.end();it++)
                            {
                                g[it->first][it->second] = -2;//回溯
                                islight[it->first][it->second] = -2;
                            }
                        }
                    }
                    for (auto it = save1.begin();it!=save1.end();it++)
                    {
                        g[it->first][it->second] = -2;//回溯
                        islight[it->first][it->second] = -2;
                    }
                }
            }
            for (auto it = save0.begin();it!=save0.end();it++)
                {
                    g[it->first][it->second] = -2;//回溯
                    islight[it->first][it->second] = -2;
                }
         }   
    }
}

void findway(vector<vector<int>>&g,int row,int col,vector<vector<int>>&islight){
    for(int x=row;x<g.size();x++){
        for (int y = col; y < g[0].size();y++){
            if(g[x][y]>=1 && g[x][y]<=3){
                 int count = 0;
                if(x-1>=0 && g[x-1][y]==5  ) //表示此处可以电灯，或者已经电灯
                { //上
                    count++;
                }  
                if(x+1<g.size()&& g[x+1][y]==5 )
                {//下
                    count++;
                }
                if(y-1>=0 &&g[x][y-1]==5)
                { //左
                    count++;
                }  
                if(y+1<g.size()&&g[x][y+1]==5)
                {//右
                    count++;
                }  
                switch(g[x][y]-count){
                    case 0:
                        //findway(g, row, col+1, islight);
                        break;
                    case 1:
                        DFS1(x, y, g,islight);
                        break;
                    case 2:
                         DFS2(x,y,g,islight);
                        break;
                    case 3:
                        DFS3(x, y, g,islight);
                        break;
                }
            }
        }
    }
    vector<pair<int, int>> white;
    for (int i = 0; i < islight.size();i++){
        for(int j=0;j<islight[0].size();j++){
            if(islight[i][j]==-2){
                white.push_back({i, j});
            }
        }
    }
    cout << "white:" << white.size()<<"  ";
    DFSwhite(g,islight, white,0);
    return;
}


vector<vector<int> > solveAkari(vector<vector<int> > & g)
{
    //-3标志此处不可使用灯  -2表示位置空余 5表示此处放灯  6表示此处被点亮
    vector<vector<int>> mark=g; //循环比较
    vector<vector<int>> islight = g;//只有所有的-2变为6才表示得到解
    vector<pair<int, int>> help; //存储可能回溯的点
        for (int i = 0; i < g.size(); i++)
        {
            for (int j = 0; j < g[0].size(); j++)

                if (g[i][j] == 0) //0的情况比较特殊，提前确定下来
                {
                    if (i - 1 >= 0 && g[i-1][j]==-2)
                        g[i - 1][j] = -3; //但此时还未点灯
                    if (i + 1 < mark.size() && g[i+1][j]==-2)
                        g[i + 1][j] = -3;
                    if (j - 1 >= 0&&  g[i][j-1]==-2)
                        g[i][j - 1] = -3;
                    if (j + 1 < mark.size()&& g[i][j+1]==-2)
                        g[i][j + 1] = -3;
                }
            }
            if(issame(g,mark)){ //图中没有0 则先处理，保证可以循环
                for (int i = 0; i < g.size(); i++)
                {
                    for (int j = 0; j < g[0].size(); j++)
                    {
                        boarderAndmark(g, i, j, islight);
                    }
                }
            } //此处保证循环的条件

            while (issame(g, mark) == false)
            { //以下处理确定情况 1 2  3  4
                mark = g;
                for (int i = 0; i < g.size(); i++)
                {
                    for (int j = 0; j < g[0].size(); j++)
                    {
                        boarderAndmark(g, i, j, islight);
                    }
                }
        }
        //此处保存需要回溯的点
        vector<vector<pair<int, int>>> waitlight;
        for (int row = 0; row < g.size();row++){
            for(int col=0;col<g[0].size();col++){
                int count = 0;
                if(g[row][col]>=1 && g[row][col]<=3){
                    vector<pair<int, int>> tmp;
                    if(row-1>=0 && g[row-1][col]==-2  ) //表示此处可以电灯，或者已经电灯
                    { //上
                        count++;
                        tmp.push_back({row - 1, col});
                    }  
                    if(row+1<g.size()&& g[row+1][col]==-2 )
                    {//下
                        count++;
                        tmp.push_back({row + 1, col});
                    }
                    if(col-1>=0 &&g[row][col-1]==-2)
                    { //左
                        count++;
                        tmp.push_back({row, col - 1});
                    }  
                    if(col+1<g.size()&&g[row][col+1]==-2)
                    {//右
                        count++;
                        tmp.push_back({row, col + 1});
                    }  
                    if(count>g[row][col]){
                         help.push_back({row, col});
                         waitlight.push_back(tmp);
                        // waitlight.push_back(help); //最后一个方目标点坐标
                    }
                }
            }
        }

       // cout << help.size() << "   ";
        for (int i = 0; i < islight.size(); i++)
        {
            for (int j = 0; j < islight[0].size(); j++)
                cout << islight[i][j] << " ";
            cout << "\n";
        }

        cout << "\n\n";
                for (int i = 0; i < islight.size(); i++)
        {
            for (int j = 0; j < islight[0].size(); j++)
                cout << g[i][j] << " ";
            cout << "\n";
        }
        //回溯法
        findway(g,0,0,islight);
        cout << ret.size()<<"   ";
        return ret;
        // 请在此函数内返回最后求得的结果

}
/* input
-2	-2	-1	1	-2	-2	-2
-2	-2	-2	-2	-2	-2	-2
-2	-2	-2	-2	-2	-2	1
0	-2	-2	-2	-2	-2	1
2	-2	-2	-2	-2	-2	-2
-2	-2	-2	-2	-2	-2	-2
-2	-2	-2	1	-1	-2	-2

2 -2 -2 -2 2 -2 -2 -2 -2 -1 
-2 -1 -2 -2 -2 -2 -2 -2 -1 -2 
-2 -2 -2 2 -2 -1 -2 -2 -2 -2 
-2 -2 -2 -2 -2 -2 -2 2 -2 -2 
-2 -2 2 -2 -2 -2 -2 -2 -2 1 
-1 -2 -2 -2 -2 -2 -2 0 -2 -2 
-2 -2 2 -2 -2 -2 -2 -2 -2 -2 
-2 -2 -2 -2 1 -2 -1 -2 -2 -2 
-2 -1 -2 -2 -2 -2 -2 -2 1 -2 
1 -2 -2 -2 -2 1 -2 -2 -2 0 
*/

vector<vector<int> > genVector(string s, int n, int m) {
    vector<vector<int> > res(n, vector<int>(m, 0));
    stringstream ss(s);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ss >> res[i][j];
        }
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> g=genVector("-2	-2	-1	1	-2	-2	-2\
                                    -2	-2	-2	-2	-2	-2	-2\
                                    -2	-2	-2	-2	-2	-2	1\
                                    0	-2	-2	-2	-2	-2	1\
                                    2	-2	-2	-2	-2	-2	-2\
                                    -2	-2	-2	-2	-2	-2	-2\
                                    -2	-2	-2	1	-1	-2	-2",7,7);

    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < n;j++)
    //         cin>>g[i][j];
    // cout << "\n\n";
    vector<vector<int>>ret=solveAkari(g);
    for (int i = 0; i < n;i++)
    {
        for (int j = 0;j<n;j++)
            cout<<ret[i][j]<<" ";
        cout << "\n";
    }
    return 0;
}
// }