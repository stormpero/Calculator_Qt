#ifndef PROJECT_DM_QT_H
#define PROJECT_DM_QT_H

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include "Allfunc.h"
#include "natural.h"

typedef vector<vector<vector<int>>> Matrix;

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

    // Main buttons slots /////////////
    void on_Btn_natural_clicked();
    void on_Btn_integer_clicked();
    void on_Btn_rational_clicked();
    void on_Btn_polynomials_clicked();
    void on_Btn_matrix_clicked();
    //\////////////////////////////////

    // Disablebuttons /////
    void disablebuttons();

    //Integer//////////////////////////////
    void integ();
    vector <int> integ_check_convert(QString a);
    //|/////////////////////////////////////

    // Matrices ////////////////////////////
    void customSlot(const QString &str);
    void finishSlot();
    void keyPressEvent(QKeyEvent* event);
    void on_m_calc_clicked();
    void on_spinBox_valueChanged(int arg1);
    //\/////////////////////////////////////



private:
    Ui::Project_DM_Qt *ui;

    // Matrices ///////////////////////////////////////////
    void createCell(QLineEdit* ple, bool readonly);
    void increaseCells();
    void decreaseCells();
    QList<QLineEdit*> getData(Matrix &mat1, Matrix &mat2);
    //\////////////////////////////////////////////////////

};
#endif // PROJECT_DM_QT_H
