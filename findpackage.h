#ifndef FINDPACKAGE_H
#define FINDPACKAGE_H

#include <QDialog>
#include <QSqlQueryModel> // Make sure this is included for the query model
#include "databaseheader.h"

namespace Ui {
class FindPackage;
}

class FindPackage : public QDialog
{
    Q_OBJECT

public:
    explicit FindPackage(QWidget *parent = nullptr);
    ~FindPackage();

private slots:
    void on_btnFindPackage_clicked();

private:
    Ui::FindPackage *ui;
    QSqlQueryModel *model;  // Declare the model as a pointer to QSqlQueryModel
};

#endif // FINDPACKAGE_H
