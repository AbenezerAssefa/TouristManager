#include "findtourist.h"
#include "ui_findtourist.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

FindTourist::FindTourist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindTourist)
{
    ui->setupUi(this);
    model = nullptr;
}

FindTourist::~FindTourist()
{
    delete ui;
    if (model != nullptr) {
        delete model;
    }
}

void FindTourist::on_btnFind_clicked()
{
    QString touristName = ui->txtTouristfName->text().trimmed();  // Trim input to remove leading/trailing spaces
    qDebug() << "Tourist Name (Trimmed): " << touristName;

    // Database connection
    QString dbPath = "C:/Users/a_wendimu/Documents/database/MytouristManager.db";
    qDebug() << "Database Path: " << dbPath;

    if (!QFile::exists(dbPath)) {
        qDebug() << "Database file doesn't exist: " << dbPath;
        return;
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "UniqueConnectionName");
    database.setDatabaseName(dbPath);

    if (!database.open()) {
        qDebug() << "Error: Unable to open the database. Error:" << database.lastError().text();
        return;
    }
    qDebug() << "Database opened successfully.";

    // Adjusted query to directly match the first name
    QSqlQuery query(database);
    query.prepare("SELECT * FROM Tourist WHERE FirstName = :firstName COLLATE NOCASE");
    query.addBindValue(touristName);

    // Debugging the query with the bound parameter
    qDebug() << "Query with bound value: " << query.boundValues();

    if (!query.exec()) {
        qDebug() << "Query execution failed: " << query.lastError().text();
        database.close();
        QSqlDatabase::removeDatabase("UniqueConnectionName");
        return;
    }
    qDebug() << "Query executed successfully.";

    // Check if query returned rows
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        qDebug() << "Row " << rowCount << ": "
                 << query.value(0).toString() << " | "
                 << query.value(1).toString() << " | "
                 << query.value(2).toString();
    }

    if (rowCount == 0) {
        qDebug() << "No rows retrieved for the given tourist name.";
    }

    // Set up model and bind it to the table view
    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    // Re-set the query for the model
    query.seek(0);  // Move to the first row
    model->setQuery(query);  // Use the query model to execute the query

    // Check for model error
    if (model->lastError().isValid()) {
        qDebug() << "Model error: " << model->lastError().text();
    } else {
        ui->tableView->setModel(model);

        // Adjust column widths for better visibility
        ui->tableView->setColumnWidth(0, 200);
        ui->tableView->setColumnWidth(1, 200);
        ui->tableView->setColumnWidth(2, 200);

        qDebug() << "Table view updated successfully.";
    }

    // Clean up the query and close the database after query execution and model update
    query.finish();  // Finish the query
    database.close(); // Close the database connection
    QSqlDatabase::removeDatabase("UniqueConnectionName"); // Clean up the database connection
}
