#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QDebug>


void Project_DM_Qt::integ()
{
    ui->Integer_res->setText("");
    QString number1 = ui->Integer_num1->toPlainText();
    QString number2 = ui->Integer_num2->toPlainText();
    vector <int> a = integ_check_convert(number1);
    vector <int> b = integ_check_convert(number2);
    vector <int> res;

    QString result;
    if (ui->Integer_choose->currentText() == "+")
        res = a;
    else if (ui->Integer_choose->currentText() == "-")
        res = a;
    else if (ui->Integer_choose->currentText() == "*")
        res = a;
    else if (ui->Integer_choose->currentText() == "/")
        res = a;

    if (res[0] == 1)
        ui->Integer_res->setText("-");
    for (int i = 1; i < res.size(); i++)
      ui->Integer_res->setText(ui->Integer_res->toPlainText() + QString::number(res[i]));
}
vector <int> Project_DM_Qt::integ_check_convert(QString a)
{

    string s = a.toStdString();
    qDebug() << a;
    vector <int> test(s.length());
    for (int i = 1; i < test.size(); i++)
        test[i] = s[i] - '0';
    if (s[0] == '-') test[0] = 1;
    else { test[0] = s[0] - '0';  test.insert(test.begin(), 0); }
    return test;
}

//    foreach(QChar s,a)
//    {
//         if (s.isLetter())
//         {
//            ui->Integer_Error->setText("Ошибка: Буквы недопустимы");
//            return test;
//         }
//         else if (s.isSpace())
//         {
//            ui->Integer_Error->setText("Ошибка: Пробелы недопустимы");
//            return test;
//         }
//         else if (s.isPunct())
//         {
//            ui->Integer_Error->setText("Ошибка: Знаки недопустимы");
//            return test;
//         }
//    }


