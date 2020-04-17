#include "project_dm_qt.h"
#include "ui_project_dm_qt.h"
#include <QRegExpValidator>
#include <QMouseEvent>
#include <QtWidgets>

#define page ui

QLineEdit *child, *newLine;
void Project_DM_Qt::customSlot(const QString &str)
{
    child->setText(str);
}
void Project_DM_Qt::finishSlot()
{
    child->setStyleSheet("background: rgb(255, 255, 255);");
}

void Project_DM_Qt::keyPressEvent ( QKeyEvent * event )
{
   if (event->key() == Qt::Key_Control)
   {
       QPoint pt = mapFromGlobal(QCursor::pos());
       child = qobject_cast<QLineEdit*>(childAt(pt));

       if (child && !child->isReadOnly())
       {
           child->setStyleSheet("background: rgb(255, 0, 0);");

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
    QRegExpValidator* rxv = new QRegExpValidator(QRegExp("[-]?\\d*"), this); // pos and neg
    ple->setValidator(rxv);

    // Параметр только для чтения
    ple->setReadOnly(readonly);
}


void Project_DM_Qt::increaseCells()
{
    int columns(sqrt(page->gridLayout_0->count()));
    for (int i(0); ; ++i)
    {
        QLineEdit* ple1 = new QLineEdit(this), *ple2 = new QLineEdit(this), *ple3 = new QLineEdit(this);
        createCell(ple1, false); createCell(ple2, false); createCell(ple3, true);
        page->gridLayout_0 ->addWidget(ple1, i, columns);
        page->gridLayout_01->addWidget(ple2, i, columns);
        page->gridLayout_02->addWidget(ple3, i, columns);

        if (i == columns) break;

        QLineEdit* ple12 = new QLineEdit(this), *ple22 = new QLineEdit(this), *ple32 = new QLineEdit(this);
        createCell(ple12, false); createCell(ple22, false); createCell(ple32, true);
        page->gridLayout_0 ->addWidget(ple12, columns, i);
        page->gridLayout_01->addWidget(ple22, columns, i);
        page->gridLayout_02->addWidget(ple32, columns, i);
    }
}

void Project_DM_Qt::decreaseCells()
{
    int columns(sqrt(page->gridLayout_0->count()) - 1);
    if (columns < 2)
        return;

    for (int i(0); ; ++i)
    {
        delete page->gridLayout_0  ->itemAtPosition(i, columns)->widget();
        delete page->gridLayout_01->itemAtPosition(i, columns)->widget();
        delete page->gridLayout_02->itemAtPosition(i, columns)->widget();

        if (i == columns) break;

        delete page->gridLayout_0  ->itemAtPosition(columns, i)->widget();
        delete page->gridLayout_01->itemAtPosition(columns, i)->widget();
        delete page->gridLayout_02->itemAtPosition(columns, i)->widget();
    }
}

void Project_DM_Qt::on_spinBox_valueChanged(int arg1)
{
    while (sqrt(page->gridLayout_0->count()) < arg1)
        increaseCells();

    while (sqrt(page->gridLayout_0->count()) > arg1)
        decreaseCells();
}


QList<QLineEdit*> Project_DM_Qt::getData(std::vector<std::vector<int>> &mat1, std::vector<std::vector<int>> &mat2)
{
    QList<QLineEdit*> list = page->scrollArea  ->findChildren<QLineEdit*>();
    QList<QLineEdit*> list1 = page->scrollArea_1->findChildren<QLineEdit*>();
    QList<QLineEdit*> list2 = page->scrollArea_2->findChildren<QLineEdit*>();

    // Сортировка листов
    for (int squar(2); squar < sqrt(list.size()); ++squar)
        for (int i(squar), j(squar * squar); i < pow(squar + 1, 2) - 1; i += squar + 1, j += 2)
        {
            list.move(j, i);
            list1.move(j, i);
            list2.move(j, i);
        }


    mat1.resize(list.size());
    mat2.resize(list1.size());
    for (int i(0); i < list.size(); ++i)
    {
        QString number(list[i]->text()), number1(list1[i]->text());
        // Обработка знака числа первой матрицы
        if (number.isEmpty())
            mat1[i].push_back(0);

        else if (number[0] == '-')
        {
            mat1[i].push_back(1);
            number.remove(0, 1);
        }
        else
            mat1[i].push_back(0);

        for (int j(0); j < number.size(); ++j)
            mat1[i].push_back(number[j].digitValue());

        // Обработка знака числа второй матрицы
        if (number1.isEmpty())
        {
            mat2[i].push_back(0);
            continue;
        }
        if (number1[0] == '-')
        {
            mat2[i].push_back(1);
            number1.remove(0, 1);
        }
        else
            mat2[i].push_back(0);

        for (int j(0); j < number1.size(); ++j)
            mat2[i].push_back(number1[j].digitValue());
    }

    return list2;
}


void Project_DM_Qt::on_pushButton_5_clicked()
{
    using namespace std;

    vector<vector<int>> mat1, mat2, result;
    QList<QLineEdit*> list = getData(mat1, mat2);

    if (page->comboBox->currentText() == "+")
        result = mat1;
    else
        result = mat2;

    int counter(page->gridLayout_0->count());

    for (int i(0); i < counter; ++i)
    {
        if (!result[i][0])
            list[i]->setText("");
        else
            list[i]->setText("-");

        for(uint j(1); j < result[i].size(); ++j)
            if (result[i][j])
                list[i]->setText(list[i]->text() + QString::number(result[i][j]));
    }
}
