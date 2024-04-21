#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;

//globals

unsigned int objetoRenderizado;
vector<vector<float>> vertices;
vector<vector<int>> faces;
vector<float> rotacao(3, 0);
vector<float> rotacaoVelocidade(3, 0.1f);
vector<float> OffsetPosition(3, 0.0f);
float EscalarPosition = 0.4;

void initGL();
void movimentar3D(double distancia, int direcao);
//void escalar3D(double escala_x, double escala_y, double escala_z);)


void keyboard3D(unsigned char key, int x, int y) {
    std::cout << key;
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'z':
        EscalarPosition = EscalarPosition + 0.1;
        break;
    case 'x':
        EscalarPosition = EscalarPosition - 0.1;
        break;
    case 'e':
        movimentar3D( 0.1, 5);
        break;
    case 'q':
        movimentar3D( 0.1, 6);
        break;
    case '1':
        movimentar3D( 0.1, 7);
        break;
    case '2':
        movimentar3D(0.1, 8);
        break;
    case '4':
        movimentar3D(0.1, 9);
        break;
    case '5':
        movimentar3D(0.1, 10);
        break;
    case '7':
        movimentar3D(0.1, 11);
        break;
    case '8':
        movimentar3D(0.1, 12);
        break;
    }
}



void keyboard_special3D(int key, int x, int y) {
    std::cout << key;
    switch (key) {
    case GLUT_KEY_DOWN:
        movimentar3D( 0.1, 2);
        break;

    case GLUT_KEY_UP:
        movimentar3D( 0.1, 1);
        break;

    case GLUT_KEY_RIGHT:
        movimentar3D( 0.1, 3);
        break;

    case GLUT_KEY_LEFT:
        movimentar3D( 0.1, 4);
        break;

    }
}


void movimentar3D( double distancia, int direcao) {

    switch (direcao) {
    case 1:
        OffsetPosition[1] = OffsetPosition[1] + distancia;
        break;

    case 2:
        OffsetPosition[1] = OffsetPosition[1] - distancia;
        break;

    case 3:
        OffsetPosition[0] = OffsetPosition[0] + distancia;
        break;
        
    case 4:
        OffsetPosition[0] = OffsetPosition[0] - distancia;
        break;
        
    case 5:
        OffsetPosition[2] = OffsetPosition[2] - distancia;
        break;
        
    case 6:
        OffsetPosition[2] = OffsetPosition[2] + distancia;
        break;

    case 7:
        rotacaoVelocidade[0] = rotacaoVelocidade[0] + distancia;
        break;

    case 8:
        rotacaoVelocidade[0] = rotacaoVelocidade[0] - distancia;
        break;

    case 9:
        rotacaoVelocidade[1] = rotacaoVelocidade[1] + distancia;
        break;

    case 10:
        rotacaoVelocidade[1] = rotacaoVelocidade[1] - distancia;
        break;

    case 11:
        rotacaoVelocidade[2] = rotacaoVelocidade[2] + distancia;
        break;

    case 12:
        rotacaoVelocidade[2] = rotacaoVelocidade[2] - distancia;
        break;
    }
}

void loadObj(string fname)
{
    int read;
    float x, y, z;
    ifstream arquivo(fname);
    if (!arquivo.is_open()) {
        cout << "arquivo nao encontrado";
        exit(1);
    }
    else {
        string tipo;
        while (arquivo >> tipo)
        {

            if (tipo == "v")
            {
                vector<float> vertice;
                float x, y, z;
                arquivo >> x >> y >> z;
                vertice.push_back(x);
                vertice.push_back(y);
                vertice.push_back(z);
                vertices.push_back(vertice);
            }

            if (tipo == "f")
            {
                vector<int> face;
                string x, y, z;
                arquivo >> x >> y >> z;
                int fp = stoi(x.substr(0, x.find("/"))) - 1;
                int fs = stoi(y.substr(0, y.find("/"))) - 1;
                int ft = stoi(z.substr(0, z.find("/"))) - 1;
                face.push_back(fp);
                face.push_back(fs);
                face.push_back(ft);
                faces.push_back(face);
            }
        }
    }




    objetoRenderizado = glGenLists(1);
    glPointSize(2.0);
    glNewList(objetoRenderizado, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_LINES);

        for (int i = 0; i < faces.size(); i++)
        {
            vector<int> face = faces[i];

            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);

            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);

            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);

        }
        glEnd();

    }
    glPopMatrix();
    glEndList();
    arquivo.close();

}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void renderObject()
{
    glPushMatrix();
    glTranslatef(OffsetPosition[0], OffsetPosition[1], OffsetPosition[2]);
    glColor3f(1.0, 0.23, 0.27);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(rotacao[0], 0, 1, 0);
    glRotatef(rotacao[1], 1, 0, 0);
    glRotatef(rotacao[2], 0, 0, 1);
    glCallList(objetoRenderizado);
    glPopMatrix();
    rotacao[0] = rotacao[0] + rotacaoVelocidade[0];
    if (rotacao[0] > 360) rotacao[0] = rotacao[0] - 360;

    rotacao[1] = rotacao[1] + rotacaoVelocidade[1];
    if (rotacao[1] > 360) rotacao[1] = rotacao[1] - 360;

    rotacao[2] = rotacao[2] + rotacaoVelocidade[2];
    if (rotacao[2] > 360) rotacao[2] = rotacao[2] - 360;
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    renderObject();
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
    glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Carregar OBJ");
    glutKeyboardFunc(keyboard3D);
    glutSpecialFunc(keyboard_special3D);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj("data/porsche.obj");
    initGL();
    glutMainLoop();
    return 0;
}