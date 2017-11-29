#include "cihmappsgbd.h"
#include "ui_cihmappsgbd.h"

CIhmAppSgbd::CIhmAppSgbd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppSgbd)
{
    QSqlError err;

    // init
    ui->setupUi(this);
    ui->lId->setVisible(false);
    model=NULL;

    // connexion à la bdd
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("bddFormation");
    db.setUserName("user");
    db.setPassword("user");
    bool ok = db.open();
    if (!ok) {
        err = db.lastError();
        qDebug() << err.text();
    } else
        qDebug() << "Connexion à la BDD " << ok;

    // click dans zone de liste
    connect(ui->lvTable, SIGNAL(clicked(QModelIndex)), this, SLOT(onSelectLineList(QModelIndex)));
}

CIhmAppSgbd::~CIhmAppSgbd()
{
    delete model;
    delete ui;
}

void CIhmAppSgbd::on_pbExtraire_clicked()
{
    if (model != NULL)
        delete model;
    model = new QStringListModel(this);
    QStringList liste;
    QSqlQuery q(db);
    q.exec("SELECT * FROM user ORDER BY nom");
    while (q.next()) {
        liste << q.value("login").toString();
    } // for
    model->setStringList(liste);
    ui->lvTable->setModel(model);
}

void CIhmAppSgbd::on_pbAjouter_clicked()
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO user VALUES (NULL, :name, :pname, :login, SHA1(:mdp))");
    q.bindValue(":name", ui->leNom->text());
    q.bindValue(":pname", ui->lePnom->text());
    q.bindValue(":login", ui->leLogin->text());
    q.bindValue(":mdp", ui->leMdp->text());
    q.exec();
    on_pbExtraire_clicked();
    ui->leNom->clear();
    ui->lePnom->clear();
    ui->leLogin->clear();
    ui->leMdp->clear();
}

void CIhmAppSgbd::on_pbEffacer_clicked()
{
    QSqlQuery q(db);
    q.prepare("DELETE FROM user WHERE id=:id");
    q.bindValue(":id", ui->lId->text());
    q.exec();
    on_pbExtraire_clicked();
    ui->leModifNom->clear();
    ui->leModifLogin->clear();
    ui->lId->clear();
}

void CIhmAppSgbd::on_pbModifier_clicked()
{
    QSqlQuery q(db);
    q.prepare("UPDATE user SET nom=:nom, login=:login WHERE id=:id");
    q.bindValue(":id", ui->lId->text().toInt());
    q.bindValue(":nom", ui->leModifNom->text());
    q.bindValue(":login", ui->leModifLogin->text());
    q.exec();
    on_pbExtraire_clicked();
}

void CIhmAppSgbd::onSelectLineList(QModelIndex mi)
{
  QSqlQuery q(db);
  q.prepare("SELECT * FROM user WHERE login=:login");
  q.bindValue(":login", mi.data().toString());
  q.exec();
  q.next();
  ui->leModifLogin->setText(q.value("login").toString());
  ui->leModifNom->setText(q.value("nom").toString());
  ui->lId->setText(q.value("id").toString());
}
