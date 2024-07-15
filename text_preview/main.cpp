#include "text_preview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextPreview t;
    t.show();
    return a.exec();
}
