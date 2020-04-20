#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"

void Project_DM_Qt::integ()
{
    ui->Integer_res->setText("");
    vector <int> a = integ_convert(ui->Integer_num1->text());
    vector <int> b = integ_convert(ui->Integer_num2->text());

    vector <int> res;

    if (ui->Integer_choose->currentText() == "+")
        res = ADD_ZZ_Z(a,b);
    else if (ui->Integer_choose->currentText() == "-")
        res = SUB_ZZ_Z(a,b);
    else if (ui->Integer_choose->currentText() == "*")
    {
        if ((check_zero(a))||(check_zero(b)))
        {
            res.push_back(0);
            res.push_back(0);
        }
        else
            res = MUL_ZZ_Z(a,b);
    }
    else if (ui->Integer_choose->currentText() == "div")
    {
        if (check_zero(b))
        {
            ui->Integer_res->setText("Error");
            return;
        }
        res = DIV_ZZ_Z(a,b);     
    }
    else if (ui->Integer_choose->currentText() == "mod")
    {
        if (check_zero(b))
        {
            ui->Integer_res->setText("Error");
            return;
        }

        res = MOD_ZZ_Z(a,b);        
    }
    // Проверка знака
    if (res[0] == 1)
        ui->Integer_res->setText("-");

    // Вывод
    for (int i = 1; i < res.size(); i++)
        ui->Integer_res->setText(ui->Integer_res->text() + QString::number(res[i]));
}
vector <int> Project_DM_Qt::integ_convert(QString a)
{
    vector <int> res;

    // Проверка знака
    if (a[0] == '-')
    {
        res.push_back(1);
        a.remove(0, 1);
    }
    else
        res.push_back(0);
    // Преобразование в строки в вектор
    for (int k(0); k < a.size(); ++k)
        res.push_back(a[k].digitValue());
    if (res.empty())

        res.push_back(0);
    return res;
}




