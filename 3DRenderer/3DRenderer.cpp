#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include <string>
using namespace std;

//globals
struct Face;
unsigned int objetoRenderizado;
vector<vector<float>> vertices;
vector<Face> faces;
vector <vector<float>> normais;
vector<float> rotacao(3, 0);
vector<float> rotacaoVelocidade(3, 0.0f);
vector<float> OffsetPosition(3, 0.0f);
float EscalarPosition = 0.1;
float colourRed[] = { 1.0, 0.0, 0.0 };
float colourBlue[] = { 0.0, 0.0, 1.0 };
float colourGreen[] = { 0.0, 1.0, 0.0 };


GLfloat luz_ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat luz_difusa[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat luz_especular[] = { 1.0, 1.0, 1.0, 1.0 };

struct Face {
    vector<int> vertices;
    vector<int> normais;
    vector<int> texturas;
};

void initGL();
void movimentar3D(double distancia, int direcao);
void loadObj(string fname, int position_z_offset);
//void escalar3D(double escala_x, double escala_y, double escala_z);)


// Create custom split() function.  
vector<string> Split(string str, char separator) {
    vector<string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

void keyboard3D(unsigned char key, int x, int y) {
    std::cout << key;
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'z':
        EscalarPosition = EscalarPosition * 0.9;
        break;
    case 'x':
        EscalarPosition = EscalarPosition * 1.1;
        break;

    case 'e':
        movimentar3D(0.1, 5);
        break;
    case 'q':
        movimentar3D(0.1, 6);
        break;

    case 'n':
        glDisable(GL_LIGHT0);
        break;
    case 'm':
        glEnable(GL_LIGHT0);
        break;

    case 'j':
        glDisable(GL_LIGHT1);
        break;
    case 'k':
        glEnable(GL_LIGHT1);
        break;

    case 'i':
        glDisable(GL_LIGHT2);
        break;
    case 'o':
        glEnable(GL_LIGHT2);
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

void loadObj(string fname, int position_z_offset)
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
                Face new_face;
                
                string faceX, faceY, faceZ;
                arquivo >> faceX >> faceY >> faceZ;
                vector<string> x = Split(faceX, '/');
                vector<string> y = Split(faceY, '/');
                vector<string> z = Split(faceZ, '/');

                //Verificar quantidade de barras na face

                // Se for duas
                if (x.size() == 3 and y.size() == 3 and z.size() == 3) {

                    int vertice_face_x = stoi(x[0]) - 1;
                    int vertice_face_y = stoi(y[0]) - 1;
                    int vertice_face_z = stoi(z[0]) - 1;


                    new_face.vertices.push_back(vertice_face_x);
                    new_face.vertices.push_back(vertice_face_y);
                    new_face.vertices.push_back(vertice_face_z);

                    // Verificar se Textura está vázia
                    if (!x[1].empty() and !y[1].empty() and !z[1].empty()) {
                        int textura_face_x = stoi(x[1]) - 1;
                        int textura_face_y = stoi(y[1]) - 1;
                        int textura_face_z = stoi(z[1]) - 1;

                        new_face.texturas.push_back(textura_face_x);
                        new_face.texturas.push_back(textura_face_y);
                        new_face.texturas.push_back(textura_face_z);
                    }

                    int normal_face_x = stoi(x[2]) - 1;
                    int normal_face_y = stoi(y[2]) - 1;
                    int normal_face_z = stoi(z[2]) - 1;


                    new_face.normais.push_back(normal_face_x);
                    new_face.normais.push_back(normal_face_y);
                    new_face.normais.push_back(normal_face_z);



                    faces.push_back(new_face);
                }
                else if (x.size() == 2 and y.size() == 2 and z.size() == 2) {

                    int vertice_face_x = stoi(x[0]) - 1;
                    int vertice_face_y = stoi(y[0]) - 1;
                    int vertice_face_z = stoi(z[0]) - 1;

                    int textura_face_x = stoi(x[1]) - 1;
                    int textura_face_y = stoi(y[1]) - 1;
                    int textura_face_z = stoi(z[1]) - 1;

                    new_face.vertices.push_back(vertice_face_x);
                    new_face.vertices.push_back(vertice_face_y);
                    new_face.vertices.push_back(vertice_face_z);

                    new_face.texturas.push_back(textura_face_x);
                    new_face.texturas.push_back(textura_face_y);
                    new_face.texturas.push_back(textura_face_z);



                    faces.push_back(new_face);

                }else if (x.size() == 1 and y.size() == 1 and z.size() == 1) {

                    int vertice_face_x = stoi(x[0]) - 1;
                    int vertice_face_y = stoi(y[0]) - 1;
                    int vertice_face_z = stoi(z[0]) - 1;


                    new_face.vertices.push_back(vertice_face_x);
                    new_face.vertices.push_back(vertice_face_y);
                    new_face.vertices.push_back(vertice_face_z);

                    faces.push_back(new_face);
                }
            }

            if (tipo == "vn")
            {
                vector<float> normal;
                float x, y, z;
                arquivo >> x >> y >> z;
                normal.push_back(x);
                normal.push_back(y);
                normal.push_back(z);
                normais.push_back(normal);
            }
        }
    }




    objetoRenderizado = glGenLists(1);
    glPointSize(2.0);
    glNewList(objetoRenderizado, GL_COMPILE);
    {
        glPushMatrix();
        
        //glBegin(GL_LINES);
        glBegin(GL_TRIANGLES);

        GLfloat cor_preto[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat cor_verde[] = { 0.0, 1.0, 0.0, 1.0 };
        GLfloat cor_branco[] = { 1.0, 1.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, cor_verde);
        
        //glMaterialfv(GL_FRONT, GL_AMBIENT, cor_verde);
        glMaterialfv(GL_FRONT, GL_SPECULAR, cor_branco);
        glMaterialf(GL_FRONT, GL_SHININESS, 60);

        for (int i = 0; i < faces.size(); i++)
        {
            Face face = faces[i];


            //glNormal3f(0, 0, 1);
            //glNormal3f(0, 1, 0);
            
            if (!face.normais.empty()) {
                glNormal3f(face.normais[0], face.normais[1], face.normais[2]);
            }
            else {
                glNormal3f(0, 0, 1);
            }

            glColor3f(colourRed[0], colourRed[1], colourRed[2]); // colour
            glVertex3f(vertices[face.vertices[0]][0], vertices[face.vertices[0]][1], vertices[face.vertices[0]][2] + position_z_offset);
            //glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
            glColor3f(colourBlue[0], colourBlue[1], colourBlue[2]); // colour
            glVertex3f(vertices[face.vertices[1]][0], vertices[face.vertices[1]][1], vertices[face.vertices[1]][2] + position_z_offset);
            //glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
            glColor3f(colourGreen[0], colourGreen[1], colourGreen[2]); // colour
            glVertex3f(vertices[face.vertices[2]][0], vertices[face.vertices[2]][1], vertices[face.vertices[2]][2] + position_z_offset);
            //glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);

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
    //glLoadIdentity();
    gluPerspective(60, aspect, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void renderObject()
{
    glPushMatrix();


    //determina a posiзгo da luz


    glTranslatef(OffsetPosition[0], OffsetPosition[1], OffsetPosition[2]);
    //glColor3f(1.0, 0.23, 0.27);
    glScalef(EscalarPosition, EscalarPosition, EscalarPosition);
    glRotatef(rotacao[0], 0, 1, 0);
    glRotatef(rotacao[1], 1, 0, 0);
    glRotatef(rotacao[2], 0, 0, 1);

    GLfloat posicao_luz[] = { 0, 0 , 19.5 ,1 };

    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz);
    glLightfv(GL_LIGHT2, GL_POSITION, posicao_luz);
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
//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    renderObject();
    glutSwapBuffers();
}

void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);   // Habilita o culling de profundidade
    glDepthFunc(GL_LEQUAL);    // Define o tipo de teste de profundidade

    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glLoadIdentity();
    

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);


    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular);

    // Ativa o "Color Tracking"
    glEnable(GL_COLOR_MATERIAL);

    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    //glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv)
{
    OffsetPosition[2] = OffsetPosition[2] - 20;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Carregar OBJ");
    initGL();
    glutKeyboardFunc(keyboard3D);
    glutSpecialFunc(keyboard_special3D);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj("data/porsche.obj",0);
    glutMainLoop();
    return 0;
}