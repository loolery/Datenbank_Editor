#ifndef _SQLITE_FUNCTIONS_H
#define _SQLITE_FUNCTIONS_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include "_struct.h"

class SQLiteDatabase
{
private:
    QSqlDatabase mydb;
    QString dbFile;
    int m_pageSize;

public:
    // Konstruktor
    SQLiteDatabase(const QString &fileName = "default.db3") {
        dbFile = fileName;
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(fileName);
        m_pageSize = 100;
    }

    bool open() {
        if (!mydb.open()) {
            qDebug() << "Error: Die Datenbank konnte nicht geöffnet werden!";
            return false;
        }
        else {
            qDebug() << "Database: Datanbank verbunden!";
            return true;
        }
    }

    QVector<Land> getLand(const int &page) {
        QStringList data;
        QSqlQuery query(mydb);
        query.prepare("SELECT * FROM tbl_land LIMIT :pageSize OFFSET :offset");
        query.bindValue(":pageSize", m_pageSize);
        query.bindValue(":offset", (page - 1) * m_pageSize);
        qDebug() << "SQL-Query: " + query.executedQuery();
        QVector<Land> land;
        if (query.exec()) {
            while (query.next()) {
                land.append({query.value(0).toInt(), query.value(1).toString(), query.value(3).toInt()});
            }
        }
        else {
            qDebug() << "Error: " << query.lastError().text();
        }
        return land;
    }

    QVector<Liga> getLiga(const int &landId=1, const int &rang= 0) {
        QStringList data;
        QSqlQuery query(mydb);
        QVector<Liga> liga;
        if(rang == 0) {
            query.prepare("SELECT * FROM tbl_ligen WHERE Land_ID=:landId");
        } else {
            query.prepare("SELECT * FROM tbl_ligen WHERE Land_ID=:landId AND Rang=:rang");
            query.bindValue(":rang", rang);
        }
        query.bindValue(":landId", landId);
        qDebug() << "SQL-Query: " + query.executedQuery();
        if (query.exec()) {
            while (query.next()) {
                liga.append({query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toInt()});
            }
        }
        else {
            qDebug() << "Error: " << query.lastError().text();
        }
        return liga;
    }

    QVector<Stadt> getStadt(const int &page) {
        QStringList data;
        QSqlQuery query(mydb);
        query.prepare("SELECT * FROM tbl_stadt LIMIT :pageSize OFFSET :offset ");
        query.bindValue(":pageSize", m_pageSize);
        query.bindValue(":offset", (page - 1) * m_pageSize);
        QVector<Stadt> stadt;
        if (query.exec()) {
            while (query.next()) {
                stadt.append({query.value(0).toInt(), query.value(1).toInt(), query.value(3).toString(), query.value(4).toInt()});
            }
        }
        else {
            qDebug() << "Error: " << query.lastError().text();
        }
        return stadt;
    }

    QVector<Vereine> getVereine(const int &ligaId, const QString &name="no", const int &page=1) {
        QStringList data;
        QSqlQuery query(mydb);
        QVector<Vereine> vereine;
        if(name=="no"){
            query.prepare("SELECT * FROM tbl_vereine WHERE Liga_ID=:ligaid LIMIT :pageSize OFFSET :offset ");
            query.bindValue(":ligaid", ligaId);
        } else {
            query.prepare("SELECT * FROM tbl_vereine WHERE Name=:name LIMIT :pageSize OFFSET :offset ");
            query.bindValue(":name", name);
        }
        query.bindValue(":pageSize", m_pageSize);
        query.bindValue(":offset", (page - 1) * m_pageSize);

        qDebug() << "SQL-Query: " + query.executedQuery();
        if (query.exec()) {
            while (query.next()) {
                vereine.append({query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toInt()});
            }
        }
        else {
            qDebug() << "Error: " << query.lastError().text();
        }
        return vereine;
    }

    QVector<Personen> getPersonen(const int &page) {
        QStringList data;
        QSqlQuery query(mydb);
        query.prepare("SELECT * FROM tbl_personen LIMIT :pageSize OFFSET :offset ");
        query.bindValue(":pageSize", m_pageSize);
        query.bindValue(":offset", (page - 1) * m_pageSize);
        QVector<Personen> personen;
        if (query.exec()) {
            while (query.next()) {
                personen.append({query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(), query.value(5).toDate(), query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt(), query.value(9).toInt(), query.value(10).toInt(), query.value(11).toInt()});
            }
        }
        else {
            qDebug() << "Error: " << query.lastError().text();
        }
        return personen;
    }

    bool setData(const QString &table, QStringList &data) {
        QSqlQuery query(mydb);
        mydb.transaction();
        for (const auto &item : data) {
            query.prepare("INSERT INTO " + table + " (col1) VALUES (:data)");
            query.bindValue(":data", item);
            if (!query.exec()) {
                qDebug() << "Error: " << query.lastError().text();
                mydb.rollback();
                return false;
            }
        }
        mydb.commit();
        return true;
    }

    // Setter and Getter
    void setPageSize(int size) { m_pageSize = size; }
    int pageSize() const { return m_pageSize; }
    void setDbFile(QString fileName) {dbFile = fileName;}
    QString getDbFile() {return dbFile;}


    void close() {
        mydb.close();
    }
};

#endif // _SQLITE_FUNCTIONS_H
