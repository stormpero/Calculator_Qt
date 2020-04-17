#include "project_dm_qt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Project_DM_Qt w;
    w.show();
    return a.exec();
}
