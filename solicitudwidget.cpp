#include "solicitudwidget.h"
#include "ui_solicitudwidget.h"
#include "global.h"
#include "transportista.h"
#include <QMessageBox>

solicitudWidget::solicitudWidget(QWidget *parent, Solicitud *s) :
    QWidget(parent),
    ui(new Ui::solicitudWidget)
{
    ui->setupUi(this);
    this->solicitud = *s;
    //Mostrando toda la info de la solicitud en el widget
    ui->nombreCliente->setText(QString::fromStdString(solicitud.getCliente().getNombre()));
    ui->direccion->setText(QString::fromStdString(solicitud.getDireccion()));
    ui->estatus->setText(QString::fromStdString(solicitud.getEstatus()));
    ui->monto->setText(QString::number(solicitud.getMonto()));
    vector<vehiculo_transportista> transportistas = Global::db.listarTransportistas();
    for (auto t : transportistas){
        ui->comboBoxTransp->addItem(QString::fromStdString(t.transportista.getNombre()) +
                                    " " + QString::fromStdString(t.transportista.getApellido())
                                    + " - " + QString::fromStdString(t.vehiculo.getTipo()));
        /*TODO: ver como verificar los transportistas despues porque aja*/
    }

}

solicitudWidget::~solicitudWidget()
{
    delete ui;
}

void solicitudWidget::on_btnAceptar_clicked()
{
    if(ui->comboBoxTransp->currentIndex()!=0){
        //Global::db.aprobarSolicitud(solicitud.getId());
        ui->btnAceptar->setEnabled(false);
        ui->btnRechazar->setEnabled(false);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Seleccione un transportista");
        msgBox.exec();
    }
}

void solicitudWidget::on_btnRechazar_clicked()
{
    //Global::db.rechazarSolicitud(solicitud.getId());
    this->deleteLater();
}
