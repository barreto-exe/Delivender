#ifndef PANTALLA_TRANSPORTISTA_H
#define PANTALLA_TRANSPORTISTA_H

#include <QWidget>
#include <entregawidget.h>

namespace Ui {
class pantalla_transportista;
}

class pantalla_transportista : public QWidget
{
    Q_OBJECT

public:
    explicit pantalla_transportista(QWidget *parent = nullptr);
    ~pantalla_transportista();
public slots:
    void cargarInfoTransp();
    void cambiarLayout(entregaWidget *widget);
private:
    Ui::pantalla_transportista *ui;
};

#endif // PANTALLA_TRANSPORTISTA_H
