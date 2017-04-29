#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

fstream file;

void plano(float comprimento){
    float m_comp = comprimento/2;

    // Nº DE TRIANGULOS
    file << "2" << endl;

    file << -m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << m_comp << endl;

    file << m_comp << " 0.0 " << m_comp << endl;
    file << m_comp << " 0.0 " << -m_comp << endl;
    file << -m_comp << " 0.0 " << -m_comp << endl;

}

void caixa(float x, float y, float z,  int dimensions){
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

void esfera(float radius, int slices, int stacks){
    int i, j; // iteradores
    double alpha1 = 0, alpha2 = 0; // angulo de cada fatia
    double beta1 = 0, beta2 = 0; // angulo de cada corte
    double alpha = (2 * M_PI) / slices; //
    double beta = -(M_PI) / stacks;

    //  Nº DE TRIANGULOS
    file << 2*stacks*slices << endl;

    for (j = -stacks/2; j < stacks/2; j++) {
        beta1 = beta * j;
        beta2 = beta * (j + 1);
        double raio1 = radius * cos(beta1);
        double raio2 = radius * cos(beta2);

        for (i = 0; i < slices; i++) {
            alpha1 = alpha * i;
            alpha2 = alpha * (i + 1);

            file << raio1 * sin(alpha1) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha1) << endl;
            file << raio2 * sin(alpha1) << " " << radius * sin(beta2) << " " << raio2 * cos(alpha1) << endl;
            file << raio1 * sin(alpha2) << " " << radius * sin(beta1) << " " << raio1 * cos(alpha2) << endl;

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
    file << stacks*slices*2+slices << endl;

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
    }}

int main(int argc, char **argv) {

    if(argc > 1){
      /* Só para quando está em debug
      string caminho = "../../motor/";
      */
      string caminho = "../motor/";

        if(argv[1] == string("plane")){
            if(argc == 4){
                file.open(caminho + argv[3], std::fstream::out);
                plano(atoi(argv[2]));
            }else{
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- comprimento" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }else if(argv[1] == string("box")) {

            if (argc == 6){
                file.open(caminho + argv[5], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), 1);
            }else if(argc == 7){
                file.open(caminho + argv[6], std::fstream::out);
                caixa(stof(argv[2]), stof(argv[3]), stof(argv[4]), atoi(argv[5]) );
            }else{
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- Tamanho X" << endl;
                cout << "\t- Tamanho Y" << endl;
                cout << "\t- Tamanho Z" << endl;
                cout << "\t- (OPCIONAL) número de divisões" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }else if(argv[1] == string("sphere")){

            if(argc == 6){
                file.open(caminho + argv[5], std::fstream::out);
                esfera(stof(argv[2]), stof(argv[3]), stof(argv[4]) );
            }else{
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }else if(argv[1] == string("cone")){

            if(argc == 7){
                file.open(caminho + argv[6], std::fstream::out);
                cone(stof(argv[2]), stof(argv[3]), stof(argv[4]), stof(argv[5]) );
            }else{
                cout << "Faltam argumentos!" << endl;
                cout << "Os argumentos necessários são:" << endl;
                cout << "\t- raio da base" << endl;
                cout << "\t- altura" << endl;
                cout << "\t- fatias" << endl;
                cout << "\t- camadas" << endl;
                cout << "\t- nome do ficheiro para guardar os vértices" << endl;
            }

        }else{
            cout << "Figura inválida" << endl;
        }
    }else{
        cout << "Não foi dado nenhum argumento" << endl;
    }

    file.close();

    return 0;
}
