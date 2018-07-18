#include "test1.h"
#include "ui_test1.h"
#include <QApplication>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

void read(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }

    QTextStream in(&file);
    //while(in=="\n");
    //list[i++].append(in);
    QString myText = in.readAll();
    qDebug() << myText;
    file.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);
    QString filename = "C:/Users/asus/Desktop/out.txt";
    read(filename);
    test1 w;
    w.show();
    return a.exec();
}
