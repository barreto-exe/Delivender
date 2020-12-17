#include <iostream>
#include "persona.h"
#include "usuario.h"

using namespace std;

// Main de pruebas
int main()
{
    Persona pedrito("Pedro", "Lopez", "29907275", "0412-923421", time(0));
    time_t fecha = pedrito.getFechaNacimiento();

    Usuario user("pedrito123", "pedro@gg.com", "1234", pedrito);

    cout << pedrito.getNombre() << " " << pedrito.getApellido() << " " << pedrito.getCedula() << " " << pedrito.getTelefono() << " " << ctime(&fecha);

    cout << user.getUsuario() << " " << user.getPersona().getNombre() << endl;

    return 0;
}