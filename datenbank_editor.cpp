#include <QMessageBox>
#include <QString>
#include "SQLiteDatabase.h"
#include "datenbank_editor.h"
#include "ui_datenbank_editor.h"

SQLiteDatabase db("default.db3"); // Erstellt das Objekt der SQliteDB

Datenbank_Editor::Datenbank_Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Datenbank_Editor)
{
    ui->setupUi(this);
	connect(ui->BtnOpen, SIGNAL(clicked()), this, SLOT(loadDb()));
    connect(ui->BtnSave, SIGNAL(clicked()), this, SLOT(saveDb()));

    radioLand->addButton(ui->radioLand1); radioLand->addButton(ui->radioLand2); radioLand->addButton(ui->radioLand3);
    radioLand->addButton(ui->radioLand4); radioLand->addButton(ui->radioLand5);
	radioVerein->addButton(ui->radioVerein1); radioVerein->addButton(ui->radioVerein2); radioVerein->addButton(ui->radioVerein3); radioVerein->addButton(ui->radioVerein4);
	radioVerein->addButton(ui->radioVerein5); radioVerein->addButton(ui->radioVerein6); radioVerein->addButton(ui->radioVerein7); radioVerein->addButton(ui->radioVerein8);
	radioVerein->addButton(ui->radioVerein9); radioVerein->addButton(ui->radioVerein10); radioVerein->addButton(ui->radioVerein11); radioVerein->addButton(ui->radioVerein12);
	radioVerein->addButton(ui->radioVerein13); radioVerein->addButton(ui->radioVerein14); radioVerein->addButton(ui->radioVerein15); radioVerein->addButton(ui->radioVerein16);
	radioVerein->addButton(ui->radioVerein17);radioVerein->addButton(ui->radioVerein18);radioVerein->addButton(ui->radioVerein19);radioVerein->addButton(ui->radioVerein20);

    connect(radioLand, SIGNAL(buttonClicked(int)), this, SLOT(checked_radioLand(int)));
    connect(ui->comboBoxLiga, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::activated),
            [&](const QString &text) { ligaWechsel(text); });

    // Läd speicher aller radioButtons in einer QList der Klasse.
	Landradios << ui->radioLand1 << ui->radioLand2 << ui->radioLand3 << ui->radioLand4 << ui->radioLand5;
	Vereinsradios << ui->radioVerein1 << ui->radioVerein2 << ui->radioVerein3 << ui->radioVerein4 << ui->radioVerein5 << ui->radioVerein6 << ui->radioVerein7;
	Vereinsradios << ui->radioVerein8 << ui->radioVerein9 << ui->radioVerein10 << ui->radioVerein11 << ui->radioVerein12 << ui->radioVerein13 << ui->radioVerein14;
	Vereinsradios << ui->radioVerein15 << ui->radioVerein16 << ui->radioVerein17 << ui->radioVerein18 << ui->radioVerein19 << ui->radioVerein20;

	// macht alle radioButtons unsichtbar, bis zu deren initialisierung.
	for(int i=-2; i>=-(radioLand->buttons().count()+1); i--){
		qDebug() << "Land -> "+ QString::number(i);
		if(radioLand->button(i)->text() == "") { radioLand->button(i)->hide(); }
	}
	for(int i=-2; i>=-(radioVerein->buttons().count()+1); i--){
		qDebug() << "Verein -> "+ QString::number(i);
		if(radioVerein->button(i)->text() == "") { radioVerein->button(i)->hide(); }
	}
}

void Datenbank_Editor::loadDb(){
    db.setPageSize(5); // Setze die maximale anzahl von reihen die zurück gegegen werden sollen je Seite.
	if (!db.open()) { // Öffnet die Datenbank
		qDebug() << "DB konnte nicht geöffnet werden!/n";
	}
    resultLand = db.getLand(1); // Liest 1 Seite aus der Tabelle tbl_land.
    qDebug() << QString::number(resultLand.size()) + " Länder geladen.";
    resultStadt = db.getStadt(1); // Liest 1 Seite aus der Tabelle tbl_stadt.
    qDebug() << QString::number(resultStadt.size()) + " Städte geladen.";
    resultPersonen = db.getPersonen(1); // Liest 1 Seite aus der Tabelle tbl_stadt.
    qDebug() << QString::number(resultPersonen.size()) + " Personen geladen.";

    if(resultLand.size()>0){ // ausgabe der Länder in den radiobuttons
        for (int i=0; i<resultLand.size(); i++) {
            qDebug() << "läuft noch..." << i;
			Landradios[i]->setText(QString(resultLand[i].name));
			Landradios[i]->show();
		}
	}
    for(int i=0; i<Landradios.size(); i++){ //macht ungenutze radioButton wieder unsichtbar.
		if(Landradios[i]->text() == "") { Landradios[i]->hide(); }
	}

	ui->radioLand1->setChecked(true);
    ui->lineEditLandName->setText(resultLand[0].name);
    ui->lineEditLandEinwohner->setText(QString::number(resultLand[0].einwohner));

	db.close(); // Schließen die Datenbank
}
void Datenbank_Editor::ligaAuswahl(){
    ui->comboBoxLiga->clear(); // leert die einträge aus der comboBox
    for(int i=0; i<resultLiga.size(); i++){ ui->comboBoxLiga->addItem(QString(resultLiga[i].name)); } // fügt die Ligen der comboBox hinzu
    ui->lineEditLigaName->setText(resultLiga[0].name);
    qDebug() << resultLiga[0].id;

    if (!db.open()) { qDebug() << db.getDbFile() + " konnte nicht geöffnet werden!/n";} // öffnet die Db.
    resultVereine = db.getVereine(resultLiga[0].id); // Liest 1 Seite aus der Tabelle tbl_vereine.
    db.close(); // Schließen die Db.

    // ausgabe der Vereine in den radiobuttons
	for (int i=0; i<20; i++) { Vereinsradios[i]->setText(""); }
	if(resultVereine.size()>0){
        for (int i=0; i<resultVereine.size(); i++) {
			Vereinsradios[i]->setText(QString(resultVereine[i].name));
			Vereinsradios[i]->show();
        }
    }
	for(int i=0; i<Vereinsradios.size(); i++){
		//macht ungenutze radioButton wieder unsichtbar.
		if(Vereinsradios[i]->text() == "") { Vereinsradios[i]->hide(); }
	}
}

void Datenbank_Editor::ligaWechsel(const QString &text){
    int ligaid;
    for (const Liga &item : resultLiga) {
        if (item.name == text) {
            ligaid = item.id;
            break;
        }
    }
    if (!db.open()) { qDebug() << db.getDbFile() + " konnte nicht geöffnet werden!/n";} // öffnet die Db.
    resultVereine = db.getVereine(ligaid); // Liest 1 Seite aus der Tabelle tbl_vereine.
    db.close(); // Schließen die Db.

    // ausgabe der Vereine in den radiobuttons
	for (int i=0; i<20; i++) { Vereinsradios[i]->setText(""); }
	if(resultVereine.size()>0){
		for (int i=0; i<resultVereine.size(); i++) {
			Vereinsradios[i]->setText(QString(resultVereine[i].name));
			Vereinsradios[i]->show();
		}
	}
	for(int i=0; i<Vereinsradios.size(); i++){
		//macht ungenutze radioButton wieder unsichtbar.
		if(Vereinsradios[i]->text() == "") { Vereinsradios[i]->hide(); }
	}
}
void Datenbank_Editor::saveDb(){
//        if (!db.setData("tbl_vereine", daten)) { // Speichern der Daten in der Tabelle.
//            qDebug() << "Error beim speichern!";
//        }
//    db.close(); // Schließen die Datenbank
}
void Datenbank_Editor::checked_radioLand(const int buttonid) {
    int land;
    if (buttonid == radioLand->id(ui->radioLand1)) {
            land = 0;
        } else if (buttonid == radioLand->id(ui->radioLand2)) {
            land = 1;
        } else if (buttonid == radioLand->id(ui->radioLand3)) {
            land = 2;
        } else if (buttonid == radioLand->id(ui->radioLand4)) {
            land = 3;
        } else if (buttonid == radioLand->id(ui->radioLand5)) {
            land = 4;
        } else {
			land = 0;
	}
    qDebug() << "Land " + QString::number(buttonid) + " wurde ausgewählt.";

    ui->lineEditLandName->setText(resultLand[land].name);
    ui->lineEditLandEinwohner->setText(QString::number(resultLand[land].einwohner));

    if (!db.open()) { qDebug() << db.getDbFile() + " konnte nicht geöffnet werden!/n";} // öffnet die Db.
    resultLiga = db.getLiga(resultLand[land].id); // Liest 1 Seite aus der Tabelle tbl_liga.
    qDebug() << "size: " + QString::number(resultLiga.size());
    db.close(); // Schließen die Db.

    ligaAuswahl();
}

void Datenbank_Editor::on_action_ber_triggered(bool checked)
{
    if(checked==false){
        QMessageBox::about(this, tr("Über..."),
                tr("Dies ist ein Info-Fenster vom <b>Datenbank-Editor</b>, welches über den "
                   "den Info Reiter geöffnet werden kann und ein paar Informationen "
                   "bereit halten soll."));
    }
}

Datenbank_Editor::~Datenbank_Editor()
{
	delete ui;
}


