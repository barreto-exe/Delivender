#ifndef PANTALLA_PRINCIPAL_H
#define PANTALLA_PRINCIPAL_H

#include <QWidget>
#include "tiendawidget.h"
#include "persona.h"
#include "global.h"

namespace Ui {
class pantalla_principal;
}

class pantalla_principal : public QWidget
{
    Q_OBJECT

public:
    explicit pantalla_principal(QWidget *parent = nullptr);
    ~pantalla_principal();
    void mostrarProveedores();

public slots:
    void mostrarTienda();
    void popupCantidad();
private slots:
    void on_btnAtras_clicked();

    void on_btnSiguiente_clicked();

private:
    Ui::pantalla_principal *ui;
};

#endif // PANTALLA_PRINCIPAL_H
