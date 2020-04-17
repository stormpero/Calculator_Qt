#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QRegExpValidator>
#include <QMouseEvent>
#include <QtWidgets>



void Project_DM_Qt::integ()
{
    QString number1 = ui->Integer_num1->toPlainText();
    QString number2 = ui->Integer_num2->toPlainText();
    vector <int> a = integ_check_convert(number1);
    vector <int> b = integ_check_convert(number2);
    if (ui->Integer_choose->currentText() == "+")
        number1 = "yes +";
    else if (ui->Integer_choose->currentText() == "-")
        number1 = "yes -";
    else if (ui->Integer_choose->currentText() == "*")
        number1 = "yes *";
    else if (ui->Integer_choose->currentText() == "/")
        number1 = "yes /";
}
vector <int> Project_DM_Qt::integ_check_convert(QString a)
{
    foreach(QChar s,a)
    {
         if (s.isLetter())
         {
            ui->Integer_Error->setText("Error");
         }
         else if (s.isSpace())
         {

         }
         else if (s.isPunct())
         {

         }
    }



//    vector <int> test(a.length());
//    int SizeTest= test.size();
//    for (int i = 1; i < SizeTest; i++)
//        test[i] = a.toInt();
//    if (a[0] == '-') test[0] = 1;
//    else { test[0] = a[0] - '0';  test.insert(test.begin(), 0); }

}
