#include "tiendawidget.h"
#include "ui_tiendawidget.h"

tiendaWidget::tiendaWidget(QWidget *parent, string nombre, string descripcion) :
    QWidget(parent),
    ui(new Ui::tiendaWidget)
{
    ui->setupUi(this);
    ui->nombre->setText(QString::fromStdString(nombre));
    ui->descripcion->setText(QString::fromStdString(descripcion));

}

tiendaWidget::~tiendaWidget()
{
    delete ui;
}
