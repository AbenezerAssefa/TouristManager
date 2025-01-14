#include "addpackage.h"
#include "ui_addpackage.h"
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include "databaseheader.h"

AddPackage::AddPackage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPackage)
{
    ui->setupUi(this);
}

AddPackage::~AddPackage()
{
    delete ui;
}

void AddPackage::on_btnSave_2_clicked()
{
    QString packageName = ui->txtPackageName->text();
    QString packageDescription = ui->txtDescription->toPlainText();
    QString amount = ui->txtAmount->text();

    qDebug() << "Package Name: " << packageName
             << " Package Description: " << packageDescription
             << " Amount: " << amount;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = "C:/Users/a_wendimu/Documents/database/MytouristManager.db";
    database.setDatabaseName(dbPath);

    if (QFile::exists(dbPath)) {
        qDebug() << "Database file exists";
    } else {
        qDebug() << "Database file doesn't exist";
        return;
    }

    if (!database.open()) {
        qDebug() << "Error: Unable to open Database";
        return;
    } else {
        qDebug() << "Database opened successfully.";
    }

    QSqlQuery query(database);

    query.prepare("INSERT INTO Package (PackageName, PackageDescription, Amount) VALUES (:PackageName, :PackageDescription, :Amount)");
    query.bindValue(":PackageName", packageName);
    query.bindValue(":PackageDescription", packageDescription);
    query.bindValue(":Amount", amount);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    } else {
        qDebug() << "Package inserted successfully.";
    }

    database.close();
}
