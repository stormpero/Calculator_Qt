#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"


vector <Drob> pl1; // Первый многочлен(Глобальный)
vector <Drob> pl2; // Второй многочлен(Глобальный)
int degreeold1 = -1; // Прошлая степень для 1 многочлена(исп, чтобы узнать нужно ли дополнять эл-ты в массив)
int degreeold2 = -1; // Прошлая степень для 2 многочлена(исп, чтобы узнать нужно ли дополнять эл-ты в массив)
void Project_DM_Qt::Create_poly()
{
    connect(ui->Poly_button_res,SIGNAL(clicked()),this,SLOT(poly_out()));
    connect(ui->Poly_addButton,SIGNAL(clicked()),this,SLOT(poly_add()));
    ui->Poly_num->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Poly_det->setValidator(new QRegExpValidator(QRegExp("^[1-9]\\d*"), this));
    ui->Poly_deg->setValidator(new QRegExpValidator(QRegExp("^([1-9]|0$)\\d{1,6}"), this));

    const QPalette poly_colour(qRgb(207, 191, 218));
    ui->Poly_scrollArea->setPalette(poly_colour);

    ui->Poly_num->setPlaceholderText("0");
    ui->Poly_det->setPlaceholderText("1");
    ui->Poly_deg->setPlaceholderText("0");    

}

void Project_DM_Qt::poly_add()
{
    vector<int>nul = {0,0}; //Нулевой вектор, для проверки числителя на пустоту, чтобы не выводить пустые степени
    vector<int>check_num = {0,1};
    vector<int>check_num_min = {1,1};
    vector<int>nul2 = {1}; //Нулевой вектор, для проверки числителя на пустоту, чтобы не выводить пустые степени
    Drob null{ vector<int> {0, 0}, vector<int> {1} };
    int degree = 0; //Степень

    Drob a = ration_convert(ui->Poly_num->text(), ui->Poly_det->text()); // Обработка дроби

    degree = ui->Poly_deg->text().toInt(); // Читает степень и переводит в Int

    if (ui->Poly_rad1->isChecked()) // Смотрим, что выбран первый многочлен
    {
        ui->Poly_res1->setText("");
        if (degree > degreeold1) // Если новая степень больше превыд. то добавляем в массив эл-ты
        {
            for(int i(0);i < degree+1; i++)
                pl1.push_back(null);
             degreeold1 = degree; // Сохраняем степень
        }

        pl1[degree] = RED_Q_Q(a); // Присваем дробь к многочлены на позицию степени(Степень - индекс)

        for (int i = pl1.size() - 1; i >= 1; i--)
       {
           if(pl1[i].numerator == nul)// Если Числитель равен нулевому вектору, то пропускаем число
               continue;

           if (pl1[i].numerator[0] == 1)
                ui->Poly_res1->setText(ui->Poly_res1->text() + " - "); // Если числитель отрицательный выводим -
            else
               if (i < degreeold1)
                ui->Poly_res1->setText(ui->Poly_res1->text() + " + "); // Если числитель положительный выводим +

            if (((pl1[i].numerator != check_num) && (pl1[i].numerator != check_num_min )) || (pl1[i].denominator != nul2))
              {
                for (int j = 1; j < pl1[i].numerator.size(); j++) // Вывод числителя дроби
                    ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].numerator[j]));

                if (pl1[i].denominator != nul2)
                {
                    ui->Poly_res1->setText(ui->Poly_res1->text() + "/"); // Вывод слеша

                    for (int j = 0; j < pl1[i].denominator.size(); j++) // Вывод знаменателя дроби
                        ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].denominator[j]));
                }
             }

            ui->Poly_res1->setText(ui->Poly_res1->text() + "x<sup>" + QString::number(i) + "</sup>"); // Вывод x и степени, степень - i
       }
       //Свободный член в самом конце выводим, уже вне цикла
       if(pl1[0].numerator != nul) // Выводим, если он не равен нулю
       {
           if (pl1[0].numerator[0] == 1)
               ui->Poly_res1->setText(ui->Poly_res1->text() + " - "); // Если числитель отрицательный выводим -
           else
           {
               if (degreeold1 != 0)
               ui->Poly_res1->setText(ui->Poly_res1->text() + " + "); // Если числитель положительный выводим +
           }
            if (((pl1[0].numerator != check_num) && (pl1[0].numerator != check_num_min )) || (pl1[0].denominator != nul2))
            {
                for (int i = 1; i < pl1[0].numerator.size(); i++) // Вывод числителя дроби
                    ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].numerator[i]));
                if (pl1[0].denominator != nul2)
                {
                    ui->Poly_res1->setText(ui->Poly_res1->text() + "/"); // Вывод слеша

                    for (int i = 0; i < pl1[0].denominator.size(); i++) // Вывод знаменателя дроби
                        ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].denominator[i]));
                }
            }
       }

    }
    //-----------------------------------------------------------------------------------------
    else if (ui->Poly_rad2->isChecked())// Смотрим, что выбран второй многочлен
    {
        ui->Poly_res2->setText("");
        if (degree > degreeold2) // Если новая степень больше превыд. то добавляем в массив эл-ты
        {
            for(int i(0);i < degree+1; i++)
                pl2.push_back(null);
             degreeold2 = degree; // Сохраняем степень
        }

        pl2[degree] = RED_Q_Q(a); // Присваем дробь к многочлены на позицию степени(Степень - индекс)

        for (int i = pl2.size() - 1; i >= 1; i--)
       {
           if(pl2[i].numerator == nul)// Если Числитель равен нулевому вектору, то пропускаем число
               continue;

           if (pl2[i].numerator[0] == 1)
                ui->Poly_res2->setText(ui->Poly_res2->text() + " - "); // Если числитель отрицательный выводим -
            else
               if (i < degreeold2)
                ui->Poly_res2->setText(ui->Poly_res2->text() + " + "); // Если числитель положительный выводим +

            if (((pl2[i].numerator != check_num) && (pl2[i].numerator != check_num_min )) || (pl2[i].denominator != nul2))
              {
                for (int j = 1; j < pl2[i].numerator.size(); j++) // Вывод числителя дроби
                    ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[i].numerator[j]));

                if (pl2[i].denominator != nul2)
                {
                    ui->Poly_res2->setText(ui->Poly_res2->text() + "/"); // Вывод слеша

                    for (int j = 0; j < pl2[i].denominator.size(); j++) // Вывод знаменателя дроби
                        ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[i].denominator[j]));
                }
             }

            ui->Poly_res2->setText(ui->Poly_res2->text() + "x<sup>" + QString::number(i) + "</sup>"); // Вывод x и степени, степень - i
       }
       //Свободный член в самом конце выводим, уже вне цикла
       if(pl2[0].numerator != nul) // Выводим, если он не равен нулю
       {
           if (pl2[0].numerator[0] == 1)
               ui->Poly_res2->setText(ui->Poly_res2->text() + " - "); // Если числитель отрицательный выводим -
           else
           {
               if (degreeold1 != 0)
               ui->Poly_res2->setText(ui->Poly_res2->text() + " + "); // Если числитель положительный выводим +
           }
            if (((pl2[0].numerator != check_num) && (pl2[0].numerator != check_num_min )) || (pl2[0].denominator != nul2))
            {
                for (int i = 1; i < pl2[0].numerator.size(); i++) // Вывод числителя дроби
                    ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[0].numerator[i]));
                if (pl2[0].denominator != nul2)
                {
                    ui->Poly_res2->setText(ui->Poly_res2->text() + "/"); // Вывод слеша

                    for (int i = 0; i < pl2[0].denominator.size(); i++) // Вывод знаменателя дроби
                        ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[0].denominator[i]));
                }
            }
       }

    }
}

void Project_DM_Qt::poly_out() // Функция обработки и операции с многочленами
{ 
    vector<int>nul = {0,0}; //Нулевой вектор, для проверки числителя на пустоту, чтобы не выводить пустые степени
    vector<int>check_num = {0,1};
    vector<int>check_num_min = {1,1};
    vector<int>nul2 = {1}; //Нулевой вектор, для проверки числителя на пустоту, чтобы не выводить пустые степени
    Drob null{ vector<int> {0, 0}, vector<int> {1} };
    if (pl1.empty())
        pl1.push_back(null);

    if (pl2.empty())
        pl2.push_back(null);

    vector <Drob> pl_res;

    if (ui->Pol_choose->currentText() == "+")
        pl_res = ADD_PP_P(pl1,pl2);
    else if (ui->Pol_choose->currentText() == "-")
        pl_res= SUB_PP_P(pl1,pl2);
    else if (ui->Pol_choose->currentText() == "*")
        pl_res = MUL_PP_P(pl1,pl2);
    else if (ui->Pol_choose->currentText() == "div")
        pl_res = DIV_PP_P(pl1,pl2);
    else if (ui->Pol_choose->currentText() == "mod")
        pl_res = MOD_PP_P(pl1,pl2);
    else if (ui->Pol_choose->currentText() == "НОД")
        pl_res = GCF_PP_P(pl1,pl2);



    ui->Poly_res3->setText("");

    for (int i = pl_res.size() - 1; i >= 1; i--)
   {
       if(pl_res[i].numerator == nul)// Если Числитель равен нулевому вектору, то пропускаем число
           continue;

       if (pl_res[i].numerator[0] == 1)
            ui->Poly_res3->setText(ui->Poly_res3->text() + " - "); // Если числитель отрицательный выводим -
        else
           if (i !=  pl_res.size() - 1)
            ui->Poly_res3->setText(ui->Poly_res3->text() + " + "); // Если числитель положительный выводим +

        if (((pl_res[i].numerator != check_num) && (pl_res[i].numerator != check_num_min )) || (pl_res[i].denominator != nul2))
          {
            for (int j = 1; j < pl_res[i].numerator.size(); j++) // Вывод числителя дроби
                ui->Poly_res3->setText(ui->Poly_res3->text() + QString::number(pl_res[i].numerator[j]));

            if (pl_res[i].denominator != nul2)
            {
                ui->Poly_res3->setText(ui->Poly_res3->text() + "/"); // Вывод слеша

                for (int j = 0; j < pl_res[i].denominator.size(); j++) // Вывод знаменателя дроби
                    ui->Poly_res3->setText(ui->Poly_res3->text() + QString::number(pl_res[i].denominator[j]));
            }
         }

        ui->Poly_res3->setText(ui->Poly_res3->text() + "x<sup>" + QString::number(i) + "</sup>"); // Вывод x и степени, степень - i
   }
   //Свободный член в самом конце выводим, уже вне цикла
   if(pl_res[0].numerator != nul) // Выводим, если он не равен нулю
   {
       if (pl_res[0].numerator[0] == 1)
           ui->Poly_res3->setText(ui->Poly_res3->text() + " - "); // Если числитель отрицательный выводим -
       else
       {
           if (degreeold1 != 0)
           ui->Poly_res3->setText(ui->Poly_res3->text() + " + "); // Если числитель положительный выводим +
       }
        if (((pl_res[0].numerator != check_num) && (pl_res[0].numerator != check_num_min )) || (pl_res[0].denominator != nul2))
        {
            for (int i = 1; i < pl_res[0].numerator.size(); i++) // Вывод числителя дроби
                ui->Poly_res3->setText(ui->Poly_res3->text() + QString::number(pl_res[0].numerator[i]));
            if (pl_res[0].denominator != nul2)
            {
                ui->Poly_res3->setText(ui->Poly_res3->text() + "/"); // Вывод слеша

                for (int i = 0; i < pl_res[0].denominator.size(); i++) // Вывод знаменателя дроби
                    ui->Poly_res3->setText(ui->Poly_res3->text() + QString::number(pl_res[0].denominator[i]));
            }
        }
   }
   if (ui->Poly_res3->text().isEmpty())
       ui->Poly_res3->setText(" 0 ");

}
//if (degree > degreeold1) // Если новая степень больше превыд. то добавляем в массив эл-ты
//{
//    pl1.resize(degree + 1);
//    for (int i(0); i < pl1.size(); i++)
//    {
//        pl1[i].numerator.resize(2); // В числитель два нуля
//        pl1[i].denominator.resize(1,1);// В знаменатель единица
//    }
//    degreeold1 = degree; // Сохраняем степень
//}


