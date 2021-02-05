#include "tiendawidget.h"
#include "ui_tiendawidget.h"
#include <QMessageBox>
#include <QStackedWidget>
#include <QDebug>

tiendaWidget::tiendaWidget(QWidget *parent, Proveedor *proveedor) :
    QWidget(parent),
    ui(new Ui::tiendaWidget)
{
    ui->setupUi(this);
    this->proveedor = *proveedor;
    ui->descripcion->setText(QString::fromStdString(this->proveedor.getDescripcion()));
    ui->btnNombre->setText(QString::fromStdString(this->proveedor.getNombre()));

}

tiendaWidget::~tiendaWidget()
{
    delete ui;
}

void tiendaWidget::on_btnNombre_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Proveedor: " + QString::fromStdString(proveedor.getNombre()));
    msgBox.exec();
    Global::proveedorSeleccionado = proveedor;
    ((QStackedWidget *)this->parentWidget()->parentWidget()->parentWidget())->setCurrentIndex(1);
}
