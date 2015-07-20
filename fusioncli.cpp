#include "fusioncli.h"

FusionCLI::FusionCLI(QObject *parent) : QObject(parent)
{
    if(!db.init())
        return;

    q = new QTextStream(stdout);
    refreshList();
}


void FusionCLI::execute(int argc, QStringList args) {

   if(argc>1)
   {
       QString arg = args[1];
       if(arg=="-g"||arg=="--allGames")
           getAllGames();
       else if(arg=="-r"||arg=="--refresh")
           refreshList();
       else if(arg=="-l"||arg=="--launch")
           launchByID(args[2]);
       else if(arg=="-i"||arg=="--gameInfo") {
           getGameByID(args[2]);
       }
   }
}


void FusionCLI::getGameByID(QString ID) {
    bool noError  = true;
    int gameID  = ID.toInt(&noError, 10);

    if(!noError)
    {
        *q << "Cannot read ID, which is: " << ID << endl;
        return;
    }

    FGame *game = db.getGame(gameID);
    if(game == NULL)
    {
        *q << "Can't find game with ID: " << ID << endl;
        return;
    }

    qDebug() << "Print game: " << game->getName();
    print(getGame(game));

}

void FusionCLI::launchByID(QString ID) {
    bool noError  = true;
    int gameID  = ID.toInt(&noError, 10);

    if(!noError)
    {
        *q << "Cannot read ID, which is: " << ID << endl;
        qWarning() << "Cannot read ID, which is: " << ID;
        return;
    }

    FGame *game = db.getGame(gameID);
    if(game == NULL)
    {
        *q << "Can't find game with ID: " << ID << endl;
        qWarning() << "Can't find game with ID: " << ID;
        return;
    }

    qDebug() << "Launch game: " << game->getName();

    try { game->execute(); } catch( const std::exception &e) { qDebug() << e.what(); }

}


void FusionCLI::refreshList() {
    gameList.clear();
    gameList = db.getGameList();
}

void FusionCLI::getAllGames() {
  //  qDebug() << "print all games.";
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
   map.insert("banner", game->getArt(FArtBanner));
   map.insert("poster", game->getArt(FArtBox));
   map.insert("clearart", game->getArt(FArtClearart));
   map.insert("clearlogo", game->getArt(FArtClearart));

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
    qDebug() << "print(QVariant list)";
    QString type = list.typeName();
    if(type == "QVariantMap") {
        print(list.toMap());
    } else {
        qDebug() << "Type: " << type;

    }
}


void FusionCLI::print(QMap<QString, QVariant> list) {
    qDebug() << "print(QMap<QString, QVariant> list)";


    *q << "{" << endl;
    QList<QString> keys = list.keys();
    QList<QVariant> values = list.values();


    int i;
    for(i=0;i<list.size()-1;++i)
        *q << "\"" <<  keys[i]<< "\": \""  << values[i].toString() << "\", " << endl;

    *q << "\"" <<  keys[i]<< "\": \""  << values[i].toString() << "\" " << endl;


    *q << "} " << endl;
}

