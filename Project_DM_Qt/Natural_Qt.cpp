#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"



void Project_DM_Qt::natural()
{
    ui->natural_res->setText("");
    vector <int> a = natural_convert(ui->natural_num1->text());
    vector <int> b = natural_convert(ui->natural_num2->text());

    vector <int> res(a);

    if (ui->Integer_choose->currentText() == "+")
        res = ADD_NN_N(a,b);
//    else if (ui->Integer_choose->currentText() == "-")
//        res = SUB_NN_N(a,b);
//    else if (ui->Integer_choose->currentText() == "*")
//        res = MUL_NN_N(a,b);
//    else if (ui->Integer_choose->currentText() == "div")
//        res = DIV_NN_N(a,b);
//    else if (ui->Integer_choose->currentText() == "mod")
//        res = MOD_NN_N(a,b);
    // Вывод
    for (unsigned int i = 1; i < res.size(); i++)
        ui->natural_res->setText(ui->natural_res->text() + QString::number(res[i]));
}
vector <int> Project_DM_Qt::natural_convert(QString a)
{
    vector <int> res;
    // Преобразование в строки в вектор
    for (int k(0); k < a.size(); ++k)
        res.push_back(a[k].digitValue());

    return res;
}
