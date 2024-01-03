#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include <sqlite3.h>
#include <cstdio>
#include <QMessageBox>

using namespace std;


sqlite3* openDatabase(string dbFile) {
    sqlite3* db;
    int rc = sqlite3_open(dbFile.c_str(), &db);
    if (rc != SQLITE_OK) {
        QMessageBox::information(nullptr, "Error...", "Fehler beim Öffnen der Datenbank: %s\n");
        sqlite3_close(db);
        return nullptr;
    }
    return db;
}
void closeDatabase(sqlite3* db) {
    sqlite3_close(db);
}

vector<vector<string>> readTable(string dbFile, string tableName) {
    sqlite3* db = openDatabase(dbFile);
    if (db == nullptr) return vector<vector<string>>();

    vector<vector<string>> result;

    // Schützt gegen SQL-Injection, indem nur erlaubte Zeichen erlaubt sind
    if (!tableName.empty() && tableName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") == string::npos) {
        string query = "SELECT * FROM " + tableName + " ORDER BY id DESC";
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            QMessageBox::information(nullptr, "Error...", "Fehler beim Vorbereiten des SQL-Statements: %s\n");
            closeDatabase(db);
            return result;
        }

        int rows = 0;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            vector<string> row;
            for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                row.push_back((char*)sqlite3_column_text(stmt, i));
            }
            result.push_back(row);
            rows++;
        }
        if (rc != SQLITE_DONE) {
            QMessageBox::information(nullptr, "Error...", "Fehler beim Ausführen des SQL-Statements: %s\n");
        }
        sqlite3_finalize(stmt);
    }
    closeDatabase(db);
    return result;
}

#endif // TEST_H
