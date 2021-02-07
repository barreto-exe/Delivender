#ifndef PANTALLA_PROVEEDOR_H
#define PANTALLA_PROVEEDOR_H

#include <QWidget>

namespace Ui {
class pantalla_proveedor;
}

class pantalla_proveedor : public QWidget
{
    Q_OBJECT

public:
    explicit pantalla_proveedor(QWidget *parent = nullptr);
    ~pantalla_proveedor();

private slots:
    void on_btnAddProducto_clicked();

    void on_btnAddMetPago_clicked();

    void on_btnRegistrarProd_clicked();

    void on_btnAtrasAddProd_clicked();

private:
    Ui::pantalla_proveedor *ui;
};

#endif // PANTALLA_PROVEEDOR_H
