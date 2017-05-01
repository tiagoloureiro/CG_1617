// este include tem de ser feito antes do glut caso contrario dá "exit redefenition" (no V.Studio).
#include "../lib/tinyxml/tinyxml.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <tuple>

// para não estar sempre a escrever std::
using namespace std;

//Estrutura para guardar 3 floats
typedef vector< tuple<float, float, float> > vector3f;

// Vector que guarda a lista de ficheiros
vector3f lista_translacoes;
vector3f lista_escalas;
vector3f lista_rotacoes;
vector<float> lista_angulos;
vector<int> lista_times;

// Vector que guarda o nome de todos os ficheiros
vector<string> lista_ficheiros;

// Vector que guarda a lista das cores (1 para cada figura)
vector3f lista_cores;

//variaveis de transformacoes usadas ao ler o XML
float translate_x = 0, translate_y = 0, translate_z = 0,
scale_x = 1, scale_y = 1, scale_z = 1,
angulo = 0, rotate_x = 0, rotate_y = 0, rotate_z = 0;
/* Ainda não é usado
#define EXP 0
#define FPS 1
*/

// flag para mudar o drwing mode
int flag_drawing_mode = 1;

// ângulos para "rodar a camera"
float alfa = 0.0f, beta = 0.0f, radius = 500;
float camX = 0.0f, camY = 0.0f, camZ = 0.0f;

/**##############################################################################
###############+++#########+++###++++++++######++++++++++########################
################+++#######+++####+++###+++####+++######+++#######################
#################+++#####+++#####+++###+++####+++######+++####++++###############
##################+++###+++######+++++++######+++######+++###+###################
###################+++#+++#######+++####+++###+++######+++####+++################
####################+++++########+++####+++###+++######+++#######+###############
#####################+++#########+++++++#######++++++++++####++++################
###############################################################################*/
// o primeiro int é o numero de pontos e o segundo é o indice do buffer;
vector< tuple <int, int> > VBO; //numero de pontos, indice do VBO
vector<tuple <int, GLuint> > VBO2; // <tuple <n_pontos, buffer> >

// buffers para os VBOs
GLuint *buffers = NULL;
// auxiliar para apontar para o próximo buffer disponivel;
int next_buffer = 0;
// frames per second
int frame = 0, fps = 0, timebase, times;
char print[20] = "";

/* Ainda não é usado
float dx = 0.0f;
float dy = 0.0f;
float dz = 0.0f;
int modo_camera = 0;
*/

/* Esta função vai buscar os nomes dos ficheiros .3d que estão no vector lista_ficheiros
* Desenha todos os pontos de cada ficheiro e por ficheiro atribui uma cor do vector lista_cores
*/

#define POINT_COUNT 5
vector<vector3f> lista_pontos_translacao; // vector com lista de todos os pontos da curva catmull
//int time_t = 0;
// funções catmull-rom da aula;
void getCatmullRomPoint(float t, int *indices, float *res) {

    int i, j, k;
    float aux[4];
    float aux_t[4];
    aux_t[0] = t*t*t; aux_t[1] = t*t; aux_t[2] = t; aux_t[3] = 1;

    // catmull-rom matrix
    float m[4][4] = { { -0.5f,  1.5f, -1.5f,  0.5f },
    { 1.0f, -2.5f,  2.0f, -0.5f },
    { -0.5f,  0.0f,  0.5f,  0.0f },
    { 0.0f,  1.0f,  0.0f,  0.0f } };

    res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
    // Compute point res = T * M * P
    // where Pi = p[indices[i]]
    for (int i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            aux[j] = 0;
            for (k = 0; k < 4; k++) {
                aux[i] += (aux_t[k] * m[k][j]);
            }
        }

        /*for (j = 0; j < 4; j++) {
            res[i] += aux[j] * getAt(indices[j], points, i);
        }*/
    }
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *res) {

    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within the segment

                   // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    getCatmullRomPoint(t, indices, res);
}

void definir_cores() {
    lista_cores.push_back(tuple<float, float, float>(1.0, 0.94, 0.0)); //sol
    lista_cores.push_back(tuple<float, float, float>(0.87, 0.72, 0.53)); //mercurio
    lista_cores.push_back(tuple<float, float, float>(0.82, 0.41, 0.12)); //venus
    lista_cores.push_back(tuple<float, float, float>(0.29, 0.59, 0.82)); //terra
    lista_cores.push_back(tuple<float, float, float>(0.97, 0.91, 0.81)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.76, 0.23, 0.13)); //marte
    lista_cores.push_back(tuple<float, float, float>(0.97, 0.91, 0.56)); //jupiter
    lista_cores.push_back(tuple<float, float, float>(0.57, 0.64, 0.69)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.83, 0.69, 0.22)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.66, 0.6, 0.53)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.4, 0.22, 0.33)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.9, 0.67, 0.44)); //saturno
    lista_cores.push_back(tuple<float, float, float>(0.76, 0.6, 0.42)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.76, 0.6, 0.42)); //lua
    lista_cores.push_back(tuple<float, float, float>(0.49, 0.98, 1.0)); //urano
    lista_cores.push_back(tuple<float, float, float>(0.0, 0.0, 0.61)); //neptuno
    lista_cores.push_back(tuple<float, float, float>(0.97, 0.91, 0.81)); //lua
}

//// função para desenhar a figura a partir dos dados guardados nos buffers;
//void drawVBO() {
//
//    for (int j = 0; j < VBO.size(); ++j) {
//        glBindBuffer(GL_ARRAY_BUFFER, get<1>(VBO2[j]));
//        glVertexPointer(3, GL_FLOAT, 0, 0);
//        glDrawArrays(GL_TRIANGLES, 0, get<0>(VBO2[j]));
//    }
//}

// esta função apenas é invocada na main para ler os ficheiros com os objectos para a memória do PC.
void desenha() {
    /*
    * Variaveis
    */
    vector3f vertices;  //vector< tuple<float, float, float> >
    float v1 = 0, v2 = 0, v3 = 0;
    string str;
    int primeira_linha = 0, k = 0, n_triangulos = 0, n_pontos = 0, n_vertices;
    float *vertexB = NULL; // array para os vértices;

    /*
    * percorrer lista com o nome dos ficheiros
    */

    //DEBUG for (int i = 0; i < lista_escalas.size(); ++i){cout << get<0>(lista_escalas[i]) << get<1>(lista_escalas[i])<< get<2>(lista_escalas[i]) << endl;}
    //DEBUG
    //for (int i = 0; i < lista_translacoes.size(); ++i){cout << get<0>(lista_translacoes[i]) << get<1>(lista_translacoes[i])<< get<2>(lista_translacoes[i]) << endl;}
    glEnableClientState(GL_VERTEX_ARRAY); // Enable buffer functionality;
    // Generate buffers;
    buffers = (GLuint*)malloc(sizeof(GLuint)*lista_ficheiros.size());
    // glGenBuffers(n_buffers, buffer_pointer);
    glGenBuffers(lista_ficheiros.size(), buffers);

    for (int i = 0; i <= lista_ficheiros.size()-1; ++i) {
        printf("%d ", i);
        const char *f = lista_ficheiros[i].c_str();
        //DEBUG cout << lista_ficheiros[i] << i << endl;
        ifstream fi(f);

        if (fi.is_open()) {
            while (getline(fi, str)) { //ler todos os vertices
                                       //a primeira linha contem o numero de vertices, calcular espaço para o array vertexB;
                if (primeira_linha == 0) {
                    istringstream ss(str);
                    ss >> n_triangulos; // guardar numero de triangulos
                    n_pontos = 3 * n_triangulos; // calcular numero de pontos
                    vertexB = (float*)malloc(3 * n_pontos * sizeof(float));
                    k = 0; // reinicializar iterador do vertexB;
                    primeira_linha = 1;
                }
                else {
                    istringstream ss(str); //carregar cada um dos vértices para o vertexB;
                    ss >> v1; vertexB[k++] = v1;
                    ss >> v2; vertexB[k++] = v2;
                    ss >> v3; vertexB[k++] = v3;
                    //DEBUG cout << v1 << " " << v2 << " " << v3 << endl;

                    // isto já não faz nada porque carregamos directamente para o array vertexB.
                    // Mas podia guardar primeiro para (v1,v2,v3), depois para o vector vertices
                    // e carregar depois para o array vertexB.
                    vertices.push_back(tuple<float, float, float>(v1, v2, v3));
                }
            }
            fi.close();
            // gerar o buffer;
            //glGenBuffers(1, &buffers[next_buffer]);
            // fazer bind do buffer;
            glBindBuffer(GL_ARRAY_BUFFER, buffers[next_buffer]);
            // preencher o buffer com os dados da figura;
            glBufferData(GL_ARRAY_BUFFER, n_pontos * 3 * sizeof(float), vertexB, GL_STATIC_DRAW);
            // vector que guarda o numero de pontos e qual o buffer associado;
            VBO.push_back(tuple<int, int>(n_pontos, next_buffer));
            VBO2.push_back(tuple<int, GLuint>(n_pontos, buffers[next_buffer]));
            // avançar para o próximo buffer;
            next_buffer++;
            // libertar o array com os dados da figura, visto que já está no buffer da gráfica;
            ::free(vertexB);
            primeira_linha = 0;
        }
        else {
            cerr << "Erro: Não foi possível abrir o ficheiro " << lista_ficheiros[i] << "." << endl;
            exit(1);
        }

        /** clear vector for next file*/
        vertices.clear();
    }
    printf("\n");
}

// invocada na renderScene porque puxa menos pelo pc e tenho de desenhar o VBO a seguir à transformação;
void desenha2() {
    for (int i = 0, k = 0; i <= lista_ficheiros.size() - 1; ++i) {
        const char *f = lista_ficheiros[i].c_str();
        //DEBUG cout << lista_ficheiros[i] << i << endl;
        /** desenhar objeto */
        definir_cores();
        glPushMatrix();

        glColor3f(get<0>(lista_cores[i]), get<1>(lista_cores[i]), get<2>(lista_cores[i]));
        //glColor3f(0, 0, 0); // DEBUG
        //DEBUG cout << "faz um translate " << get<0>(lista_translacoes[i]) << " " << get<1>(lista_translacoes[i]) << " " << get<2>(lista_translacoes[i]) << endl;
        glTranslatef(get<0>(lista_translacoes[i]), get<1>(lista_translacoes[i]), get<2>(lista_translacoes[i]));
        glRotatef(lista_angulos[i], get<0>(lista_rotacoes[i]), get<1>(lista_rotacoes[i]), get<2>(lista_rotacoes[i]));
        glScalef(get<0>(lista_escalas[i]), get<1>(lista_escalas[i]), get<2>(lista_escalas[i]));

        //drawVBO();
        //glBindBuffer(GL_ARRAY_BUFFER, buffers[<numero>]);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]); //buffers[get<1>(VBO[k])]
        printf("n_pontos: %d buffers: %d\n", get<0>(VBO[k]),buffers[get<1>(VBO[k])]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        //glDrawArrays(GL_TRIANGLES, first, count); count é nº total de vertices.
        glDrawArrays(GL_TRIANGLES, 0, get<0>(VBO[k])*3);
        glPopMatrix();
        k++;
    }
}

void spherical2Cartesian() {

    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(cos(beta)*sin(alfa)*radius, sin(beta)*radius, cos(beta)*cos(alfa)*radius, 0, 0, 0, 0, 1, 0);

    /*visao lateral dos planetas*/
    /*gluLookAt(camX, camY, camZ,
    250, 50.0f, 50.0f,
    0.0f, 1.0f, 0.0f);
    */

    // put the geometric transformations here
    if (flag_drawing_mode == 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (flag_drawing_mode == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (flag_drawing_mode == 2) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    //glutWireTeapot(1);
    //desenha();
    //glPushMatrix();
    desenha2();
    //glPopMatrix();
    //drawVBO();

    frame++;
    times = glutGet(GLUT_ELAPSED_TIME);
    if (times - timebase > 1000)
    {
        fps = frame*1000.0 / (times - timebase);
        timebase = times;
        frame = 0;
    }
    sprintf(print, "%d", fps);
    glutSetWindowTitle(print);

    // End of frame
    glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    if (c == 27) exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
    case GLUT_KEY_RIGHT:
        alfa -= 0.1; break;

    case GLUT_KEY_LEFT:
        alfa += 0.1; break;

    case GLUT_KEY_UP:
        beta += 0.1f;
        if (beta > 1.5f)
            beta = 1.5f;
        break;

    case GLUT_KEY_DOWN:
        beta -= 0.1f;
        if (beta < -1.5f)
            beta = -1.5f;
        break;

    case GLUT_KEY_PAGE_UP:
        radius -= 0.8f;
        if (radius < 0.1f)
            radius = 0.8f;
        break;

    case GLUT_KEY_PAGE_DOWN:
        radius += 0.8f;
        break;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}

int translacao(TiXmlElement* translate) {
    //translate_x = 0, translate_y = 0, translate_z = 0;
    const char *aux_x = translate->Attribute("X");
    const char *aux_y = translate->Attribute("Y");
    const char *aux_z = translate->Attribute("Z");

    if (aux_x)   translate_x = atof(aux_x);
    if (aux_y)   translate_y = atof(aux_y);
    if (aux_z)   translate_z = atof(aux_z);

    //guardar valores desta translacao
    //lista_translacoes.push_back(tuple<float,float,float>(translate_x,translate_y,translate_z));
    //cout << "faz um translate " << translate_x << " " <<translate_y << " " << translate_z << endl;
    return 0;
}
int rotacao(TiXmlElement* rotate) {

    const char *aux_a = rotate->Attribute("angle");
    const char *aux_x = rotate->Attribute("axisX");
    const char *aux_y = rotate->Attribute("axisY");
    const char *aux_z = rotate->Attribute("axisZ");

    if (aux_a)   angulo = atof(aux_a);
    if (aux_x)   rotate_x = atof(aux_x);
    if (aux_y)   rotate_y = atof(aux_y);
    if (aux_z)   rotate_z = atof(aux_z);

    //guardar valores desta rotacao
    //lista_rotacoes.push_back(tuple<float,float,float>(rotate_x,rotate_y,rotate_z));
    //lista_angulos.push_back(angulo);
    //cout << "faz uma rotacao " << rotate_x << " " <<rotate_y << " " << rotate_z << endl;
    return 0;
}
int escala(TiXmlElement* scale) {

    const char *aux_x = scale->Attribute("X");
    const char *aux_y = scale->Attribute("Y");
    const char *aux_z = scale->Attribute("Z");

    if (aux_x)   scale_x = atof(scale->Attribute("X"));
    if (aux_y)   scale_y = atof(scale->Attribute("Y"));
    if (aux_z)   scale_z = atof(scale->Attribute("Z"));

    //guardar valores desta escala
    //lista_escalas.push_back(tuple<float,float,float>(scale_x,scale_y,scale_z));
    //cout << "faz uma escala " << scale_x << " " <<scale_y << " " << scale_z << endl;
    return 0;
}
//int modelo(){}

int le_xml(char *nome) {
    int erros = 0;
    //string caminho = "xml/" + (string)nome;

    string caminho_windows = "..\\"; //WINDOWS
    string caminho_unix = "../"; //Unix
    caminho_windows += nome;

    TiXmlDocument doc;

    if(!doc.LoadFile(nome)) {
        if (!doc.LoadFile(caminho_unix.c_str())) {
            if (!doc.LoadFile(caminho_windows.c_str())) {
                cout << "Nome do ficheiro inválido" << nome << endl;
                return erros + 1;
            }
        }
    }


    //scene
    TiXmlElement* raiz = doc.FirstChildElement();
    if (raiz == NULL) return erros + 1;

    // Grupos
    TiXmlElement* grupo_ext = NULL;
    for (grupo_ext = raiz->FirstChildElement("group"); grupo_ext; grupo_ext = grupo_ext->NextSiblingElement("group")) {

        // TRANSLATE
        TiXmlElement* translate = grupo_ext->FirstChildElement("translate");
        if (translate != NULL) { // entrar no translate;
            translacao(translate);
            //const char* t_aux = translate->Attribute("time"); // guardar time;
            //if (t_aux) { // se time existir, converter para int e ler pontos;
            //    time_t = atoi(t_aux); // conversão
            //    lista_times.push_back(time_t); // guardar
            //    while (TiXmlElement* point = translate->NextSiblingElement("point")) { // enquanto tiver pontos
            //        translacao(translate); // tratar da translação;
            //                               // guardar esta translação no vector;
            //        lista_translacoes.push_back(tuple<float, float, float>(translate_x, translate_y, translate_z));
            //    }
            //    // guardar pontos da translação;
            //    lista_pontos_translacao.push_back(lista_translacoes);
            //    lista_translacoes.clear(); //
            //}
        }

        // ROTATE
        TiXmlElement* rotate = grupo_ext->FirstChildElement("rotate");
        if (rotate != NULL)
            rotacao(rotate);

        // SCALE
        TiXmlElement* scale = grupo_ext->FirstChildElement("scale");
        if (scale != NULL)
            escala(scale);

        TiXmlElement* models = grupo_ext->FirstChildElement("models");
        if (models != NULL) {
            const char* nome_aux = NULL;

            nome_aux = models->FirstChildElement("model")->Attribute("file");
            if (nome_aux == NULL) return 0;
            std::string nome_ficheiro = "";
            nome_ficheiro += "../formas/";
            nome_ficheiro += nome_aux;

            lista_ficheiros.push_back(nome_ficheiro);
            lista_rotacoes.push_back(tuple<float, float, float>(rotate_x, rotate_y, rotate_z));
            lista_angulos.push_back(angulo);
            lista_translacoes.push_back(tuple<float, float, float>(translate_x, translate_y, translate_z));
            //lista_times.push_back(time);
            lista_escalas.push_back(tuple<float, float, float>(scale_x, scale_y, scale_z));

        }

        TiXmlElement* grupo_int = NULL;
        for (grupo_int = grupo_ext->FirstChildElement("group"); grupo_int; grupo_int = grupo_int->NextSiblingElement("group")) {
            // TRANSLATE
            TiXmlElement* translate = grupo_int->FirstChildElement("translate");
            if (translate != NULL) { // entrar no translate;
                translacao(translate);
                //const char* t_aux = translate->Attribute("time"); // guardar time;
                //if (t_aux) { // se time existir, converter para int e ler pontos;
                //    time_t = atoi(t_aux); // conversão
                //    lista_times.push_back(time_t); // guardar
                //    while (TiXmlElement* point = translate->NextSiblingElement("point")) { // enquanto tiver pontos
                //        translacao(translate); // tratar da translação;
                //        // guardar esta translação no vector;
                //        lista_translacoes.push_back(tuple<float, float, float>(translate_x, translate_y, translate_z));
                //    }
                //    // guardar pontos da translação;
                //    lista_pontos_translacao.push_back(lista_translacoes);
                //    lista_translacoes.clear(); //
                //}
            }


            // ROTATE
            TiXmlElement* rotate = grupo_int->FirstChildElement("rotate");
            if (rotate != NULL)
                rotacao(rotate);

            // SCALE
            TiXmlElement* scale = grupo_int->FirstChildElement("scale");
            if (scale != NULL)
                escala(scale);

            TiXmlElement* models = grupo_int->FirstChildElement("models");
            if (models != NULL) {
                const char* nome_aux = NULL;

                nome_aux = models->FirstChildElement("model")->Attribute("file");
                if (nome_aux == NULL) return 0;
                std::string nome_ficheiro = "";
                nome_ficheiro += "../formas/";
                nome_ficheiro += nome_aux;

                lista_ficheiros.push_back(nome_ficheiro);
                lista_rotacoes.push_back(tuple<float, float, float>(rotate_x, rotate_y, rotate_z));
                lista_angulos.push_back(angulo);
                lista_translacoes.push_back(tuple<float, float, float>(translate_x, translate_y, translate_z));
                //lista_times.push_back(time);
                lista_escalas.push_back(tuple<float, float, float>(scale_x, scale_y, scale_z));

            }
        }
    }
    return 0;
}

void processMenuEvents(int option) {

    switch (option) {
    case 0:
        flag_drawing_mode = 0;
        break;
    case 1:
        flag_drawing_mode = 1;
        break;
    case 2:
        flag_drawing_mode = 2;
        break;
    default:
        break;
    }

    glutPostRedisplay();

}

void createGLUTMenus() {

    int menu;

    menu = glutCreateMenu(processMenuEvents);

    glutAddMenuEntry("Fill", 0);
    glutAddMenuEntry("Line", 1);
    glutAddMenuEntry("Point", 2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    /*printf("\nUse Arrows to move the camera up/down and left/right\n");
    printf("Home and End control the distance from the camera to the origin");*/
}

int main(int argc, char **argv) {

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("MOTOR");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glewInit();

    // MENUS
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    createGLUTMenus();


    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glGenBuffers(1024, buffers);
    glClearColor(1, 1, 1, 1);

    /*if(argc == 2){
    if(le_xml(argv[1]) > 0){
    cout << "O ficheiro xml não foi encontrado" << endl;
    return 1;
    }
    }else{
    cout << "Número de argumentos inválido" << endl;
    return 1;
    }*/

    le_xml(argv[1]);

    //cout << lista_ficheiros.size() << endl;
    desenha();
    glutPostRedisplay();
    spherical2Cartesian();
    printInfo();
    // enter GLUT's main cycle
    glutMainLoop();

    return 0;
}