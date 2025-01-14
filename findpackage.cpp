#include "findpackage.h"
#include "ui_findpackage.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

FindPackage::FindPackage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPackage),
    model(new QSqlQueryModel()) // Initialize model in constructor
{
    ui->setupUi(this);
}

FindPackage::~FindPackage()
{
    qDebug() << "~ FindPackage()";
    delete ui;
    delete model;  // Make sure to delete the model in the destructor
}

void FindPackage::on_btnFindPackage_clicked()
{
    QString packageName = ui->txtfName->text();
    qDebug() << "Package Name: " << packageName;

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
    query.prepare("SELECT * FROM Package WHERE PackageName LIKE '%" + packageName + "%'");
    query.exec();

    qDebug() << "Last query: " << query.lastQuery();
    qDebug() << "Last error: " << query.lastError().text();

    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery(query);  // Use the model to execute the query
    ui->tableView->setModel(model);  // Set the model to the table view
    ui->tableView->setColumnWidth(0, 200);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 200);

    database.close();
}
