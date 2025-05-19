#include <stdio.h>
#include "glut.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Biến vị trí camera
double eyeX = 0, eyeY = 21, eyeZ = 0; // Vị trí camera
double yaw = 0.0;   // Góc xoay ngang (độ)
double pitch = 0.0; // Góc xoay dọc (độ)
double moveSpeed = 0.5; // Tốc độ di chuyển
int lastMouseX = 500, lastMouseY = 400; // Vị trí chuột trung tâm
int windowWidth = 1000, windowHeight = 800; // Kích thước cửa sổ

// Biến điểm tham chiếu
double refX, refY, refZ;

void veKhoiLapPhuong1() {
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 3.0);
    glVertex3f(3.0, 0.0, 3.0);
    glVertex3f(3.0, 0.0, 0.0);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    glVertex3f(0.0, 3.0, 3.0);
    glVertex3f(3.0, 3.0, 3.0);
    glVertex3f(3.0, 3.0, 0.0);

    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 3.0);
    glVertex3f(0.0, 3.0, 3.0);
    glVertex3f(3.0, 3.0, 3.0);
    glVertex3f(3.0, 0.0, 3.0);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 3.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 3.0);
    glVertex3f(3.0, 3.0, 3.0);
    glVertex3f(3.0, 3.0, 0.0);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
    glVertex3f(0.0, 3.0, 3.0);
    glVertex3f(0.0, 0.0, 3.0);
    glEnd();
}

void veTuongPhong() {
    glPushMatrix();
    glColor3f(0.2, 0.6, 0.8);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(0.03, 3, 10);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.6, 0.8);
    glTranslatef(18, 0.0, 0.0);
    glScalef(0.03, 3, 10);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(6, 3, 0.03);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(0.0, 0.0, 30);
    glScalef(6, 3, 0.03);
    veKhoiLapPhuong1();
    glPopMatrix();
}

void veSanNha() {
    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(6, 0.33, 10);
    veKhoiLapPhuong1();
    glPopMatrix();
}

void veThamTraiSan() {
    glPushMatrix();
    glColor3f(0.8, 0.2, 0.2);
    glTranslatef(5, 1.01, 5);
    glScalef(2.67, 0.0167, 4);
    veKhoiLapPhuong1();
    glPopMatrix();
}

void drawPlantPot() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    // 1) Chậu (loại loe)
    glPushMatrix();
    glColor3f(0.8f, 0.4f, 0.1f);      // Nâu gốm
    // Dịch: về vị trí bàn (-0.5,1,15) + di chuyển ra giữa bàn (+1.5, +0.1, +0.5)
    glTranslatef(1.0f, 1.1f, 0.5f);
    glRotatef(-90, 1, 0, 0);          // Quay cho trục Z lên
    gluCylinder(quad, 0.3, 0.35, 0.4, 30, 10);
    gluDisk(quad, 0.0, 0.3, 30, 1);   // Đáy chậu
    glPopMatrix();

    // 2) Đất
    glPushMatrix();
    glColor3f(0.3f, 0.2f, 0.1f);
    glTranslatef(1.0f, 1.5f, .5f);
    glRotatef(-90, 1, 0, 0);
    gluDisk(quad, 0.0, 0.28, 30, 1);
    glPopMatrix();

    // 3) Thân cây
    glPushMatrix();
    glColor3f(0.4f, 0.2f, 0.1f);
    glTranslatef(1.0f, 1.5f, 0.5f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.05, 0.05, 1.2, 20, 5);
    glPopMatrix();

    // 4) Tán lá
    glPushMatrix();
    glColor3f(0.0f, 0.6f, 0.0f);
    glTranslatef(1.0f, 2.7f, 0.5f);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

// === Hàm vẽ tranh treo tường (trên tường trước z=0) ===
void drawPicture() {
    glPushMatrix();
    glColor3f(0.2f, 1.6f, 0.1f);    // Nền vàng nâu
    // Đặt ở giữa tường trước (x≈9, y≈2), lùi ra ngoài chút tránh z=0
    glTranslatef(14.0f, 6.5f, 1.0f);
    glScalef(2.0f, 3.0f, 0.1f);

    // Nền
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0);
    glVertex3f(0.5f, -0.5f, 0);
    glVertex3f(0.5f, 0.5f, 0);
    glVertex3f(-0.5f, 0.5f, 0);
    glEnd();

    // Viền
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, -0.5f, 0.01f);
    glVertex3f(0.5f, -0.5f, 0.01f);
    glVertex3f(0.5f, 0.5f, 0.01f);
    glVertex3f(-0.5f, 0.5f, 0.01f);
    glEnd();
    glPopMatrix();
}

void vecaitivi() {
    glPushMatrix();
    glColor3f(0.678, 0.847, 0.902); // Light Blue (LightSkyBlue)
    glTranslatef(9.0, 3.5, 29.5);
    glScalef(4.0f, 3.0f, 0.1f);

    // Nền
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0);
    glVertex3f(0.5f, -0.5f, 0);
    glVertex3f(0.5f, 0.5f, 0);
    glVertex3f(-0.5f, 0.5f, 0);
    glEnd();

    // Viền
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, -0.5f, 0.01f);
    glVertex3f(0.5f, -0.5f, 0.01f);
    glVertex3f(0.5f, 0.5f, 0.01f);
    glVertex3f(-0.5f, 0.5f, 0.01f);
    glEnd();
    glPopMatrix();
}

void veketv() {
    // Kệ tivi bên dưới
    glPushMatrix();
    glTranslatef(9.0, 1.3, 29.8);
    glScalef(6, 1, 1.5);
    glColor3f(0.5, 0.3, 0.1); // màu gỗ
    glutSolidCube(1);
    glPopMatrix();
}

void vecuaso() {
    // Cửa sổ trái
    glPushMatrix();
    glTranslatef(0.1, 6.0, 12.0); // sát tường trái
    glScalef(0.01, 2.8, 3.5);       // độ mỏng, cao, rộng
    glColor3f(0.7, 0.9, 1.0);      // màu kính xanh nhạt
    glutSolidCube(1);
    glPopMatrix();

    // Cửa sổ bên phải
    glPushMatrix();
    glTranslatef(17.9, 6.0, 12.0); // sát tường phải
    glScalef(0.01, 2.8, 3.5);
    glColor3f(0.7, 0.9, 1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void veCuaChinh() {
    glPushMatrix();
    glTranslatef(0.2, 3., 23.0); // sát tường trái
    glScalef(0.2, 8.0, 3.7);       // độ mỏng, cao, rộng
    glColor3f(0.55, 0.27, 0.07); // Màu nâu gỗ  
    glutSolidCube(1);
    glPopMatrix();
}

// === Hàm vẽ đồng hồ treo tường (trên tường phải x=18) ===
void drawClock() {
    const float cx = 8.0f, cy = 7.0f, cz = 1.2f; // Treo ở giữa tường phải
    const float R = 1.0f;
    int i;

    // 1) Mặt đồng hồ
    glPushMatrix();
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, cz);
    for (i = 1;i <= 360;i += 10) {
        float a = i * M_PI / 180.0f;
        glVertex3f(cx + cos(a) * R, cy + sin(a) * R, cz);
    }
    glEnd();

    // 2) Vạch giờ
    glColor3f(0, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (i = 0;i < 12;i++) {
        float ang = i * (2 * M_PI / 12) - M_PI / 2;
        float x1 = cx + cos(ang) * 0.9f, y1 = cy + sin(ang) * 0.9f;
        float x2 = cx + cos(ang) * R, y2 = cy + sin(ang) * R;
        glVertex3f(x1, y1, cz + 0.01f);
        glVertex3f(x2, y2, cz + 0.01f);
    }
    glEnd();

    // 3) Kim giờ (giả định 10h)
    glColor3f(0, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex3f(cx, cy, cz + 0.02f);
    {
        float angH = (10.0f / 12.0f) * 2 * M_PI - M_PI / 2;
        glVertex3f(cx + cos(angH) * 0.5f, cy + sin(angH) * 0.5f, cz + 0.02f);
    }
    glEnd();

    // 4) Kim phút (giả định 30')
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(cx, cy, cz + 0.03f);
    {
        float angM = (30.0f / 60.0f) * 2 * M_PI - M_PI / 2;
        glVertex3f(cx + cos(angM) * 0.8f, cy + sin(angM) * 0.8f, cz + 0.03f);
    }
    glEnd();
    glPopMatrix();
}

void veCaiBan() {
    glPushMatrix();
    glColor3f(0.5, 0.3, 0.1);
    glTranslatef(1.0, 2.95, 7.8);
    glScalef(2.0, 0.14, 1);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glTranslatef(1.5, -0.05, 8.3);
    glScalef(0.067, 1.0, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glTranslatef(6.3, -0.05, 8.3);
    glScalef(0.067, 1.0, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glTranslatef(1.5, -0.05, 10.1);
    glScalef(0.067, 1.0, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7, 0.5, 0.3);
    glTranslatef(6.3, -0.05, 10.1);
    glScalef(0.067, 1.0, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();
}

void veCaiGhe() {
    glPushMatrix();
    glColor3f(0.5, 0.3, 0.1);
    glTranslatef(0, 5.5, 0);
    glScalef(0.4, 0.1, 0.4);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(1, 4, 0);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(0, 4, 1);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(1, 4, 1);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(0, 4, 0);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(0, 5.7, 0.3);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslatef(0, 5.7, 0.7);
    glScalef(0.067, 0.5, 0.067);
    veKhoiLapPhuong1();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.3, 0.1);
    glTranslatef(0, 7.2, 0);
    glScalef(0.1, 0.1, 0.4);
    veKhoiLapPhuong1();
    glPopMatrix();
}

void drawTeapot() {
    glColor3f(0.0f, 0.8f, 0.6f);
    glPushMatrix();
    glTranslatef(8.5, 4.6, 0 + 10.8);
    glRotatef(30.0, 0.0, 0.0, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glutSolidTeapot(0.4);
    glPopMatrix();
}

void drawRealisticCup() {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    glPushMatrix();
    glTranslatef(9.3, 4.42, 11.5);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    glColor3f(0.95f, 0.95f, 0.95f);
    gluCylinder(quad, 0.12, 0.17, 0.25, 40, 10);
    gluDisk(quad, 0.0, 0.12, 40, 1);

    glTranslatef(0.0, 0.0, 0.25);
    glColor3f(0.98f, 0.98f, 0.98f);
    gluCylinder(quad, 0.16, 0.11, -0.25, 40, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.3, 4.42, 11.5 - 0.7);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    glColor3f(0.95f, 0.95f, 0.95f);
    gluCylinder(quad, 0.12, 0.17, 0.25, 40, 10);
    gluDisk(quad, 0.0, 0.12, 40, 1);

    glTranslatef(0.0, 0.0, 0.25);
    glColor3f(0.98f, 0.98f, 0.98f);
    gluCylinder(quad, 0.16, 0.11, -0.25, 40, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.3, 4.42, 11.5 - 1.4);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);

    glColor3f(0.95f, 0.95f, 0.95f);
    gluCylinder(quad, 0.12, 0.17, 0.25, 40, 10);
    gluDisk(quad, 0.0, 0.12, 40, 1);

    glTranslatef(0.0, 0.0, 0.25);
    glColor3f(0.98f, 0.98f, 0.98f);
    gluCylinder(quad, 0.16, 0.11, -0.25, 40, 10);
    glPopMatrix();
}

void drawFridge() {
    glPushMatrix();
    glTranslatef(16.9f, 3.0f, 0.0f);
    glColor3f(0.88f, 0.88f, 0.93f);
    glScalef(2.0f, 6.0f, 3.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.75f);
    glTranslatef(16.9f, 4.2f, 1.51f);
    glScalef(2.0f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(17.9f, 5.1f, 1.5f);
    glScalef(0.1f, 1.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(17.9f, 2.6f, 1.5f);
    glScalef(0.1f, 2.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.78f);
    glTranslatef(16.9f, 3.0f, 1.5f);
    glScalef(2.0f, 6.0f, 0.02f);
    glutWireCube(1.0f);
    glPopMatrix();
}

void DrawCoodinate() {
    glColor3f(0.0, 1.0, 0.0); // y
    glBegin(GL_LINES);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // x
    glBegin(GL_LINES);
    glVertex3f(0.0, 100.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0); // z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 100.0);
    glVertex3f(0.0, 0.0, -100.0);
    glEnd();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double radYaw = yaw * M_PI / 180.0;
    double radPitch = pitch * M_PI / 180.0;
    refX = eyeX + cos(radPitch) * sin(radYaw);
    refY = eyeY + sin(radPitch);
    refZ = eyeZ + cos(radPitch) * cos(radYaw);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    DrawCoodinate();
    veTuongPhong();
    veSanNha();
    veThamTraiSan();

    glPushMatrix();
    glTranslatef(-0.5, 1, 15);
    glRotatef(90, 0, 1, 0);
    veCaiBan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.7, -3, 8.3);
    veCaiGhe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.7, -3, 10.2);
    veCaiGhe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.7, -3, 12.3);
    veCaiGhe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.9, -3, 13.5);
    glRotatef(180, 0, 1, 0);
    veCaiGhe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.9, -3, 11.4);
    glRotatef(180, 0, 1, 0);
    veCaiGhe();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(11.9, -3, 9.3);
    glRotatef(180, 0, 1, 0);
    veCaiGhe();
    glPopMatrix();

    drawTeapot();
    drawRealisticCup();

    glPushMatrix();
    glTranslatef(-15.6, 1, 28);
    drawFridge();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, -5);
    vecaitivi();
    veketv();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.1, 0, 30); 
    glRotatef(90, 0, 1, 0); 
    drawClock();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-14, 1, 0.5); 
    glRotatef(90, 0, 1, 0); 
    veCuaChinh();
    glPopMatrix();

	glPushMatrix();
	glScalef(3, 3, 3);
	glTranslatef(0, -0.8, 0);
    drawPlantPot();
	glPopMatrix();


    drawPicture();

    vecuaso();

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc(unsigned char key, int x, int y) {
    double radYaw = yaw * M_PI / 180.0;
    switch (key) {
    case 'w': // Tiến
        eyeX += moveSpeed * sin(radYaw);
        eyeZ += moveSpeed * cos(radYaw);
        break;
    case 's': // Lùi
        eyeX -= moveSpeed * sin(radYaw);
        eyeZ -= moveSpeed * cos(radYaw);
        break;
    case 'd': // Trái
        eyeX -= moveSpeed * cos(radYaw);
        eyeZ += moveSpeed * sin(radYaw);
        break;
    case 'a': // Phải
        eyeX += moveSpeed * cos(radYaw);
        eyeZ -= moveSpeed * sin(radYaw);
        break;
    case 'e': // Lên
        eyeY += moveSpeed;
        break;
    case 'x': // Xuống
        eyeY -= moveSpeed;
        break;
    case 'q': // Reset
        eyeX = 6.0;
        eyeY = 7.0;
        eyeZ = 10.0;
        yaw = 0.0;
        pitch = 0.0;
        break;
    }
    glutPostRedisplay();
}

void mousePassiveMotionFunc(int x, int y) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;
    yaw -= deltaX * 0.2; // Xoay ngang: trái/phải
    pitch -= deltaY * 0.2; // Xoay dọc: lên/xuống (đảo ngược lại để di lên nhìn lên)
    if (pitch > 89.0) pitch = 89.0;
    if (pitch < -89.0) pitch = -89.0;
    glutWarpPointer(windowWidth / 2, windowHeight / 2); // Đưa chuột về giữa
    lastMouseX = windowWidth / 2;
    lastMouseY = windowHeight / 2;
    glutPostRedisplay();
}

void fullScreen(int w, int h) {
    if (h == 0) h = 1;
    windowWidth = w;
    windowHeight = h;
    float ratio = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(60, ratio, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    glutWarpPointer(w / 2, h / 2); // Đặt chuột về giữa khi thay đổi kích thước
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    printf("Điều khiển:\n");
    printf("W: tiến\n");
    printf("S: lùi\n");
    printf("A: phải\n");
    printf("D: trái\n");
    printf("E: lên\n");
    printf("X: xuống\n");
    printf("Di chuyển chuột: xoay camera\n");
    printf("Q: reset vị trí và góc nhìn\n");
    printf("Esc: thoát\n");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Phong An 3D");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutPassiveMotionFunc(mousePassiveMotionFunc);
    glutReshapeFunc(fullScreen);
    glutMainLoop();
    return 0;
}