#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QDebug>
void Project_DM_Qt::ration()
{
    ui->Rational_res_num->setText("");
    ui->Rational_res_det->setText("");
    Drob a,b;

    a = ration_convert(ui->Rational_num1_num->text(), ui->Rational_num1_det->text());
    b = ration_convert(ui->Rational_num2_num->text(), ui->Rational_num2_det->text());

    Drob res;
    //Ошибка, если введён только минус
    if (a.numerator.size()==1 && a.numerator[0]==1)
    {
        QMessageBox::critical(this, "Almighty calculator", "Error, wrong input");
        return;
    }
    if (ui->Rational_choose->currentText() == "+")
        res = ADD_QQ_Q(a,b);
    else if (ui->Rational_choose->currentText() == "-")
        res = SUB_QQ_Q(a,b);
    else if (ui->Rational_choose->currentText() == "*")
    {
        // Если один из множителей ноль, то выводим 0
        if((check_zero(a.numerator))||(check_zero(b.numerator)))
        {
          res.numerator.push_back(0);
          res.numerator.push_back(0);
          res.denominator.push_back(1);
        }
        else
            res = MUL_QQ_Q(a,b);
    }
    else if (ui->Rational_choose->currentText() == "÷")
    {
        // Проверка на ноль
        if (POZ_Z_D(b.numerator)==0)
        {
            QMessageBox::critical(this, "Almighty calculator", "Error, wrong input");
            return;
        }
        res = DIV_QQ_Q(a,b);
    }

    // Проверка знака
    if (res.numerator[0] == 1)
        ui->Rational_res_num->setText("-");

    // Вывод
    for (int i = 1; i < res.numerator.size(); i++)
        ui->Rational_res_num->setText(ui->Rational_res_num->text() + QString::number(res.numerator[i]));
    for (int i = 0; i < res.denominator.size(); i++)
        ui->Rational_res_det->setText(ui->Rational_res_det->text() + QString::number(res.denominator[i]));
}

Drob Project_DM_Qt::ration_convert(QString a, QString b)
{
    Drob number;

    number.numerator = integ_convert(a);
    number.denominator = natural_convert(b);
    if (number.denominator.size()==1 && number.denominator[0]==0)
        number.denominator[0] = 1;
    return number;

//   qDebug() <<"Размер числителя: " <<number.numerator.size();
//   qDebug() <<"==========================";
//   qDebug() <<"Размер знаменателя: " << number.denominator.size();
//   qDebug() <<"==========================";
//    for (int k(0); k < number.numerator.size(); k++)
//        qDebug() << number.numerator[k];
//   qDebug() <<"==========================";
//    for (int k(0); k < number.denominator.size(); k++)
//        qDebug() << number.denominator[k]<< " ";
//    qDebug() <<"-----------STOP---------------";


}

