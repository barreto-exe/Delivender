#include "tiendawidget.h"
#include "ui_tiendawidget.h"
#include <QStackedWidget>

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
    Global::proveedorSeleccionado = proveedor;
    ((QStackedWidget *)this->parentWidget()->parentWidget()->parentWidget())->setCurrentIndex(1);
}
