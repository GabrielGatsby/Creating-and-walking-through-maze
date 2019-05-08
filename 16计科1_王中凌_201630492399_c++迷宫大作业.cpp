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

	//�ж��Թ��Ƿ��������
	if(rows<1||cols<1||startCOL<0||startROW<0) {
		cout<<"�Թ�������Ҫ��"<<endl;
		return false;
	}
	
	if(!(startCOL^startROW)){
		cout<<"�Թ�������Ҫ��"<<endl;
		return false;
	}


	//�����Թ������ڴ�
	char** matrix=new char*[rrows];
	for(int i=0;i<rrows;i++){
		matrix[i]=new char[rcols];
		memset(matrix[i], '#', rcols);
	}
	
	
	//�����Թ�����
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
    			bcol++;//������һ��
    		}
    		else if(matrix[brow][bcol-1]!='.'&&matrix[brow][bcol+1]=='.'){
    			matrix[brow][bcol]=matrix[brow][bcol-1]='.';
    			bcol--;//������һ��
    		}
    		else continue;
    	}
    	else if(brow%2==0){
    		if(matrix[brow-1][bcol]=='.'&&matrix[brow+1][bcol]!='.'){
    			matrix[brow][bcol]=matrix[brow+1][bcol]='.';
    			brow++;//������һ��
    		}
    		else if(matrix[brow-1][bcol]!='.'&&matrix[brow+1][bcol]=='.'){
    			matrix[brow][bcol]=matrix[brow-1][bcol]='.';
    			brow--;//������һ��
    		}
    		else continue;
    	}
		//����һ�������build��
    	if(brow>2)
    		build.push_back(make_pair(brow-1,bcol));
    	if(brow<(rrows-3))
    		build.push_back(make_pair(brow+1,bcol));
    	if(bcol>2)
    		build.push_back(make_pair(brow,bcol-1));
    	if(bcol<(rcols-3))
    		build.push_back(make_pair(brow,bcol+1));
    }


	//���ɳ���
	openEnd(matrix,rrows,rcols,rstartROW,rstartCOL);



	//��ʾ��ʼ�Թ�����
	cout<<"���ǳ�ʼ�����Թ�"<<endl;
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
	cout<<"�������Թ�����"<<endl;
	cout<<"û���յ��û�к��ʵ��յ㣬�ص����"<<endl;
	return false;

}

bool mazeTraverse(char** matrix,int rrows,int rcols, int row, int col, int rstartROW, 
	                int rstartCOL, int direct, vector<pair<int,int>>& path,int& pathLength){
	//��Χ
	if((row>=0)&&(row<rrows)&&(col>=0)&&(col<rcols)){
		//�ж��Ƿ��ҵ��յ�
        if(matrix[row][col]=='.'&&!((row==rstartROW)&&(col==rstartCOL))){
        	if(row==0||row==rrows-1||col==0||col==rcols-1){

				//����߹��ĵ�
				matrix[row][col]='X';
				//·�����ȼ�һ
				pathLength++;
				//�ѵ�ѹ��·��
        		path.push_back(make_pair(row,col));
				//�ȴ���������
				cin.get();
				//��ʾ�Թ�����
				showMatrix(matrix,rrows,rcols);
				//��ʾ��·��
				showPath(path,pathLength);
        		cout<<"�յ�("<<row<<","<<col<<")"<<endl;
				int p=-1;
        		cout<<"�Ƿ������һ���յ�:����0�����ң�����1���ң�"<<endl;
				cin>>p;
				while(!(p==0||p==1)){
					cout<<"�����������������"<<endl;
					cout<<"�Ƿ������һ���յ�:����0�����ң�����1���ң�"<<endl;
					cin>>p;
				}
				if(p==0){
					cout<<"�������Թ�����"<<endl;
					cout<<"�ɹ����յ��߳�"<<endl;
					return true;
				}
				if(p==1){
					//·�����ȼ�һ
					pathLength--;
					//���õ��·�����Ƴ�
					path.pop_back();
					//�ȴ���������
					cin.get();
					//��ʾ�Թ�����
					showMatrix(matrix,rrows,rcols);
					//��ʾ��·��
					showPath(path,pathLength);
					return false;
				}
			}
		}

		bool hasPath=false;
		if(matrix[row][col]=='.'){
			//����߹��ĵ�
		    matrix[row][col]='X';
			//·�����ȼ�һ
			pathLength++;
			//�ѵ�ѹ��·��
			path.push_back(make_pair(row,col));
			//�ȴ���������
			cin.get();
			//��ʾ�Թ�����
			showMatrix(matrix,rrows,rcols);
			//��ʾ��·��
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
				//·�����ȼ�һ
				pathLength--;
				//���õ��·���Ƴ�
				path.pop_back();
				//�ȴ���������
				cin.get();
				//��ʾ�Թ�����
				showMatrix(matrix,rrows,rcols);
				//��ʾ��·��
				showPath(path,pathLength);
			}
		}

		return hasPath;


	}
	else return false;

}

//���ɳ��ں���
void openEnd(char** matrix, int rrows, int rcols, int rstartROW,int rstartCOL){
	//��¼�������յ�ĵ�
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
	cout<<"�������յ���Ŀ�����ڵ���0��С�ڵ���"<<ends.size()<<"��"<<endl;
	cin>>n;
	while(n<0||n>ends.size()){
		cout<<"�յ���������Ҫ������������"<<endl;
        cout<<"�������յ���Ŀ�����ڵ���0��С�ڵ���"<<ends.size()<<"��"<<endl;
        cin>>n;
	}
	//�����յ�
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

//��ʾ�Թ�����
void showMatrix(char** matrix, int rrows, int rcols){
	cout<<"��ǰ�Թ�"<<endl;
	for(int i=0;i<rrows;i++){
		for(int j=0;j<rcols;j++)
			cout<<matrix[i][j];
		cout<<endl;
	}
	cout<<endl;
}

//��ʾ��·������
void showPath(vector<pair<int,int>>& path, int& pathLength){
	cout<<"��ǰ��·��"<<endl;
	if(!path.empty()){
        int i;
        for(i=0;i<path.size()-1;i++)
        	cout<<"("<<path[i].first<<","<<path[i].second<<")"<<"-->";
        cout<<"("<<path[i].first<<","<<path[i].second<<")"<<endl;
	}
	cout<<"��ǰ��·������:"<<pathLength<<endl;
	cout<<endl;

}



};

int main(){

	system("mode 200,200");

	int rows;
	int cols;	
	int startROW;
	int startCOL;
	
	cout<<"��������������Թ�����"<<endl;
	cout<<"���������Թ���С"<<endl;
	cout<<"���������������ڵ���1���ɣ�"<<endl;
	cin>>rows;
	while(rows<1){
		cout<<"�������"<<endl;
		cout<<"���������������ڵ���1���ɣ�"<<endl;
		cin>>rows;
	}
	cout<<"���������������ڵ���1���ɣ�"<<endl;
	cin>>cols;
	while(cols<1){
		cout<<"�������"<<endl;
		cout<<"���������������ڵ���1���ɣ�"<<endl;
		cin>>cols;
	}
	cout<<"��������ʼ����"<<endl;
	cout<<"Ҫ����ʼ���б���һ��Ϊ��һ����Ϊ�㣬�����ʼ�в�Ϊ�㣬����С�ڵ��������������ʼ�в�Ϊ�㣬��С�ڵ���������"<<endl;
	cout<<"��������ʼ����"<<endl;
	cin>>startROW;
	while(startROW<0||startROW>rows){
		cout<<"�������"<<endl;
		cout<<"��������ʼ����"<<endl;
		cin>>startROW;
	}
	if(startROW==0){
		cout<<"��������ʼ����"<<endl;
		cin>>startCOL;
		while(startCOL<1||startCOL>cols){
			cout<<"�������"<<endl;
			cout<<"��������ʼ����"<<endl;
			cin>>startCOL;
		}
	}
	else{
		cout<<"��ʼ�����϶����������Ұ���д�Ͽ�"<<endl;
		startCOL=0;
	}
	

	Solution solution;
	solution.mazeGenerator(rows,cols,startROW,startCOL);
		

    system("pause");
	return 0;
}