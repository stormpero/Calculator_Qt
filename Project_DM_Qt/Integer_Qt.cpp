#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"

void Project_DM_Qt::integ()
{
    ui->Integer_res->setText("");
    vector <int> a = integ_convert_int(ui->Integer_num1->text());
    vector <int> b = integ_convert_int(ui->Integer_num2->text());
    vector <int> res;

    //Ошибка, если введён только минус
    if ((a.size()==1 && a[0]==1)||(b.size()==1 && b[0]==1))
    {
        ui->Integer_res->setText("Error");
        QMessageBox::critical(this, "Almighty calculator", "Error, wrong input =) ");
        return;
    }

    if (ui->Integer_choose->currentText() == "+")
        res = ADD_ZZ_Z(a,b);
    else if (ui->Integer_choose->currentText() == "-")
        res = SUB_ZZ_Z(a,b);
    else if (ui->Integer_choose->currentText() == "*")
    {
        // Если один из множителей ноль, то выводим 0
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
        // Деление на ноль
        if (check_zero(b))
        {
            QMessageBox::critical(this, "Almighty calculator", "Деление на нуль!");
            return;
        }
        res = DIV_ZZ_Z(a,b);
        // Проверка если -0, испр на 0
        if (res.size()==2 && res[0]==1 && res[1]==0)
            res[0]=0;
    }
    else if (ui->Integer_choose->currentText() == "mod")
    {
        // Деление на ноль
        if (check_zero(b))
        {
            QMessageBox::critical(this, "Almighty calculator", "Деление на нуль!");
            return;
        }
        // Если второе число больше первого, то первое число это остаток
        if ((COM_NN_D(ABS_Z_N(a),ABS_Z_N(b))==1 && POZ_Z_D(a)==1 && POZ_Z_D(b)==1)||(check_zero(a)))
            res = a;
        else
            res = MOD_ZZ_Z(a,b);
    }

    // Проверка знака
    if (res[0] == 1)
        ui->Integer_res->setText("-");

    // Вывод
    for (unsigned int i = 1; i < res.size(); i++)
        ui->Integer_res->setText(ui->Integer_res->text() + QString::number(res[i]));
}
vector <int> Project_DM_Qt::integ_convert(QString a)
{
    vector <int> res;

    if ((a.isEmpty()) || (a[0]== '-' && a.size() == 1))
    {
        res.push_back(0);
        res.push_back(0);
        return res;
    }

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


    return res;
}
vector <int> Project_DM_Qt::integ_convert_int(QString a)
{
    vector <int> res;

    if (a.isEmpty())
    {
        res.push_back(0);
        res.push_back(0);
        return res;
    }

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

    return res;
}



