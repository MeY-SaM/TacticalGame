#include "page.h"
#include "pagename.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Page w;
    //w.show();
    pageName w;
    w.show();
    return a.exec();
}
