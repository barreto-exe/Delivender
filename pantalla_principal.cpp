#include "pantalla_principal.h"
#include "ui_pantalla_principal.h"

pantalla_principal::pantalla_principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pantalla_principal)
{
    ui->setupUi(this);
}

pantalla_principal::~pantalla_principal()
{
    delete ui;
}
