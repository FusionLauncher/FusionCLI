#include "fusioncli.h"


FusionCLI::FusionCLI(QObject *parent) : QObject(parent)
{
    if(!db.init())
        return;

    q = new QTextStream(stdout);
}


void FusionCLI::execute(int argc, char *argv[]) {
   if(argc==2)
   {
       QString arg = argv[1];
       if(arg=="-g"||arg=="--allGames")
           getAllGames();
   }
}


void FusionCLI::getAllGames() {
    qDebug() << "print all games.";
    QList<FGame> gameList = db.getGameList();
    QList<QVariant> games;
    qDebug() << "Found " << gameList.length() << " games.";

    for(int i=0;i<gameList.length();++i) {
       games.append(getGame(&gameList[i]));
    }


    print(games, "Games");
}

QMap<QString, QVariant> FusionCLI::getGame(FGame *game){
    qDebug() << "Print Game: "<< game->getName();

   QMap<QString, QVariant> map;
   map.insert("name", game->getName().replace("\\", "\\\\"));
   map.insert("id", game->dbId);
   map.insert("exe", game->getExe().replace("\\", "\\\\"));
   map.insert("path", game->getPath().replace("\\", "\\\\"));
   map.insert("type", game->getType());

   return map;
}



void FusionCLI::print(QList<QVariant> list, QString title) {
    qDebug() << "Print QList<QVariant>";

    *q << "{ \"" << title << "\" : [" << endl;


    int i;
    for(i=0;i<list.length()-1;++i) {
        print(list[i]);
        *q << ", " << endl;
    }

    print(list[i]);


   *q << "] }" << endl;
}


void FusionCLI::print(QVariant list) {
    QString type = list.typeName();
    if(type == "QVariantMap") {
        print(list.toMap());

    } else {
        qDebug() << "Type: " << type;

    }
}


void FusionCLI::print(QMap<QString, QVariant> list) {
    *q << "{" << endl;
    QList<QString> keys = list.keys();
    QList<QVariant> values = list.values();


    int i;
    for(i=0;i<list.size()-1;++i)
        *q << "\"" <<  keys[i]<< "\": \""  << values[i].toString() << "\", " << endl;

    *q << "\"" <<  keys[i]<< "\": \""  << values[i].toString() << "\" " << endl;


    *q << "} ";
}

