#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define  innode 4       //输入结点数
#define  hidenode 2     //隐含结点数
#define  outnode 1      //输出结点数
#define  trainsample 4  //BP训练样本数

class BpNet
{
public:
    void train(double p[trainsample][innode], double t[trainsample][outnode]);  //Bp训练
    double p[trainsample][innode];     //输入的样本
    double t[trainsample][outnode];    //样本要输出的
    double *recognize(double *p);      //Bp识别
    BpNet();
public:
    void init();
    double w[innode][hidenode];     //隐含结点权值
    double w1[hidenode][outnode];   //输出结点权值
    double b1[hidenode];            //隐含结点阀值
    double b2[outnode];             //输出结点阀值
    double rate_w;      //权值学习率（输入层-隐含层)
    double rate_w1;     //权值学习率 (隐含层-输出层)
    double rate_b1;     //隐含层阀值学习率
    double rate_b2;     //输出层阀值学习率
    double e;           //误差计算
    double error;       //允许的最大误差
    double result[outnode];         //Bp输出
};

BpNet::BpNet()
{
    error=1.0;
    e=0.0;
    rate_w = 0.01;   //权值学习率（输入层--隐含层)
    rate_w1 = 0.01;  //权值学习率 (隐含层--输出层)
    rate_b1 = 0.01;  //隐含层阀值学习率
    rate_b2 = 0.01;  //输出层阀值学习率
}

//产生[low, high)之间的随机数
double randval(double low, double high)  
{   
    double val;   
    val = ((double)(rand() % RAND_MAX)/(double)RAND_MAX) * (high - low) + low;   
    //cout<<"val:"<<val<<endl;
    return(val);   
}

void winit(double w[], int n) //权值初始化
{
    for(int i=0; i<n; i++)
        w[i] = randval(-0.01, 0.01);
}

//初始化
void BpNet::init()
{
    winit((double*)w, innode * hidenode);
    winit((double*)w1, hidenode * outnode);
    winit(b1, hidenode);
    winit(b2, outnode);
}

//训练
void BpNet::train(double p[trainsample][innode], double t[trainsample][outnode])
{
    double pp[hidenode];    //隐含结点的校正误差
    double qq[outnode];     //希望输出值与实际输出值的偏差
    double yd[outnode];     //希望输出值
    double x[innode];       //输入向量
    double x1[hidenode];    //隐含结点状态值
    double x2[outnode];     //输出结点状态值
    double o1[hidenode];    //隐含层激活值
    double o2[hidenode];    //输出层激活值

    for(int t1=0; t1<trainsample; t1++)  //循环训练一次样品
    {
        int i, j, k;
        for(i=0; i<innode; i++)
            x[i] = p[t1][i];     //输入的样本
        for(i=0; i<outnode; i++)
            yd[i] = t[t1][i];    //希望输出的样本

        //正向传播
        //构造每个样品的输入和输出标准
        for(j=0; j<hidenode; j++)
        {
            o1[j] = 0.0;
            for(i=0; i< innode; i++)
                o1[j] += w[i][j] * x[i];                //隐含层各单元输入激活值
            x1[j] = 1.0 / (1.0 + exp(-o1[j] - b1[j]));  //隐含层各单元的输出  1/(1+e^-x) x=∑wij*xi  +  aj 
        }

        for(k=0; k<outnode; k++)
        {
            o2[k] = 0.0;
            for(int j=0; j<hidenode; j++)
                o2[k] += w1[j][k] * x1[j];              //输出层各单元输入激活值
            x2[k] = 1.0 / (1.0 + exp(-o2[k] - b2[k]));  //输出层各单元输出
        }

        //误差反向传播
        for(k=0; k<outnode; k++)  //对于网络中每个输出单元，计算误差项，并更新权值
        {
            qq[k] = (yd[k] - x2[k]) * x2[k] * (1-x2[k]);    //希望输出与实际输出的偏差  
            for(j=0; j<hidenode; j++)
                w1[j][k] += rate_w1 * qq[k] * x1[j];        //更新隐含层和输出层之间的连接权
        }

        for(j=0; j<hidenode; j++) //对于网络中每个隐藏单元，计算误差项，并更新权值
        {
            pp[j] = 0.0;
            for(k=0; k<outnode; k++)
                pp[j] += qq[k] * w1[j][k];
            pp[j] = pp[j] * x1[j] * (1 - x1[j]);    //隐含层的校正误差

            for(i=0; i<innode; i++)
                w[i][j] += rate_w * pp[j] * x[i];   //更新输入层和隐含层之间的连接权
        }

        for(k=0; k<outnode; k++)
        {
            e += (yd[k] - x2[k])*(yd[k] - x2[k]);  //计算全局误差
        }
        for(k=0; k<outnode; k++)
            b2[k] += rate_b2 * qq[k]; //更新隐含层和输出层之间的阈值
        for(j=0; j<hidenode; j++)
            b1[j] += rate_b1 * pp[j]; //更新输入层和隐含层之间的阈值
        /*for(int c=0;c<innode;c++)
        	for(int c1=0;c1<hidenode;c1++)
        		cout<<"w["<<c<<"]["<<c1<<"]="<<w[c][c1]<<endl;
        for(int c=0;c<hidenode;c++)
        	for(int c1=0;c1<outnode;c1++)
        		cout<<"w1["<<c<<"]["<<c1<<"]="<<w1[c][c1]<<endl;*/
    }
}

//输入样本
double X[trainsample][innode] = 
{
    {1,0,-1,0},
    {-1,0,0,1},
    {0,-1,1,-1},
    {-1,-1,-1,0}
};
double Y[trainsample][outnode]={
	-2,5,-5,-2
};

int main()
{
    srand(time(NULL));
    int i, j, k;
    BpNet bp;
    bp.init();
    int times = 0;

    while(bp.error > 0.0001 && times < 1000)
    {
        bp.e = 0.0;
        times++;
        bp.train(X, Y);
        bp.error=bp.e/(2*trainsample);
        cout<<times<<":全局误差e="<<bp.error<<endl; 
    }
    system("pause"); 
    return 0;
}
