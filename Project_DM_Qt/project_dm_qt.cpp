#include <QPropertyAnimation>
#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"


/* Modules x coords
 *
 * Natural      0
 * Integer     -1110px
 * Rational    -2220px
 * Polynomials -3330px
 * Matrices    -4440px
 *
 */


// Animation object
QPropertyAnimation *animation = new QPropertyAnimation();

// Initialization
Project_DM_Qt::Project_DM_Qt(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Project_DM_Qt)
{
    ui->setupUi(this);

// Detecting release mode
#ifndef QT_DEBUG
    ui->main->setGeometry(0, 0, 5550, 721);
    ui->Btn_natural->setDisabled(true);
#endif

    setWindowTitle("The best of the best");

    // Animation properties
    animation->setTargetObject(ui->main);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->setDuration(500);
    animation->setPropertyName("geometry");

    // Background color for Natural
    const QPalette palet3(qRgb(152, 251, 152)); //(212, 102, 102)
    ui->natural->setPalette(palet3);
    ui->natural->setAutoFillBackground(true);

    // Background color for Integer
        
    const QPalette palet1(qRgb(135, 222, 194));
    ui->integer->setPalette(palet1);
    ui->integer->setAutoFillBackground(true);

    // Background color for Rational
    const QPalette palet2(qRgb(240, 230, 140)); //(0, 200, 0)
    ui->rational->setPalette(palet2);
    ui->rational->setAutoFillBackground(true);

    // Background color for Polynomials
    const QPalette palet4(qRgb(221, 160, 221)); //(222, 135, 222)
    ui->polynomials->setPalette(palet4);
    ui->polynomials->setAutoFillBackground(true);

    // Background color for Matrices

    const QPalette palet5(qRgb(214,214,77));
    ui->matrix->setPalette(palet5);
    ui->matrix->setAutoFillBackground(true);

    // Matrix initialization //
    increaseCells();         //
    increaseCells();         //
    increaseCells();         //
    //\////////////////////////
        
    //Buttons_Integer
      connect(ui->Integer_Button,SIGNAL(clicked()),this,SLOT(integ()));

}

// Destructor
Project_DM_Qt::~Project_DM_Qt()
{
    delete ui;
}


void Project_DM_Qt::disablebuttons()
{
    ui->Btn_matrix->setDisabled(false);
    ui->Btn_polynomials->setDisabled(false);
    ui->Btn_rational->setDisabled(false);
    ui->Btn_integer->setDisabled(false);
    ui->Btn_natural->setDisabled(false);
}


// Natural button click
void Project_DM_Qt::on_Btn_natural_clicked()
{
    animation->stop();

    disablebuttons();
    ui->Btn_natural->setDisabled(true);

    animation->setStartValue(ui->main->geometry());
    animation->setEndValue(QRect(-ui->natural->x(), 0, ui->main->width(), ui->main->height()));

    animation->start();
}

// Integer button click
void Project_DM_Qt::on_Btn_integer_clicked()
{
    animation->stop();

    disablebuttons();
    ui->Btn_integer->setDisabled(true);

    animation->setStartValue(ui->main->geometry());
    animation->setEndValue(QRect(-ui->integer->x(), 0, ui->main->width(), ui->main->height()));

    animation->start();
}

// Rational button click
void Project_DM_Qt::on_Btn_rational_clicked()
{
    animation->stop();

    disablebuttons();
    ui->Btn_rational->setDisabled(true);

    animation->setStartValue(ui->main->geometry());
    animation->setEndValue(QRect(-ui->rational->x(), 0, ui->main->width(), ui->main->height()));

    animation->start();
}

// Polynomials button click
void Project_DM_Qt::on_Btn_polynomials_clicked()
{
    animation->stop();

    disablebuttons();
    ui->Btn_polynomials->setDisabled(true);

    animation->setStartValue(ui->main->geometry());
    animation->setEndValue(QRect(-ui->polynomials->x(), 0, ui->main->width(), ui->main->height()));

    animation->start();
}

// Matrix button click
void Project_DM_Qt::on_Btn_matrix_clicked()
{
    animation->stop();

    disablebuttons();
    ui->Btn_matrix->setDisabled(true);

    animation->setStartValue(ui->main->geometry());
    animation->setEndValue(QRect(-ui->matrix->x(), 0, ui->main->width(), ui->main->height()));

    animation->start();
}
