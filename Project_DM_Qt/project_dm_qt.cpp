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

    setWindowTitle("Almighty calculator");
    setWindowIcon(QIcon(":/buttons/img/1200x630bb.png"));

    // Animation properties
    animation->setTargetObject(ui->main);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->setDuration(500);
    animation->setPropertyName("geometry");

    // Background color for Natural
    QBrush fon_nat(QImage(":/buttons/img/fon_nat.jpg"));
    QPalette fon_nat_pal =ui->natural->palette();
    fon_nat_pal.setBrush(QPalette::Background, fon_nat);
    ui->natural->setPalette(fon_nat_pal);
    ui->natural->setAutoFillBackground(true);

    // Background color for Integer
    QBrush fon_int(QImage(":/buttons/img/fon_int.jpg"));
    QPalette fon_int_pal =ui->integer->palette();
    fon_int_pal.setBrush(QPalette::Background, fon_int);
    ui->integer->setPalette(fon_int_pal);
    ui->integer->setAutoFillBackground(true);

    // Background color for Rational
    QBrush fon_rat(QImage(":/buttons/img/fon_rat.jpg"));
    QPalette fon_rat_pal =ui->rational->palette();
    fon_rat_pal.setBrush(QPalette::Background, fon_rat);
    ui->rational->setPalette(fon_rat_pal);
    ui->rational->setAutoFillBackground(true);

    // Background color for Polynomials
    QBrush fon_pol(QImage(":/buttons/img/fon_pol.jpg"));
    QPalette fon_pol_pal =ui->polynomials->palette();
    fon_pol_pal.setBrush(QPalette::Background, fon_pol);
    ui->polynomials->setPalette(fon_pol_pal);
    ui->polynomials->setAutoFillBackground(true);

    // Background color for Matrices
    QBrush fon_mat(QImage(":/buttons/img/fon_mat.jpg"));
    QPalette fon_mat_pal =ui->matrix->palette();
    fon_mat_pal.setBrush(QPalette::Background, fon_mat);
    ui->matrix->setPalette(fon_mat_pal);
    ui->matrix->setAutoFillBackground(true);

    // Background color for mini Matrices
    const QPalette pmatmin(qRgb(237, 186, 183));
    ui->scrollAreaWidgetContents_8->setPalette(pmatmin);
    ui->scrollAreaWidgetContents_9->setPalette(pmatmin);
    ui->scrollAreaWidgetContents_10->setPalette(pmatmin);
    //


    // Buttons_Natural
    connect(ui->natural_Button,SIGNAL(clicked()),this,SLOT(natural()));
    ui->natural_num1->setValidator(new QRegExpValidator(QRegExp("^(0$|[1-9])\\d*"), this));
    ui->natural_num2->setValidator(new QRegExpValidator(QRegExp("^(0$|[1-9])\\d*"), this));
    ui->natural_res->setReadOnly(true);
    ui->natural_num1->setPlaceholderText("0");
    ui->natural_num2->setPlaceholderText("0");


    // Buttons_Integer
    connect(ui->Integer_Button,SIGNAL(clicked()),this,SLOT(integ()));    
    ui->Integer_num1->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Integer_num2->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Integer_res->setReadOnly(true);
    ui->Integer_num1->setPlaceholderText("0"); //
    ui->Integer_num2->setPlaceholderText("0");
    //

    //Rational_Button
    connect(ui->Rational_Button,SIGNAL(clicked()),this,SLOT(ration()));
    ui->Rational_num1_num->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Rational_num2_num->setValidator(new QRegExpValidator(QRegExp("^([1-9]|-[1-9]|0$)\\d*"), this));
    ui->Rational_num1_det->setValidator(new QRegExpValidator(QRegExp("^[1-9]\\d*"), this));
    ui->Rational_num2_det->setValidator(new QRegExpValidator(QRegExp("^[1-9]\\d*"), this));
    ui->Rational_res_num->setReadOnly(true);
    ui->Rational_res_det->setReadOnly(true);
    ui->Rational_num1_num->setPlaceholderText("0");
    ui->Rational_num2_num->setPlaceholderText("0");
    ui->Rational_num1_det->setPlaceholderText("1");
    ui->Rational_num2_det->setPlaceholderText("1");

    //
    Create_poly();

    // Matrix initialization //
    increaseCells();         //
    increaseCells();         //
    increaseCells();         //
    //\////////////////////////

    //info_buttons
    //connect(ui->natural_Button_help_1,SIGNAL(clicked()),this,SLOT(on_natural_Button_help_clicked()));
    connect(ui->natural_Button_help_2,SIGNAL(clicked()),this,SLOT(on_natural_Button_help_clicked()));
    connect(ui->natural_Button_help_3,SIGNAL(clicked()),this,SLOT(on_natural_Button_help_clicked()));
    connect(ui->natural_Button_help_4,SIGNAL(clicked()),this,SLOT(on_natural_Button_help_clicked()));
    connect(ui->natural_Button_help_5,SIGNAL(clicked()),this,SLOT(on_natural_Button_help_clicked()));
    //\////////////////////////
}

// Destructor
Project_DM_Qt::~Project_DM_Qt()
{
    delete ui;
}
QLineEdit *child, *newLine;

void Project_DM_Qt::customSlot(const QString &str)
{
    child->setText(str);
}
void Project_DM_Qt::finishSlot()
{
    child->setStyleSheet("QLineEdit {border: 2px solid gray; border-radius: 5px; padding: 0 8px; selection-background-color: #1E90FF; background: rgb(255, 255, 255);}");
    newLine->close();
}

void Project_DM_Qt::keyPressEvent ( QKeyEvent * event )
{
   if (event->key() == Qt::Key_Alt)
   {
       QPoint pt = mapFromGlobal(QCursor::pos());
       child = qobject_cast<QLineEdit*>(childAt(pt));

       if (child)
       {
           child->setStyleSheet("QLineEdit {border: 2px solid gray; border-radius: 5px; padding: 0 8px; selection-background-color: #1E90FF; background: rgb(178, 34, 34);}");

            newLine = new QLineEdit();
            createCell(newLine, false);

            QPoint pos = child->mapToGlobal(QPoint(0,0));
            newLine->setGeometry(pos.x(),pos.y()+child->height(),400,child->height());
            newLine->setReadOnly((child->isReadOnly()));
            newLine->setWindowFlag(Qt::FramelessWindowHint);
            newLine->setObjectName("myObject");
            newLine->setStyleSheet("#myObject { border: 2px solid darkGray; border-radius: 5px; }");
            newLine->setAlignment(Qt::AlignLeft);
            newLine->setText(child->text());
            newLine->setTextMargins(3,0,43,0);
            newLine->setWindowModality(Qt::ApplicationModal);

            QPushButton *butt = new QPushButton(newLine);
            butt->setGeometry(newLine->width()-40,newLine->height() / 2 - 15, 30, 30);
            butt->setText("X");
            butt->setStyleSheet("QPushButton { border: 1px solid darkGray; border-radius: 3px; }");
            butt->setCursor(Qt::PointingHandCursor);
            butt->show();


            connect(butt, SIGNAL(pressed()), this, SLOT(finishSlot()));
            connect(newLine, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot(const QString &)));
            connect(newLine, SIGNAL(editingFinished()), this, SLOT(finishSlot()));
            newLine->show();
            newLine->setFocus();
       }
   }
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
    if ( ((zero[0]==0)&&(zero.size()==1)) || ((zero[0]==0)&&(zero[1]==0))  )
        return true;
    else
        return false;
}

void Project_DM_Qt::on_natural_Button_help_clicked()
{

    QMessageBox msgBox;
    msgBox.setParent(0);
    msgBox.setWindowTitle(" Справка ");
    msgBox.setText("");
    QPixmap p;
    p.load(":/buttons/img/info.png");
    msgBox.setIconPixmap(p);// no sound, but with icon

    msgBox.exec();
}
