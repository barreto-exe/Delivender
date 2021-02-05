#ifndef TIENDAWIDGET_H
#define TIENDAWIDGET_H

#include <QWidget>
#include <string>
#include "proveedor.h"
#include "global.h"

using std::string;

namespace Ui {
class tiendaWidget;
}

class tiendaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tiendaWidget(QWidget *parent = nullptr, Proveedor *proveedor = nullptr);
    ~tiendaWidget();

private slots:
    void on_btnNombre_clicked();

private:
    Ui::tiendaWidget *ui;
    Proveedor proveedor;
};

#endif // TIENDAWIDGET_H
