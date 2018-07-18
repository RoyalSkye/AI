/*���������� A*+�����پ���+����չ��+����Ȩ���� ʹ�������پ�����Ϊ���ۺ���h��ֵ��ʹ�ÿ���չ����ֵ��Ϊ��ϣ���ص����� */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue> 
#include <set>
#include <string>
#include <ctime>
#include <fstream>
#include <stdlib.h>
using namespace std;
const int maxn=9;
const int maxn1=400000;
int hash1[maxn]={1,1,2,6,24,120,720,5040,40320};  //0!-8!
int dir[4][2] = { { -1,0 },{ 1,0 },{ 0,-1 },{ 0,1 } };  //direction:u d l r
int visited[maxn1];  //1--O���� 2--C���� 0--����O��C���� 
int times=0;  //�ƶ����� 
string direction="udlr";  //ע���������е��±꣺(2,2)->(1,2)
char path[100];

struct node{
	int map[maxn];  //��ǰ״̬ 
	int f,g,h;  //f=g+h
	int x,y;  //�ո��λ�� 
	int prehash;  //���ڼ�¼ǰһ���
	char nodepath;  //���ڼ�¼·��
	int hash;  //hash�������� 
	bool operator < (const node &n) const{  //ʹ�õ���ԽС����������ȨԼ�͵�����Ȩ����  
		return f!=n.f?f>n.f:h>n.h; //f��ȵ�����±Ƚ�h 
	}
};
node start;  //��ʼ���(״̬) 
node end1;  //Ŀ����(״̬) 
//priority_queue<node> pq; 
queue<node> pq1;  //Ϊ�˴�ӡ·������printpath 

int gethash(node n){  //���ݿ���չ����hash 
	int result=0;
	for(int i=0;i<maxn;i++){
		int count=0;
		for(int j=0;j<i;j++){
			if(n.map[i]<n.map[j]) count++;
		}
		result+=hash1[i]*count; 
	}
	return result;
}

int geth(node n){  //���������پ��� 
	int result=0;
	for(int i=0;i<maxn;i++){
		if(n.map[i]==0) continue;
		int pos=0;
		for(int j=0;j<maxn;j++){
			if(end1.map[j]==n.map[i]){
				pos=j;
				break;
			}
		}
		int x1=i/3;
		int y1=i%3;
		int x2=pos/3;
		int y2=pos%3;
		result+=abs(x1-x2)+abs(y1-y2);
		//cout<<"result:"<<result<<endl;
	}
	return result;
}

void print(node n){  //��ӡ���� 
	cout<<"times:"<<times<<endl;
	for(int i=0;i<maxn;i++){
		cout<<n.map[i]<<" ";
		if(i%3==2) cout<<endl;
	}
}

node queueget1(queue<node> &pq,int targethash){  //�����������ض�hash�Ľ�� 
	node target;
	queue<node> temp; 
	while(!pq.empty()){
		node m=pq.front();
		if(m.hash==targethash){
			target=m;
			pq.pop();
			break;
		}
		pq.pop();
		temp.push(m);
	}
	while(!temp.empty()){
		node m=temp.front();
		temp.pop();
		pq.push(m);
	}
	return target;
}

node queueget(priority_queue<node> &pq,int targethash){  //��������Ȩ�������ض�hash�Ľ�� 
	node target;
	//priority_queue<node> temp;
	queue<node> temp; 
	while(!pq.empty()){
		node m=pq.top();
		if(m.hash==targethash){
			target=m;
			pq.pop();
			break;
		}
		pq.pop();
		temp.push(m);
	}
	while(!temp.empty()){
		//node m=temp.top();
		node m=temp.front();
		temp.pop();
		pq.push(m);
	}
	return target;
}

void printpath(int targethash){  //��ӡ��ѽ�·�� 
	if(targethash==-1) return;
	node target=queueget1(pq1,targethash);
	targethash=target.prehash;
	//cout<<"targethash:"<<targethash<<endl;
	printpath(targethash);
	if(targethash!=-1) path[times-1]=target.nodepath;
	/*cout<<"target.nodepath:"<<target.nodepath<<endl; 
	cout<<"targethash:"<<targethash<<endl;
	cout<<"times:"<<times<<endl;*/
	print(target);
	times++;
}

void Astar(){  //A*
	priority_queue<node> open;
	//priority_queue<node> closed;
	queue<node> closed;
	open.push(start);
	pq1.push(start);
	while(!open.empty()){
		node temp=open.top();
		open.pop();
		if(temp.hash==end1.hash){ //���ҵ�Ŀ��״̬
			end1.nodepath=temp.nodepath;
			end1.prehash=temp.prehash;
			return;
		}    
		closed.push(temp);  //�ý������չ��ϣ����뵽closed���� 
		visited[temp.hash]=2;  //����ý����closed���� 
		for(int i=0;i<4;i++){
			node tempnext=temp;
			int tempx=tempnext.x;
			int tempy=tempnext.y;
			tempnext.x+=dir[i][0];
			tempnext.y+=dir[i][1];
			if(tempnext.x<0||tempnext.x>2||tempnext.y<0||tempnext.y>2) continue;  //out of range
			swap(tempnext.map[tempx*3+tempy],tempnext.map[tempnext.x*3+tempnext.y]);
			tempnext.h=geth(tempnext);
			tempnext.nodepath=direction[i];
			tempnext.g=temp.g+1;
			tempnext.f=tempnext.g+tempnext.h;
			tempnext.hash=gethash(tempnext);
			tempnext.prehash=temp.hash;
			if(visited[tempnext.hash]==1){  //hash���� ����O���� 
				node target=queueget(open,tempnext.hash);
				//queueget(pq1,tempnext.hash);
				queueget1(pq1,tempnext.hash);
				if(((tempnext.f=target.f)&&(tempnext.h<target.h))||tempnext.f<target.f){  //f(temp,tempnext)<f(tempnext) 
					open.push(tempnext);
					pq1.push(tempnext);
				}else{
					open.push(target);
					pq1.push(target); 
				}
				continue;  
			} 
			if(visited[tempnext.hash]==2){  //hash���� ����C���� 
				node target=queueget1(closed,tempnext.hash);
				//queueget(pq1,tempnext.hash);
				queueget1(pq1,tempnext.hash);
				if(((tempnext.f=target.f)&&(tempnext.h<target.h))||tempnext.f<target.f){  //f(temp,tempnext)<f(tempnext)
					open.push(tempnext);
					pq1.push(tempnext);
					visited[tempnext.hash]=1;
				}else{
					closed.push(target);
					pq1.push(target);
				}
				continue;  
			}
			visited[tempnext.hash]=1;  //�ý��Ϊ����չ�Ľ�㣬������O��C�� 
			pq1.push(tempnext);
			open.push(tempnext);  //���뵽O���� 
		}
	}
}

bool judge(){ //�ж�����İ������������޽⣬��������������ż���Ƿ���ͬ�ж�
	int reverse1=0,reverse2=0;
	for(int i=0;i<maxn;i++){
		int j=i-1;
		if(start.map[i]==0) continue;
		while(j>=0){
			if(start.map[j]>start.map[i]) reverse1++;
			j--;
		}
	}
	for(int i=0;i<maxn;i++){
		int j=i-1;
		if(end1.map[i]==0) continue;
		while(j>=0){
			if(end1.map[j]>end1.map[i]) reverse2++;
			j--;
		}
	}
	//cout<<"reverse1="<<reverse1<<endl;
	//cout<<"reverse2="<<reverse2<<endl;
	if((reverse1%2)==(reverse2%2)) return true;
	else return false;		
}

bool correct(){  //�ж��������ȷ��(0-8)  
	int temp1[maxn+1],temp2[maxn+1];
	memset(temp1,0,sizeof(temp1));
	memset(temp2,0,sizeof(temp2));
	for(int i=0;i<maxn;i++){  //correct: temp1[1-9]=1
		if(start.map[i]<0||start.map[i]>=maxn||end1.map[i]<0||end1.map[i]>=maxn) return false;  
		temp1[start.map[i]+1]=1;
		temp2[end1.map[i]+1]=1;
	}
	for(int i=1;i<=maxn;i++){
		if(temp1[i]!=1||temp2[i]!=1) return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	clock_t begin,finish;
	memset(start.map,0,sizeof(start.map));
	memset(end1.map,0,sizeof(end1.map));
	memset(visited,0,sizeof(visited));
	cout<<"�������ʼ״̬(0-8,0��ʾ�ո�):"<<endl;
	for(int i=0;i<maxn;i++){
			cin>>start.map[i];
	}
	cin.sync(); //������뻺����
	cout<<"������Ŀ��״̬(0-8,0��ʾ�ո�):"<<endl; 
	for(int i=0;i<maxn;i++){
			cin>>end1.map[i];
	}
	cin.sync();
	if(correct()&&judge()){   
		cout<<"��ʼ״̬Ϊ��"<<endl;
		for(int i=0;i<maxn;i++){
			cout<<start.map[i]<<" ";
			if(i%3==2) cout<<endl;
			if(start.map[i]==0){
				start.x=i/3;
				start.y=i%3;
			}
		}
		cout<<"Ŀ��״̬Ϊ��"<<endl;
		for(int i=0;i<maxn;i++){
			cout<<start.map[i]<<" ";
			if(i%3==2) cout<<endl;
		}
		//print(end1);
		cout<<"--------------------------------"<<endl;
		cout<<"���Ž�·��:"<<endl;
		start.h=geth(start);
		start.g=0;
		start.f=start.g+start.h;
		start.hash=gethash(start);
		start.prehash=-1;
		end1.hash=gethash(end1);
		visited[start.hash]=1;
		begin=clock();
		Astar();
		finish=clock();
		printpath(end1.prehash);
		path[times-1]=end1.nodepath;
		print(end1);
		cout<<"�ƶ�����times:"<<times<<endl;
		cout<<"�ƶ�·��path:"<<path<<endl;
		ofstream in;
    	in.open("C:/Users/asus/Desktop/out.txt",ios::trunc); //ios::trunc��ʾ�ڴ��ļ�ǰ���ļ����,������д��,�ļ��������򴴽� 
		for(int i=0;i<maxn;i++) in<<start.map[i];
        in << "\n";
		for(int i=0;i<maxn;i++) in<<end1.map[i];
		in << "\n";
        in << path;  
        in.close();    
	}else{
		cout<<"input error!(���벻���Ϲ淶�������޽�)"<<endl;
	}
	cout << (finish-begin)/(double)CLOCKS_PER_SEC  << "s"<< endl;
	cout << (finish-begin)<< "ms"<< endl;	
	system("pause"); 
	return 0;
}
