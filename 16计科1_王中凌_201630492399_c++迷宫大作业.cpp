#include <iostream>
#include <vector>
#include<time.h>
using namespace std;

class Solution{
private:
    int rrows;
	int rcols;
	int rstartROW;
	int rstartCOL;
public:
bool mazeGenerator(int rows, int cols, int startROW, int startCOL){
	rrows=2*rows+1;
	rcols=2*cols+1;
	rstartROW=2*startROW-1;
	rstartCOL=2*startCOL-1;

	//判断迷宫是否可以生成
	if(rows<1||cols<1||startCOL<0||startROW<0) {
		cout<<"迷宫不符合要求"<<endl;
		return false;
	}
	
	if(!(startCOL^startROW)){
		cout<<"迷宫不符合要求"<<endl;
		return false;
	}


	//生成迷宫矩阵内存
	char** matrix=new char*[rrows];
	for(int i=0;i<rrows;i++){
		matrix[i]=new char[rcols];
		memset(matrix[i], '#', rcols);
	}
	
	
	//生成迷宫矩阵
	vector<pair<int,int>> build;
    
	if(startCOL==0){
		matrix[rstartROW][0]='.';
		matrix[rstartROW][0+1]='.';
		if(rstartROW>=3)
			build.push_back(make_pair(rstartROW-1,0+1));
		if(rrows>=rstartROW+4)
		    build.push_back(make_pair(rstartROW+1,0+1));
		if(cols>1)
			build.push_back(make_pair(rstartROW,0+2));
	}
	if(startROW==0){
		matrix[0][rstartCOL]='.';
		matrix[0+1][rstartCOL]='.';
		if(rstartCOL>=3)
		    build.push_back(make_pair(0+1,rstartCOL-1));
		if(rcols>=rstartCOL+4)
			build.push_back(make_pair(0+1,rstartCOL+1));
		if(rows>1)
			build.push_back(make_pair(0+2,rstartCOL));
	}

	srand((unsigned long)time(0));

	int bindex,brow,bcol;
    while(!build.empty()){
    	bindex=rand()%build.size();
    	brow=build[bindex].first;
    	bcol=build[bindex].second;
    	build[bindex]=build.back();
    	build.pop_back();
    	if(brow%2==1){
    		if(matrix[brow][bcol-1]=='.'&&matrix[brow][bcol+1]!='.'){
    			matrix[brow][bcol]=matrix[brow][bcol+1]='.';
    			bcol++;//遍历下一点
    		}
    		else if(matrix[brow][bcol-1]!='.'&&matrix[brow][bcol+1]=='.'){
    			matrix[brow][bcol]=matrix[brow][bcol-1]='.';
    			bcol--;//遍历下一点
    		}
    		else continue;
    	}
    	else if(brow%2==0){
    		if(matrix[brow-1][bcol]=='.'&&matrix[brow+1][bcol]!='.'){
    			matrix[brow][bcol]=matrix[brow+1][bcol]='.';
    			brow++;//遍历下一点
    		}
    		else if(matrix[brow-1][bcol]!='.'&&matrix[brow+1][bcol]=='.'){
    			matrix[brow][bcol]=matrix[brow-1][bcol]='.';
    			brow--;//遍历下一点
    		}
    		else continue;
    	}
		//把下一个点加入build中
    	if(brow>2)
    		build.push_back(make_pair(brow-1,bcol));
    	if(brow<(rrows-3))
    		build.push_back(make_pair(brow+1,bcol));
    	if(bcol>2)
    		build.push_back(make_pair(brow,bcol-1));
    	if(bcol<(rcols-3))
    		build.push_back(make_pair(brow,bcol+1));
    }


	//生成出口
	openEnd(matrix,rrows,rcols,rstartROW,rstartCOL);



	//显示初始迷宫矩阵
	cout<<"这是初始化的迷宫"<<endl;
	showMatrix(matrix,rrows,rcols);
	cin.get();

	int pathLength=0;
	vector<pair<int,int>> path;
	
	if(startROW==0){
        if(mazeTraverse(matrix,rrows,rcols,0,rstartCOL,0,rstartCOL,2,path,pathLength)){
        	return true;
		}
	}

	if(startCOL==0){
        if(mazeTraverse(matrix,rrows,rcols,rstartROW,0,rstartROW,0,3,path,pathLength))
        	return true;
	}
	cout<<"结束走迷宫程序"<<endl;
	cout<<"没有终点或没有合适的终点，回到入口"<<endl;
	return false;

}

bool mazeTraverse(char** matrix,int rrows,int rcols, int row, int col, int rstartROW, 
	                int rstartCOL, int direct, vector<pair<int,int>>& path,int& pathLength){
	//范围
	if((row>=0)&&(row<rrows)&&(col>=0)&&(col<rcols)){
		//判断是否找到终点
        if(matrix[row][col]=='.'&&!((row==rstartROW)&&(col==rstartCOL))){
        	if(row==0||row==rrows-1||col==0||col==rcols-1){

				//标记走过的点
				matrix[row][col]='X';
				//路径长度加一
				pathLength++;
				//把点压如路径
        		path.push_back(make_pair(row,col));
				//等待输入命令
				cin.get();
				//显示迷宫矩阵
				showMatrix(matrix,rrows,rcols);
				//显示简化路径
				showPath(path,pathLength);
        		cout<<"终点("<<row<<","<<col<<")"<<endl;
				int p=-1;
        		cout<<"是否查找下一个终点:输入0不查找；输入1查找；"<<endl;
				cin>>p;
				while(!(p==0||p==1)){
					cout<<"输入错误，请重新输入"<<endl;
					cout<<"是否查找下一个终点:输入0不查找；输入1查找；"<<endl;
					cin>>p;
				}
				if(p==0){
					cout<<"结束走迷宫程序"<<endl;
					cout<<"成功从终点走出"<<endl;
					return true;
				}
				if(p==1){
					//路径长度减一
					pathLength--;
					//将该点从路径中移除
					path.pop_back();
					//等待输入命令
					cin.get();
					//显示迷宫矩阵
					showMatrix(matrix,rrows,rcols);
					//显示简化路径
					showPath(path,pathLength);
					return false;
				}
			}
		}

		bool hasPath=false;
		if(matrix[row][col]=='.'){
			//标记走过的点
		    matrix[row][col]='X';
			//路径长度加一
			pathLength++;
			//把点压如路径
			path.push_back(make_pair(row,col));
			//等待输入命令
			cin.get();
			//显示迷宫矩阵
			showMatrix(matrix,rrows,rcols);
			//显示简化路径
			showPath(path,pathLength);

            switch(direct){
			case(0):
                hasPath=
                	mazeTraverse(matrix,rrows,rcols,row,col+1,rstartROW,rstartCOL,3,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row-1,col,rstartROW,rstartCOL,0,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col-1,rstartROW,rstartCOL,1,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row+1,col,rstartROW,rstartCOL,2,path,pathLength);
				break;
			case(1):
                hasPath=
                	mazeTraverse(matrix,rrows,rcols,row-1,col,rstartROW,rstartCOL,0,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col-1,rstartROW,rstartCOL,1,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row+1,col,rstartROW,rstartCOL,2,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col+1,rstartROW,rstartCOL,3,path,pathLength);
				break;
			case(2):
                hasPath=
                	mazeTraverse(matrix,rrows,rcols,row,col-1,rstartROW,rstartCOL,1,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row+1,col,rstartROW,rstartCOL,2,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col+1,rstartROW,rstartCOL,3,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row-1,col,rstartROW,rstartCOL,0,path,pathLength);
				break;
			case(3):
                hasPath=
                	mazeTraverse(matrix,rrows,rcols,row+1,col,rstartROW,rstartCOL,2,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col+1,rstartROW,rstartCOL,3,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row-1,col,rstartROW,rstartCOL,0,path,pathLength)||
                	mazeTraverse(matrix,rrows,rcols,row,col+1,rstartROW,rstartCOL,1,path,pathLength);
				break;
			}

			if(hasPath==false){
				//路径长度减一
				pathLength--;
				//将该点从路径移除
				path.pop_back();
				//等待输入命令
				cin.get();
				//显示迷宫矩阵
				showMatrix(matrix,rrows,rcols);
				//显示简化路径
				showPath(path,pathLength);
			}
		}

		return hasPath;


	}
	else return false;

}

//生成出口函数
void openEnd(char** matrix, int rrows, int rcols, int rstartROW,int rstartCOL){
	//记录可用作终点的点
	vector<pair<int,int>> ends;
	for(int i=1;i<rcols-1;i++)
		if(rstartCOL!=i&&matrix[1][i]=='.'){
	ends.push_back(make_pair(0,i));}
	for(int i=1;i<rcols-1;i++)
		if(matrix[rrows-2][i]=='.'){
	ends.push_back(make_pair(rrows-1,i));}
	for(int i=1;i<rrows-1;i++)
		if(rstartROW!=i&&matrix[i][1]=='.'){
	ends.push_back(make_pair(i,0));}
	for(int i=1;i<rrows-1;i++)
		if(matrix[i][rcols-2]=='.'){
	ends.push_back(make_pair(i,rcols-1));}
	int n;
	cout<<"请输入终点数目（大于等于0且小于等于"<<ends.size()<<"）"<<endl;
	cin>>n;
	while(n<0||n>ends.size()){
		cout<<"终点数不符合要求，请重新输入"<<endl;
        cout<<"请输入终点数目（大于等于0且小于等于"<<ends.size()<<"）"<<endl;
        cin>>n;
	}
	//开启终点
	srand((unsigned long)time(0));
	for(int i=0;i<n;i++){
		int a,r,c;
		a=rand()%ends.size();
		r=ends[a].first;
		c=ends[a].second;
		ends[a]=ends.back();
		ends.pop_back();
		matrix[r][c]='.';
	}

}

//显示迷宫函数
void showMatrix(char** matrix, int rrows, int rcols){
	cout<<"当前迷宫"<<endl;
	for(int i=0;i<rrows;i++){
		for(int j=0;j<rcols;j++)
			cout<<matrix[i][j];
		cout<<endl;
	}
	cout<<endl;
}

//显示简化路径函数
void showPath(vector<pair<int,int>>& path, int& pathLength){
	cout<<"当前简化路径"<<endl;
	if(!path.empty()){
        int i;
        for(i=0;i<path.size()-1;i++)
        	cout<<"("<<path[i].first<<","<<path[i].second<<")"<<"-->";
        cout<<"("<<path[i].first<<","<<path[i].second<<")"<<endl;
	}
	cout<<"当前简化路径长度:"<<pathLength<<endl;
	cout<<endl;

}



};

int main(){

	system("mode 200,200");

	int rows;
	int cols;	
	int startROW;
	int startCOL;
	
	cout<<"这是王中凌的走迷宫程序"<<endl;
	cout<<"请先输入迷宫大小"<<endl;
	cout<<"请输入行数（大于等于1即可）"<<endl;
	cin>>rows;
	while(rows<1){
		cout<<"输入错误"<<endl;
		cout<<"请输入行数（大于等于1即可）"<<endl;
		cin>>rows;
	}
	cout<<"请输入列数（大于等于1即可）"<<endl;
	cin>>cols;
	while(cols<1){
		cout<<"输入错误"<<endl;
		cout<<"请输入列数（大于等于1即可）"<<endl;
		cin>>cols;
	}
	cout<<"再输入起始坐标"<<endl;
	cout<<"要求起始行列必须一个为零一个不为零，如果起始列不为零，则数小于等于列数；如果起始行不为零，则小于等于行数；"<<endl;
	cout<<"请输入起始行数"<<endl;
	cin>>startROW;
	while(startROW<0||startROW>rows){
		cout<<"输入错误"<<endl;
		cout<<"请输入起始行数"<<endl;
		cin>>startROW;
	}
	if(startROW==0){
		cout<<"请输入起始列数"<<endl;
		cin>>startCOL;
		while(startCOL<1||startCOL>cols){
			cout<<"输入错误"<<endl;
			cout<<"请输入起始列数"<<endl;
			cin>>startCOL;
		}
	}
	else{
		cout<<"起始列数肯定是零啦，我帮你写上咯"<<endl;
		startCOL=0;
	}
	

	Solution solution;
	solution.mazeGenerator(rows,cols,startROW,startCOL);
		

    system("pause");
	return 0;
}