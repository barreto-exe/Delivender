#ifndef PANTALLA_REGISTRO_H
#define PANTALLA_REGISTRO_H

#include <QWidget>

namespace Ui {
class pantalla_registro;
}

class pantalla_registro : public QWidget
{
    Q_OBJECT

public:
    explicit pantalla_registro(QWidget *parent = nullptr);
    ~pantalla_registro();

private slots:
    void on_btnAceptarPersona_clicked();

    void on_atrasProv_clicked();

    void on_atrasTransp_clicked();

    void on_atrasRegistroPersona_clicked();

    void on_btnCliente_clicked();

    void on_btnProveedor_clicked();

    void on_btnTransp_clicked();

private:
    Ui::pantalla_registro *ui;

signals:
    void AtrasCLick();
};

#endif // PANTALLA_REGISTRO_H
