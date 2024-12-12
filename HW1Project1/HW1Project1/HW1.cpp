#include<GL/freeglut.h>

int FlatShaded = 0;	int Wireframed = 0;
//flatshading과 Wireframe을 토글링하기 위한 부울 변수

int ViewX = 0, ViewY = 0;
// 마우스 움직임에 따라 시점을 바꾸기 위한 변수 

GLfloat MyVertices1[4][3] = { {0.0, -0.3, 0.1}, {0.1, -0.3, -0.1}, {-0.1, -0.3, -0.1}, {0.0, -0.1, 0.0} };   //서있는 사면체
GLfloat MyVertices2[4][3] = { {0.0, -0.15, -0.12}, {-0.1, -0.15, 0.08}, {0.1, -0.15, 0.08}, {0.0, -0.35, -0.02} };  //뒤집어진 사면체
GLubyte VertexList[12] = { 0,1,2 , 0,1,3 , 0,2,3 , 1,2,3 };

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
	ViewX = X;
	ViewY = Y;
	// 마우스 움직임 X,Y를 전역 변수인 ViewX, ViewY에 할당
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 's':
		if (FlatShaded) {
			FlatShaded = 0;
			glShadeModel(GL_SMOOTH);
		}
		else {
			FlatShaded = 1;
			glShadeModel(GL_FLAT);
		}
		glutPostRedisplay();
		break;
	case 'w':
		if (Wireframed) {
			Wireframed = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 채움 모드
		}
		else {
			Wireframed = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 와이어프레임 모드
		}
		glutPostRedisplay();
		break;
	}
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0,
		ViewX, ViewY, 100.0,             //z 값이 작아지면 화면 감도가 확봐뀌어서 키움
		0.0, 1.0, 0.0);

	glPushMatrix();                   //탁자
	glTranslatef(0.0, -0.4, 0.0);
	glScalef(1.5, 0.1, 1.5);
	glutSolidCube(1.0); 
	glPopMatrix();
	for (int i = -1; i <= 1; i += 2) { //다리
		for (int j = -1; j <= 1; j += 2) {
			glPushMatrix();
			glTranslatef(i * 0.7, -0.6, j * 0.7);
			glScalef(0.05, 0.4, 0.05); 
			glutSolidCube(1.0);
			glPopMatrix();
		}
	}

	glPushMatrix(); // 주전자
	glTranslatef( 0.5, -0.25, 0.5);
	glutSolidTeapot(0.15);
	glPopMatrix();

	glPushMatrix();  //구
	glTranslatef(-0.5, -0.25, -0.5);
	glutSolidSphere(0.10, 25, 25);
	glPopMatrix();

	glPushMatrix(); //사면체
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices1);
	for (GLint i = 0; i < 4; i++)
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &VertexList[3 * i]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();

	glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices2);
	for (GLint i = 0; i < 4; i++)
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, &VertexList[3 * i]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	
	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}
