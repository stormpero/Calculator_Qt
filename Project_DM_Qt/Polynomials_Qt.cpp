#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QDebug>
#include <QPixmap>

void Project_DM_Qt::Create_poly()
{
    connect(ui->Poly_addButton,SIGNAL(clicked()),this,SLOT(poly()));
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

void Project_DM_Qt::poly()
{


    ui->Poly_res1->setText("");
//    ui->Pol_res->setText("");
    static vector <Drob> pl1;
    static vector <Drob> pl2;
    Drob a;
    vector<int>nul = {0,0};
    int degree = 0;
    static int degreeold = -1;

    a = ration_convert(ui->Poly_num->text(), ui->Poly_det->text());


    degree = ui->Poly_deg->text().toInt();

       if (degree > degreeold)
       {
            pl1.resize(degree + 1);
            for (int i(0); i < pl1.size(); i++)
            {
               pl1[i].numerator.resize(2); // В числитель два нуля
               pl1[i].denominator.resize(1,1);// В знаменатель единица
            }
            degreeold = degree;
       }
       else
       {
           if (degree < degreeold)
                degreeold = degree;
       }
       pl1[degree] = a;

       int degmin = degree+1;
       for (int i = pl1.size() - 1; i >= 1; i--)
       {
           degmin--;
           if(pl1[i].numerator == nul)
               continue;
            if (i != pl1.size() - 1)
                ui->Poly_res1->setText(ui->Poly_res1->text() + " + ");

            for (int j = 1; j < pl1[i].numerator.size(); j++)
            {
                ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].numerator[j]));
            }

            ui->Poly_res1->setText(ui->Poly_res1->text() + "/");

            for (int j = 0; j < pl1[i].denominator.size(); j++)
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[i].denominator[j]));

            ui->Poly_res1->setText(ui->Poly_res1->text() + "x<sup>" + QString::number(degmin) + "</sup>"); // Степень x
       }
       if(pl1[0].numerator != nul)
       {
           ui->Poly_res1->setText(ui->Poly_res1->text() + " + ");
           for (int i = 1; i < pl1[0].numerator.size(); i++)
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].numerator[i]));

           ui->Poly_res1->setText(ui->Poly_res1->text() + "/");

           for (int i = 0; i < pl1[0].denominator.size(); i++)
               ui->Poly_res1->setText(ui->Poly_res1->text() + QString::number(pl1[0].denominator[i]));
       }


    //------------------------------------------------------------------------------------------------------
//    }
//    else if (ui->Poly_rad2->isChecked())
//    {
//        if (degree > degreeold)
//             pl1.resize(degree);
//        pl1[degree]=a;
//        for (int i = pl1.size() - 1; i >= 1; i--)
//        {
//            for (int j = 1; j < pl1[i].numerator.size(); j++)
//                ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl1[i].numerator[j]));

//            ui->Poly_res2->setText(ui->Poly_res2->text() + "/");

//            for (int j = 0; j < pl1[i].denominator.size(); j++)
//                ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl1[i].denominator[j]));

//            ui->Poly_res2->setText("x<sup>" + QString::number(degree) + "<sup> +"); // Степень x

//        }
//        for (int i = 1; i < pl1[0].numerator.size(); i++)
//            ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl1[0].numerator[i]));

//        ui->Poly_res2->setText(ui->Poly_res2->text() + "/");

//        for (int i = 0; i < pl1[0].denominator.size(); i++)
//            ui->Poly_res2->setText(ui->Poly_res2->text() + QString::number(pl1[0].denominator[i]));
//    }




//    vector<Drob> a = poly_convert(ui->Pol_num1->text());
//    vector<Drob> b = poly_convert(ui->Pol_num2->text());

}

vector<Drob> Project_DM_Qt::poly_out(QString a)
{








}


