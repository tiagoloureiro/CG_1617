#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "tinyxml/tinyxml.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>

// para não estar sempre a escrever std::
using namespace std;

/* Ainda não é usado
#define EXP 0
#define FPS 1
*/

// Vector que guarda a lista de ficheiros
std::vector<string> lista_ficheiros;
// Vector que guarda a lista das cores (1 para cada figura)
std::vector< pair<float, float> > lista_cores;

// falg para mudar o drwing mode
int flag_drawing_mode = 1;

// ângulos para "rodar a camera"
float alfa = 0.0f, beta = 0.0f, radius = 7.0f;
float camX, camY, camZ;

/* Ainda não é usado
float dx = 0.0f;
float dy = 0.0f;
float dz = 0.0f;
int modo_camera = 0;
 */

/* Esta função vai buscar os nomes dos ficheiros .3d que estão no vector lista_ficheiros
 * Desenha todos os pontos de cada ficheiro e por ficheiro atribui uma cor do vector lista_cores
 */
void desenha(void){

    for(int i=0; i<lista_ficheiros.size(); i++){

        const char *f = lista_ficheiros[i].c_str();
        ifstream fi(f);
        string str;

        /*
        float vermelho = lista_cores[i][0];
        float verde = lista_cores[i][1];
        float azul = lista_cores[i][2];
        */

        float verde = lista_cores[i].first;
        float azul = lista_cores[i].second;

        glColor3f(0, verde, azul);
        glBegin(GL_TRIANGLES);
        getline(fi,str);
        while (getline(fi, str)) {
            float v1, v2, v3;
            istringstream ss(str);

            ss >> v1;
            ss >> v2;
            ss >> v3;
            glVertex3f(v1, v2, v3);
        }
        glEnd();
    }

}

void cria_cores(int x){
    float vermelho=255, verde=255, azul=255;
    bool flag;

    //cout << x << endl;

    for(int i=0; i<x; i++){
        flag = true;
        while(flag) {
            vermelho = rand() % 255;
            vermelho = vermelho / 255;

            verde = rand() % 255;
            verde = verde / 255;

            azul = rand() % 255;
            azul = azul / 255;

            if (verde > 0 && verde < 1 && azul > 0 && azul < 1) {
                float arr[3] = {vermelho, verde, azul};
                lista_cores.push_back(make_pair(verde, azul));
                flag = false;
                //cout << "verde: " << verde << " | " << "azul: " << azul << endl;
            }
        }
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
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

// put the geometric transformations here
	if(flag_drawing_mode == 0){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}else if(flag_drawing_mode == 1){
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}else if(flag_drawing_mode == 2){
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	}

    //glutWireTeapot(1);
    desenha();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

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
            radius -= 0.1f;
            if (radius < 0.1f)
                radius = 0.1f;
            break;

        case GLUT_KEY_PAGE_DOWN:
            radius += 0.1f;
            break;
    }
    spherical2Cartesian();
    glutPostRedisplay();

}


int le_xml(char *nome){
    string caminho = "xml/" + (string)nome;

    TiXmlDocument doc;

    if(!doc.LoadFile(caminho.c_str()) ){
        cout << "Nome do ficheiro inválido" << endl;
        return 1;
    }

    TiXmlNode* pRoot = doc.FirstChild();

    TiXmlElement* pListElement = pRoot->FirstChildElement("model");
    if (pListElement == NULL) return 0;

    while (pListElement != NULL){
        const char* nome_aux = NULL;

        nome_aux = pListElement->Attribute("file");
        if (nome_aux == NULL) return 0;

        /* Só quando está em debug
        std::string nome_ficheiro = "../";
        */
        std::string nome_ficheiro = "";
        nome_ficheiro += nome_aux;

        lista_ficheiros.push_back(nome_ficheiro);

        //cout << nome_ficheiro << endl;

        pListElement = pListElement->NextSiblingElement("model");
    }

    cria_cores(lista_ficheiros.size());
    return 0;
}


void processMenuEvents(int option) {

    switch (option) {
        case 0 :
            flag_drawing_mode = 0;
            break;
        case 1 :
            flag_drawing_mode = 1;
            break;
        case 2 :
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

    glutAddMenuEntry("Fill",0);
    glutAddMenuEntry("Line",1);
    glutAddMenuEntry("Point",2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("MOTOR");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

// MENUS
    glutDetachMenu(GLUT_RIGHT_BUTTON);
    createGLUTMenus();


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(1,1,1,1);

    if(argc == 2){
        if(le_xml(argv[1]) == 1){
            cout << "O ficheiro xml não foi encontrado" << endl;
        }
    }else{
        cout << "Número de argumentos inválido" << endl;
    }
    glutPostRedisplay();
    spherical2Cartesian();

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
