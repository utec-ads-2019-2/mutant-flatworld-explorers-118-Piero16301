#include <bits/stdc++.h>

using namespace std;

int xWorld = 0, yWorld = 0;
vector <vector <int>> sombrasCoordenada;
vector <char> sombrasDireccion;

void moveFront(int &x, int &y, char direccion) {

    switch (direccion) {
        case 'N': {y++; break;}
        case 'S': {y--; break;}
        case 'E': {x++; break;}
        case 'W': {x--; break;}
    }

}

void girarDireccion(char &actual, char movimiento) {

    switch (actual) {
        case 'N': {
            if (movimiento == 'R') {
                actual = 'E';
            } else {
                actual = 'W';
            }
            break;
        }
        case 'S': {
            if (movimiento == 'R') {
                actual = 'W';
            } else {
                actual = 'E';
            }
            break;
        }
        case 'E': {
            if (movimiento == 'R') {
                actual = 'S';
            } else {
                actual = 'N';
            }
            break;
        }
        case 'W': {
            if (movimiento == 'R') {
                actual = 'N';
            } else {
                actual = 'S';
            }
            break;
        }
    }

}

map <int, pair <int, pair <char, string>>> calcularMovimiento(int x, int y, char dir, vector <char> direcciones) {

    map <int, pair <int, pair <char, string>>> resultado;
    bool saltarPaso = false, concatenar = false;
    int size = direcciones.size();
    int xTemp, yTemp;
    char direccionActual = dir;
    for (int i = 0; i < size; i++) {
        saltarPaso = false;
        concatenar = false;
        for (int j = 0; j < sombrasCoordenada.size(); j++) {
            if (concatenar) break;
            if ((sombrasCoordenada[j][0] == x) && (sombrasCoordenada[j][1] == y) && (sombrasDireccion[j] == direccionActual)) {
                saltarPaso = true;
                //cout << "Entrando sombra" << endl;
            }
        }
        if (saltarPaso) {
            concatenar = true;
            continue;
        }
        if (x > xWorld || y > yWorld || x < 0 || y < 0) {
            resultado[xTemp] = make_pair(yTemp, make_pair(direccionActual, "LOST"));
            vector <int> sombra_robot;
            sombra_robot.push_back(xTemp);
            sombra_robot.push_back(yTemp);
            sombrasCoordenada.push_back(sombra_robot);
            sombrasDireccion.push_back(direccionActual);
            return resultado;
        } else {
            if (direcciones[i] == 'F') {
                xTemp = x;
                yTemp = y;
                moveFront(x, y, direccionActual);
            } else {
                girarDireccion(direccionActual, direcciones[i]);
            }
        }
        if (x > xWorld || y > yWorld || x < 0 || y < 0) {
            resultado[xTemp] = make_pair(yTemp, make_pair(direccionActual, "LOST"));
            vector <int> sombra_robot;
            sombra_robot.push_back(xTemp);
            sombra_robot.push_back(yTemp);
            sombrasCoordenada.push_back(sombra_robot);
            sombrasDireccion.push_back(direccionActual);
            return resultado;
        }
        //cout << x << ' ' << y << ' ' << direccionActual << endl;
    }
    resultado[x] = make_pair(y, make_pair(direccionActual, "ALIVE"));
    return resultado;

}

int main() {

    int xInitial = 0, yInitial = 0;
    char direction = 'N';
    cin >> xWorld >> yWorld;
    while (scanf("%d %d %c", &xInitial, &yInitial, &direction) == 3) {
        char instrucciones[100];
        int i = 0;
        vector <char> direcciones;
        scanf("%s", &instrucciones);
        while (instrucciones[i]) {
            direcciones.push_back(instrucciones[i]);
            i++;
        }
        map <int, pair <int, pair <char, string>>> resultado = calcularMovimiento(xInitial, yInitial, direction, direcciones);
        for (auto itr = resultado.begin(); itr != resultado.end(); itr++) {
            cout << itr->first << ' ' << itr->second.first << ' ' << itr->second.second.first;
            if (itr->second.second.second == "LOST") {
                cout << ' ' << itr->second.second.second;
            }
            cout << endl;
        }
    }

    return 0;
    
}
