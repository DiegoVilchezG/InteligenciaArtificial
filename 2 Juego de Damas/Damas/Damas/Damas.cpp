
#include <iostream>
#include <conio.h>
#include <ctime>
#include<vector>
using namespace std;

class Damas
{
public:
    int** arr;
    bool game;
    int turno;
    int nivel;
    Damas(int n, int t);
    ~Damas();
    void print(int);
    int Xs();
    int Os();
    vector<vector<int>> Movimientos(int, int);
    vector<vector<int>> MovimientosE(int, int);
    void Comparacion();
    void Game();
    vector<vector<int>> PosicionesO(int val);
    vector<vector<vector<int>>> Destinos(vector<vector<int>> P, int val);
    int minimax(int n, int jug);
    void IAmove(int jug);
};
Damas::Damas(int n, int t) {
    arr = new int* [10];
    for (int i = 0; i < 10; i++)
        arr[i] = new int[10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            arr[i][j] = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1) {
                arr[i][j] = 1;
            }
        }
    }
    for (int i = 6; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 1) {
                arr[i][j] = 2;
            }
        }
    }
    //arr[4][5] = 2;
    //arr[5][6] = 1;
    game = true;
    turno = t;
    nivel = n;
}
Damas::~Damas() {
    for (int i = 0; i < 10; i++)
        delete[] arr[i];
    delete[] arr;
}
void Damas::print(int t) {
    cout << endl << "\t\t\t\t   Damas \t" << endl;
    cout << "\n \t\t    0   1   2   3   4   5   6   7   8   9";
    cout << "\n \t\t  -----------------------------------------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << " \t\t" << i << " |";
        for (int j = 0; j < 10; j++) {
            //cout << " " << *(*(arr + i) + j) << " |"; 
            if (*(*(arr + i) + j) == 1) { cout << " X |"; }
            else if (*(*(arr + i) + j) == 2) { cout << " O |"; }
            else { cout << " " << "  |"; }
        }
        cout << "\n  \t\t  -----------------------------------------" << endl;
    }
    if (t == 1) { cout << " Turno Jugador " << t << "(X) : "; }
    else { cout << " Turno Jugador " << t << "(O) : "; }
}
int Damas::Xs() {
    int val = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (arr[i][j] == 1) { val++; }
        }
    }
    return val;
}
int Damas::Os() {
    int val = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (arr[i][j] == 0) { val++; }
        }
    }
    return val;
}
vector<vector<int>> Damas::Movimientos(int f, int c) { //Posibles movimientos
    vector<vector<int>> M;
    //Por der
    vector<int> m(2);
    int f1, c1;
    f1 = f + 1;
    if (f1 != 10) {
        c1 = c + 1;
        if (c1 != 10) {
            //cout << " 1:  p: " << f << " " << c << " d:" << f1 << " " << c1 << "\n ";
            if (arr[f1][c1] == 0) {
                m[0] = f1;
                m[1] = c1;
                M.push_back(m);
            }
            else if (arr[f1][c1] == 2) {
                f1 += 1;
                c1 += 1;
                if (f1 != 10 && c1 != 10 && arr[f1][c1] == 0) {
                    m[0] = f1;
                    m[1] = c1;
                    M.push_back(m);
                }
            }
        }
        //Por izq
        f1 = f + 1;
        c1 = c - 1;
        if (c1 >= 0) {
            if (arr[f1][c1] == 0) {
                m[0] = f1;
                m[1] = c1;
                M.push_back(m);
            }
            else if (arr[f1][c1] == 2) {
                f1 += 1;
                c1 -= 1;
                if (f1 != 10 && c1 >= 0 && arr[f1][c1] == 0) {
                    m[0] = f1;
                    m[1] = c1;
                    M.push_back(m);
                }
            }
        }
    }
    return M;
}
vector<vector<int>> Damas::MovimientosE(int f, int c) { //Posibles movimientos
    vector<vector<int>> M;
    //Por der
    vector<int> m(2);
    int f1, c1;
    f1 = f - 1;
    if (f1 != 0) {
        c1 = c + 1;
        if (c1 != 0) {
            //cout << " 2:  p: "<< f << " " << c << " d:" << f1 << " " << c1 << "\n ";
            if (arr[f1][c1] == 0) {
                m[0] = f1;
                m[1] = c1;
                M.push_back(m);
            }
            else if (arr[f1][c1] == 1) {
                f1 -= 1;
                c1 += 1;
                if (f1 >= 0 && c1 != 10 && arr[f1][c1] == 0) {
                    m[0] = f1;
                    m[1] = c1;
                    M.push_back(m);
                }
            }
        }
        //Por izq
        f1 = f - 1;
        c1 = c - 1;
        if (c1 >= 0) {
            if (arr[f1][c1] == 0) {
                m[0] = f1;
                m[1] = c1;
                M.push_back(m);
            }
            else if (arr[f1][c1] == 1) {
                f1 -= 1;
                c1 -= 1;
                if (f1 >= 0 && c1 >= 0 && arr[f1][c1] == 0) {
                    m[0] = f1;
                    m[1] = c1;
                    M.push_back(m);
                }
            }
        }
    }
    return M;
}
void Damas::Comparacion() {
    cout << " Felicidades xd" << endl;
}
void Damas::Game() {
    int f, c;
    int f1, c1;
    while (game) {
        if (true) {
            print(turno);
            cout << "\n Ingrese posicion de fila ficha a usar: ";
            cin >> f;
            cout << " Ingrese posicion de columna ficha a usar: ";
            cin >> c;
            system("cls");
            vector<vector<int>> M;
            bool Mval = false;
            while (!Mval) {
                while (arr[f][c] != 1) {
                    print(turno);
                    cout << " Por favor ingrese solamente posiciones de sus fichas: ";
                    cout << "\n Ingrese posicion de fila ficha: ";
                    cin >> f;
                    cout << " Ingrese posicion de columna ficha: ";
                    cin >> c;
                    system("cls");
                }
                if (turno == 1) { M = Movimientos(f, c); }
                else { M = MovimientosE(f, c); }
                if (M.size() != 0) {
                    Mval = true;
                }
                else {
                    print(turno);
                    cout << " Por favor ingrese solamente fichas movibles: ";
                    cout << "\n Ingrese posicion de fila ficha: ";
                    cin >> f;
                    cout << " Ingrese posicion de columna ficha: ";
                    cin >> c;
                    system("cls");
                }
            }
            f1 = f;
            c1 = c;
            //system("cls");
            Mval = false;
            print(turno);
            cout << " Ficha seleccionada: [" << f1 << "][" << c1 << "]";
            cout << "\n Ingrese posicion de fila a mover: ";
            cin >> f;
            cout << " Ingrese posicion de columna a mover: ";
            cin >> c;
            for (int i = 0; i < M.size(); i++) {
                cout << M[i][0] << " " << M[i][1] << "\n";
                if (M[i][0] == f && M[i][1] == c) {
                    Mval = true;
                }
            }
            while (!Mval) {
                print(turno);
                cout << " Ficha seleccionada: [" << f1 << "][" << c1 << "]";
                cout << "\n Por favor ingrese solamente posiciones validas para mover ";
                cout << "\n Ingrese posicion de fila: ";
                cin >> f;
                cout << " Ingrese posicion de columna: ";
                cin >> c;
                for (int i = 0; i < M.size(); i++) {
                    if (M[i][0] == f && M[i][1] == c) {
                        Mval = true;
                    }
                }
                system("cls");
            }
            swap(arr[f1][c1], arr[f][c]);
            system("cls");
            if (c1 - c == 2 || c1 - c == -2) {
                arr[(f + f1) / 2][(c + c1) / 2] = 0;
            }
            IAmove(2);
        }
    }
}
vector<vector<int>> Damas::PosicionesO(int val) {
    vector<vector<int>> Pos;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; ++j) {
            if (arr[i][j] == val) {
                vector<int> m(2);
                m[0] = i; m[1] = j;
                Pos.push_back(m);
            }
        }
    }
    return Pos;
}
vector<vector<vector<int>>> Damas::Destinos(vector<vector<int>> Pos, int val) {
    vector<vector<vector<int>>> Des;
    for (int i = 0; i < Pos.size(); ++i) {
        vector<vector<int>> Mov;
        if (val == 2) { Mov = MovimientosE(Pos[i][0], Pos[i][1]); }
        else { Mov = Movimientos(Pos[i][0], Pos[i][1]); }
        Des.push_back(Mov);
    }
    return Des;
}
int Damas::minimax(int n, int jug) {
    if (n <= 0) { return Os() - Xs(); }
    int movimiento = -1;
    vector<int> mov(2);
    int puntuacion = -2; // Perder los movimientos son preferibles a ningún movimiento
    int val;
    if (jug == 2) { val = Os() - Xs(); }
    else { val = Xs() - Os(); }
    vector<vector<int>> Pos = PosicionesO(jug);
    vector<vector<vector<int>>> Des = Destinos(Pos, jug);
    int p = 0;
    for (int i = 0; i < Des.size(); ++i) {
        int pf = Pos[i][0];
        int pc = Pos[i][1];
        for (int j = 0; j < Des[i].size(); ++j) {
            int df = Des[i][j][0];
            int dc = Des[i][j][1];
            swap(arr[pf][pc], arr[df][dc]);
            if (dc - pc == 2 || dc - pc == -2) { arr[(df + pf) / 2][(dc + pc) / 2] = 0; } //Si comes ficha
            int thispuntuacion = -minimax(--n, 1 + (jug % 2));
            if (thispuntuacion > puntuacion) {
                puntuacion = thispuntuacion;
                p = i;
                mov[0] = df;
                mov[1] = dc;
            }
            swap(arr[pf][pc], arr[df][dc]);
            if (dc - pc == 2 || dc - pc == -2) { arr[(df + pf) / 2][(dc + pc) / 2] = jug % 2; } //Devolver al estado

        }
    }
    return val;
}

void Damas::IAmove(int jug) {
    //int puntuacion = Os() - Xs();
    int puntuacion = 30;
    //
    print(1);
    vector<int> mov(2);
    vector<vector<int>> Pos = PosicionesO(jug);
    vector<vector<vector<int>>> Des = Destinos(Pos, jug);
    int p = 0;
    for (int i = 0; i < Des.size(); ++i) {
        int pf = Pos[i][0];
        int pc = Pos[i][1];
        for (int j = 0; j < Des[i].size(); ++j) {
            int df = Des[i][j][0];
            int dc = Des[i][j][1];
            swap(arr[pf][pc], arr[df][dc]);
            if (dc - pc == 2 || dc - pc == -2) { arr[(df + pf) / 2][(dc + pc) / 2] = 0; } //Si comes ficha
            int temppuntuacion = -minimax(nivel--, 1 + (jug % 2));
            if (dc - pc == 2 || dc - pc == -2) { arr[(df + pf) / 2][(dc + pc) / 2] = 1; } //Devolver al estado
            swap(arr[pf][pc], arr[df][dc]);
            if (temppuntuacion < puntuacion) {
                puntuacion = temppuntuacion;
                mov[0] = df;
                mov[1] = dc;
                p = i;
            }
        }
    }
    swap(arr[Pos[p][0]][Pos[p][1]], arr[mov[0]][mov[1]]);
    if (mov[1] - Pos[p][1] == 2 || mov[1] - Pos[p][1] == -2) { arr[(mov[0] + Pos[p][0]) / 2][(mov[1] + Pos[p][1]) / 2] = 0; } //Si comes ficha
}

int main()
{
    int a;
    cout << "Nivel de minimax: ";
    cin >> a;
    Damas A(a, 1);
    A.Game();
}