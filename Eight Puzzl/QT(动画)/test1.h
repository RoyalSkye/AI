#ifndef TEST1_H
#define TEST1_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class test1;
}

class test1 : public QMainWindow
{
    Q_OBJECT

public:
    int times1=0;
    int length1;
    QTimer *updateTimer;
    explicit test1(QWidget *parent = 0);
    ~test1();
private slots:
    void updatetimes();
private:
    Ui::test1 *ui;
};

#endif // TEST1_H
