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
    ui->fechaEntrega->setDate(QDate::currentDate());
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
                cant = QInputDialog::getInt(this,"Cantidad de productos a ordenar", "Nombre del Producto: " + boton->text() + "\nPrecio: " + QString::number(p.producto.getPrecio()) + "$\nDescripcion: " + QString::fromStdString(p.producto.getDescripcion()) + "\nCantidad disponible: " + QString::number(p.cantidad), 0, 0, p.cantidad);
                if (cant!=0){ //si la cantidad a comprar es distinta de 0
                    Global::solicitud.agregarProducto(Global::db.structProductoCantidad(p.producto, cant));  //el producto se añade al pedido
                    QMessageBox msgBox;
                    msgBox.setText("Producto agregado al carrito!");
                    msgBox.exec();
                }

                qDebug() << "productos en pedido: " + QString::number(Global::solicitud.getPedido().size());
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

    int i=0;
    float monto=0; //donde se guarda el total del pedido

    //Limpiando tabla
    ui->reciboTable->clearContents();
    ui->reciboTable->setRowCount(0);

    //Filas y columnas de la tabla
    ui->reciboTable->setRowCount(Global::solicitud.getPedido().size()+2);
    ui->reciboTable->setColumnCount(4);

    for (auto p : Global::solicitud.getPedido()){ //por cada producto en el pedido
        //Los añade a la tabla
        ui->reciboTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(p.producto.getNombre())));
        ui->reciboTable->setItem(i,1,new QTableWidgetItem(QString::number(p.cantidad)));
        ui->reciboTable->setItem(i,2,new QTableWidgetItem(QString::number(p.producto.getPrecio())));
        ui->reciboTable->setItem(i,3,new QTableWidgetItem(QString::number(p.cantidad*p.producto.getPrecio()) + "$"));
        i++;
        monto += p.cantidad*p.producto.getPrecio(); //va sumando los precios
    }
    //Ajustes de la tabla
    ui->reciboTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reciboTable->verticalHeader()->setVisible(false);
    //Muestra el total en la esquina de la tabla
    ui->reciboTable->setItem(i+1,0,new QTableWidgetItem("TOTAL"));
    ui->reciboTable->setItem(i+1,3,new QTableWidgetItem(QString::number(monto) + "$"));

    //Llena el combobox de tipos de pago
    ui->comboBoxPago->clear();
    ui->comboBoxPago->addItem("Seleccione un Método de Pago");
    vector<string> tiposPago = Global::db.listarTiposDePago(Global::proveedorSeleccionado);
    for (auto s : tiposPago){
        ui->comboBoxPago->addItem(QString::fromStdString(s));
    }
    ui->stackedWidget->setCurrentIndex(2);

}


void pantalla_principal::on_btnProcesarSolic_clicked()
{
    QMessageBox msgBox;
    QMessageBox::StandardButton confirmar;
    confirmar = QMessageBox::question(this,"Confirmar","¿Esta seguro que desea continuar? No podrá editar su solicitud luego");
    if (confirmar == QMessageBox::Yes){
        if (!ui->direccion->text().isEmpty() && ui->comboBoxPago->currentIndex()!=0){
            Global::solicitud.setDireccion(ui->direccion->text().toStdString());
            Global::solicitud.setTipoPago(ui->comboBoxPago->currentText().toStdString());
            Global::solicitud.setFechaPedido(QDate::currentDate());
            Global::solicitud.setFechaEntrega(ui->fechaEntrega->date());
            Global::solicitud.setEstatus("en espera");
            Global::solicitud.setProveedor(Global::proveedorSeleccionado);

            if(Global::db.registrarSolicitud(Global::solicitud)!=0){
                msgBox.setText("¡Solicitud procesada con éxito!");
                msgBox.exec();

                ui->stackedWidget->setCurrentIndex(0);

                //Limpiando inputs y solicitud anterior de var global
                Global::solicitud.clear();
                ui->direccion->setText("");
                ui->comboBoxPago->setCurrentIndex(0);
                ui->fechaEntrega->setDate(QDate::currentDate());
            }
        } else {
            msgBox.setText("Por favor, complete todos los datos para continuar");
            msgBox.exec();
        }
    }

}

void pantalla_principal::on_btnMisSolicitudes_clicked()
{
    vector<Solicitud> solicitudes = Global::db.listarSolicitudes();
    int i=0;
    //Limpia la tabla
    ui->solicitudesTable->clearContents();
    ui->solicitudesTable->setRowCount(0);

    //Filas y columnas de la tabla
    ui->solicitudesTable->setRowCount(solicitudes.size());
    ui->solicitudesTable->setColumnCount(4);

    for (auto s : solicitudes){ //por cada solicitud
        //Las añade a la tabla
        ui->solicitudesTable->setItem(i,0,new QTableWidgetItem(s.getFechaPedido().toString("dd / MM / yyyy")));
        ui->solicitudesTable->setItem(i,1,new QTableWidgetItem(QString::fromStdString(s.getProveedor().getNombre())));
        ui->solicitudesTable->setItem(i,2,new QTableWidgetItem(QString::fromStdString(s.getEstatus())));
        ui->solicitudesTable->setItem(i,3,new QTableWidgetItem(QString::number(s.getMonto()) + "$"));
        i++;
    }
    //Ajustes de la tabla
    ui->solicitudesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->solicitudesTable->verticalHeader()->setVisible(false);

    //cambia la pagina
    ui->stackedWidget->setCurrentIndex(3);
}

void pantalla_principal::on_btnAtrasSolic_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void pantalla_principal::on_btnAtrasMisSolic_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
