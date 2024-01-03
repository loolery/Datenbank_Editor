#ifndef DATENBANK_EDITOR_H
#define DATENBANK_EDITOR_H

#include <QMainWindow>
#include <_struct.h>
#include <QVector>
#include <QList>
#include <QRadioButton>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class Datenbank_Editor; }
QT_END_NAMESPACE

class Datenbank_Editor : public QMainWindow
{
    Q_OBJECT

    QButtonGroup* radioLand = new QButtonGroup(this);
    QButtonGroup* radioVerein = new QButtonGroup(this);
	QList<QRadioButton*> Landradios;
	QList<QRadioButton*> Vereinsradios;

    QVector<Land> resultLand;
    QVector<Liga> resultLiga;
    QVector<Stadt> resultStadt;
    QVector<Vereine> resultVereine;
    QVector<Personen> resultPersonen;

    public:
        Datenbank_Editor(QWidget *parent = nullptr);
        ~Datenbank_Editor();

    private slots:
        void loadDb();
        void saveDb();
        void checked_radioLand(const int);
        void on_action_ber_triggered(bool checked);

    private:
        Ui::Datenbank_Editor *ui;
        void ligaAuswahl();
        void ligaWechsel(const QString &text);

};
#endif // DATENBANK_EDITOR_H
