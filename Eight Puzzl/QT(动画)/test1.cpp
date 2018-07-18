#include "test1.h"
#include "ui_test1.h"

#include <QPropertyAnimation>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <cstring>
#include "QLabel"
#include <QTime>
#include <QSequentialAnimationGroup>
#include <QTimer>

test1::test1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::test1)
{
    ui->setupUi(this);

    //read file
    QString filename = "C:/Users/asus/Desktop/out.txt";
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream in(&file);
    QString matrix = in.readLine();
    QString targetmatrix = in.readLine();
    QString path = in.readLine();
    file.close();
    qDebug() << matrix;
    qDebug() << targetmatrix;
    qDebug() << path;

    //put the matrix value to label
    int space=0;  //for preserving the relative position of 0
    QLabel *label[9];
    QLabel *targetlabel1[9];
    QLabel *targetlabel2[9];
    QString qstring;
    int temp;
    for(int i=0;i<9;i++){
        QString qstring=matrix.mid(i,1);
        if(qstring=="0") temp=i;
    }
    label[0]=ui->label0;
    label[1]=ui->label1;
    label[2]=ui->label2;
    label[3]=ui->label3;
    label[4]=ui->label4;
    label[5]=ui->label5;
    label[6]=ui->label6;
    label[7]=ui->label7;
    label[8]=ui->label8;
    label[temp]->setVisible (false); //标签不可视

    targetlabel1[0]=ui->label8_0;
    targetlabel1[1]=ui->label8_1;
    targetlabel1[2]=ui->label8_2;
    targetlabel1[3]=ui->label8_3;
    targetlabel1[4]=ui->label8_4;
    targetlabel1[5]=ui->label8_5;
    targetlabel1[6]=ui->label8_6;
    targetlabel1[7]=ui->label8_7;
    targetlabel1[8]=ui->label8_8;
    targetlabel2[0]=ui->label9_0;
    targetlabel2[1]=ui->label9_1;
    targetlabel2[2]=ui->label9_2;
    targetlabel2[3]=ui->label9_3;
    targetlabel2[4]=ui->label9_4;
    targetlabel2[5]=ui->label9_5;
    targetlabel2[6]=ui->label9_6;
    targetlabel2[7]=ui->label9_7;
    targetlabel2[8]=ui->label9_8;

    /*label[temp]=new QLabel(this);
    label[temp]->move(200+(temp%3)*100, 100+(temp/3)*100 );
    QPalette pa=label[1]->palette();
    pa.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    label[1]->setAutoFillBackground(true);
    label[1]->setPalette(pa);*/

    for(int i=0;i<9;i++){
        QString qstring=matrix.mid(i,1);
        QString qstring1=targetmatrix.mid(i,1);
        label[i]->setAlignment(Qt::AlignCenter);
        targetlabel1[i]->setAlignment(Qt::AlignCenter);
        targetlabel2[i]->setAlignment(Qt::AlignCenter);
        targetlabel1[i]->setText(qstring);
        targetlabel2[i]->setText(qstring1);
        if(qstring=="0"){
            label[i]->setText("");
            space=i;
            continue;
        }
        label[i]->setText(qstring);
    }
    ui->label->setAlignment(Qt::AlignCenter);

    //move the number according to the path
    int length=path.length();
    length1=length;
    QChar dir[length];
    memcpy(dir, path.data(), sizeof(QChar)*length);
    QPropertyAnimation* animation[length];
    int x,y,target;  //target for preserve the relative position of moving node
    int pre[9];  //record which label is located at the position i / the relative position between labels
    for(int i=0;i<9;i++) pre[i]=i;
    int count=0;  //for preserving the current animation
    for(int i=0;i<length;i++){
        if(dir[i]=='u'){  //moving node moves "d" : 0 1 2 3 4 5
            target=space-3;
            animation[count]=new QPropertyAnimation(label[pre[target]], "geometry");
            x=label[target]->x();
            y=label[target]->y();
            animation[count]->setDuration(1000);
            animation[count]->setStartValue(QRect(x, y, 100, 100));
            animation[count]->setEndValue(QRect(x, y+100, 100, 100));
            count++;
            int temp=pre[space];
            pre[space]=pre[target];
            pre[target]=temp;
            space=target;
            /*qDebug()<<pre[0]<<pre[1]<<pre[2];
            qDebug()<<pre[3]<<pre[4]<<pre[5];
            qDebug()<<pre[6]<<pre[7]<<pre[8];*/
        }
        if(dir[i]=='d'){  //moving node moves "u" : 3 4 5 6 7 8
            target=space+3;
            animation[count]=new QPropertyAnimation(label[pre[target]], "geometry");
            x=label[target]->x();
            y=label[target]->y();
            animation[count]->setDuration(1000);
            animation[count]->setStartValue(QRect(x, y, 100, 100));
            animation[count]->setEndValue(QRect(x, y-100, 100, 100));
            count++;
            int temp=pre[space];
            pre[space]=pre[target];
            pre[target]=temp;
            space=target;
        }
        if(dir[i]=='l'){  //moving node moves "r" : 0 1 3 4 6 7
            target=space-1;
            animation[count]=new QPropertyAnimation(label[pre[target]], "geometry");
            x=label[target]->x();
            y=label[target]->y();
            animation[count]->setDuration(1000);
            animation[count]->setStartValue(QRect(x, y, 100, 100));
            animation[count]->setEndValue(QRect(x+100, y, 100, 100));
            count++;
            int temp=pre[space];
            pre[space]=pre[target];
            pre[target]=temp;
            space=target;
        }
        if(dir[i]=='r'){  //moving node moves "l" : 1 2 4 5 7 8
            target=space+1;
            animation[count]=new QPropertyAnimation(label[pre[target]], "geometry");
            x=label[target]->x();
            y=label[target]->y();
            animation[count]->setDuration(1000);
            animation[count]->setStartValue(QRect(x, y, 100, 100));
            animation[count]->setEndValue(QRect(x-100, y, 100, 100));
            count++;
            int temp=pre[space];
            pre[space]=pre[target];
            pre[target]=temp;
            space=target;
        }
    }

    //play animations in order
    QSequentialAnimationGroup *group=new QSequentialAnimationGroup;
    for(int i=0;i<length;i++){
        group->addAnimation(animation[i]);
    }

    for(int i=0;i<9;i++){
        QString tempmatrix=matrix.mid(i,1);
        if(tempmatrix=="0"){
            label[i]->setText("");
            space=i;
            continue;
        }
        label[i]->setText(tempmatrix);
    }
    group->start();

    updateTimer = new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updatetimes()));
    updateTimer->start(1000);  //以2000ms周期刷新当前移动次数
    return;
}

test1::~test1()
{
    delete ui;
}

void test1::updatetimes()
{
    times1++;
    if(times1>=length1) updateTimer->stop();
    QString times = QString::number(times1, 10);
    ui->label->setText("第"+times+"步");
}
