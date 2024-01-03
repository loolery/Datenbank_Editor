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

class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual QVector<Land> getData(const QString &table, const int &page) = 0;
	virtual bool setData(const QString &table, QStringList &data) = 0;
};

class Database : public IDatabase
{
private:
	QSqlDatabase mydb;
	int m_pageSize;

public:
	// Konstruktor
	Database(const QString &fileName) {
		mydb = QSqlDatabase::addDatabase("QSQLITE");
		mydb.setDatabaseName(fileName);
		m_pageSize = 100;
	}

	bool open() override {
		if (!mydb.open()) {
			qDebug() << "Error: Die Datenbank konnte nicht geöffnet werden!";
			return false;
		}
		else {
			qDebug() << "Database: Datanbank verbunden!";
			return true;
		}
	}

	QVector<Land> getData(const QString &table, const int &page) override {
		QStringList data;
		QSqlQuery query(mydb);
		query.prepare("SELECT * FROM " + table + " LIMIT :pageSize OFFSET :offset ");
		query.bindValue(":pageSize", m_pageSize);
		query.bindValue(":offset", (page - 1) * m_pageSize);
		QVector<Land> land;
		if (query.exec()) {
			while (query.next()) {
				land.append({query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt()});
//                data << query.value(0).toString();
//                data << query.value(1).toString();
//                data << query.value(2).toString();
			}
		}
		else {
			qDebug() << "Error: " << query.lastError().text();
		}
		return land;
	}

	bool setData(const QString &table, QStringList &data) override {
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

	void close() override {
		mydb.close();
	}
};

#endif // _SQLITE_FUNCTIONS_H
