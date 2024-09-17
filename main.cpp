#include "basicnotepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BasicNotepad w;
    w.show();
    return a.exec();
}
