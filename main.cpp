#include <Windows.h>
#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QString>
#include <QTranslator>
#include <QMessageBox>
#include "datenbank_editor.h"
#include "datenbank_editor.cpp"
#include <_functions.h>

using namespace std;
QVector<Land> result;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Datenbank_Editor w;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Datenbank_Editor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

	QMessageBox::information(nullptr, "aha", "...");

	w.show(); // anzeige des GUI
    return a.exec();
}
