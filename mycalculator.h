#ifndef MYCALCULATOR_H
#define MYCALCULATOR_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyCalculator;
}
QT_END_NAMESPACE

class MyCalculator : public QMainWindow
{
    Q_OBJECT

public:
    MyCalculator(QWidget *parent = nullptr);
    ~MyCalculator();

public slots:

    void addition();
    void miultiplication();
    void soustraction();
    void division();
    void equal();
    void cleaning();
    void nbr_0();
    void nbr_1();
    void nbr_2();
    void nbr_3();
    void nbr_4();
    void nbr_5();
    void nbr_6();
    void nbr_7();
    void nbr_8();
    void nbr_9();

private:
    Ui::MyCalculator *ui;
    QString operation;
    QString opr;
    bool state=false;
};
#endif // MYCALCULATOR_H
