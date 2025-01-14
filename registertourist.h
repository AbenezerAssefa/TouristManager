#ifndef REGISTERTOURIST_H
#define REGISTERTOURIST_H

#include <QDialog>
#include "databaseheader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class RegisterTourist;
}

class RegisterTourist : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterTourist(QWidget *parent = nullptr);
    ~RegisterTourist();

private slots:
   // Slot for ComboBox change
    void on_btnSave_clicked();            // Slot for Save button

private:
    Ui::RegisterTourist *ui;
    QSqlDatabase database;
    // QSqlQueryModel *modal;
};

#endif // REGISTERTOURIST_H
