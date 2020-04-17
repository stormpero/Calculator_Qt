#ifndef PROJECT_DM_QT_H
#define PROJECT_DM_QT_H

#include <QMainWindow>
#include "Allfunc.h"
#include "natural.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Project_DM_Qt; }
QT_END_NAMESPACE

class Project_DM_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Project_DM_Qt(QWidget *parent = nullptr);
    ~Project_DM_Qt();

private slots:

    // Main buttons slots //
    void on_Btn_natural_clicked();
    void on_Btn_integer_clicked();
    void on_Btn_rational_clicked();
    void on_Btn_polynomials_clicked();
    void on_Btn_matrix_clicked();
    //\/////////////////////

private:
    Ui::Project_DM_Qt *ui;

};
#endif // PROJECT_DM_QT_H
