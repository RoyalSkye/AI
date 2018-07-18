#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define  innode 4       //��������
#define  hidenode 2     //���������
#define  outnode 1      //��������
#define  trainsample 4  //BPѵ��������

class BpNet
{
public:
    void train(double p[trainsample][innode], double t[trainsample][outnode]);  //Bpѵ��
    double p[trainsample][innode];     //���������
    double t[trainsample][outnode];    //����Ҫ�����
    double *recognize(double *p);      //Bpʶ��
    BpNet();
public:
    void init();
    double w[innode][hidenode];     //�������Ȩֵ
    double w1[hidenode][outnode];   //������Ȩֵ
    double b1[hidenode];            //������㷧ֵ
    double b2[outnode];             //�����㷧ֵ
    double rate_w;      //Ȩֵѧϰ�ʣ������-������)
    double rate_w1;     //Ȩֵѧϰ�� (������-�����)
    double rate_b1;     //�����㷧ֵѧϰ��
    double rate_b2;     //����㷧ֵѧϰ��
    double e;           //������
    double error;       //�����������
    double result[outnode];         //Bp���
};

BpNet::BpNet()
{
    error=1.0;
    e=0.0;
    rate_w = 0.01;   //Ȩֵѧϰ�ʣ������--������)
    rate_w1 = 0.01;  //Ȩֵѧϰ�� (������--�����)
    rate_b1 = 0.01;  //�����㷧ֵѧϰ��
    rate_b2 = 0.01;  //����㷧ֵѧϰ��
}

//����[low, high)֮��������
double randval(double low, double high)  
{   
    double val;   
    val = ((double)(rand() % RAND_MAX)/(double)RAND_MAX) * (high - low) + low;   
    //cout<<"val:"<<val<<endl;
    return(val);   
}

void winit(double w[], int n) //Ȩֵ��ʼ��
{
    for(int i=0; i<n; i++)
        w[i] = randval(-0.01, 0.01);
}

//��ʼ��
void BpNet::init()
{
    winit((double*)w, innode * hidenode);
    winit((double*)w1, hidenode * outnode);
    winit(b1, hidenode);
    winit(b2, outnode);
}

//ѵ��
void BpNet::train(double p[trainsample][innode], double t[trainsample][outnode])
{
    double pp[hidenode];    //��������У�����
    double qq[outnode];     //ϣ�����ֵ��ʵ�����ֵ��ƫ��
    double yd[outnode];     //ϣ�����ֵ
    double x[innode];       //��������
    double x1[hidenode];    //�������״ֵ̬
    double x2[outnode];     //������״ֵ̬
    double o1[hidenode];    //�����㼤��ֵ
    double o2[hidenode];    //����㼤��ֵ

    for(int t1=0; t1<trainsample; t1++)  //ѭ��ѵ��һ����Ʒ
    {
        int i, j, k;
        for(i=0; i<innode; i++)
            x[i] = p[t1][i];     //���������
        for(i=0; i<outnode; i++)
            yd[i] = t[t1][i];    //ϣ�����������

        //���򴫲�
        //����ÿ����Ʒ������������׼
        for(j=0; j<hidenode; j++)
        {
            o1[j] = 0.0;
            for(i=0; i< innode; i++)
                o1[j] += w[i][j] * x[i];                //���������Ԫ���뼤��ֵ
            x1[j] = 1.0 / (1.0 + exp(-o1[j] - b1[j]));  //���������Ԫ�����  1/(1+e^-x) x=��wij*xi  +  aj 
        }

        for(k=0; k<outnode; k++)
        {
            o2[k] = 0.0;
            for(int j=0; j<hidenode; j++)
                o2[k] += w1[j][k] * x1[j];              //��������Ԫ���뼤��ֵ
            x2[k] = 1.0 / (1.0 + exp(-o2[k] - b2[k]));  //��������Ԫ���
        }

        //���򴫲�
        for(k=0; k<outnode; k++)  //����������ÿ�������Ԫ����������������Ȩֵ
        {
            qq[k] = (yd[k] - x2[k]) * x2[k] * (1-x2[k]);    //ϣ�������ʵ�������ƫ��  
            for(j=0; j<hidenode; j++)
                w1[j][k] += rate_w1 * qq[k] * x1[j];        //����������������֮�������Ȩ
        }

        for(j=0; j<hidenode; j++) //����������ÿ�����ص�Ԫ����������������Ȩֵ
        {
            pp[j] = 0.0;
            for(k=0; k<outnode; k++)
                pp[j] += qq[k] * w1[j][k];
            pp[j] = pp[j] * x1[j] * (1 - x1[j]);    //�������У�����

            for(i=0; i<innode; i++)
                w[i][j] += rate_w * pp[j] * x[i];   //����������������֮�������Ȩ
        }

        for(k=0; k<outnode; k++)
        {
            e += (yd[k] - x2[k])*(yd[k] - x2[k]);  //����ȫ�����
        }
        for(k=0; k<outnode; k++)
            b2[k] += rate_b2 * qq[k]; //����������������֮�����ֵ
        for(j=0; j<hidenode; j++)
            b1[j] += rate_b1 * pp[j]; //����������������֮�����ֵ
        /*for(int c=0;c<innode;c++)
        	for(int c1=0;c1<hidenode;c1++)
        		cout<<"w["<<c<<"]["<<c1<<"]="<<w[c][c1]<<endl;
        for(int c=0;c<hidenode;c++)
        	for(int c1=0;c1<outnode;c1++)
        		cout<<"w1["<<c<<"]["<<c1<<"]="<<w1[c][c1]<<endl;*/
    }
}

//��������
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
        cout<<times<<":ȫ�����e="<<bp.error<<endl; 
    }
    system("pause"); 
    return 0;
}
