#ifndef STRUCT_H
#define STRUCT_H

#include <QString>
#include <QDate>

struct Land {
	int id;
	QString name;
	int einwohner;
};
struct Liga {
    int id;
    int landid;
    int rang;
    QString name;
    int plaetze;
};
struct Stadt {
	int id;
	int landid;
	QString name;
	int einwohner;
};
struct Vereine {
	int id;
	int stadtid;
	int ligaid;
	QString name;
    int geld;
};
struct Personen {
	int id;
	int landid;
	int vereinsid;
	QString vorname;
	QString nachname;
	QDate geburtsdatum;
	int position;
	int tempo;
	int technik;
	int einsatz;
	int fitness;
	int trikotnr;
};

#endif // STRUCT_H
