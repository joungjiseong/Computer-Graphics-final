#define STB_IMAGE_IMPLEMENTATION
#include <GL/freeglut.h>
#include "stb_image.h"
#include <math.h>
#include <stdio.h>

// 카메라 각도 (시점 변환)
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraZoom = 3.0f;   // 카메라의 줌(거리)
GLfloat fov = 45.0f;  // 시야각 (투상 변환)

#define PI 3.141592 // 원기둥 그리기위한 것

bool lampOn = false; // 초기값: 램프 꺼짐

// 텍스처 ID
GLuint textureID[5]; // 택스처 용 이미지 주소 배열

// 텍스처 로드 함수
GLuint loadTexture(const char* filename) {  
    int width, height, channels;            // 이미지의 너비, 높이, 채널 수 저장 변수
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);   // 이미지의 정보를 변수에 저장
    if (!data) {                            // 이미지 로드 실패 시, 오류 메시지를 출력하고 0을 반환
        printf("Failed to load texture: %s\n", filename);
        return 0;
    }

    GLuint texture;                         // 텍스처 객체 생성할 변수 선언
    glGenTextures(1, &texture);             // 텍스처 객체를 1개 생성하고 texture 변수에 그 ID를 저장
    glBindTexture(GL_TEXTURE_2D, texture);  // 생성한 텍스처를 현재 활성화된 텍스처로 바인딩

    // 텍스처 파라미터 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // 텍스처의 가로 방향 반복 방식 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       // 텍스처의 세로 방향 반복 방식 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // 텍스처 축소 시 선형 보간법 사용
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // 텍스처 확대 시 선형 보간법 사용

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);   // 텍스처 이미지와 속성을 OpenGL에 전달

    stbi_image_free(data);  // 이미지 데이터 메모리 해제
    return texture;         // 생성된 텍스처 객체 ID를 반환
}

void textureCube() {        // 택스처를 적용한 큐브 그리는 함수
    glBegin(GL_QUADS);      // 큐브의 각 면을 그릴 때 4개의 점을 그린다
    // 앞면
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);   // 왼쪽 아래와 3차원 공간 점과 연결
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);    // 오른쪽 아래와 3차원 공간 점과 연결
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);     // 오른쪽 위와 3차원 공간 점과 연결
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);    // 왼쪽 위와 3차원 공간 점과 연결

    // 뒷면 (앞면의 반복)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // 왼쪽면 (앞면의 반복)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // 오른쪽면 (앞면의 반복)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // 윗면 (앞면의 반복)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // 아랫면 (앞면의 반복)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd(); // 큐브그리기 끝
}

void textureCylinder(float radius, float height, int segments) {    // 택스처를 추가한 원기둥 그리는 함수
    float angleStep = 2.0f * PI / segments;             // 원주를 세그먼트 개수로 나눔

    // 측면 그리기
    glBegin(GL_QUADS);                      // 각 세그먼트는 사각형으로 그려짐
    for (int i = 0; i < segments; i++) {
        float theta1 = i * angleStep;       // 현재 세그먼트의 첫 번째 각도
        float theta2 = (i + 1) * angleStep; // 다음 세그먼트의 첫 번째 각도

        // 세그먼트의 각 점에 대한 x, z 좌표 계산
        float x1 = radius * cosf(theta1);
        float z1 = radius * sinf(theta1);
        float x2 = radius * cosf(theta2);
        float z2 = radius * sinf(theta2);

        // 텍스처 좌표 계산 (세그먼트별로 텍스처가 고르게 분포되도록 설정)
        float s1 = (float)i / segments;
        float s2 = (float)(i + 1) / segments;

        // 분포된 텍스처 아래쪽 연결
        glTexCoord2f(s1, 0.0f); glVertex3f(x1, -height / 2, z1);
        glTexCoord2f(s2, 0.0f); glVertex3f(x2, -height / 2, z2);
        // 분포된 텍스처 위쪽 연결
        glTexCoord2f(s2, 1.0f); glVertex3f(x2, height / 2, z2);
        glTexCoord2f(s1, 1.0f); glVertex3f(x1, height / 2, z1);
    }
    glEnd();    // 측면 그리기 완료

    // 아래 원판
    glBegin(GL_TRIANGLE_FAN);       // GL_TRIANGLE_FAN 모드로 원판을 그림
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, -height / 2, 0.0f); // 중심 점
    for (int i = 0; i <= segments; i++) {
        float theta = i * angleStep;    // 각도 계산
        float x = radius * cosf(theta); // 원의 x 좌표
        float z = radius * sinf(theta); // 원의 z 좌표
        // 원형 텍스처 좌표
        float s = 0.5f + 0.5f * cosf(theta);// x축에 대한 텍스처 좌표
        float t = 0.5f + 0.5f * sinf(theta);// z축에 대한 텍스처 좌표
        glTexCoord2f(s, t);                 // 텍스처 좌표 설정
        glVertex3f(x, -height / 2, z);      // 원판의 각 점을 그린다
    }
    glEnd(); // 아래 원판 그리기 종료

    // 위 원판 (아래 원판 그리기의 반복)
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, height / 2, 0.0f); // 중심
    for (int i = 0; i <= segments; i++) {
        float theta = i * angleStep;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        float s = 0.5f + 0.5f * cosf(theta); // 원형 텍스처 좌표
        float t = 0.5f + 0.5f * sinf(theta);
        glTexCoord2f(s, t);
        glVertex3f(x, height / 2, z);
    }
    glEnd();
}

// 초기화 함수
void init() {
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화
    glEnable(GL_LIGHTING);    // 광원 활성화
    glEnable(GL_LIGHT0);      // 기본 광원 사용
    glEnable(GL_COLOR_MATERIAL); // 재질 반사 활성화
    glEnable(GL_TEXTURE_2D);  // 텍스처 활성화

    // 광원 설정
    GLfloat lightPos[] = { 2.0f, 4.0f, -3.0f, 0.0f };  // 광원의 위치
    GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 0.5f }; // 주변광
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// 반사광
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 0.5f }; // 확산광
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);        // 광원의 위치 설정
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);     // 주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);     // 확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);   // 반사광 설정

    GLfloat lightPosi[] = { 0.7f, 0.4f, -1.3f, 1.0f };  // 광원의 위치
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosi);       // 광원의 위치 설정
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);     // 주변광 설정
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);     // 확산광 설정
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);   // 반사광 설정

    textureID[0] = loadTexture("image/texture1.jpg"); // 밝은 나무 재질의 이미지
    textureID[1] = loadTexture("image/texture2.jpg"); // 어두운 나무 재질의 이미지
    textureID[2] = loadTexture("image/texture3.jpg"); // 스테인레스 재질의 이미지
    textureID[3] = loadTexture("image/texture4.jpg"); // 화면 이미지
    textureID[4] = loadTexture("image/texture5.jpg"); // 키보드 이미지

    glClearColor(0.8f, 0.9f, 1.0f, 1.0f); // 배경색 (밝은 하늘색)
}

// 책상 그리기 함수 (모델 변환)
void drawDesk() {
    // 텍스처 로드
    glPushMatrix();                     // 책상 판
    glTranslatef(0.0f, 0.0f, -0.5f);    // 위치 조정
    glScalef(2.0f, 0.1f, 1.5f);         // 책상 크기 조정
    glEnable(GL_TEXTURE_2D);            // 텍스처 사용 활성화
    glBindTexture(GL_TEXTURE_2D, textureID[0]); // 책상 판에 텍스처 적용
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // 텍스처가 조명 영향을 받도록 설정
    textureCube();                      // 텍스처가 적용된 큐브 그리기
    glDisable(GL_TEXTURE_2D);           // 텍스처 사용 비활성화
    glPopMatrix();                      // 책상 판 그리기 종료

    glPushMatrix();                     // 다리 가림판
    glTranslatef(0.0f, -0.3f, -1.0f);   // 위치 조정
    glScalef(1.95f, 0.6f, 0.1f);        // 책상 크기 조정
    glEnable(GL_TEXTURE_2D);            // 텍스처 사용 활성화
    glBindTexture(GL_TEXTURE_2D, textureID[0]); // 다리 가림판에 텍스처 적용
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // 텍스처가 조명 영향을 받도록 설정
    textureCube();                      // 텍스처가 적용된 큐브 그리기
    glDisable(GL_TEXTURE_2D);           // 텍스처 사용 비활성화
    glPopMatrix();                      // 다리 가림판 그리기 종료

    // 책상 다리 
    for (float x = -0.95f; x <= 1.0f; x += 1.9f) { 
        glPushMatrix();                     // 책상 다리
        glTranslatef(x, -0.55f, -0.5f);     // 좌우 위치 조정
        glScalef(0.099f, 1.1f, 1.45f);      // 다리 크기 조정
        glEnable(GL_TEXTURE_2D);            // 텍스처 사용 활성화
        glBindTexture(GL_TEXTURE_2D, textureID[0]); // 다리에 텍스처 적용
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // 텍스처가 조명 영향을 받도록 설정
        textureCube();                      // 텍스처가 적용된 큐브 그리기
        glDisable(GL_TEXTURE_2D);           // 텍스처 사용 비활성화
        glPopMatrix();                      // 다리 그리기 종료
    }
}

// 의자 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawChair() {
    glPushMatrix();                     // 의자 좌석
    glTranslatef(0.0f, -0.5f, 0.0f);   
    glScalef(0.8f, 0.1f, 0.8f);        
    glEnable(GL_TEXTURE_2D);           
    glBindTexture(GL_TEXTURE_2D, textureID[1]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                     // 의자 등받이
    glTranslatef(0.0f, -0.1f, 0.45f);  
    glRotatef(15, 1, 0, 0);            
    glScalef(0.8f, 0.8f, 0.1f);        
    glEnable(GL_TEXTURE_2D);           
    glBindTexture(GL_TEXTURE_2D, textureID[1]); 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // 의자 다리
    for (float x = -0.35f; x <= 0.35f; x += 0.7f) {
        for (float z = 0.15f; z <= 0.85f; z += 0.7f) {
            glPushMatrix();                                         // 의자 다리
            glTranslatef(x, -0.85f, z - 0.5f);                      
            GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // 반사광 (흰색)
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 믈체 반사광 설정
            glEnable(GL_TEXTURE_2D);            
            glBindTexture(GL_TEXTURE_2D, textureID[2]);
            textureCylinder(0.05f, 0.7f, 20);                       // 텍스처 적용된 원기둥 그리기
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }
    }
}

// 노트북 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawLaptop() {
    glPushMatrix();                     // 노트북 화면
    glColor3f(0.0f, 0.0f, 0.0f);        // 검은색
    glTranslatef(-0.3f, 0.275f, -0.98f);
    glRotatef(-30, 1, 0, 0);            // 화면 기울기
    glScalef(0.6f, 0.4f, 0.02f);        // 화면 크기 조정
    glutSolidCube(1.0);                 // 화면: 직육면체
    glPopMatrix();

    glPushMatrix();                     // 노트북 화면: 텍스처
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

    glPushMatrix();                     // 노트북 하단
    glColor3f(0.2f, 0.2f, 0.2f);        
    glTranslatef(-0.3f, 0.075f, -0.7f); 
    glScalef(0.6f, 0.05f, 0.4f);        
    glutSolidCube(1.0);                 
    glPopMatrix();

    glPushMatrix();                     // 노트북 하단
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

// 키보드 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawKeyboard() {
    glPushMatrix();                     // 키보드
    glColor3f(0.3f, 0.3f, 0.3f);        // 어두운 회색
    glTranslatef(-0.3f, 0.075f, -0.2f); 
    glScalef(0.6f, 0.05f, 0.2f);        
    glutSolidCube(1.0);                 
    glPopMatrix();

    glPushMatrix();                     // 노트북 하단
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

// 마우스 패드 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawMousepad() {
    glPushMatrix();                     // 마우스 패드
    glColor3f(0.0f, 0.0f, 0.0f);        // 검정
    glTranslatef(0.5f, 0.065f, -0.2f);  
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // 패드 눕히기
    glutSolidCylinder(0.2f, 0.03f, 20, 20); // 패드: 원기둥
    glPopMatrix();
}

// 마우스 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawMouse() {
    glPushMatrix();                     // 마우스
    glTranslatef(0.5f, 0.08f, -0.2f);   // 위치 조정
        glPushMatrix();                     // 마우스 본체
        glColor3f(0.8f, 0.8f, 0.8f);        // 밝은 회색
        glScalef(0.05f, 0.06f, 0.1f);       // 본체 크기 조정
        glutSolidSphere(1.0, 30, 30);       // 마우스 본체 : 구체
        glPopMatrix();

        glPushMatrix();                     // 마우스 휠
        glColor3f(0.3f, 0.3f, 0.3f);        // 어두운 회색
        glTranslatef(-0.005f, 0.05f, -0.05f);// 위치 조정
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // 휠 세우기
        glutSolidCylinder(0.01f, 0.01f, 20, 20);  // 원기둥으로 휠 구현
        glPopMatrix();
    glPopMatrix();
}

// 전등 그리기 함수 (이전과 동일 사용 명령어는 주석 생략)
void drawLamp(bool lampOn) {
    glPushMatrix();                     // 전등 받침대
    glTranslatef(0.7f, 0.075f, -0.8f);  
    glScalef(0.2f, 0.05f, 0.15f);       
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };    // 반사광 (흰색)
    GLfloat mat_shininess[] = { 100.0f };                   // 높은 반짝임 정도
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 믈체 반사광 설정
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // 물체 반짝임 설정
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[2]);             // 스테인레스 텍스처
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    textureCube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                     // 전등 기둥
    glTranslatef(0.7f, 0.2f, -0.8f);    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 믈체 반사광 설정
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // 물체 반짝임 설정
    glEnable(GL_TEXTURE_2D);            
    glBindTexture(GL_TEXTURE_2D, textureID[2]);             // 스테인레스 텍스처
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    textureCylinder(0.02f, 0.35f, 20);                      // 패드: 원기둥
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();                         // 전등 머리
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);      // 믈체 반사광 설정
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);    // 물체 반짝임 설정
    if(lampOn) glColor3f(1.0f, 1.0f, 1.0f); // 켜지면 흰색
    else glColor3f(0.4f, 0.4f, 0.4f);       // 꺼지면 회색
    glTranslatef(0.7f, 0.4f, -0.8f);        
    glutSolidSphere(0.1f, 20, 20);          // 전구: 구체
    glPopMatrix();
    if(lampOn)                          // 램프의 on/off 상태
        glEnable(GL_LIGHT1);           // 광원 활성화
    else
        glDisable(GL_LIGHT1);          // 광원 비활성화
}

// 디스플레이 함수
void MyDisplay() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, 1.33, 1.0, 100.0);  // 원근법 설정 (FOV 45도, near 1.0, far 100.0)
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면 및 깊이 버퍼 초기화
    glLoadIdentity();           // 변환 행렬 초기화 (단위 행렬로 설정)

    // 카메라 변환
    gluLookAt(
        0.0f, 0.0f, 3.0f + cameraZoom,  // 카메라 위치 (z축으로 확대/축소)
        0.0f, 0.0f, 0.0f,  // 카메라가 보는 방향
        0.0f, 1.0f, 0.0f   // 위쪽 방향
    );

    glRotated(cameraAngleX, 0.0f, 1.0f, 0.0f);  // Y축 기준 카메라 회전 (좌우 회전)
    glRotated(cameraAngleY, 1.0f, 0.0f, 0.0f);  // X축 기준 카메라 회전 (위아래 회전)
        
    // 물체 그리기
    drawDesk();         // 책상
    drawChair();        // 의자
    drawLaptop();       // 노트북
    drawKeyboard();     // 키보드
    drawMousepad();     // 마우스 패드
    drawMouse();        // 마우스
    drawLamp(lampOn);   // 전등

    glutSwapBuffers(); // 이중 버퍼를 교체하여 화면에 출력
}

void printHelp() {      // 도움말 출력 함수
    printf("사용법:\n");
    printf(" - w/s: 카메라 위/아래 이동\n");
    printf(" - a/d: 카메라 좌/우 이동\n");
    printf(" - +/-: 카메라 줌 인/아웃\n");
    printf(" - q/e: 카메라 시야각 확대/축소\n");
    printf(" - o: 전등 키고 끄기\n");
    printf(" - h: 도움말 표시\n");
    printf(" - ESC: 종료\n");
}

// 키보드 입력 처리
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': cameraAngleX += 1.0f; break;  // 왼쪽 회전
    case 'd': cameraAngleX -= 1.0f; break;  // 오른쪽 회전
    case 'w': cameraAngleY += 1.0f; break;  // 위로 회전
    case 's': cameraAngleY -= 1.0f; break;  // 아래로 회전
    case '+': cameraZoom -= 0.1f; break;    // 줌 인
    case '-': cameraZoom += 0.1f; break;    // 줌 아웃
    case 'o': lampOn = !lampOn; break;      // 램프 on/off
    case 'h': printHelp(); break;           // 도움말 표시
    case 'q': fov += 5.0f; break;           // 시야각 확대
    case 'e': fov -= 5.0f; break;           // 시야각 축소
    case 27: exit(0); break;                // ESC 키
    }
    glutPostRedisplay();                    // 화면 다시 그리기 호출
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // GLUT 라이브러리 초기화 및 명령줄 인수 처리
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // 디스플레이 모드 설정 (RGB, 더블 버퍼, 깊이 버퍼)
    glutInitWindowSize(800, 600);                   // 윈도우 크기 설정
    glutCreateWindow("책상 장면");                  // 윈도우 제목 설정

    init();         // 초기화 함수 호출

    glMatrixMode(GL_PROJECTION);        // 투영 행렬 모드로 전환
    glLoadIdentity();                   // 기존 투영 행렬 초기화
    glMatrixMode(GL_MODELVIEW);         // 모델뷰 행렬 모드로 전환

    glutDisplayFunc(MyDisplay); // 디스플레이 갱신 시 MyDisplay 호출
    glutKeyboardFunc(keyboard); // 키보드 입력 처리 함수 등록

    printHelp();                // 도움말 출력

    glutMainLoop();             // GLUT 이벤트 루프 실행
}
