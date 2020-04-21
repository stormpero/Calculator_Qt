#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QRegExpValidator>
#include <QMouseEvent>
#include <QtWidgets>

QLineEdit *child, *newLine;
void Project_DM_Qt::customSlot(const QString &str)
{
    child->setText(str);
}
void Project_DM_Qt::finishSlot()
{
    child->setStyleSheet("QLineEdit {border: 2px solid gray; border-radius: 5px; padding: 0 8px; selection-background-color: #1E90FF; background: rgb(255, 255, 255);}");
}

void Project_DM_Qt::keyPressEvent ( QKeyEvent * event )
{
   if (event->key() == Qt::Key_Control)
   {
       QPoint pt = mapFromGlobal(QCursor::pos());
       child = qobject_cast<QLineEdit*>(childAt(pt));

       if (child && !child->isReadOnly())
       {
           child->setStyleSheet("QLineEdit {border: 2px solid gray; border-radius: 5px; padding: 0 8px; selection-background-color: #1E90FF; background: rgb(178, 34, 34);}");

            newLine = new QLineEdit();
            createCell(newLine, false);
            newLine->setGeometry(QStyle::alignedRect(
                                     Qt::LeftToRight,
                                     Qt::AlignCenter,
                                     QSize(400, child->height()),
                                     qApp->desktop()->geometry()
                                 ));
            newLine->setText(child->text());
            newLine->setAlignment(Qt::AlignLeft);
            newLine->setWindowModality(Qt::ApplicationModal);
            connect(newLine, SIGNAL(textChanged(const QString &)), this, SLOT(customSlot(const QString &)));
            connect(newLine, SIGNAL(editingFinished()), this, SLOT(finishSlot()));
            newLine->show();
            newLine->setFocus();
       }
   }
}


void Project_DM_Qt::createCell(QLineEdit* ple, bool readonly = false)
{
    // Настроиваем размер ячейки
    QSizePolicy *size = new QSizePolicy();
    size->setVerticalPolicy(QSizePolicy::Expanding);
    ple->setSizePolicy(*size);
    ple->setMinimumSize(70, 40);

    // Настраиваем размер текста
    auto font = ple->font();
    font.setPointSizeF(20);
    ple->setFont(font);

    // Настраиваем заполнитель
    ple->setPlaceholderText("0");

    // Расположение текста
    ple->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Убираем рамки ячейки
    ple->setFrame(false);

    // Подсказка
    ple->setToolTip("Matrix cell");

    // Фильтрация ввода
    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("^(?!0[\\d*])[-]?\\d*"), this); // pos and neg
    ple->setValidator(rxv);

    // Параметр только для чтения
    ple->setReadOnly(readonly);
}


void Project_DM_Qt::increaseCells()
{
    int columns(sqrt(ui->m_gridLayout->count()));

    for (int i(0); ; ++i)
    {
        QLineEdit* ple1 = new QLineEdit(this), *ple2 = new QLineEdit(this), *ple3 = new QLineEdit(this);
        createCell(ple1, false); createCell(ple2, false); createCell(ple3, true);

        ui->m_gridLayout  ->addWidget(ple1, i, columns);
        ui->m_gridLayout_1->addWidget(ple2, i, columns);
        ui->m_gridLayout_2->addWidget(ple3, i, columns);

        if (i == columns) break;

        QLineEdit* ple12 = new QLineEdit(this), *ple22 = new QLineEdit(this), *ple32 = new QLineEdit(this);
        createCell(ple12, false); createCell(ple22, false); createCell(ple32, true);

        ui->m_gridLayout  ->addWidget(ple12, columns, i);
        ui->m_gridLayout_1->addWidget(ple22, columns, i);
        ui->m_gridLayout_2->addWidget(ple32, columns, i);
    }
}

void Project_DM_Qt::decreaseCells()
{
    int columns(sqrt(ui->m_gridLayout->count()) - 1);

    if (columns < 2)
        return;

    for (int i(0); ; ++i)
    {
        delete ui->m_gridLayout  ->itemAtPosition(i, columns)->widget();
        delete ui->m_gridLayout_1->itemAtPosition(i, columns)->widget();
        delete ui->m_gridLayout_2->itemAtPosition(i, columns)->widget();

        if (i == columns) break;

        delete ui->m_gridLayout  ->itemAtPosition(columns, i)->widget();
        delete ui->m_gridLayout_1->itemAtPosition(columns, i)->widget();
        delete ui->m_gridLayout_2->itemAtPosition(columns, i)->widget();
    }
}

void Project_DM_Qt::on_spinBox_valueChanged(int arg1)
{
    while (sqrt(ui->m_gridLayout->count()) < arg1)
        increaseCells();

    while (sqrt(ui->m_gridLayout->count()) > arg1)
        decreaseCells();
}


QList<QLineEdit*> Project_DM_Qt::getData(Matrix &mat1, Matrix &mat2)
{
    QList<QLineEdit*> list = ui-> m_scrollArea->findChildren<QLineEdit*>();
    QList<QLineEdit*> list1 = ui->m_scrollArea_1->findChildren<QLineEdit*>();
    QList<QLineEdit*> list2 = ui->m_scrollArea_2->findChildren<QLineEdit*>();

    // Сортировка листов
    for (int squar(2); squar < sqrt(list.size()); ++squar)
        for (int i(squar), j(squar * squar); i < pow(squar + 1, 2) - 1; i += squar + 1, j += 2)
        {
            list.move(j, i);
            list1.move(j, i);
            list2.move(j, i);
        }

    uint lSize(sqrt(list.size()));

    mat1.resize(lSize);
    mat2.resize(lSize);
    for (uint i(0); i < lSize; ++i)
    {
        mat1[i].resize(lSize);
        mat2[i].resize(lSize);
        for (uint j(0); j < lSize; ++j)
        {
            QString number(list[i * lSize + j]->text()), number1(list1[i * lSize + j]->text());
            // Обработка знаков чисел первой матрицы
            if (number.isEmpty())
                mat1[i][j].push_back(0);            

            else if (number[0] == '-')
            {
                mat1[i][j].push_back(1);
                number.remove(0, 1);
            }
            else
                mat1[i][j].push_back(0);

            for (int k(0); k < number.size(); ++k)
                mat1[i][j].push_back(number[k].digitValue());

            if (text_error_integer(mat1[i][j]))
            {
                QMessageBox::warning(this, "Внимание","Ошибка ввода");
            }

            // Обработка знаков чисел второй матрицы
            if (number1.isEmpty())
            {
                mat2[i][j].push_back(0);
                continue;
            }
            if (number1[0] == '-')
            {
                mat2[i][j].push_back(1);
                number1.remove(0, 1);
            }
            else
                mat2[i][j].push_back(0);

            for (int k(0); k < number1.size(); ++k)
                mat2[i][j].push_back(number1[k].digitValue());

            if (text_error_integer(mat2[i][j]))
                QMessageBox::warning(this, "Внимание","Ошибка ввода");
        }
    }

    return list2;
}


void Project_DM_Qt::on_m_calc_clicked()
{
    using namespace std;

    Matrix mat1, mat2, result;
    QList<QLineEdit*> list = getData(mat1, mat2);

    if (ui->m_operation->currentText() == "+")
        result = MAT_Z_SUM(mat1, mat2);
    else
        result = MAT_Z_MUL(mat1, mat2);

    int counter(sqrt(ui->m_gridLayout->count()));

    for (int i(0); i < counter; ++i)
        for (int j(0); j < counter; ++j)
        {
            if (!result[i][j][0])
                list[i * counter + j]->setText("");
            else
                list[i * counter + j]->setText("-");

            for(uint k(1); k < result[i][j].size(); ++k)
                if (result[i][j][k])
                    list[i * counter + j]->setText(list[i * counter + j]->text() + QString::number(result[i][j][k]));
        }
}
