#ifndef FUSIONCLI_H
#define FUSIONCLI_H

#include <QObject>
#include <QList>
#include <QTextStream>

#include "fdb.h"
#include "fgame.h"


class FusionCLI : public QObject
{
    Q_OBJECT
public:
    explicit FusionCLI(QObject *parent = 0);
    void execute(int argc, char *argv[]);
signals:

public slots:

private:
    FDB db;
    void getAllGames();
    QMap<QString, QVariant> getGame(FGame *game);
    void print(QMap<QString, QVariant> list);
    void print(QList<QVariant> list, QString title);
    void print(QVariant list);
    QTextStream *q;
};

#endif // FUSIONCLI_H
