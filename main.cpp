#include <QCoreApplication>
#include "fusioncli.h"
#include <QTextStream>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qout(stdout);

    if(argc<=1) {
       qout << "Fusion Commandline-Interface"<< endl <<endl;
       qout << "Usage: fusioncli [options]"<< endl;
       qout << "--allGames -g: Get all Games with all Info"<< endl<<endl;

       QTimer::singleShot(100, &a, SLOT(quit()));
    }

    FusionCLI cli;
    cli.execute(argc, argv);

    QTimer::singleShot(1000, &a, SLOT(quit()));
    return a.exec();
}
