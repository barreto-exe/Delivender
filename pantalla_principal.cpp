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
    QVector<Proveedor> lista = QVector<Proveedor>::fromStdVector(proveedores);
    int j=0, k=0;
    QVectorIterator<Proveedor> i(lista);
    string nombre, descripcion;
    while (i.hasNext()){
        Proveedor a = i.next();
        nombre = a.getNombre();
        descripcion = a.getDescripcion();
        qDebug() << QString::fromStdString(nombre) << " Descrip: " << QString::fromStdString(descripcion);
        ui->provLayout->addWidget(new tiendaWidget(this,nombre,descripcion),j,k,1,1);
        k++;
        if (k==3){
            j++;
            k=0;
        }
    }

}
