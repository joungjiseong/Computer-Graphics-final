#define STB_IMAGE_IMPLEMENTATION
#include <GL/freeglut.h>
#include <stb_image.h>
#include <math.h>
#include <stdio.h>

// ī�޶� ���� (���� ��ȯ)
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraZoom = 3.0f;   // ī�޶��� ��(�Ÿ�)
GLfloat fov = 45.0f;  // �þ߰� (���� ��ȯ)

#define PI 3.141592 // ����� �׸������� ��

bool lampOn = false; // �ʱⰪ: ���� ����

// �ؽ�ó ID
GLuint textureID[5]; // �ý�ó �� �̹��� �ּ� �迭

// �ؽ�ó �ε� �Լ�
GLuint loadTexture(const char* filename) {  
    int width, height, channels;            // �̹����� �ʺ�, ����, ä�� �� ���� ����
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);   // �̹����� ������ ������ ����
    if (!data) {                            // �̹��� �ε� ���� ��, ���� �޽����� ����ϰ� 0�� ��ȯ
        printf("Failed to load texture: %s\n", filename);
        return 0;
    }

    GLuint texture;                         // �ؽ�ó ��ü ������ ���� ����
    glGenTextures(1, &texture);             // �ؽ�ó ��ü�� 1�� �����ϰ� texture ������ �� ID�� ����
    glBindTexture(GL_TEXTURE_2D, texture);  // ������ �ؽ�ó�� ���� Ȱ��ȭ�� �ؽ�ó�� ���ε�

    // �ؽ�ó �Ķ���� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // �ؽ�ó�� ���� ���� �ݺ� ��� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // �ؽ�ó�� ���� ���� �ݺ� ��� ����
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // �ؽ�ó ��� �� ���� ������ ���
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // �ؽ�ó Ȯ�� �� ���� ������ ���

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   // �ؽ�ó �̹����� �Ӽ��� OpenGL�� ����

    stbi_image_free(data);  // �̹��� ������ �޸� ����
    return texture;         // ������ �ؽ�ó ��ü ID�� ��ȯ
}

void textureCube() {        // �ý�ó�� ������ ť�� �׸��� �Լ�
    glBegin(GL_QUADS);      // ť���� �� ���� �׸� �� 4���� ���� �׸���
    // �ո�
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);   // ���� �Ʒ��� 3���� ���� ���� ����
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);    // ������ �Ʒ��� 3���� ���� ���� ����
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);     // ������ ���� 3���� ���� ���� ����
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);    // ���� ���� 3���� ���� ���� ����

    // �޸� (�ո��� �ݺ�)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // ���ʸ� (�ո��� �ݺ�)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // �����ʸ� (�ո��� �ݺ�)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // ���� (�ո��� �ݺ�)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // �Ʒ��� (�ո��� �ݺ�)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd(); // ť��׸��� ��
}

void textureCylinder(float radius, float height, int segments) {    // �ý�ó�� �߰��� ����� �׸��� �Լ�
    float angleStep = 2.0f * PI / segments;             // ���ָ� ���׸�Ʈ ������ ����

    // ���� �׸���
    glBegin(GL_QUADS);                      // �� ���׸�Ʈ�� �簢������ �׷���
    for (int i = 0; i < segments; i++) {
        float theta1 = i * angleStep;       // ���� ���׸�Ʈ�� ù ��° ����
        float theta2 = (i + 1) * angleStep; // ���� ���׸�Ʈ�� ù ��° ����

        // ���׸�Ʈ�� �� ���� ���� x, z ��ǥ ���
        float x1 = radius * cosf(theta1);
        float z1 = radius * sinf(theta1);
        float x2 = radius * cosf(theta2);
        float z2 = radius * sinf(theta2);

        // �ؽ�ó ��ǥ ��� (���׸�Ʈ���� �ؽ�ó�� ���� �����ǵ��� ����)
        float s1 = (float)i / segments;
        float s2 = (float)(i + 1) / segments;

        // ������ �ؽ�ó �Ʒ��� ����
        glTexCoord2f(s1, 0.0f); glVertex3f(x1, -height / 2, z1);
        glTexCoord2f(s2, 0.0f); glVertex3f(x2, -height / 2, z2);
        // ������ �ؽ�ó ���� ����
        glTexCoord2f(s2, 1.0f); glVertex3f(x2, height / 2, z2);
        glTexCoord2f(s1, 1.0f); glVertex3f(x1, height / 2, z1);
    }
    glEnd();    // ���� �׸��� �Ϸ�

    // �Ʒ� ����
    glBegin(GL_TRIANGLE_FAN);       // GL_TRIANGLE_FAN ���� ������ �׸�
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, -height / 2, 0.0f); // �߽� ��
    for (int i = 0; i <= segments; i++) {
        float theta = i * angleStep;    // ���� ���
        float x = radius * cosf(theta); // ���� x ��ǥ
        float z = radius * sinf(theta); // ���� z ��ǥ
        // ���� �ؽ�ó ��ǥ
        float s = 0.5f + 0.5f * cosf(theta);// x�࿡ ���� �ؽ�ó ��ǥ
        float t = 0.5f + 0.5f * sinf(theta);// z�࿡ ���� �ؽ�ó ��ǥ
        glTexCoord2f(s, t);                 // �ؽ�ó ��ǥ ����
        glVertex3f(x, -height / 2, z);      // ������ �� ���� �׸���
    }
    glEnd(); // �Ʒ� ���� �׸��� ����

    // �� ���� (�Ʒ� ���� �׸����� �ݺ�)
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, height / 2, 0.0f); // �߽�
    for (int i = 0; i <= segments; i++) {
        float theta = i * angleStep;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        float s = 0.5f + 0.5f * cosf(theta); // ���� �ؽ�ó ��ǥ
        float t = 0.5f + 0.5f * sinf(theta);
        glTexCoord2f(s, t);
        glVertex3f(x, height / 2, z);
    }
    glEnd();
}

// �ʱ�ȭ �Լ�
void init() {
    glEnable(GL_DEPTH_TEST);  // ���� �׽�Ʈ Ȱ��ȭ
    glEnable(GL_LIGHTING);    // ���� Ȱ��ȭ
    glEnable(GL_LIGHT0);      // �⺻ ���� ���
    glEnable(GL_COLOR_MATERIAL); // ���� �ݻ� Ȱ��ȭ
    glEnable(GL_TEXTURE_2D);  // �ؽ�ó Ȱ��ȭ

    // ���� ����
    GLfloat lightPos[] = { 2.0f, 4.0f, -3.0f, 0.0f };  // ������ ��ġ
    GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 0.5f }; // �ֺ���
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// �ݻ籤
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.5f }; // Ȯ�걤
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);        // ������ ��ġ ����
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);     // �ֺ��� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);     // Ȯ�걤 ����
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);   // �ݻ籤 ����

    GLfloat lightPosi[] = { 0.7f, 0.4f, -1.3f, 1.0f };  // ������ ��ġ
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosi);       // ������ ��ġ ����
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);     // �ֺ��� ����
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);     // Ȯ�걤 ����
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);   // �ݻ籤 ����

    textureID[0] = loadTexture("image/texture1.jpg"); // ���� ���� ������ �̹���
    textureID[1] = loadTexture("image/texture2.jpg"); // ��ο� ���� ������ �̹���
    textureID[2] = loadTexture("image/texture3.jpg"); // �����η��� ������ �̹���
    textureID[3] = loadTexture("image/texture4.jpg"); // ȭ�� �̹���
    textureID[4] = loadTexture("image/texture5.jpg"); // Ű���� �̹���

    glClearColor(0.8f, 0.9f, 1.0f, 1.0f); // ���� (���� �ϴû�)
}

// å�� �׸��� �Լ� (�� ��ȯ)
void drawDesk() {
    // �ؽ�ó �ε�
    glPushMatrix();                     // å�� ��
    glTranslatef(0.0f, 0.0f, -0.5f);    // ��ġ ����
    glScalef(2.0f, 0.1f, 1.5f);         // å�� ũ�� ����
    glEnable(GL_TEXTURE_2D);            // �ؽ�ó ��� Ȱ��ȭ
    glBindTexture(GL_TEXTURE_2D, textureID[0]); // å�� �ǿ� �ؽ�ó ����
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó�� ���� ������ �޵��� ����
    textureCube();                      // �ؽ�ó�� ����� ť�� �׸���
    glDisable(GL_TEXTURE_2D);           // �ؽ�ó ��� ��Ȱ��ȭ
    glPopMatrix();                      // å�� �� �׸��� ����

    glPushMatrix();                     // �ٸ� ������
    glTranslatef(0.0f, -0.3f, -1.0f);   // ��ġ ����
    glScalef(1.95f, 0.6f, 0.1f);        // å�� ũ�� ����
    glEnable(GL_TEXTURE_2D);            // �ؽ�ó ��� Ȱ��ȭ
    glBindTexture(GL_TEXTURE_2D, textureID[0]); // �ٸ� �����ǿ� �ؽ�ó ����
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó�� ���� ������ �޵��� ����
    textureCube();                      // �ؽ�ó�� ����� ť�� �׸���
    glDisable(GL_TEXTURE_2D);           // �ؽ�ó ��� ��Ȱ��ȭ
    glPopMatrix();                      // �ٸ� ������ �׸��� ����

    // å�� �ٸ� 
    for (float x = -0.95f; x <= 1.0f; x += 1.9f) { 
        glPushMatrix();                     // å�� �ٸ�
        glTranslatef(x, -0.55f, -0.5f);     // �¿� ��ġ ����
        glScalef(0.099f, 1.1f, 1.45f);      // �ٸ� ũ�� ����
        glEnable(GL_TEXTURE_2D);            // �ؽ�ó ��� Ȱ��ȭ
        glBindTexture(GL_TEXTURE_2D, textureID[0]); // �ٸ��� �ؽ�ó ����
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // �ؽ�ó�� ���� ������ �޵��� ����
        textureCube();                      // �ؽ�ó�� ����� ť�� �׸���
        glDisable(GL_TEXTURE_2D);           // �ؽ�ó ��� ��Ȱ��ȭ
        glPopMatrix();                      // �ٸ� �׸��� ����
    }
}

// ���� �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawChair() {
    glPushMatrix();                     // ���� �¼�
    glTranslatef(0.0f, -0.5f, 0.0f);   
    glScalef(0.8f, 0.1f, 0.8f);        
    glEnable(GL_TEXTURE_2D);           
    glBindTexture(GL_TEXTURE_2D, textureID[1]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                     // ���� �����
    glTranslatef(0.0f, -0.1f, 0.45f);  
    glRotatef(15, 1, 0, 0);            
    glScalef(0.8f, 0.8f, 0.1f);        
    glEnable(GL_TEXTURE_2D);           
    glBindTexture(GL_TEXTURE_2D, textureID[1]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ���� �ٸ�
    for (float x = -0.35f; x <= 0.35f; x += 0.7f) {
        for (float z = 0.15f; z <= 0.85f; z += 0.7f) {
            glPushMatrix();                                         // ���� �ٸ�
            glTranslatef(x, -0.85f, z - 0.5f);                      
            GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // �ݻ籤 (���)
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // ��ü �ݻ籤 ����
            glEnable(GL_TEXTURE_2D);            
            glBindTexture(GL_TEXTURE_2D, textureID[2]);
            textureCylinder(0.05f, 0.7f, 20);                       // �ؽ�ó ����� ����� �׸���
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }
    }
}

// ��Ʈ�� �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawLaptop() {
    glPushMatrix();                     // ��Ʈ�� ȭ��
    glColor3f(0.0f, 0.0f, 0.0f);        // ������
    glTranslatef(-0.3f, 0.275f, -0.98f);
    glRotatef(-30, 1, 0, 0);            // ȭ�� ����
    glScalef(0.6f, 0.4f, 0.02f);        // ȭ�� ũ�� ����
    glutSolidCube(1.0);                 // ȭ��: ������ü
    glPopMatrix();

    glPushMatrix();                     // ��Ʈ�� ȭ��: �ؽ�ó
    glTranslatef(-0.3f, 0.29f, -0.974f);
    glRotatef(-30, 1, 0, 0);            
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[3]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.2f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, -0.2f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, 0.2f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.2f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                     // ��Ʈ�� �ϴ�
    glColor3f(0.2f, 0.2f, 0.2f);        
    glTranslatef(-0.3f, 0.075f, -0.7f); 
    glScalef(0.6f, 0.05f, 0.4f);        
    glutSolidCube(1.0);                 
    glPopMatrix();

    glPushMatrix();                     // ��Ʈ�� �ϴ�
    glTranslatef(-0.3f, 0.101f, -0.7f); 
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[4]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    glBegin(GL_QUADS);
    glTexCoord2f(0.11f, 0.26f); glVertex3f(-0.3f, 0.0f, -0.2f);
    glTexCoord2f(0.89f, 0.26f); glVertex3f(0.3f, 0.0f, -0.2f);
    glTexCoord2f(0.89f, 0.73f); glVertex3f(0.3f, 0.0f, 0.2f);
    glTexCoord2f(0.11f, 0.73f); glVertex3f(-0.3f, 0.0f, 0.2f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Ű���� �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawKeyboard() {
    glPushMatrix();                     // Ű����
    glColor3f(0.3f, 0.3f, 0.3f);        // ��ο� ȸ��
    glTranslatef(-0.3f, 0.075f, -0.2f); 
    glScalef(0.6f, 0.05f, 0.2f);        
    glutSolidCube(1.0);                 
    glPopMatrix();

    glPushMatrix();                     // ��Ʈ�� �ϴ�
    glTranslatef(-0.3f, 0.101f, -0.2f); 
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[4]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    glBegin(GL_QUADS);
    glTexCoord2f(0.11f, 0.26f); glVertex3f(-0.3f, 0.0f, -0.1f);
    glTexCoord2f(0.89f, 0.26f); glVertex3f(0.3f, 0.0f, -0.1f);
    glTexCoord2f(0.89f, 0.74f); glVertex3f(0.3f, 0.0f, 0.1f);
    glTexCoord2f(0.11f, 0.74f); glVertex3f(-0.3f, 0.0f, 0.1f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// ���콺 �е� �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawMousepad() {
    glPushMatrix();                     // ���콺 �е�
    glColor3f(0.0f, 0.0f, 0.0f);        // ����
    glTranslatef(0.5f, 0.065f, -0.2f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // �е� ������
    glutSolidCylinder(0.2f, 0.03f, 20, 20); // �е�: �����
    glPopMatrix();
}

// ���콺 �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawMouse() {
    glPushMatrix();                     // ���콺
    glTranslatef(0.5f, 0.08f, -0.2f);   // ��ġ ����
        glPushMatrix();                     // ���콺 ��ü
        glColor3f(0.8f, 0.8f, 0.8f);        // ���� ȸ��
        glScalef(0.05f, 0.06f, 0.1f);       // ��ü ũ�� ����
        glutSolidSphere(1.0, 30, 30);       // ���콺 ��ü : ��ü
        glPopMatrix();

        glPushMatrix();                     // ���콺 ��
        glColor3f(0.3f, 0.3f, 0.3f);        // ��ο� ȸ��
        glTranslatef(-0.005f, 0.05f, -0.05f);// ��ġ ����
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // �� �����
        glutSolidCylinder(0.01f, 0.01f, 20, 20);  // ��������� �� ����
        glPopMatrix();
    glPopMatrix();
}

// ���� �׸��� �Լ� (������ ���� ��� ��ɾ�� �ּ� ����)
void drawLamp(bool lampOn) {
    glPushMatrix();                     // ���� ��ħ��
    glTranslatef(0.7f, 0.075f, -0.8f);  
    glScalef(0.2f, 0.05f, 0.15f);       
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // �ݻ籤 (���)
    GLfloat mat_shininess[] = { 100.0f };                   // ���� ��¦�� ����
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // ��ü �ݻ籤 ����
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // ��ü ��¦�� ����
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[2]);             // �����η��� �ؽ�ó
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                     // ���� ���
    glTranslatef(0.7f, 0.2f, -0.8f);    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // ��ü �ݻ籤 ����
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // ��ü ��¦�� ����
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[2]);             // �����η��� �ؽ�ó
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    textureCylinder(0.02f, 0.35f, 20);                      // �е�: �����
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                         // ���� �Ӹ�
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // ��ü �ݻ籤 ����
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // ��ü ��¦�� ����
    if(lampOn) glColor3f(1.0f, 1.0f, 1.0f); // ������ ���
    else glColor3f(0.4f, 0.4f, 0.4f);       // ������ ȸ��
    glTranslatef(0.7f, 0.4f, -0.8f);        
    glutSolidSphere(0.1f, 20, 20);          // ����: ��ü
    glPopMatrix();
    if(lampOn)                          // ������ on/off ����
        glEnable(GL_LIGHT1);           // ���� Ȱ��ȭ
    else
        glDisable(GL_LIGHT1);          // ���� ��Ȱ��ȭ
}

// ���÷��� �Լ�
void MyDisplay() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, 1.33, 1.0, 100.0);  // ���ٹ� ���� (FOV 45��, near 1.0, far 100.0)
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ȭ�� �� ���� ���� �ʱ�ȭ
    glLoadIdentity();           // ��ȯ ��� �ʱ�ȭ (���� ��ķ� ����)

    // ī�޶� ��ȯ
    gluLookAt(
        0.0f, 0.0f, 3.0f + cameraZoom,  // ī�޶� ��ġ (z������ Ȯ��/���)
        0.0f, 0.0f, 0.0f,  // ī�޶� ���� ����
        0.0f, 1.0f, 0.0f   // ���� ����
    );

    glRotated(cameraAngleX, 0.0f, 1.0f, 0.0f);  // Y�� ���� ī�޶� ȸ�� (�¿� ȸ��)
    glRotated(cameraAngleY, 1.0f, 0.0f, 0.0f);  // X�� ���� ī�޶� ȸ�� (���Ʒ� ȸ��)
        
    // ��ü �׸���
    drawDesk();         // å��
    drawChair();        // ����
    drawLaptop();       // ��Ʈ��
    drawKeyboard();     // Ű����
    drawMousepad();     // ���콺 �е�
    drawMouse();        // ���콺
    drawLamp(lampOn);   // ����

    glutSwapBuffers(); // ���� ���۸� ��ü�Ͽ� ȭ�鿡 ���
}

void printHelp() {      // ���� ��� �Լ�
    printf("����:\n");
    printf(" - w/s: ī�޶� ��/�Ʒ� �̵�\n");
    printf(" - a/d: ī�޶� ��/�� �̵�\n");
    printf(" - +/-: ī�޶� �� ��/�ƿ�\n");
    printf(" - q/e: ī�޶� �þ߰� Ȯ��/���\n");
    printf(" - o: ���� Ű�� ����\n");
    printf(" - h: ���� ǥ��\n");
    printf(" - ESC: ����\n");
}

// Ű���� �Է� ó��
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': cameraAngleX += 1.0f; break;  // ���� ȸ��
    case 'd': cameraAngleX -= 1.0f; break;  // ������ ȸ��
    case 'w': cameraAngleY += 1.0f; break;  // ���� ȸ��
    case 's': cameraAngleY -= 1.0f; break;  // �Ʒ��� ȸ��
    case '+': cameraZoom -= 0.1f; break;    // �� ��
    case '-': cameraZoom += 0.1f; break;    // �� �ƿ�
    case 'o': lampOn = !lampOn; break;      // ���� on/off
    case 'h': printHelp(); break;           // ���� ǥ��
    case 'q': fov += 5.0f; break;           // �þ߰� Ȯ��
    case 'e': fov -= 5.0f; break;           // �þ߰� ���
    case 27: exit(0); break;                // ESC Ű
    }
    glutPostRedisplay();                    // ȭ�� �ٽ� �׸��� ȣ��
}

// ���� �Լ�
int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // GLUT ���̺귯�� �ʱ�ȭ �� ����� �μ� ó��
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // ���÷��� ��� ���� (RGB, ���� ����, ���� ����)
    glutInitWindowSize(800, 600);                   // ������ ũ�� ����
    glutCreateWindow("å�� ���");                  // ������ ���� ����

    init();         // �ʱ�ȭ �Լ� ȣ��

    glMatrixMode(GL_PROJECTION);        // ���� ��� ���� ��ȯ
    glLoadIdentity();                   // ���� ���� ��� �ʱ�ȭ
    glMatrixMode(GL_MODELVIEW);         // �𵨺� ��� ���� ��ȯ

    glutDisplayFunc(MyDisplay); // ���÷��� ���� �� MyDisplay ȣ��
    glutKeyboardFunc(keyboard); // Ű���� �Է� ó�� �Լ� ���

    printHelp();                // ���� ���

    glutMainLoop();             // GLUT �̺�Ʈ ���� ����
}
