#include "registertourist.h"
#include "ui_registertourist.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

RegisterTourist::RegisterTourist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterTourist),
    database(QSqlDatabase::addDatabase("QSQLITE")) // Initialize the database object
{
    ui->setupUi(this);

    QString dbPath = "C:/Users/a_wendimu/Documents/database/MytouristManager.db"; // Database path

    // Check if the database file exists
    if (QFile::exists(dbPath)) {
        qDebug() << "Database file exists";
    } else {
        qDebug() << "Database file doesn't exist";
        return; // Exit if the database doesn't exist
    }

    database.setDatabaseName(dbPath); // Set the database path

    // Open the database connection
    if (!database.open()) {
        qDebug() << "Failed to open the database!";
        return; // Exit if the database cannot be opened
    }
    qDebug() << "Database opened successfully";
}

RegisterTourist::~RegisterTourist()
{
    delete ui;
}

void RegisterTourist::on_btnSave_clicked()
{
    // Get data from UI fields
    QString firstName = ui->txtFirstName->text();
    QString middleName = ui->txtMiddleName->text();
    QString lastName = ui->txtLastName->text();
    QString passportNo = ui->txtPassportNo->text();
    QString contactNo = ui->txtContactNo->text();
    QString permanentAddress = ui->txtPermanentAddress->text();
    QString packageName = ui->cmbChoosePackage->currentText();

    // Prepare SQL query to insert data into the database
    QSqlQuery query;
    query.prepare("INSERT INTO tourists (first_name, middle_name, last_name, passport_no, contact_no, permanent_address, package_name) "
                  "VALUES (:first_name, :middle_name, :last_name, :passport_no, :contact_no, :permanent_address, :package_name)");



    // Bind the parameters to the query
    query.bindValue(":first_name", firstName);
    query.bindValue(":middle_name", middleName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":passport_no", passportNo);
    query.bindValue(":contact_no", contactNo);
    query.bindValue(":permanent_address", permanentAddress);
    query.bindValue(":package_name", packageName);

    // Execute the query and handle errors
    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError();
    } else {
        qDebug() << "Data inserted successfully";
    }
}
