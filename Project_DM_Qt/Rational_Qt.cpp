#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"


void Project_DM_Qt::ration()
{
    ui->Integer_res->setText("");
    Drob a,b;

    a.numerator = integ_convert(ui->Integer_num1->text());
    b.numerator = integ_convert(ui->Integer_num2->text());

    vector <int> res(a.numerator);

//    if (ui->Integer_choose->currentText() == "+")
//        res = ADD_ZZ_Z(a,b);
//    else if (ui->Integer_choose->currentText() == "-")
//        res = SUB_ZZ_Z(a,b);
//    else if (ui->Integer_choose->currentText() == "*")
//        res = MUL_ZZ_Z(a,b);
//    else if (ui->Integer_choose->currentText() == "/")
//        res = DIV_ZZ_Z(a,b);

    // Проверка знака
    if (res[0] == 1)
        ui->Integer_res->setText("-");

    // Вывод
    for (int i = 1; i < res.size(); i++)
        ui->Integer_res->setText(ui->Integer_res->text() + QString::number(res[i]));
}

