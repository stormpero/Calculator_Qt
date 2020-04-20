#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"


void Project_DM_Qt::ration()
{
    ui->Rational_res_num->setText("");
    ui->Rational_res_det->setText("");
    Drob a,b;

    a = ration_convert(ui->Rational_num1_num->text(), ui->Rational_num1_det->text());
    b = ration_convert(ui->Rational_num2_num->text(), ui->Rational_num2_det->text());

    Drob res;

    if (ui->Rational_choose->currentText() == "+")
        res = ADD_QQ_Q(a,b);
    else if (ui->Rational_choose->currentText() == "-")
        res = SUB_QQ_Q(a,b);
    else if (ui->Rational_choose->currentText() == "*")
    {
        if((check_zero(a.numerator))||(check_zero(b.numerator)))
        {
          res.numerator.push_back(0);
          res.numerator.push_back(0);
          res.denominator.push_back(0);
        }
        else
            res = MUL_QQ_Q(a,b);
    }
    else if (ui->Rational_choose->currentText() == "/")
        res = DIV_QQ_Q(a,b);

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
    if(a.length() == 1 && a[0] == "0")
    {
        number.numerator.resize(2);
        number.denominator.push_back(1);
        return number;
    }
    else
        number.numerator.resize(a.length());
    number.numerator = integ_convert(a);
    number.denominator.resize(b.length());
    number.denominator = natural_convert(b);
}

