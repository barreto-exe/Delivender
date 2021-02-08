#include "pantalla_transportista.h"
#include "ui_pantalla_transportista.h"
#include "global.h"
#include "persona.h"
#include <QMessageBox>

pantalla_transportista::pantalla_transportista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_transportista)
{
    ui->setupUi(this);
}

pantalla_transportista::~pantalla_transportista()
{
    delete ui;
}

void pantalla_transportista::cargarInfoTransp(){

}
