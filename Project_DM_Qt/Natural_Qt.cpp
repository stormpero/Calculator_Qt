#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"



void Project_DM_Qt::natural()
{
    ui->natural_res->setText("");
    vector <int> a = natural_convert(ui->natural_num1->text());
    vector <int> b = natural_convert(ui->natural_num2->text());

    vector <int> res;

    if (ui->natural_choose->currentText() == "+")
        res = ADD_NN_N(a,b);
    else if (ui->natural_choose->currentText() == "-")
        res = SUB_NN_N(a,b);
    else if (ui->natural_choose->currentText() == "*")
    {
        if ((check_zero(a))||(check_zero(b)))
            res.push_back(0);
        else
            res = MUL_NN_N(a,b);
    }
    else if (ui->natural_choose->currentText() == "div")
    {
        if (check_zero(b))
        {
            ui->natural_res->setText("Error");
            return;
        }
        res = DIV_NN_N(a,b);
    }
    else if (ui->natural_choose->currentText() == "mod")
    {
        if (check_zero(b))
        {
            ui->natural_res->setText("Error");
            return;
        }
        if(check_zero(a))
        {
            ui->natural_res->setText("0");
            return;
        }
        if (COM_NN_D(a,b)==1)
            res = a;
        else
            res = MOD_NN_N(a,b);
    }



    // Вывод
    for (unsigned int i = 0; i < res.size(); i++)
        ui->natural_res->setText(ui->natural_res->text() + QString::number(res[i]));
}
vector <int> Project_DM_Qt::natural_convert(QString a)
{
    vector <int> res;

    // Преобразование в строки в вектор
    for (int k(0); k < a.size(); ++k)
        res.push_back(a[k].digitValue());
     if (res.empty())
         res.push_back(0);

    return res;
}
