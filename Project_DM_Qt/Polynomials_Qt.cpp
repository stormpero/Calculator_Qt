#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QDebug>
#include <QPixmap>

void Project_DM_Qt::Create_poly()
{
    connect(ui->Poly_button_res,SIGNAL(clicked()),this,SLOT(poly_out()));
    connect(ui->Poly_addButton,SIGNAL(clicked()),this,SLOT(poly_add()));
    ui->Poly_num->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Poly_det->setValidator(new QRegExpValidator(QRegExp("^[1-9]\\d*"), this));
    ui->Poly_deg->setValidator(new QRegExpValidator(QRegExp("^([1-9]|0$)\\d{1,6}"), this));

    ui->Poly_num->setPlaceholderText("0");
    ui->Poly_det->setPlaceholderText("1");
    ui->Poly_deg->setPlaceholderText("0");

    //Poly_num
    //Poly_det
    //Poly_deg
    //Poly_res1
    //Poly_res2
}

void Project_DM_Qt::poly_add()
{

    static vector <Drob> pl1; // Первый многочлен(Статический, при выходе из этой функции останется)
    static vector <Drob> pl2; // Второй многочлен(Статический, при выходе из этой функции останется)

    vector<int>nul = {0,0}; //Нулевой вектор, для проверки числителя на пустоту, чтобы не выводить пустые степени
    int degree = 0; //Степень
    static int degreeold1 = -1; // Прошлая степень для 1 многочлена(исп, чтобы узнать нужно ли дополнять эл-ты в массив)
    static int degreeold2 = -1; // Прошлая степень для 2 многочлена(исп, чтобы узнать нужно ли дополнять эл-ты в массив)

    Drob a = ration_convert(ui->Poly_num->text(), ui->Poly_det->text()); // Обработка дроби


    degree = ui->Poly_deg->text().toInt(); // Читает степень и переводит в Int


    if (ui->Poly_rad1->isChecked()) // Смотрим, что выбран первый многочлен
    {
        ui->Poly_res1->setText("");
        if (degree > degreeold1) // Если новая степень больше превыд. то добавляем в массив эл-ты
        {
             pl1.resize(degree + 1);
             for (int i(0); i < pl1.size(); i++)
             {
                pl1[i].numerator.resize(2); // В числитель два нуля
                pl1[i].denominator.resize(1,1);// В знаменатель единица
             }
             degreeold1 = degree; // Сохраняем степень
        }

        pl1[degree] = a; // Присваем дробь к многочлены на позицию степени(Степень - индекс)

       for (int i = pl1.size() - 1; i >= 1; i--)
       {           
           if(pl1[i].numerator == nul)// Если Числитель равен нулевому вектору, то пропускаем число
               continue;

           if (pl1[i].numerator[0] == 1)
                ui->Poly_res1->setText(ui->Poly_res1->text() + " - "); // Если числитель отрицательный выводим -
            else
                if (i != pl1.size() - 1) //Заходим всегда, кроме первого раза
                    ui->Poly_res1->setText(ui->Poly_res1->text() + " + "); // Если числитель положительный выводим +

            for (int j = 1; j < pl1[i].numerator.size(); j++) // Вывод числителя дроби
                ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].numerator[j]));

            ui->Poly_res1->setText(ui->Poly_res1->text() + "/"); // Вывод слеша

            for (int j = 0; j < pl1[i].denominator.size(); j++) // Вывод знаменателя дроби
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].denominator[j]));

            ui->Poly_res1->setText(ui->Poly_res1->text() + "x<sup>" + QString::number(i) + "</sup>"); // Вывод x и степени, степень - i
       }
       //Свободный член в самом конце выводим, уже вне цикла
       if(pl1[0].numerator != nul) // Выводим, если он не равен нулю
       {
           if (pl1[0].numerator[0] == 1)
               ui->Poly_res1->setText(ui->Poly_res1->text() + " - "); // Если числитель отрицательный выводим -
           else
               ui->Poly_res1->setText(ui->Poly_res1->text() + " + "); // Если числитель положительный выводим +

           for (int i = 1; i < pl1[0].numerator.size(); i++) // Вывод числителя дроби
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].numerator[i]));

           ui->Poly_res1->setText(ui->Poly_res1->text() + "/"); // Вывод слеша

           for (int i = 0; i < pl1[0].denominator.size(); i++) // Вывод знаменателя дроби
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].denominator[i]));
       }
    }
    //-----------------------------------------------------------------------------------------
    else if (ui->Poly_rad2->isChecked())// Смотрим, что выбран второй многочлен
    {
        ui->Poly_res2->setText("");
        if (degree > degreeold2)//Если новая степень больше превыд. то добавляем в массив эл-ты
        {
             pl2.resize(degree + 1);
             for (int i(0); i < pl2.size(); i++)
             {
                pl2[i].numerator.resize(2); // В числитель два нуля
                pl2[i].denominator.resize(1,1);// В знаменатель единица
             }
             degreeold2 = degree; // Сохраняем степень
        }

        pl2[degree] = a; // Присваем дробь к многочлены на позицию степени(Степень - индекс)

        for (int i = pl2.size() - 1; i >= 1; i--)
        {
            if(pl2[i].numerator == nul)// Если Числитель равен нулевому вектору, то пропускаем число
                continue;

             if (pl2[i].numerator[0] == 1)
                 ui->Poly_res2->setText(ui->Poly_res2->text() + " - ");
             else
                 if (i != pl2.size() - 1) //Заходим всегда, кроме первого раза
                     ui->Poly_res2->setText(ui->Poly_res2->text() + " + "); // Если числитель положительный выводим +

             for (int j = 1; j < pl2[i].numerator.size(); j++) // Вывод числителя дроби
                 ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[i].numerator[j]));

             ui->Poly_res2->setText(ui->Poly_res2->text() + "/"); // Вывод слеша

             for (int j = 0; j < pl2[i].denominator.size(); j++) // Вывод знаменателя дроби
                ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[i].denominator[j]));

                ui->Poly_res2->setText(ui->Poly_res2->text() + "x<sup>" + QString::number(i) + "</sup>"); // Вывод x и степени, степень - i
        }
        //Свободный член в самом конце выводим, уже вне цикла
        if(pl2[0].numerator != nul)
        {
            if (pl2[0].numerator[0] == 1)
                ui->Poly_res2->setText(ui->Poly_res2->text() + " - "); // Если числитель отрицательный выводим -
            else
                ui->Poly_res2->setText(ui->Poly_res2->text() + " + "); // Если числитель положительный выводим +

            for (int i = 1; i < pl2[0].numerator.size(); i++) // Вывод числителя дроби
                ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[0].numerator[i]));

            ui->Poly_res2->setText(ui->Poly_res2->text() + "/"); // Вывод слеша

            for (int i = 0; i < pl2[0].denominator.size(); i++) // Вывод знаменателя дроби
                ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl2[0].denominator[i]));
        }
    }
}

vector<Drob> Project_DM_Qt::poly_out() // Функция обработки и операции с многочленами
{








}


