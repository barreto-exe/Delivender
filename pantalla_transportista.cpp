#include "pantalla_transportista.h"
#include "ui_pantalla_transportista.h"
#include "global.h"
#include "persona.h"
#include <QMessageBox>
#include <entregawidget.h>

pantalla_transportista::pantalla_transportista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_transportista)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

pantalla_transportista::~pantalla_transportista()
{
    delete ui;
}

void pantalla_transportista::cargarInfoTransp(){

    vector<Solicitud> entregas = Global::db.listarEntregasPendientes();
    for(auto e : entregas){
        entregaWidget *widget = new entregaWidget(this,&e,false);
        ui->entregasLayout->addWidget(widget);
        connect(widget,SIGNAL(entregada(entregaWidget*)), this, SLOT(cambiarLayout(entregaWidget*)));
    }

    vector<Solicitud> realizadas = Global::db.listarEntregasRealizadas();
    for(auto e : realizadas){
        ui->realizadasLayout->addWidget(new entregaWidget(this,&e,true));
    }
}

void pantalla_transportista::cambiarLayout(entregaWidget *widget){
    ui->realizadasLayout->addWidget(widget);
    ui->entregasLayout->removeWidget(widget);
}
