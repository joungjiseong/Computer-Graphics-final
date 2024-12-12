#include<GL/freeglut.h>

float y = 10.0f, speed = 0.0f;
float gravity = -0.00098f;
bool isLow = false, ballCon = false;
float ballx = 1, bally = 1;
bool isWireframe = false;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glPushMatrix();  //바닥
	glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(10.0, 0.1, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();

	glPushMatrix();  //구
	glColor3f(1, 1, 1);
	glTranslatef(0.0, y, 0.0);
	glScalef(ballx, bally, ballx);
	if (isWireframe) {
		glutWireSphere(0.5, 25, 25);  // 와이어프레임 모드
	}
	else {
		glutSolidSphere(0.5, 25, 25); // 채움 모드
	}
	glPopMatrix();

	if (!ballCon) {
		y += speed;
		speed += gravity;
		if (y > 10.0f) {
			y = 10.0f;
			speed = 0;
		}
		if (y <= -0.5f) {
			y = -0.5f;
			speed *= -0.95f;
			isLow = true;
			ballCon = true;
		}
	}
	else {
		if (isLow) {
			ballx *= 1.01f;
			bally *= 0.095f;
			if (ballx > 1.6f)
				isLow = false;
		}
		else {
			ballx *= 0.1f;
			bally *= 1.005f;
			if (ballx < 0.8f) {
				ballx = 1.0f;
				bally = 1.0f;
				ballCon = false;
			}
		}
	}

	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 's':
		isWireframe = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 채움 모드
		glutPostRedisplay();
		break;
	case 'w':
		isWireframe = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 와이어프레임 모드
		glutPostRedisplay();
		break;
	case 'r':
		gravity /= 10;
		break;
	case 'd':
		gravity *= 10;
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutCreateWindow("OpenGL Ploject 2");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.33, 1.0, 100.0);
	glTranslatef(0.0f, -2.0f, -15.0f); // 카메라 위치 설정

	glClearColor(0.4, 0.4, 0.4, 0.0);
	glutDisplayFunc(MyDisplay);
	glutIdleFunc(MyDisplay);  // MyDisplay 함수를 유휴 상태 함수로 등록

	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
}
