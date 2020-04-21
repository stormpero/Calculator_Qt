#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"

void Project_DM_Qt::ration()
{
    ui->Rational_res_num->setText("");
    ui->Rational_res_det->setText("");
    Drob a,b;

    a = ration_convert(ui->Rational_num1_num->text(), ui->Rational_num1_det->text());
    b = ration_convert(ui->Rational_num2_num->text(), ui->Rational_num2_det->text());

    if (text_error_integer(a.numerator)||text_error_integer(b.numerator))
    {
        ui->Rational_res_num->setText("Error");
        ui->Rational_res_det->setText(" =) ");
        return;
    }
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
    else if (ui->Rational_choose->currentText() == "÷")
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
        number.numerator.push_back(0);
        number.numerator.push_back(0);
        number.denominator.push_back(1);
    }
    else
    {
        number.numerator = integ_convert(a);
        number.denominator = natural_convert(b);
    }
    return number;
}
