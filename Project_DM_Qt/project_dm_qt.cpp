#include <QPropertyAnimation>
#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QMessageBox>

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

    setWindowTitle("Almighty calculator");
    setWindowIcon(QIcon(":/buttons/img/1200x630bb.png"));

    // Animation properties
    animation->setTargetObject(ui->main);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->setDuration(500);
    animation->setPropertyName("geometry");

    // Background color for Natural
    //const QPalette palet3(qRgb(152, 251, 152)); //(212, 102, 102)
    //ui->natural->setPalette(palet3);
    //
     //ui->natural->setTextureImage(QPixmap(":/buttons/img/fon_nat.jpg"));

     QBrush br(Qt::TexturePattern);
     br.setTextureImage(QImage(":/buttons/img/fon_nat.jpg"));
     QPalette fon_nat =ui->natural->palette();
     fon_nat.setBrush(QPalette::Background, br);
     ui->natural->setPalette(fon_nat);
    ui->natural->setAutoFillBackground(true);

    // Background color for Integer
    const QPalette palet1(qRgb(135, 206, 250));
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
    const QPalette palet5(qRgb(240, 128, 128));
    ui->matrix->setPalette(palet5);
    ui->matrix->setAutoFillBackground(true);
	

    // Buttons_Natural
    connect(ui->natural_Button,SIGNAL(clicked()),this,SLOT(natural()));
    ui->natural_num1->setValidator(new QRegExpValidator(QRegExp("^(?!0[\\d*])\\d*"), this));
    ui->natural_num2->setValidator(new QRegExpValidator(QRegExp("^(?!0[\\d*])\\d*"), this));
    ui->natural_res->setReadOnly(true);
    ui->natural_num1->setPlaceholderText("0");
    ui->natural_num2->setPlaceholderText("0");


    // Buttons_Integer
    connect(ui->Integer_Button,SIGNAL(clicked()),this,SLOT(integ()));    
    ui->Integer_num1->setValidator(new QRegExpValidator(QRegExp("[-]?\\d*"), this));
    ui->Integer_num2->setValidator(new QRegExpValidator(QRegExp("[-]?\\d*"), this));
    ui->Integer_res->setReadOnly(true);
    ui->Integer_num1->setPlaceholderText("0");
    ui->Integer_num2->setPlaceholderText("0");
    //

    //Rational_Button
    connect(ui->Rational_Button,SIGNAL(clicked()),this,SLOT(ration()));
    ui->Rational_num1_num->setValidator(new QRegExpValidator(QRegExp("[-]?\\d*"), this));
    ui->Rational_num1_det->setValidator(new QRegExpValidator(QRegExp("^(?!0[\\d*])\\d*"), this));
    ui->Rational_num2_num->setValidator(new QRegExpValidator(QRegExp("[-]?\\d*"), this));
    ui->Rational_num2_det->setValidator(new QRegExpValidator(QRegExp("^(?!0[\\d*])\\d*"), this));
    ui->Rational_res_num->setReadOnly(true);
    ui->Rational_res_det->setReadOnly(true);
    ui->Rational_num1_num->setPlaceholderText("0");
    ui->Rational_num2_num->setPlaceholderText("0");
    ui->Rational_num1_det->setPlaceholderText("1");
    ui->Rational_num2_det->setPlaceholderText("1");

    //

    // Matrix initialization //
    increaseCells();         //
    increaseCells();         //
    increaseCells();         //
    //\////////////////////////

    ui->label_Pol->setPixmap(QPixmap(":/buttons/img/indevelop.png"));
    ui->Btn_natural->setDisabled(true);
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

bool Project_DM_Qt::check_zero(vector <int> zero)
{
    if (POZ_Z_D(zero)==0)
        return true;
    else
        return false;
}


void Project_DM_Qt::on_natural_Button_help_clicked()
{

    QMessageBox msgBox;
    msgBox.setParent(0);
    msgBox.setWindowTitle(" =) ");
    msgBox.setText("");
    QPixmap p;
    p.load(":/buttons/img/new.jpg");
    msgBox.setIconPixmap(p);// no sound, but with icon

    msgBox.exec();
}
