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
        res = MUL_NN_N(a,b);
    else if (ui->natural_choose->currentText() == "div")
        res = DIV_NN_N(a,b);
    else if (ui->natural_choose->currentText() == "mod")
        res = MOD_NN_N(a,b);

//    //Убираем лишние нули
//    if (NZER_N_B(res)==1) // 1 - есди число не равно нулю
//        while(res[0]!=0)
//            res.erase(res.begin());
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

    return res;
}
