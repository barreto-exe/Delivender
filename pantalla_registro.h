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
    void on_pushButton_clicked();

    void on_atrasAdmin_clicked();

    void on_atrasTransp_clicked();

    void on_atrasRegistro_clicked();

private:
    Ui::pantalla_registro *ui;

signals:
    void AtrasCLick();
};

#endif // PANTALLA_REGISTRO_H
