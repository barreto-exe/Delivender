#include "entregawidget.h"
#include "ui_entregawidget.h"
#include "global.h"
#include "persona.h"
#include <QMessageBox>

entregaWidget::entregaWidget(QWidget *parent, Solicitud *s, bool realizada) :
    QWidget(parent),
    ui(new Ui::entregaWidget)
{
    ui->setupUi(this);
    this->solicitud = *s;
    if(realizada){
        ui->btnAceptar->setEnabled(false);
    }
    ui->nombreCliente->setText(QString::fromStdString(solicitud.getCliente().getNombre()));
    ui->direccion->setText(QString::fromStdString(solicitud.getDireccion()));
    ui->estatus->setText(QString::fromStdString(solicitud.getEstatus()));
    ui->monto->setText(QString::number(solicitud.getMonto()));
}

entregaWidget::~entregaWidget()
{
    delete ui;
}

void entregaWidget::on_btnAceptar_clicked()
{
    QMessageBox msgBox;
    if(Global::db.realizarEntrega(solicitud)!=0){
        msgBox.setText("Se ha realizado la entrega!");
        this->deleteLater();
    } else {
        msgBox.setText("Intentelo nuevamente");
    }
    msgBox.exec();
}
