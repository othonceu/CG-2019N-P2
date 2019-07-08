/**
 *  Implementação de uma aplicação gráfica usando OpenGL que mostra uma esfera e um cubo. A esfera estar
 *  à esquerda do cubo. Na exata posição onde está a esfera,existe uma fonte de luz sendo vermelha
 *  (​ GL_LIGHT​ ).O cubo gira ao redor do próprio eixo.
 *
 *  Autor: Othon Paiva Arêas Costa <othonceu7@gmail.com>
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float RotaZ   = 0;
float angLight = 0;
int gTimeLastUpdateMs = 0;

// Define how many frames per seconds we want our
const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;


GLfloat mat_specular[] = { 1, 0, 1, 1 };
GLfloat mat_shininess[] = { 100};

GLfloat light_0_position[] = { 0, 1, 0, 0};
GLfloat light_0_difuse[]   = { 1, 0, 0 };  //RED
GLfloat light_0_specular[] = { 1, 0, 1 };  //WHITE
GLfloat light_0_ambient[]  = { 0.2, 0.2, 0.2 };

GLfloat light_1_position[] = { -4, 0, 0, 0 };
GLfloat light_1_difuse[]   = { 1, 0, 0 };  //GREEN
GLfloat light_1_specular[] = { 1, 1, 1 };  //WHITE
GLfloat light_1_ambient[]  = { 1.2, 0.2, 1.2 };

void init(void)
{
   glClearColor (1.0, 1.0, 1.0, 1.0);

   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_0_difuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
   glLightfv(GL_LIGHT0, GL_AMBIENT,  light_0_ambient);

   glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
   glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_1_difuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_specular);
   glLightfv(GL_LIGHT1, GL_AMBIENT,  light_1_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
		glTranslated(4,0,0);
		glRotated(RotaZ, 0.f, 1, 0.f);
		glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
		glTranslated(light_1_position[0],light_1_position[1] , light_1_position[2]);
		glutSolidSphere (1.0, 20, 16);
	glPopMatrix();

	
	glutSwapBuffers();
}

void update(double delta)
{
	
	
	if(RotaZ >= 360)
	{
		RotaZ= 0;
	
	}
	RotaZ +=2;
}
void reshape (int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (-10, 10, -10,10, -10.0, 10.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   if( key == 'w')
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void internalUpdate(int value)
{
	int timeNowMs = glutGet(GLUT_ELAPSED_TIME);
	double deltaSeconds = (timeNowMs - gTimeLastUpdateMs) / 1000.0;

	// Save the time update() was called
	gTimeLastUpdateMs = timeNowMs;

	// Invoke our update() function
	update(deltaSeconds);

	// Request a new frame rendering
	glutPostRedisplay();

	// Re-schedule the update() function to be called after a few
	// milliseconds again.
	glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);
}





int main(int argc, char** argv)
{
   glutInit(&argc, argv);

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Lighting. Press W or any other key");
   printf("Type W or any other key to change the visualization mode.\n");
   
   // Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);
   
   
   init();
   
  
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc(UPDATE_INTERVAL_MS, internalUpdate, 0);
   
   glutMainLoop();
   return 0;
}

