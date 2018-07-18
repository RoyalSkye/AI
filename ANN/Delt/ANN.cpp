#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std; 
const int N=4;  //Ȩ�ظ���
const int M=4;  //�������� 
const double rate=0.5;  //��ѧϰ�� 
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1};  //���� M=3 
double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0};  //���� M=4 target : -2
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0};  //���� M=5 target : 1
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0,1,1,1,1};  //���� M=6 target : 1 6
//double p1[M*N]={1,0,-1,0,-1,0,0,1,0,-1,1,-1,-1,-1,-1,0,0,1,-1,0,-1,-1,0,0};  //���� M=6 target : 1 -1
double target[M]={-2,5,-5,-2};  //Ŀ����� 
double result[M]={0,0,0,0};  //ʵ����� 
double e=0;  //������� e=Sqrt(��(tie-aie)2)
double w[N]={0,0,0,0};  //Ȩֵwi
int count=0;  //ѧϰ���� 

double cale(){  //����Ŀ��ֵ��ʵ������������ 
	double res=0;
	for(int i=0;i<M;i++){
		res+=(result[i]-target[i])*(result[i]-target[i]);
	}
	res=sqrt(res);
	return res;
}

void delt(){  //ʹ��Delt�㷨��������ѵ�� 
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
	cout<<"Ȩ������:" <<N<<endl; 
	cout<<"��������:" <<M<<endl;
	cout<<"ѧϰ��:"<<rate<<endl;
	int times;
	cout<<"������ѧϰ����:"<<endl; 
	cin>>times;
	e=cale();
	cout<<"��"<<count<<"��ѧϰ���e="<<e<<endl;
	while(count<times){
		count++;
		delt();
		e=cale();
		cout<<"��"<<count<<"��ѧϰ���e="<<e<<endl;
	}
	system("pause"); 
	return 0;
}
