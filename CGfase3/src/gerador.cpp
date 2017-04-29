#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>

using namespace std;

fstream file;
//fstream patch;

float *pontosPatch(int *patches, int n_patches, float *control_points, int n_control_points, int nivel) {
    float coordenadas[48];
    float peso = 1.0 / nivel, *pontos = (float*)malloc(n_patches*(3 * (nivel + 1) ^ 2) * sizeof(float));
    float a, b, c, d;
    int i = 0, j = 0, k = 0, t = 0;

    for (t = 0; t < n_patches; t++) {

        a = 0.0;
        b = 1.0 - a;
        c = 0.0;
        d = 1.0 - c;

        // 1º ponto
        coordenadas[0] = control_points[3 * patches[16 * t]];
        coordenadas[1] = control_points[3 * patches[16 * t] + 1];
        coordenadas[2] = control_points[3 * patches[16 * t] + 2];
        // 2º ponto
        coordenadas[3] = control_points[3 * patches[16 * t + 1]];
        coordenadas[4] = control_points[3 * patches[16 * t + 1] + 1];
        coordenadas[5] = control_points[3 * patches[16 * t + 1] + 2];
        // 3º ponto
        coordenadas[6] = control_points[3 * patches[16 * t + 2]];
        coordenadas[7] = control_points[3 * patches[16 * t + 2] + 1];
        coordenadas[8] = control_points[3 * patches[16 * t + 2] + 2];
        // 4º ponto
        coordenadas[9] = control_points[3 * patches[16 * t + 3]];
        coordenadas[10] = control_points[3 * patches[16 * t + 3] + 1];
        coordenadas[11] = control_points[3 * patches[16 * t + 3] + 2];
        // 5º ponto
        coordenadas[12] = control_points[3 * patches[16 * t + 4]];
        coordenadas[13] = control_points[3 * patches[16 * t + 4] + 1];
        coordenadas[14] = control_points[3 * patches[16 * t + 4] + 2];
        // 6º ponto
        coordenadas[15] = control_points[3 * patches[16 * t + 5]];
        coordenadas[16] = control_points[3 * patches[16 * t + 5] + 1];
        coordenadas[17] = control_points[3 * patches[16 * t + 5] + 2];
        // 7º ponto
        coordenadas[18] = control_points[3 * patches[16 * t + 6]];
        coordenadas[19] = control_points[3 * patches[16 * t + 6] + 1];
        coordenadas[20] = control_points[3 * patches[16 * t + 6] + 2];
        // 8º ponto
        coordenadas[21] = control_points[3 * patches[16 * t + 7]];
        coordenadas[22] = control_points[3 * patches[16 * t + 7] + 1];
        coordenadas[23] = control_points[3 * patches[16 * t + 7] + 2];
        // 9º ponto
        coordenadas[24] = control_points[3 * patches[16 * t + 8]];
        coordenadas[25] = control_points[3 * patches[16 * t + 8] + 1];
        coordenadas[26] = control_points[3 * patches[16 * t + 8] + 2];
        // 10º ponto
        coordenadas[27] = control_points[3 * patches[16 * t + 9]];
        coordenadas[28] = control_points[3 * patches[16 * t + 9] + 1];
        coordenadas[29] = control_points[3 * patches[16 * t + 9] + 2];
        // 11º ponto
        coordenadas[30] = control_points[3 * patches[16 * t + 10]];
        coordenadas[31] = control_points[3 * patches[16 * t + 10] + 1];
        coordenadas[32] = control_points[3 * patches[16 * t + 10] + 2];
        // 12º ponto
        coordenadas[33] = control_points[3 * patches[16 * t + 11]];
        coordenadas[34] = control_points[3 * patches[16 * t + 11] + 1];
        coordenadas[35] = control_points[3 * patches[16 * t + 11] + 2];
        // 13º ponto
        coordenadas[36] = control_points[3 * patches[16 * t + 12]];
        coordenadas[37] = control_points[3 * patches[16 * t + 12] + 1];
        coordenadas[38] = control_points[3 * patches[16 * t + 12] + 2];
        // 14º ponto
        coordenadas[39] = control_points[3 * patches[16 * t + 13]];
        coordenadas[40] = control_points[3 * patches[16 * t + 13] + 1];
        coordenadas[41] = control_points[3 * patches[16 * t + 13] + 2];
        // 15º ponto
        coordenadas[42] = control_points[3 * patches[16 * t + 14]];
        coordenadas[43] = control_points[3 * patches[16 * t + 14] + 1];
        coordenadas[44] = control_points[3 * patches[16 * t + 14] + 2];
        // 16º ponto
        coordenadas[45] = control_points[3 * patches[16 * t + 15]];
        coordenadas[46] = control_points[3 * patches[16 * t + 15] + 1];
        coordenadas[47] = control_points[3 * patches[16 * t + 15] + 2];

        for (i = 0; i < nivel; i++) {
            for (j = 0; j < nivel; j++) {
                pontos[k++] = coordenadas[0] * a*a*a*c*c*c + coordenadas[3] * 3 * a*a*a*c*c*d + coordenadas[6] * 3 * a*a*a*c*d*d + coordenadas[9] * a*a*a*d*d*d
                              + coordenadas[12] * 3 * a*a*b*c*c*c + coordenadas[15] * 9 * a*a*b*c*c*d + coordenadas[18] * 9 * a*a*b*c*d*d + coordenadas[21] * 3 * a*a*b*d*d*d
                              + coordenadas[24] * 3 * a*b*b*c*c*c + coordenadas[27] * 9 * a*b*b*c*c*d + coordenadas[30] * 9 * a*b*b*c*d*d + coordenadas[33] * 3 * a*b*b*d*d*d
                              + coordenadas[36] * b*b*b*c*c*c + coordenadas[39] * 3 * b*b*b*c*c*d + coordenadas[42] * 3 * b*b*b*c*d*d + coordenadas[45] * b*b*b*d*d*d;

                pontos[k++] = coordenadas[1] * a*a*a*c*c*c + coordenadas[4] * 3 * a*a*a*c*c*d + coordenadas[7] * 3 * a*a*a*c*d*d + coordenadas[10] * a*a*a*d*d*d
                              + coordenadas[13] * 3 * a*a*b*c*c*c + coordenadas[16] * 9 * a*a*b*c*c*d + coordenadas[19] * 9 * a*a*b*c*d*d + coordenadas[22] * 3 * a*a*b*d*d*d
                              + coordenadas[25] * 3 * a*b*b*c*c*c + coordenadas[28] * 9 * a*b*b*c*c*d + coordenadas[31] * 9 * a*b*b*c*d*d + coordenadas[34] * 3 * a*b*b*d*d*d
                              + coordenadas[37] * b*b*b*c*c*c + coordenadas[40] * 3 * b*b*b*c*c*d + coordenadas[43] * 3 * b*b*b*c*d*d + coordenadas[46] * b*b*b*d*d*d;

                pontos[k++] = coordenadas[2] * a*a*a*c*c*c + coordenadas[5] * 3 * a*a*a*c*c*d + coordenadas[8] * 3 * a*a*a*c*d*d + coordenadas[11] * a*a*a*d*d*d
                              + coordenadas[14] * 3 * a*a*b*c*c*c + coordenadas[17] * 9 * a*a*b*c*c*d + coordenadas[20] * 9 * a*a*b*c*d*d + coordenadas[23] * 3 * a*a*b*d*d*d
                              + coordenadas[26] * 3 * a*b*b*c*c*c + coordenadas[29] * 9 * a*b*b*c*c*d + coordenadas[32] * 9 * a*b*b*c*d*d + coordenadas[35] * 3 * a*b*b*d*d*d
                              + coordenadas[38] * b*b*b*c*c*c + coordenadas[41] * 3 * b*b*b*c*c*d + coordenadas[44] * 3 * b*b*b*c*d*d + coordenadas[47] * b*b*b*d*d*d;

                c += peso;
                d = 1.0 - c;
            }
            a += peso;
            b = 1.0 - a;

            c = 0.0;
            d = 1.0 - c;
        }
        return pontos;
    }
}

// esta função recebe o ficheiro para o qual está a escrever e o nivel de tesselagem;
void read_patch(FILE *f_patch, int nivel) {
    int n_patches, n_control_points, i, j, m, aux, p = 0, *patches = NULL;
    float * points = NULL, *control_points = NULL, x, y, z;

    // lê a primeira linha do ficheiro f_patch e guarda o número para a variável n_patches;
    fscanf(f_patch, "%d\n", &n_patches);

    // aloca memória para as patches (n linhas, 16 por linha com tamanho int);
    patches = (int*)malloc(16 * n_patches * sizeof(int));

    // percorre cada linha
    for (i = 0; i < n_patches; i++) {
        // percorre cada indice da linha (16 no total)
        for (j = 0; j < 15; j++) {
            fscanf(f_patch, "%d, ", &aux);
            patches[p++] = aux;
        }
        fscanf(f_patch, "%d\n", &aux);
        patches[p++] = aux;
    }

    // lê numero de pontos de controlo
    fscanf(f_patch, "%d\n", &n_control_points);
    control_points = (float*)malloc(3 * n_control_points * sizeof(float));

    for (i = 0; fscanf(f_patch, "%f %f %f\n", &x, &y, &z) != EOF; i += 3) {
        control_points[i] = x;
        control_points[i + 1] = y;
        control_points[i + 2] = z;
    }

    //função pontosPatch
    points = pontosPatch(patches, n_patches, control_points, n_control_points, nivel);


    //imprimir pontos para o documento
    n_control_points = n_patches * (3 * (nivel + 1)*(nivel + 1));
    file << n_control_points << endl; // guarda número de pontos

    for (i = 0; i < n_control_points; i += 3) {
        file << points[i] << " " << points[i + 1] << " " << points[i + 2] << endl;
    }

    n_control_points = n_patches * nivel * nivel * 3 * 2;

    file << n_control_points << endl;

    m = (nivel + 1) ^ 2;

    for (i = 0; i < n_patches; i++) {
        for (j = 0; j < nivel; j++) {
            for (p = 0; p < nivel; p++) {
                file << i*m + j*(nivel + 1) + p << " " << i*m + j*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p << endl;
                file << i*m + j*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p << endl;
            }
        }
    }

}

void plano(float comprimento) {
    float m_comp = comprimento / 2;

    // Nº DE TRIANGULOS
    file << "2" << endl;

    file << -m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << m_comp << endl;

    file << m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << -m_comp << endl;
}

void planoVBO(float comprimento) {
    float m_comp = comprimento / 2;
    int i = 0;
    // 2 triângulos, cada um com 3 pontos, num total de 6 pontos (apesar de 2 serem repetidos).
    int n_pontos = 6;

    // com 6 pontos, cada um com 3 indices, temos 6x3 = 18 indices.
    int n_indices = 18;

    float *vertexB = (float*)malloc(n_pontos * sizeof(float));
    int * indices = (int*)malloc(n_indices * sizeof(int));

    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;
    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;
    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;

    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;
    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;
    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;

    /** inacabada, não sei como trabalhar com indices... Podemos não fazer com indices, mas então
      também não há grande motivo para fazer uma função nova visto que já temos os pontos todos.
      Apenas precisamos de adaptar o motor para trabalhar com VBO's. */
}

void caixa(float x, float y, float z, int dimensions) {
    double dim_x = x / dimensions, dim_y = y / dimensions, dim_z = z / dimensions;
    double ori_x = -x / 2, ori_y = -y / 2, ori_z = -z / 2; // origem x, y e z
    double xx = ori_x, yy = ori_y, zz = ori_z; // ponto "origem"

    file << 4 << endl;

    for (xx = ori_x; xx < (-ori_x); xx += dim_x) {
        //x2 = x1 + dim_x;

        for (yy = ori_y; yy < (-ori_y); yy += dim_y) {
            //y2 = y1 + dim_y;

            for (zz = ori_z; zz < (-ori_z); zz += dim_z) {
                //z2 = z1 + dim_z;

                if (xx == ori_x) {
                    //glColor3f(0.09 << " " << 0.5 << " " << 0.99 << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz + dim_z << endl;

                    //glColor3f(0.18 << " " << 0.5 << " " << 0.90 << endl;
                    file << xx << " " << yy + dim_y << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz + dim_z << endl;

                }

                if (yy == ori_y) {
                    //glColor3f(0.27 << " " << 0.5 << " " << 0.81 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz + dim_z << endl;

                    //glColor3f(0.36 << " " << 0.5 << " " << 0.73 << endl;
                    file << xx + dim_x << " " << yy << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                }

                if (zz == ori_z) {
                    //glColor3f(0.45 << " " << 0.5 << " " << 0.64 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;

                    //glColor3f(0.54 << " " << 0.5 << " " << 0.55 << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx + dim_x << " " << yy + dim_y << " " << zz << endl;
                }
            }
        }
    }

    for (xx = -ori_x; xx > ori_x; xx -= dim_x) {
        for (yy = -ori_y; yy > ori_y; yy -= dim_y) {
            for (zz = -ori_z; zz > ori_z; zz -= dim_z) {
                if (xx == -ori_x) {
                    //glColor3f(0.63 << " " << 0.63 << " " << 0.46 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz - dim_z << endl;

                    //glColor3f(0.72 << " " << 0.72 << " " << 0.37 << endl;
                    file << xx << " " << yy - dim_y << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;

                }

                if (yy == -ori_y) {
                    //glColor3f(0.81 << " " << 0.81 << " " << 0.28 << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy << " " << zz - dim_z << endl;

                    //glColor3f(0.9 << " " << 0.9 << " " << 0.19 << endl;
                    file << xx - dim_x << " " << yy << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz - dim_z << endl;
                }

                if (zz == -ori_z) {
                    //glColor3f(0.95 << " " << 0.95 << " " << 0.10 << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;

                    //glColor3f(0.99 << " " << 0.99 << " " << 0.01 << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                }
            }
        }
    }
}

/* esta função (juntamente com todas as outras que geram as figuras) tem de ser alterada para que escreva para um ficheiro os
pontos do VBO. Mas não tenho a certeza se precisa ser feito se não usarmos VBO's com indices... */
void esfera(float radius, int slices, int stacks) {
    int i, j; // iteradores
    double alpha1 = 0, alpha2 = 0; // angulo de cada fatia
    double beta1 = 0, beta2 = 0; // angulo de cada corte
    double alpha = (2 * M_PI) / slices; //
    double beta = -(M_PI) / stacks;

    //  Nº DE TRIANGULOS
    file << 2 * stacks*slices << endl;

    for (j = -stacks / 2; j < stacks / 2; j++) {
        beta1 = beta * j;
        beta2 = beta * (j + 1);
        double raio1 = radius * cos(beta1);
        double raio2 = radius * cos(beta2);

        for (i = 0; i < slices; i++) {
            alpha1 = alpha * i;
            alpha2 = alpha * (i + 1);
            // 1º triangulo 
            file << raio1 * sin(alpha1) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha1) << endl;
            file << raio2 * sin(alpha1) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha1) << endl;
            file << raio1 * sin(alpha2) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha2) << endl;
            // 2º triangulo
            file << raio2 * sin(alpha2) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha2) << endl;
            file << raio1 * sin(alpha2) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha1) << endl;
        }
    }
}

void cone(float radius, float height, int slices, int stacks) {
    int i, j; // iteradores
    double altura2 = 0, altura1 = 0; // altura de cada base
    double alpha1 = 0, alpha2 = 0; // angulo de cada fatia
    double alpha = (2 * M_PI) / slices; //
    double stack_height = height / stacks;
    double raio2, raio1 = radius;

    // Nº DE TRIANGULOS
    file << stacks*slices * 2 + slices << endl;

    for (j = 0; j < stacks; j++) {
        altura2 += stack_height;
        raio1 = radius - radius * ((float)j / stacks);
        raio2 = radius - radius * ((float)(j + 1) / stacks);

        for (i = 0; i < slices; i++) {
            alpha1 = alpha * i;
            alpha2 = alpha * (i + 1);


            if (j == 0) {
                file << 0.0 << " " << 0.0 << " " << 0.0 << endl;
                file << raio1 * sin(alpha2) << " " << 0.0 << " " << raio1 * cos(alpha2) << endl;
                file << raio1 * sin(alpha1) << " " << 0.0 << " " << raio1 * cos(alpha1) << endl;
            }

            file << raio1 * sin(alpha1) << " " << altura1 << " " << raio1 * cos(alpha1) << endl;
            file << raio1 * sin(alpha2) << " " << altura1 << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << altura2 << " " << raio2 * cos(alpha1) << endl;

            file << raio1 * sin(alpha2) << " " << altura1 << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha2) << " " << altura2 << " " << raio2 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << altura2 << " " << raio2 * cos(alpha1) << endl;
        }
        altura1 = altura2;
    }
}

int main(int argc, char **argv) {
    FILE *patch = NULL;
    if (argc > 1) {
        /* Só para quando está em debug
        string caminho = "../../motor/";
        */
        string caminho = "../motor/";

        if (argv[1] == string("plane")) {
            if (argc == 4) {
                file.open(caminho + argv[3], std::fstream::out);
                plano(atoi(argv[2]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- comprimento" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("box")) {

            if (argc == 6) {
                file.open(caminho + argv[5], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), 1);
            }
            else if (argc == 7) {
                file.open(caminho + argv[6], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), atoi(argv[5]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- Tamanho X" << endl;
                cout << "\t- Tamanho Y" << endl;
                cout << "\t- Tamanho Z" << endl;
                cout << "\t- (OPCIONAL) número de divisões" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("sphere")) {

            if (argc == 6) {
                file.open(caminho + argv[5], std::fstream::out);
                esfera(stof(argv[2]), stof(argv[3]), stof(argv[4]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("cone")) {

            if (argc == 7) {
                file.open(caminho + argv[6], std::fstream::out);
                cone(stof(argv[2]), stof(argv[3]), stof(argv[4]), stof(argv[5]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio da base" << endl;
                cout << "\t- altura" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("patch")) {
            if (argc == 5) { //generator patch <NIVEL_TES> <FILE_IN> <FILE_OUT>
                patch = fopen(caminho.c_str() + *argv[3], "r");
                if (patch) {
                    file.open(caminho + argv[4], std::fstream::out);
                    read_patch(patch, stoi(argv[2]));
                }
                else {
                    printf("ERRO: O ficheiro patch especificado não existe.\n");
                }
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- Nivel de tecelagem" << endl;
                cout << "\t- Ficheiro de Input" << endl;
                cout << "\t- nome do ficheiro para guardar os pontos" << endl;
            }
        }
        else {
            cout << "Figura inválida" << endl;
        }
    }
    else {
        cout << "Não foi dado nenhum argumento" << endl;
    }

    file.close();

    return 0;
}#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>

using namespace std;

fstream file;
//fstream patch;

float *pontosPatch(int *patches, int n_patches, float *control_points, int n_control_points, int nivel) {
    float coordenadas[48];
    float peso = 1.0 / nivel, *pontos = (float*)malloc(n_patches*(3 * (nivel + 1) ^ 2) * sizeof(float));
    float a, b, c, d;
    int i = 0, j = 0, k = 0, t = 0;

    for (t = 0; t < n_patches; t++) {

        a = 0.0;
        b = 1.0 - a;
        c = 0.0;
        d = 1.0 - c;

        // 1º ponto
        coordenadas[0] = control_points[3 * patches[16 * t]];
        coordenadas[1] = control_points[3 * patches[16 * t] + 1];
        coordenadas[2] = control_points[3 * patches[16 * t] + 2];
        // 2º ponto
        coordenadas[3] = control_points[3 * patches[16 * t + 1]];
        coordenadas[4] = control_points[3 * patches[16 * t + 1] + 1];
        coordenadas[5] = control_points[3 * patches[16 * t + 1] + 2];
        // 3º ponto
        coordenadas[6] = control_points[3 * patches[16 * t + 2]];
        coordenadas[7] = control_points[3 * patches[16 * t + 2] + 1];
        coordenadas[8] = control_points[3 * patches[16 * t + 2] + 2];
        // 4º ponto
        coordenadas[9] = control_points[3 * patches[16 * t + 3]];
        coordenadas[10] = control_points[3 * patches[16 * t + 3] + 1];
        coordenadas[11] = control_points[3 * patches[16 * t + 3] + 2];
        // 5º ponto
        coordenadas[12] = control_points[3 * patches[16 * t + 4]];
        coordenadas[13] = control_points[3 * patches[16 * t + 4] + 1];
        coordenadas[14] = control_points[3 * patches[16 * t + 4] + 2];
        // 6º ponto
        coordenadas[15] = control_points[3 * patches[16 * t + 5]];
        coordenadas[16] = control_points[3 * patches[16 * t + 5] + 1];
        coordenadas[17] = control_points[3 * patches[16 * t + 5] + 2];
        // 7º ponto
        coordenadas[18] = control_points[3 * patches[16 * t + 6]];
        coordenadas[19] = control_points[3 * patches[16 * t + 6] + 1];
        coordenadas[20] = control_points[3 * patches[16 * t + 6] + 2];
        // 8º ponto
        coordenadas[21] = control_points[3 * patches[16 * t + 7]];
        coordenadas[22] = control_points[3 * patches[16 * t + 7] + 1];
        coordenadas[23] = control_points[3 * patches[16 * t + 7] + 2];
        // 9º ponto
        coordenadas[24] = control_points[3 * patches[16 * t + 8]];
        coordenadas[25] = control_points[3 * patches[16 * t + 8] + 1];
        coordenadas[26] = control_points[3 * patches[16 * t + 8] + 2];
        // 10º ponto
        coordenadas[27] = control_points[3 * patches[16 * t + 9]];
        coordenadas[28] = control_points[3 * patches[16 * t + 9] + 1];
        coordenadas[29] = control_points[3 * patches[16 * t + 9] + 2];
        // 11º ponto
        coordenadas[30] = control_points[3 * patches[16 * t + 10]];
        coordenadas[31] = control_points[3 * patches[16 * t + 10] + 1];
        coordenadas[32] = control_points[3 * patches[16 * t + 10] + 2];
        // 12º ponto
        coordenadas[33] = control_points[3 * patches[16 * t + 11]];
        coordenadas[34] = control_points[3 * patches[16 * t + 11] + 1];
        coordenadas[35] = control_points[3 * patches[16 * t + 11] + 2];
        // 13º ponto
        coordenadas[36] = control_points[3 * patches[16 * t + 12]];
        coordenadas[37] = control_points[3 * patches[16 * t + 12] + 1];
        coordenadas[38] = control_points[3 * patches[16 * t + 12] + 2];
        // 14º ponto
        coordenadas[39] = control_points[3 * patches[16 * t + 13]];
        coordenadas[40] = control_points[3 * patches[16 * t + 13] + 1];
        coordenadas[41] = control_points[3 * patches[16 * t + 13] + 2];
        // 15º ponto
        coordenadas[42] = control_points[3 * patches[16 * t + 14]];
        coordenadas[43] = control_points[3 * patches[16 * t + 14] + 1];
        coordenadas[44] = control_points[3 * patches[16 * t + 14] + 2];
        // 16º ponto
        coordenadas[45] = control_points[3 * patches[16 * t + 15]];
        coordenadas[46] = control_points[3 * patches[16 * t + 15] + 1];
        coordenadas[47] = control_points[3 * patches[16 * t + 15] + 2];

        for (i = 0; i < nivel; i++) {
            for (j = 0; j < nivel; j++) {
                pontos[k++] = coordenadas[0] * a*a*a*c*c*c + coordenadas[3] * 3 * a*a*a*c*c*d + coordenadas[6] * 3 * a*a*a*c*d*d + coordenadas[9] * a*a*a*d*d*d
                              + coordenadas[12] * 3 * a*a*b*c*c*c + coordenadas[15] * 9 * a*a*b*c*c*d + coordenadas[18] * 9 * a*a*b*c*d*d + coordenadas[21] * 3 * a*a*b*d*d*d
                              + coordenadas[24] * 3 * a*b*b*c*c*c + coordenadas[27] * 9 * a*b*b*c*c*d + coordenadas[30] * 9 * a*b*b*c*d*d + coordenadas[33] * 3 * a*b*b*d*d*d
                              + coordenadas[36] * b*b*b*c*c*c + coordenadas[39] * 3 * b*b*b*c*c*d + coordenadas[42] * 3 * b*b*b*c*d*d + coordenadas[45] * b*b*b*d*d*d;

                pontos[k++] = coordenadas[1] * a*a*a*c*c*c + coordenadas[4] * 3 * a*a*a*c*c*d + coordenadas[7] * 3 * a*a*a*c*d*d + coordenadas[10] * a*a*a*d*d*d
                              + coordenadas[13] * 3 * a*a*b*c*c*c + coordenadas[16] * 9 * a*a*b*c*c*d + coordenadas[19] * 9 * a*a*b*c*d*d + coordenadas[22] * 3 * a*a*b*d*d*d
                              + coordenadas[25] * 3 * a*b*b*c*c*c + coordenadas[28] * 9 * a*b*b*c*c*d + coordenadas[31] * 9 * a*b*b*c*d*d + coordenadas[34] * 3 * a*b*b*d*d*d
                              + coordenadas[37] * b*b*b*c*c*c + coordenadas[40] * 3 * b*b*b*c*c*d + coordenadas[43] * 3 * b*b*b*c*d*d + coordenadas[46] * b*b*b*d*d*d;

                pontos[k++] = coordenadas[2] * a*a*a*c*c*c + coordenadas[5] * 3 * a*a*a*c*c*d + coordenadas[8] * 3 * a*a*a*c*d*d + coordenadas[11] * a*a*a*d*d*d
                              + coordenadas[14] * 3 * a*a*b*c*c*c + coordenadas[17] * 9 * a*a*b*c*c*d + coordenadas[20] * 9 * a*a*b*c*d*d + coordenadas[23] * 3 * a*a*b*d*d*d
                              + coordenadas[26] * 3 * a*b*b*c*c*c + coordenadas[29] * 9 * a*b*b*c*c*d + coordenadas[32] * 9 * a*b*b*c*d*d + coordenadas[35] * 3 * a*b*b*d*d*d
                              + coordenadas[38] * b*b*b*c*c*c + coordenadas[41] * 3 * b*b*b*c*c*d + coordenadas[44] * 3 * b*b*b*c*d*d + coordenadas[47] * b*b*b*d*d*d;

                c += peso;
                d = 1.0 - c;
            }
            a += peso;
            b = 1.0 - a;

            c = 0.0;
            d = 1.0 - c;
        }
        return pontos;
    }
}

// esta função recebe o ficheiro para o qual está a escrever e o nivel de tesselagem;
void read_patch(FILE *f_patch, int nivel) {
    int n_patches, n_control_points, i, j, m, aux, p = 0, *patches = NULL;
    float * points = NULL, *control_points = NULL, x, y, z;

    // lê a primeira linha do ficheiro f_patch e guarda o número para a variável n_patches;
    fscanf(f_patch, "%d\n", &n_patches);

    // aloca memória para as patches (n linhas, 16 por linha com tamanho int);
    patches = (int*)malloc(16 * n_patches * sizeof(int));

    // percorre cada linha
    for (i = 0; i < n_patches; i++) {
        // percorre cada indice da linha (16 no total)
        for (j = 0; j < 15; j++) {
            fscanf(f_patch, "%d, ", &aux);
            patches[p++] = aux;
        }
        fscanf(f_patch, "%d\n", &aux);
        patches[p++] = aux;
    }

    // lê numero de pontos de controlo
    fscanf(f_patch, "%d\n", &n_control_points);
    control_points = (float*)malloc(3 * n_control_points * sizeof(float));

    for (i = 0; fscanf(f_patch, "%f %f %f\n", &x, &y, &z) != EOF; i += 3) {
        control_points[i] = x;
        control_points[i + 1] = y;
        control_points[i + 2] = z;
    }

    //função pontosPatch
    points = pontosPatch(patches, n_patches, control_points, n_control_points, nivel);


    //imprimir pontos para o documento
    n_control_points = n_patches * (3 * (nivel + 1)*(nivel + 1));
    file << n_control_points << endl; // guarda número de pontos

    for (i = 0; i < n_control_points; i += 3) {
        file << points[i] << " " << points[i + 1] << " " << points[i + 2] << endl;
    }

    n_control_points = n_patches * nivel * nivel * 3 * 2;

    file << n_control_points << endl;

    m = (nivel + 1) ^ 2;

    for (i = 0; i < n_patches; i++) {
        for (j = 0; j < nivel; j++) {
            for (p = 0; p < nivel; p++) {
                file << i*m + j*(nivel + 1) + p << " " << i*m + j*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p << endl;
                file << i*m + j*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p + 1 << " " << i*m + (j + 1)*(nivel + 1) + p << endl;
            }
        }
    }

}

void plano(float comprimento) {
    float m_comp = comprimento / 2;

    // Nº DE TRIANGULOS
    file << "2" << endl;

    file << -m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << m_comp << endl;

    file << m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << -m_comp << endl;
}

void planoVBO(float comprimento) {
    float m_comp = comprimento / 2;
    int i = 0;
    // 2 triângulos, cada um com 3 pontos, num total de 6 pontos (apesar de 2 serem repetidos).
    int n_pontos = 6;

    // com 6 pontos, cada um com 3 indices, temos 6x3 = 18 indices.
    int n_indices = 18;

    float *vertexB = (float*)malloc(n_pontos * sizeof(float));
    int * indices = (int*)malloc(n_indices * sizeof(int));

    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;
    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;
    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;

    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = m_comp;
    vertexB[i++] = m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;
    vertexB[i++] = -m_comp; vertexB[i++] = 0.0f; vertexB[i++] = -m_comp;

    /** inacabada, não sei como trabalhar com indices... Podemos não fazer com indices, mas então
      também não há grande motivo para fazer uma função nova visto que já temos os pontos todos.
      Apenas precisamos de adaptar o motor para trabalhar com VBO's. */
}

void caixa(float x, float y, float z, int dimensions) {
    double dim_x = x / dimensions, dim_y = y / dimensions, dim_z = z / dimensions;
    double ori_x = -x / 2, ori_y = -y / 2, ori_z = -z / 2; // origem x, y e z
    double xx = ori_x, yy = ori_y, zz = ori_z; // ponto "origem"

    file << 4 << endl;

    for (xx = ori_x; xx < (-ori_x); xx += dim_x) {
        //x2 = x1 + dim_x;

        for (yy = ori_y; yy < (-ori_y); yy += dim_y) {
            //y2 = y1 + dim_y;

            for (zz = ori_z; zz < (-ori_z); zz += dim_z) {
                //z2 = z1 + dim_z;

                if (xx == ori_x) {
                    //glColor3f(0.09 << " " << 0.5 << " " << 0.99 << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz + dim_z << endl;

                    //glColor3f(0.18 << " " << 0.5 << " " << 0.90 << endl;
                    file << xx << " " << yy + dim_y << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz + dim_z << endl;

                }

                if (yy == ori_y) {
                    //glColor3f(0.27 << " " << 0.5 << " " << 0.81 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz + dim_z << endl;

                    //glColor3f(0.36 << " " << 0.5 << " " << 0.73 << endl;
                    file << xx + dim_x << " " << yy << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz + dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                }

                if (zz == ori_z) {
                    //glColor3f(0.45 << " " << 0.5 << " " << 0.64 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;

                    //glColor3f(0.54 << " " << 0.5 << " " << 0.55 << endl;
                    file << xx + dim_x << " " << yy << " " << zz << endl;
                    file << xx << " " << yy + dim_y << " " << zz << endl;
                    file << xx + dim_x << " " << yy + dim_y << " " << zz << endl;
                }
            }
        }
    }

    for (xx = -ori_x; xx > ori_x; xx -= dim_x) {
        for (yy = -ori_y; yy > ori_y; yy -= dim_y) {
            for (zz = -ori_z; zz > ori_z; zz -= dim_z) {
                if (xx == -ori_x) {
                    //glColor3f(0.63 << " " << 0.63 << " " << 0.46 << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz - dim_z << endl;

                    //glColor3f(0.72 << " " << 0.72 << " " << 0.37 << endl;
                    file << xx << " " << yy - dim_y << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;

                }

                if (yy == -ori_y) {
                    //glColor3f(0.81 << " " << 0.81 << " " << 0.28 << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy << " " << zz - dim_z << endl;

                    //glColor3f(0.9 << " " << 0.9 << " " << 0.19 << endl;
                    file << xx - dim_x << " " << yy << " " << zz - dim_z << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx << " " << yy << " " << zz - dim_z << endl;
                }

                if (zz == -ori_z) {
                    //glColor3f(0.95 << " " << 0.95 << " " << 0.10 << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;

                    //glColor3f(0.99 << " " << 0.99 << " " << 0.01 << endl;
                    file << xx - dim_x << " " << yy << " " << zz << endl;
                    file << xx - dim_x << " " << yy - dim_y << " " << zz << endl;
                    file << xx << " " << yy - dim_y << " " << zz << endl;
                }
            }
        }
    }
}

/* esta função (juntamente com todas as outras que geram as figuras) tem de ser alterada para que escreva para um ficheiro os
pontos do VBO. Mas não tenho a certeza se precisa ser feito se não usarmos VBO's com indices... */
void esfera(float radius, int slices, int stacks) {
    int i, j; // iteradores
    double alpha1 = 0, alpha2 = 0; // angulo de cada fatia
    double beta1 = 0, beta2 = 0; // angulo de cada corte
    double alpha = (2 * M_PI) / slices; //
    double beta = -(M_PI) / stacks;

    //  Nº DE TRIANGULOS
    file << 2 * stacks*slices << endl;

    for (j = -stacks / 2; j < stacks / 2; j++) {
        beta1 = beta * j;
        beta2 = beta * (j + 1);
        double raio1 = radius * cos(beta1);
        double raio2 = radius * cos(beta2);

        for (i = 0; i < slices; i++) {
            alpha1 = alpha * i;
            alpha2 = alpha * (i + 1);
            // 1º triangulo
            file << raio1 * sin(alpha1) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha1) << endl;
            file << raio2 * sin(alpha1) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha1) << endl;
            file << raio1 * sin(alpha2) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha2) << endl;
            // 2º triangulo
            file << raio2 * sin(alpha2) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha2) << endl;
            file << raio1 * sin(alpha2) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha1) << endl;
        }
    }
}

void cone(float radius, float height, int slices, int stacks) {
    int i, j; // iteradores
    double altura2 = 0, altura1 = 0; // altura de cada base
    double alpha1 = 0, alpha2 = 0; // angulo de cada fatia
    double alpha = (2 * M_PI) / slices; //
    double stack_height = height / stacks;
    double raio2, raio1 = radius;

    // Nº DE TRIANGULOS
    file << stacks*slices * 2 + slices << endl;

    for (j = 0; j < stacks; j++) {
        altura2 += stack_height;
        raio1 = radius - radius * ((float)j / stacks);
        raio2 = radius - radius * ((float)(j + 1) / stacks);

        for (i = 0; i < slices; i++) {
            alpha1 = alpha * i;
            alpha2 = alpha * (i + 1);


            if (j == 0) {
                file << 0.0 << " " << 0.0 << " " << 0.0 << endl;
                file << raio1 * sin(alpha2) << " " << 0.0 << " " << raio1 * cos(alpha2) << endl;
                file << raio1 * sin(alpha1) << " " << 0.0 << " " << raio1 * cos(alpha1) << endl;
            }

            file << raio1 * sin(alpha1) << " " << altura1 << " " << raio1 * cos(alpha1) << endl;
            file << raio1 * sin(alpha2) << " " << altura1 << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << altura2 << " " << raio2 * cos(alpha1) << endl;

            file << raio1 * sin(alpha2) << " " << altura1 << " " << raio1 * cos(alpha2) << endl;
            file << raio2 * sin(alpha2) << " " << altura2 << " " << raio2 * cos(alpha2) << endl;
            file << raio2 * sin(alpha1) << " " << altura2 << " " << raio2 * cos(alpha1) << endl;
        }
        altura1 = altura2;
    }
}

int main(int argc, char **argv) {
    FILE *patch = NULL;
    if (argc > 1) {
        /* Só para quando está em debug
        string caminho = "../../motor/";
        */
        string caminho = "../motor/";

        if (argv[1] == string("plane")) {
            if (argc == 4) {
                file.open(caminho + argv[3], std::fstream::out);
                plano(atoi(argv[2]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- comprimento" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("box")) {

            if (argc == 6) {
                file.open(caminho + argv[5], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), 1);
            }
            else if (argc == 7) {
                file.open(caminho + argv[6], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), atoi(argv[5]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- Tamanho X" << endl;
                cout << "\t- Tamanho Y" << endl;
                cout << "\t- Tamanho Z" << endl;
                cout << "\t- (OPCIONAL) número de divisões" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("sphere")) {

            if (argc == 6) {
                file.open(caminho + argv[5], std::fstream::out);
                esfera(stof(argv[2]), stof(argv[3]), stof(argv[4]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("cone")) {

            if (argc == 7) {
                file.open(caminho + argv[6], std::fstream::out);
                cone(stof(argv[2]), stof(argv[3]), stof(argv[4]), stof(argv[5]));
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio da base" << endl;
                cout << "\t- altura" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }
        else if (argv[1] == string("patch")) {
            if (argc == 5) { //generator patch <NIVEL_TES> <FILE_IN> <FILE_OUT>
                patch = fopen(caminho.c_str() + *argv[3], "r");
                if (patch) {
                    file.open(caminho + argv[4], std::fstream::out);
                    read_patch(patch, stoi(argv[2]));
                }
                else {
                    printf("ERRO: O ficheiro patch especificado não existe.\n");
                }
            }
            else {
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- Nivel de tecelagem" << endl;
                cout << "\t- Ficheiro de Input" << endl;
                cout << "\t- nome do ficheiro para guardar os pontos" << endl;
            }
        }
        else {
            cout << "Figura inválida" << endl;
        }
    }
    else {
        cout << "Não foi dado nenhum argumento" << endl;
    }

    file.close();

    return 0;
}