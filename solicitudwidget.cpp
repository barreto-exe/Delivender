#include "solicitudwidget.h"
#include "ui_solicitudwidget.h"
#include "global.h"
#include "transportista.h"
#include <QMessageBox>
#include <QDebug>

solicitudWidget::solicitudWidget(QWidget *parent, Solicitud *s, bool realizada) :
    QWidget(parent),
    ui(new Ui::solicitudWidget)
{
    ui->setupUi(this);
    this->solicitud = *s;
    if(realizada){
        ui->btnAceptar->setEnabled(false);
        ui->btnAceptar->hide();
        ui->btnRechazar->setEnabled(false);
        ui->btnRechazar->hide();
        ui->comboBoxTransp->hide();
    }
    //Mostrando toda la info de la solicitud en el widget
    ui->nombreCliente->setText("Cliente: "+ QString::fromStdString(solicitud.getCliente().getNombre()) +
                               " " + QString::fromStdString(solicitud.getCliente().getApellido()));
    ui->direccion->setText("Direccion: "+QString::fromStdString(solicitud.getDireccion()));
    ui->estatus->setText("Estatus: "+QString::fromStdString(solicitud.getEstatus()));
    ui->monto->setText("Monto: "+QString::number(solicitud.getMonto()));
    vector<vehiculo_transportista> transportistas = Global::db.listarTransportistas();
    for (auto t : transportistas){
        ui->comboBoxTransp->addItem(QString::fromStdString(t.vehiculo.getPLaca())+
                                    " -" + QString::fromStdString(t.transportista.getNombre()) +
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
    QMessageBox msgBox;
    if(ui->comboBoxTransp->currentIndex()!=0){
        string transp = ui->comboBoxTransp->currentText().toStdString().c_str();
        string placa = transp.substr(0,transp.find(" "));
        if(Global::db.aprobarSolicitud(solicitud,placa.c_str())){
            emit aprobada(this);
            ui->btnAceptar->setEnabled(false);
            ui->btnAceptar->hide();
            ui->btnRechazar->setEnabled(false);
            ui->btnRechazar->hide();
            ui->comboBoxTransp->hide();
            ui->estatus->setText("Estatus: aprobada");

            msgBox.setText("Solicitud aprobada con éxito");
        } else {
            msgBox.setText("No se pudo aprobar la solicitud, intentelo nuevamente");
        }
    } else {
        msgBox.setText("Seleccione un transportista"); 
    }
    msgBox.exec();
}

void solicitudWidget::on_btnRechazar_clicked()
{
    QMessageBox msgBox;
    QMessageBox::StandardButton confirmar;
    confirmar = QMessageBox::question(this,"Confirmar","¿Esta seguro que desea rechazar esta solicitud?");
    if (confirmar == QMessageBox::Yes){
        if(Global::db.rechazarSolicitud(solicitud)){
            msgBox.setText("Solicitud rechazada con éxito");
            this->deleteLater();
        } else {
            msgBox.setText("No se pudo rechazar la solicitud, intentelo nuevamente");
        }
        msgBox.exec();
    }
}
