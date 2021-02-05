#include "pantalla_principal.h"
#include "ui_pantalla_principal.h"
#include <QDebug>
#include "tiendawidget.h"
#include "global.h"
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QSize>


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

    int j=0, k=0; //fila y columna del layout

    QVectorIterator<Proveedor> i(lista);
    while (i.hasNext()){ //mientras haya un proveedor en la lista
        Proveedor infoProv = i.next();
        qDebug() << "Nombre proveedor: "<< QString::fromStdString(infoProv.getNombre()) << " Descripcion: " << QString::fromStdString(infoProv.getDescripcion());
        ui->provLayout->addWidget(new tiendaWidget(this,&infoProv),j,k,1,1); //lo muestra en la pantalla
        k++;
        if (k==3){ //cambia la fila y la columna
            j++;
            k=0;
        }
    }

}

void pantalla_principal::mostrarTienda(){
    Proveedor proveedor = Global::proveedorSeleccionado; //toma el proveedor seleccionado de la variable global

    ui->provNombre->setText(QString::fromStdString(proveedor.getNombre())); //pone el nombre del proveedor en la pantalla
    ui->provDescripcion->setText(QString::fromStdString(proveedor.getDescripcion()));
    //obtiene el almacen del proveedor, transformado a QVector
    QVector<producto_cantidad> lista = QVector<producto_cantidad>::fromStdVector(proveedor.getAlmacen());
    QVectorIterator<producto_cantidad> i(lista);

    int j=0, k=0; //fila y columna del layout
    const QSize btnSize = QSize(125,75);
    while (i.hasNext()){ //mientras haya un producto en la lista
        producto_cantidad p = i.next();

        //crea el boton, lo personaliza y lo muestra en el layout
        QPushButton *boton = new QPushButton(this);
        boton->setFixedSize(btnSize);
        boton->setText(QString::fromStdString(p.producto.getNombre()));
        boton->setStyleSheet("border: none; background-color: rgb(226, 226, 226); color: rgb(200, 162, 200); text-align: center; text-decoration: none; font-size:14px; font: 75 13pt \"Quicksand Bold\";");
        connect(boton, SIGNAL(clicked(bool)), this, SLOT(popupCantidad())); //conecta la señal cuando se presiona el boton a popupCantidad
        ui->productLayout->addWidget(boton,j,k,1,1);
        k++;
        if (k==3){
            j++;
            k=0;
        }
    }
}

void pantalla_principal::popupCantidad(){
    QPushButton *boton = qobject_cast<QPushButton*>(sender()); //obtiene la info del boton del producto presionado

    if (boton!=NULL){
        //obtiene el almacen del proveedor seleccionado y busca entre sus producto uno igual al del boton
        Proveedor proveedor = Global::proveedorSeleccionado;
        QVector<producto_cantidad> lista = QVector<producto_cantidad>::fromStdVector(proveedor.getAlmacen());
        QVectorIterator<producto_cantidad> i(lista);

        while (i.hasNext()){
            producto_cantidad p = i.next();
            if (boton->text() == QString::fromStdString(p.producto.getNombre())){
                //si son iguales muestra la ventana del input
                int cant = 0;
                cant = QInputDialog::getInt(this,"Cantidad de productos a ordenar", "Nombre del Producto: " + boton->text() + "\nPrecio: " + QString::number(p.producto.getPrecio()) + "$\nDescripcion: " + QString::fromStdString(p.producto.getDescripcion()));
                if (cant!=0){ //si la cantidad a comprar es distinta de 0
                    p.cantidad = cant;
                    Global::pedido.push_back(p); //el producto se añade al pedido
                    QMessageBox msgBox;
                    msgBox.setText("Producto agregado al carrito!");
                    msgBox.exec();
                }

                qDebug() << "productos en pedido: " + QString::number(Global::pedido.size());
            }
        }
    }
}



void pantalla_principal::on_btnAtras_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void pantalla_principal::on_btnSiguiente_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
