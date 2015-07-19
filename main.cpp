#include <QCoreApplication>
#include "fusioncli.h"
#include <QTextStream>
#include <QTimer>
#include <QtDebug>
#include <QFile>

#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG_TEST


#ifdef DEBUG_TEST
QTextStream *dbgStream;

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
void crashMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString s(str);
    s = s.replace("\"", "-");
    const char * msg = s.toStdString().c_str();
#else
void crashMessageOutput(QtMsgType type, const char *msg)
{
#endif
    switch (type)
    {
        case QtDebugMsg:
            *dbgStream << "Debug: " << str << "\n";
            break;
        case QtWarningMsg:
            *dbgStream << "Warning: " << str << "\n";
            break;
        case QtCriticalMsg:
            *dbgStream << "Critical: " << str << "\n";
            break;
        case QtFatalMsg:
            *dbgStream << "Fatal: " << str << "\n";
            abort();
    }
}
#endif



int main(int argc, char *argv[])
{
#ifdef DEBUG_TEST

    QFile dbgFile("./CLI_DBG.log");

    if (dbgFile.open(QIODevice::WriteOnly|QIODevice::Append)) {
        dbgStream = new QTextStream(&dbgFile);
    }


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    qInstallMessageHandler(crashMessageOutput);
#else
    qInstallMsgHandler(crashMessageOutput);
#endif
#endif

    QCoreApplication a(argc, argv);

    QTextStream qout(stdout);
    QStringList args;
    qDebug() << "Launching";

    for(int i=0;i<argc;++i) {
        args.append((argv[i]));
    }

    qDebug() << "Args " <<args;



    if(argc<=1) {
       qout << "Fusion Commandline-Interface"<< endl <<endl;
       qout << "Usage: fusioncli [options]"<< endl;
       qout << "--allGames -g: Get all Games with all Info"<< endl<<endl;

       QTimer::singleShot(10, &a, SLOT(quit()));
        #ifdef DEBUG_TEST
       dbgFile.close();
       delete dbgStream;
        #endif
    }

    FusionCLI cli;
    cli.execute(argc, argv);

    QTimer::singleShot(10, &a, SLOT(quit()));

    #ifdef DEBUG_TEST
    dbgFile.close();
    delete dbgStream;
    #endif

    return a.exec();
}
