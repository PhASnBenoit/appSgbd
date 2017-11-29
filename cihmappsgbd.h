#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QStringListModel>
#include <QDebug>

namespace Ui {
class CIhmAppSgbd;
}

class CIhmAppSgbd : public QMainWindow
{
    Q_OBJECT

public:
    explicit CIhmAppSgbd(QWidget *parent = 0);
    ~CIhmAppSgbd();

private slots:
    void on_pbExtraire_clicked();
    void on_pbAjouter_clicked();
    void on_pbEffacer_clicked();
    void on_pbModifier_clicked();
    void onSelectLineList(QModelIndex mi);

private:
    Ui::CIhmAppSgbd *ui;
    QSqlDatabase db;
    QStringListModel *model;
};

#endif // MAINWINDOW_H
