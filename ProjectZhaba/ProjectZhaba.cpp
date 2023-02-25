#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
using namespace std;
struct Arr {
    int field[12][12];
    int coords[12][12];
    int mosquitto;
    int mosquittoCoord[12][12];

};

void play(int* a, int N, Arr& field);
void records();
void settings(int* a, int N);
void inputSettings(int* a, int N, int choose2);
void fieldGen(int* a, int N, Arr& field, int score);
void Control(int* a, int N, Arr& field, int score);
void endGame(int result, int score);

int main() {
    int move;
    struct Arr field;
    setlocale(LC_ALL, "RUSSIAN");
    int choose, N = 0;
    int a[2];
    // буфер для считавания данных из файла
    char buffer[256];
    // чтение из файла
    FILE* fp = fopen("mainMenu.txt", "r");
    if (fp) {
        // пока не дойдем до конца, считываем по 256 байт
        while ((fgets(buffer, 256, fp)) != NULL) {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    do {
        cout << "\n";
        cin >> choose;
        switch (choose) {
        case 1: cout << "*КВА*\n"; play(a, N, field);  break;
        case 2: cout << "*КВА*\n"; records();  break;
        case 3: cout << "*КВА*\n"; settings(a, N);  break;
        case 4: break;
        default: cout << "Ошибка ввода!\n";
        }
    } while ((choose != 1) && (choose != 2) && (choose != 3) && (choose != 4));

}

void play(int* a, int N, Arr& field) {
    FILE* ft;
    ft = fopen("settings.txt", "rt");
    fscanf(ft, "%d", &N);
    for (int i = 0; i < 2; i++)
        fscanf(ft, "%d", &a[i]);
    fclose(ft);
    srand(time(NULL));
    for (int i = 0; i < a[0]; i++) {
        for (int j = 0; j < a[1]; j++) {
            field.field[i][j] = rand() % (100 - 0 + 1) + 0;
            field.coords[i][j] = 0;
        }
    }
    field.field[0][0] = 0;
    field.coords[0][0] = 1;

    srand(time(NULL));
    field.mosquittoCoord[rand() % ((a[0] - 1) - 2 + 1) + 2][rand() % ((a[1] - 1) - 2 + 1) + 2] = 1;
    
    int score = 10 * (1000/ N);
    fieldGen(a, N, field, score);
}

void settings(int* a, int N) {
    int choose2;
    FILE* ft;
    ft = fopen("settings.txt", "rt");
    fscanf(ft, "%d", &N);
    for (int i = 0; i < 2; i++)
        fscanf(ft, "%d", &a[i]);
    fclose(ft);
    cout << "Количество ходов - " << N << "\n";
    cout << "Размер поля - " << a[0] << "x" << a[1] << "\n" << "*КВА*\n";
    cout << "1) Настроить количество ходов\n";
    cout << "2) Настроить размер поля\n";
    cout << "3) Выйти в меню\n";
    do {
        cin >> choose2;
        switch (choose2) {
        case 1: inputSettings(a, N, choose2); break;
        case 2: inputSettings(a, N, choose2); break;
        case 3: main(); break;
        default: cout << "Ошибка ввода!\n";
        }
    } while ((choose2 != 1) && (choose2 != 2) && (choose2 != 3));
}

void inputSettings(int* a, int N, int choose2) {
    if (choose2 == 1) {
        do {
            cout << "Введите кол-во ходов от 1 до 100\n";
            cin >> N;
            if ((N < 1) || (N > 100)) cout << "Ошибка ввода!\n";
        } while ((N < 1) || (N > 100));
    }
    if (choose2 == 2) {
        do {
            cout << "Введите размер поля (мин. 5х5; макс. 12х12)\n";
            cin >> a[0] >> a[1];
            if ((a[0] < 5) || (a[1] > 12) || (a[0] > 12) || (a[1] < 5)) cout << "Ошибка ввода!\n";
        } while ((a[0] < 5) || (a[1] > 12) || (a[0] > 12) || (a[1] < 5));
    }

    FILE* ft;
    ft = fopen("settings.txt", "w+");
    fprintf(ft, "%d\n", N);
    for (int i = 0; i < 2; i++) {
        fprintf(ft, "%d ", a[i]);
    }
    fclose(ft);
    settings(a, N);
}

void records() {
    int num;
    FILE* ft;
    ft = fopen("score.txt", "rt");
    fscanf(ft, "%d", &num);
    cout << "Последний рекорд - " << num <<"\n";
    fclose(ft);
    main();
}

void fieldGen(int* a, int N, Arr& field, int score) {
    int countX = 0;
    int countY = 0;
    int countXX = 0;
    for (int i = 0; i < a[0]; i++) {
        for (int j = 0; j < a[1]; j++) {
            if ((i == 0)) {
                cout << "     " << countX << "   ";
                countX++;
            }
        }
        if (i == 0) cout << "\n";
        for (int j = 0; j < a[1]; j++) {
            if (j == 0) cout << "   _______ ";
            else cout << " _______ ";
        }
        cout << "\n";
        int countXY = 0;
        for (int i = 0; i < 3; i++) {
            countXY = 0;
            for (int j = 0; j < a[1]; j++) {
                if (field.field[countXX][countXY] < 41) {
                    if ((j == 0) && (i == 1) && (countY < 10)) {
                        if (field.coords[countXX][countXY] == 1) {
                            cout << countY << " |  Frog |";
                            countY += 1;
                        }
                        else if (field.mosquittoCoord[countXX][countXY] == 1) {
                            cout << countY << " |  <*>  |";
                            countY += 1;
                        }
                        else {
                            cout << countY << " |       |";
                            countY += 1;
                        }
                    }
                    else if ((j == 0) && (i == 1) && (countY > 9)) {
                        if (field.coords[countXX][countXY] == 1) {
                            cout << countY << "|  Frog |";
                            countY += 1;
                        }
                        else if (field.mosquittoCoord[countXX][countXY] == 1) {
                            cout << countY << "|  <*>  |";
                            countY += 1;
                        }
                        else {
                            cout << countY << "|       |";
                            countY += 1;
                        }
                    }
                    if ((j == 0) && (i != 1)) cout << "  |       |";
                    if ((j != 0)&&(field.coords[countXX][countXY]== 1)&&(i == 1)){ cout << "|  Frog |"; }
                    else if ((j != 0) && (field.mosquittoCoord[countXX][countXY] == 1) && (i == 1)) { cout << "|  <*>  |"; }
                    else if (j != 0)  cout << "|       |";
                }
                else if (field.field[countXX][countXY] > 40) {
                    if ((j == 0) && (i == 1) && (countY < 10)) {
                        if (field.mosquittoCoord[countXX][countXY] == 1) {
                            cout << countY << " | ~<*>~ |";
                            countY += 1;
                        }
                        else {
                            cout << countY << " | ~~~~~ |";
                            countY += 1;
                        }
                    }
                    else if ((j == 0) && (i == 1) && (countY > 9)) {
                        if (field.mosquittoCoord[countXX][countXY] == 1) {
                            cout << countY << "| ~<*>~ |";
                            countY += 1;
                        }
                        else {
                            cout << countY << "| ~~~~~ |";
                            countY += 1;
                        }
                    }
                    if ((j == 0) && (i != 1)) cout << "  | ~~~~~ |";
                    else if ((j != 0) && (field.mosquittoCoord[countXX][countXY] == 1) && (i == 1)) { cout << "| ~<*>~ |"; }
                    else if (j != 0)  cout << "| ~~~~~ |";
                }
                countXY += 1;
            }
            cout << "\n";
        }
        countXX += 1;
        for (int j = 0; j < a[1]; j++)
            if (j == 0) cout << "  |_______|";
            else cout << "|_______|";
        cout << "\n";
    }
    cout << "Кол-во ходов осталось: " << N - 1 << " Счёт: " << score <<  "\n";
    Control(a, N, field, score);
}

void Control(int* a, int N, Arr& field, int score){
    int control, diag;
    int coord;
    int frogCoord[2];
    int mosquttoCoords[2];
    for (int i = 0; i < a[0]; i++) {
        for (int j = 0; j < a[1]; j++) {
            if (field.coords[i][j] == 1) {
                frogCoord[0] = i; frogCoord[1] = j;
            }
        }
    }

    do {
        cout << "Выберите направление\n";
        cout << "1) Наверх\n2) Вниз\n";
        cout << "3) Налево\n4) Направо\n";
        cout << "5) По диагонали\n";
        cin >> control;
        if (control == 5) {
            do {
                cout << "1) Налево-вверх\n2) Налево-вниз\n";
                cout << "3) Направо-вверх\n4) Направо-вниз\n5) Назад\n";
                cin >> diag;
            if ((diag < 1)||(diag > 5)) cout << "Ошибка ввода!\n";
        } while ((diag < 1) || (diag > 5));
        if (diag == 5) { fieldGen(a, N, field, score); }
        }
        if ((control <1) || (control >6)) cout << "Ошибка ввода!\n";
    } while ((control < 1) || (control > 6));
    do {
        cout << "Введите длинну прыжка (Макс. 5)\n";
        cin >> coord;
        if ((coord < 1) || (coord > 5)) cout << "Ошибка ввода!\n";
    } while ((coord < 1) || (coord > 5));
    if ((control == 1) || (control == 3)) coord *= -1;
    //Наверх
    if ((control == 1) && (coord + frogCoord[0] >= 0)) {
        field.coords[frogCoord[0]][frogCoord[1]] = 0;
        frogCoord[0] = coord + frogCoord[0];
        field.coords[frogCoord[0]][frogCoord[1]] = 1;
    }//Вниз
    if ((control == 2) && (coord + frogCoord[0] < a[0])) {
        field.coords[frogCoord[0]][frogCoord[1]] = 0;
        frogCoord[0] = coord + frogCoord[0];
        field.coords[frogCoord[0]][frogCoord[1]] = 1;
    }//Налево
    if ((control == 3) && (coord + frogCoord[1] >= 0)) {
        field.coords[frogCoord[0]][frogCoord[1]] = 0;
        frogCoord[1] = coord + frogCoord[1];
        field.coords[frogCoord[0]][frogCoord[1]] = 1;
    }//Направо
    if ((control == 4) && (coord + frogCoord[1] < a[1])) {
        field.coords[frogCoord[0]][frogCoord[1]] = 0;
        frogCoord[1] = coord + frogCoord[1];
        field.coords[frogCoord[0]][frogCoord[1]] = 1;
    }//По диагонали
    if (control == 5) {//Налево-вверх
        if ((diag == 1) && (coord * -1 + frogCoord[0] >= 0) && (coord * -1 + frogCoord[1] >= 0)) {
            field.coords[frogCoord[0]][frogCoord[1]] = 0;
            frogCoord[0] = coord * -1 + frogCoord[0];
            frogCoord[1] = coord * -1 + frogCoord[1];
            field.coords[frogCoord[0]][frogCoord[1]] = 1;
        }//Налево-вниз
        if ((diag == 2) && (coord + frogCoord[0] < a[0]) && (coord * -1 + frogCoord[1] >= 0)) {
            field.coords[frogCoord[0]][frogCoord[1]] = 0;
            frogCoord[0] = coord + frogCoord[0];
            frogCoord[1] = coord * -1 + frogCoord[1];
            field.coords[frogCoord[0]][frogCoord[1]] = 1;
        }//Направо-вверх
        if ((diag == 3) && (coord * -1 + frogCoord[0] >= 0) && (coord + frogCoord[1] < a[1])) {
            field.coords[frogCoord[0]][frogCoord[1]] = 0;
            frogCoord[0] = coord * -1 + frogCoord[0];
            frogCoord[1] = coord + frogCoord[1];
            field.coords[frogCoord[0]][frogCoord[1]] = 1;
        }//Направо-вниз
        if ((diag == 4) && (coord + frogCoord[0] < a[0]) && (coord + frogCoord[1] < a[1])) {
            field.coords[frogCoord[0]][frogCoord[1]] = 0;
            frogCoord[0] = coord + frogCoord[0];
            frogCoord[1] = coord + frogCoord[1];
            field.coords[frogCoord[0]][frogCoord[1]] = 1;
        }
    }
    N = N - 1;
    score = score * (1- 0.05);
    if (field.field[frogCoord[0]][frogCoord[1]] > 40) {
        endGame(1, 0);
    }
    else if ((N >= 0) && (field.field[frogCoord[0]][frogCoord[1]] < 41)) {
        if (field.mosquittoCoord[frogCoord[0]][frogCoord[1]] == 1)
            endGame(0, score);
            srand(time(NULL));
            field.mosquitto = rand() % (8 - 1 + 1) + 1;
            for (int i = 0; i < a[0]; i++) {
                for (int j = 0; j < a[1]; j++) {
                    if (field.mosquittoCoord[i][j] == 1) {
                        mosquttoCoords[0] = i; mosquttoCoords[1] = j;
                    }
                }
            }
            int mosc[2] = { mosquttoCoords[0], mosquttoCoords[1] };
            if (field.mosquittoCoord[frogCoord[0]][frogCoord[1]] != 1) {
                switch (field.mosquitto) {// Наверх
                case 1: if (-1 + mosquttoCoords[0] >= 0) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = -1 + mosquttoCoords[0];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                } break;// Направо-вверх
                case 2: if ((-1 + mosquttoCoords[0] >= 0) && (1 + mosquttoCoords[1] < a[1])) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = -1 + mosquttoCoords[0];
                    mosquttoCoords[1] = 1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;// Направо
                case 3: if (1 + mosquttoCoords[1] < a[1]) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[1] = 1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;//Направо-вниз
                case 4: if ((1 + mosquttoCoords[0] < a[0]) && (1 + mosquttoCoords[1] < a[1])) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = 1 + mosquttoCoords[0];
                    mosquttoCoords[1] = 1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;// Вниз
                case 5: if (1 + mosquttoCoords[0] < a[0]) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = 1 + mosquttoCoords[0];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;//Налево-вниз
                case 6: if ((1 + mosquttoCoords[0] < a[0]) && (-1 + mosquttoCoords[1] >= 0)) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = 1 + mosquttoCoords[0];
                    mosquttoCoords[1] = -1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;//Налево
                case 7:if (-1 + mosquttoCoords[1] >= 0) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[1] = -1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;//Налево-вверх
                case 8: if ((-1 + mosquttoCoords[0] >= 0) && (-1 + mosquttoCoords[1] >= 0)) {
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 0;
                    mosquttoCoords[0] = -1 + mosquttoCoords[0];
                    mosquttoCoords[1] = -1 + mosquttoCoords[1];
                    field.mosquittoCoord[mosquttoCoords[0]][mosquttoCoords[1]] = 1;
                }break;
                }
            }
    }
    if ((N == 0)&& (field.mosquittoCoord[frogCoord[0]][frogCoord[1]] != 1)&& (field.field[frogCoord[0]][frogCoord[1]] < 41)) endGame(2, 0);
    if ((N>0)&&((field.mosquittoCoord[frogCoord[0]][frogCoord[1]] != 1)&& (field.field[frogCoord[0]][frogCoord[1]] < 41))) { cout << "*КВА*\n";  fieldGen(a, N, field, score); }
}

void endGame(int result, int score) {
    int choose;
    if (result == 1) { cout << "*БУЛЬК*\nВы забыли, что не умеете плавать\n"; cout << "ВЫ ПРОИГРАЛИ!!!\n"; }
    if (result == 2) { cout << "Вы устали раньше чем успели съесть комара\n"; cout << "ВЫ ПРОИГРАЛИ!!!\n"; }
    if (result != 0) {
        // буфер для считавания данных из файла
        char buffer[256];
        // чтение из файла
        FILE* fp = fopen("Defeat.txt", "r");
        if (fp) {
            // пока не дойдем до конца, считываем по 256 байт
            while ((fgets(buffer, 256, fp)) != NULL) {
                printf("%s", buffer);
            }
            fclose(fp);
        }
    }
    if (result == 0) {
        // буфер для считавания данных из файла
        char buffer[256];
        // чтение из файла
        FILE* fp = fopen("victory.txt", "r");
        if (fp) {
            // пока не дойдем до конца, считываем по 256 байт
            while ((fgets(buffer, 256, fp)) != NULL) {
                printf("%s", buffer);
            }
            fclose(fp);
        }
        cout << "\n*ХРУМ*\n" << "Вы победили!!!\n";
        do {
            cout << "Сохранить рекорд?\n1) Да\n2) Нет\n";
            cin >> choose;
            if ((choose < 1) || (choose > 2)) cout << "Ошибка ввода!\n";
        } while ((choose < 1) || (choose > 2));
        if (choose == 1) {
            FILE* ft;
            ft = fopen("score.txt", "w+");
            fprintf(ft, "%d\n", score);
            fclose(ft);
        }
    }
            
}