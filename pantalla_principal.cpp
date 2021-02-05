#include "pantalla_principal.h"
#include "ui_pantalla_principal.h"
#include <QDebug>
#include "tiendawidget.h"
#include "global.h"
#include <QPushButton>
#include <QInputDialog>


pantalla_principal::pantalla_principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_principal)
{
    ui->setupUi(this);
    mostrarProveedores();
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(mostrarTienda()));


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
    while (i.hasNext()){
        Proveedor infoProv = i.next();
        qDebug() << "Nombre proveedor: "<< QString::fromStdString(infoProv.getNombre()) << " Descripcion: " << QString::fromStdString(infoProv.getDescripcion());
        ui->provLayout->addWidget(new tiendaWidget(this,&infoProv),j,k,1,1);
        k++;
        if (k==3){
            j++;
            k=0;
        }
    }

}

void pantalla_principal::mostrarTienda(){
    Proveedor proveedor = Global::proveedorSeleccionado;
    ui->provNombre->setText(QString::fromStdString(proveedor.getNombre()));
    QVector<producto_cantidad> lista = QVector<producto_cantidad>::fromStdVector(proveedor.getAlmacen());
    if (proveedor.getAlmacen().empty()){
        qDebug() << "aqui no hay nada mi pana";
    } else {
        qDebug() << "aqui si hay algo mi pana";
    }
    QVectorIterator<producto_cantidad> i(lista);
    int j=0, k=0;
    while (i.hasNext()){
        producto_cantidad p = i.next();
        qDebug() << QString::fromStdString(p.producto.getNombre());
        QPushButton *boton = new QPushButton(this);
        boton->setText(QString::fromStdString(p.producto.getNombre()));
        boton->setStyleSheet("border: none; background-color: rgb(226, 226, 226); color: rgb(200, 162, 200); text-align: center; text-decoration: none; font-size:14px; font: 75 13pt \"Quicksand Bold\";");
        connect(boton, SIGNAL(clicked(bool)), this, SLOT(popupCantidad()));
        ui->productLayout->addWidget(boton,j,k,1,1);
        //boton->show();
        k++;
        if (k==3){
            j++;
            k=0;
        }
    }
}

void pantalla_principal::popupCantidad(){
    QPushButton *boton = qobject_cast<QPushButton*>(sender());
    if (boton!=NULL){
        Proveedor proveedor = Global::proveedorSeleccionado;
        ui->provNombre->setText(QString::fromStdString(proveedor.getNombre()));
        QVector<producto_cantidad> lista = QVector<producto_cantidad>::fromStdVector(proveedor.getAlmacen());
        QVectorIterator<producto_cantidad> i(lista);
        while (i.hasNext()){
            producto_cantidad p = i.next();
            if (boton->text() == QString::fromStdString(p.producto.getNombre())){
                p.cantidad = QInputDialog::getInt(this,"Ingrese la cantidad de productos a ordenar", "Producto: " + boton->text());
                Global::pedido.push_back(p);
            }
        }
    }
}


