#include "pantalla_principal.h"
#include "ui_pantalla_principal.h"
#include <QDebug>

pantalla_principal::pantalla_principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_principal)
{
    ui->setupUi(this);
    mostrarProveedores();
}

pantalla_principal::~pantalla_principal()
{
    delete ui;
}

void pantalla_principal::mostrarProveedores(){
    vector <Proveedor> proveedores = Global::db.listarProveedores();

    QVectorIterator<Proveedor> i(QVector<Proveedor>::fromStdVector(proveedores));
    /*while (i.hasNext()){
        ui->provLayout->addWidget(new tiendaWidget(this,i.next().getNombre(),i.next().getDescripcion()));
        i.next();
    }*/

}
