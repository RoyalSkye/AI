#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std; 
const int N=4;  //权重个数
const int M=4;  //样本个数 
const double rate=0.5;  //η学习率 
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1};  //输入 M=3 
double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0};  //输入 M=4 target : -2
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0};  //输入 M=5 target : 1
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0,1,1,1,1};  //输入 M=6 target : 1 6
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0,-1,-1,0,0};  //输入 M=6 target : 1 -1
double target[M]={-2,5,-5,-2};  //目标输出 
double result[M]={0,0,0,0};  //实际输出 
double e=0;  //网络误差 e=Sqrt(∑(tie-aie)2)
double w[N]={0,0,0,0};  //权值wi
int count=0;  //学习次数 

double cale(){  //计算目标值与实际网络输出误差 
	double res=0;
	for(int i=0;i<M;i++){
		res+=(result[i]-target[i])*(result[i]-target[i]);
	}
	res=sqrt(res);
	return res;
}

void delt(){  //使用Delt算法进行网络训练 
	double sum=0;
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			sum+=p1[4*i+j]*w[j];
		}
		result[i]=sum;
		//cout<<"result[i]:"<<sum<<endl;
		sum=0;
		for(int j=0;j<N;j++) w[j]+=rate*(target[i]-result[i])*p1[4*i+j];
		//for(int j=0;j<N;j++) cout<<"w["<<j<<"]:"<<w[j]<<endl;
	}
	for(int i=0;i<M;i++){
		for(int j=0;j<N;j++){
			sum+=p1[4*i+j]*w[j];
		}
		result[i]=sum;
		//cout<<"i:"<<i<<" "<<"result[i]:"<<sum<<endl;
		sum=0;
	}
}

int main(int argc, char *argv[]) {
	cout<<"权重数量:" <<N<<endl; 
	cout<<"样本数量:" <<M<<endl;
	cout<<"学习率:"<<rate<<endl;
	int times;
	cout<<"请输入学习次数:"<<endl; 
	cin>>times;
	e=cale();
	cout<<"第"<<count<<"次学习误差e="<<e<<endl;
	while(count<times){
		count++;
		delt();
		e=cale();
		cout<<"第"<<count<<"次学习误差e="<<e<<endl;
	}
	system("pause"); 
	return 0;
}
