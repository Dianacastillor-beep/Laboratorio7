// Laboratorio7.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
using namespace std;

class CuentaBancaria {
private:
    string titular;
    double saldo;
    bool activa;
    int intentosFallidos;
    int mesesInactivo;

public:
    // 🔥 Constructor predeterminado agregado
    CuentaBancaria() {
        titular = "";
        saldo = 0;
        activa = false;
        intentosFallidos = 0;
        mesesInactivo = 0;
    }

    // 🔥 Constructor personalizado
    CuentaBancaria(string tit, double saldoInicial) {
        titular = tit;
        saldo = saldoInicial;
        activa = true;
        intentosFallidos = 0;
        mesesInactivo = 0;
    }

    void depositar(double monto) {
        if (!activa) {
            cout << "No se pueden hacer depositos. La cuenta esta bloqueada." << endl;
            return;
        }

        if (monto <= 0) {
            cout << "No se pueden hacer transacciones con montos negativos o cero." << endl;
            return;
        }

        saldo += monto;
        cout << "Deposito exitoso. Nuevo saldo: Q" << saldo << endl;

        mesesInactivo = 0;
    }

    void retirar(double monto) {
        if (!activa) {
            cout << "No se pueden hacer retiros. La cuenta esta bloqueada." << endl;
            return;
        }

        if (monto <= 0) {
            cout << "No se pueden hacer transacciones con montos negativos o cero." << endl;
            return;
        }

        if (monto > saldo) {
            intentosFallidos++;
            cout << "Saldo insuficiente. Intento fallido #" << intentosFallidos << endl;

            if (intentosFallidos >= 3) {
                activa = false;
                cout << "La cuenta ha sido bloqueada por intentos fallidos." << endl;
            }
            return;
        }

        saldo -= monto;
        cout << "Retiro exitoso. Nuevo saldo: Q" << saldo << endl;

        if (saldo < 100) {
            cout << "Advertencia: Su saldo está por debajo de Q100." << endl;
        }

        intentosFallidos = 0;
        mesesInactivo = 0;
    }

    void consultarSaldo() {
        cout << "Titular: " << titular << endl;
        cout << "Saldo: Q" << saldo << endl;
        cout << "Estado: " << (activa ? "Activa" : "Bloqueada") << endl;
        if (!activa) {
            cout << "Intentos fallidos: " << intentosFallidos << endl;
        }
    }

    void pasarMes() {
        mesesInactivo++;
        if (mesesInactivo >= 6) {
            activa = false;
            cout << "La cuenta ha sido bloqueada automaticamente por inactividad (6 meses)." << endl;
        }
    }

    string getTitular() {
        return titular;
    }
};

int main() {
    CuentaBancaria cuentas[10];  // 🔥 Ahora funciona porque hay un constructor predeterminado
    int opcion;
    double monto;
    int indiceCuenta = -1;
    int cuentasRegistradas = 0;

    do {
        cout << endl << "--- Menu ---" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Seleccionar cuenta" << endl;
        cout << "3. Depositar" << endl;
        cout << "4. Retirar" << endl;
        cout << "5. Consultar Saldo" << endl;
        cout << "6. Simular paso de un mes" << endl;
        cout << "7. Mostrar todas las cuentas" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (cuentasRegistradas >= 10) {
                cout << "No se pueden crear mas cuentas. Límite alcanzado." << endl;
                break;
            }

            string nombre;
            double saldoInicial;
            cout << "Ingrese el nombre del titular: ";
            cin.ignore(); // Para evitar errores con getline()
            getline(cin, nombre);

            cout << "Ingrese el saldo inicial: Q";
            cin >> saldoInicial;

            cuentas[cuentasRegistradas] = CuentaBancaria(nombre, saldoInicial);
            cout << "Cuenta creada exitosamente." << endl;

            if (indiceCuenta == -1) {
                indiceCuenta = cuentasRegistradas;
                cout << "Cuenta de " << cuentas[indiceCuenta].getTitular() << " seleccionada." << endl;
            }

            cuentasRegistradas++;
            break;
        }

        case 2: {
            if (cuentasRegistradas == 0) {
                cout << "No hay cuentas creadas. Cree una cuenta primero." << endl;
                break;
            }

            cout << "Cuentas disponibles:" << endl;
            for (int i = 0; i < cuentasRegistradas; i++) {
                cout << i + 1 << ". " << cuentas[i].getTitular() << endl;
            }

            cout << "Seleccione el numero de cuenta: ";
            int seleccion;
            cin >> seleccion;

            if (seleccion >= 1 && seleccion <= cuentasRegistradas) {
                indiceCuenta = seleccion - 1;
                cout << "Cuenta de " << cuentas[indiceCuenta].getTitular() << " seleccionada." << endl;
            }
            else {
                cout << "Numero de cuenta invalido." << endl;
            }
            break;
        }

        case 3:
            if (indiceCuenta == -1) {
                cout << "No hay cuenta seleccionada." << endl;
                break;
            }
            cout << "Ingrese monto a depositar: Q";
            cin >> monto;
            cuentas[indiceCuenta].depositar(monto);
            break;

        case 4:
            if (indiceCuenta == -1) {
                cout << "No hay cuenta seleccionada." << endl;
                break;
            }
            cout << "Ingrese monto a retirar: Q";
            cin >> monto;
            cuentas[indiceCuenta].retirar(monto);
            break;

        case 5:
            if (indiceCuenta == -1) {
                cout << "No hay cuenta seleccionada." << endl;
                break;
            }
            cuentas[indiceCuenta].consultarSaldo();
            break;

        case 6:
            if (indiceCuenta == -1) {
                cout << "No hay cuenta seleccionada." << endl;
                break;
            }
            cuentas[indiceCuenta].pasarMes();
            cout << "Ha pasado un mes." << endl;
            break;

        case 7:
            if (cuentasRegistradas == 0) {
                cout << "No hay cuentas creadas." << endl;
                break;
            }
            cout << "Lista de todas las cuentas:" << endl;
            for (int i = 0; i < cuentasRegistradas; i++) {
                cout << "--- Cuenta " << i + 1 << " ---" << endl;
                cuentas[i].consultarSaldo();
                cout << endl;
            }
            break;

        case 8:
            cout << "Gracias por utilizar nuestros servicios." << endl;
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 8);

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
