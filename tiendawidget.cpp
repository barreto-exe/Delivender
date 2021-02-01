#include "tiendawidget.h"
#include "ui_tiendawidget.h"
#include <QMessageBox>

tiendaWidget::tiendaWidget(QWidget *parent, string nombre, string descripcion) :
    QWidget(parent),
    ui(new Ui::tiendaWidget)
{
    ui->setupUi(this);
    ui->descripcion->setText(QString::fromStdString(descripcion));
    ui->btnNombre->setText(QString::fromStdString(nombre));

}

tiendaWidget::~tiendaWidget()
{
    delete ui;
}

void tiendaWidget::on_btnNombre_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Holaa");
    msgBox.exec();
}
