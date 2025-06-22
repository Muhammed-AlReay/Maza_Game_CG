/*pop*/
/*
#include<Windows.h>
#include<iostream>
#include<glut.h>
using namespace std;

float width, heigh;
bool fullScreenMode = true;
float ratio, a1, a2, a3, a4, a5, a6;
void background();
void mydraw();
void reshape(int, int);
void timer(int);
void keyboard(unsigned char, int, int);
void specialKeyboard(int, int, int);
void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow(" 3D shapes and animation");
    glutFullScreen();

    background();
    glutDisplayFunc(mydraw);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();
}

void background() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void mydraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-2, 0, -7);
    glRotatef(a1, 0, 0, 1);
    glBegin(GL_LINES);   //l1
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();

    glTranslatef(1, 0, 0);
    glRotatef(a2, 0, 0, 1);
    glBegin(GL_LINES);  //l2
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -1, 0);
    glEnd();

    glTranslatef(0, -1, 0);
    glPushMatrix();
    glRotatef(a3, 0, 0, 1);
    glBegin(GL_LINES);   //l3
    glColor3f(0, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(-1, -1, 0);
    glEnd();
    glPopMatrix();

    glRotatef(a4, 0, 0, 1);
    glBegin(GL_LINES);   //l4
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(1, -1, 0);
    glEnd();

    glTranslatef(1, -1, 0);
    glPushMatrix();
    glRotatef(a5, 0, 0, 1);
    glBegin(GL_LINES);   //l5
    glColor3f(.5, .5, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(-1, -1, 0);
    glEnd();
    glPopMatrix();

    glRotatef(a6, 0, 0, 1);
    glBegin(GL_LINES);   //l6
    glColor3f(.5, .5, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, -1, 0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    ratio = w / (float)h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    else if (key == '1')
        a1++;
    else if (key == '2')
        a2++;
    else if (key == '3')
        a3++;
    else if (key == '4')
        a4++;
    else if (key == '5')
        a5++;
    else if (key == '6')
        a6++;
}

void specialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        fullScreenMode = !fullScreenMode;
        if (fullScreenMode) {
            glutFullScreen();
        }
        else {
            glutReshapeWindow(GetSystemMetrics(SM_CXSCREEN) / 2,
                GetSystemMetrics(SM_CYSCREEN) / 2);
            glutPositionWindow(GetSystemMetrics(SM_CXSCREEN) / 4,
                GetSystemMetrics(SM_CYSCREEN) / 4);
        }
    }
}*/
/*task 2*/
/*
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <iostream>

// زوايا الدوران
float angleRed = 0, anglePurple = 0, angleGreen = 0, angleCyan = 0;

// الكاميرا
float camX = 0.0f, camY = 0.0f, camz = 2.0f;
float bgColor[3] = { 0, 0, 0 };

// Textures
GLuint textures[5];
const char* textureFiles[5] = { "tex4.bmp", "tex5.bmp", "tex3.bmp", "tex4.bmp", "tex5.bmp" };

void changeBackgroundColor() {
    bgColor[0] = static_cast<float>(rand()) / RAND_MAX;
    bgColor[1] = static_cast<float>(rand()) / RAND_MAX;
    bgColor[2] = static_cast<float>(rand()) / RAND_MAX;
}

GLuint loadTexture(const char* filename) {
    GLuint textureID;
    int width, height;
    unsigned char* data;
    FILE* file;

    file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Failed to load " << filename << std::endl;
        return 0;
    }

    unsigned char header[54];
    fread(header, 1, 54, file);

    width = *(int*)&header[18];
    height = *(int*)&header[22];
    int size = 3 * width * height;
    data = new unsigned char[size];

    fseek(file, 54, SEEK_SET);
    fread(data, 1, size, file);
    fclose(file);

    // BMP files are BGR, convert to RGB
    for (int i = 0; i < size; i += 3) {
        std::swap(data[i], data[i + 2]);
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;
    return textureID;
}

void drawTexturedSquare(GLuint texID) {
    glBindTexture(GL_TEXTURE_2D, texID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-0.4f, -0.1f);
    glTexCoord2f(1, 0); glVertex2f(0.6f, -0.1f);
    glTexCoord2f(1, 1); glVertex2f(0.1f, 0.1f);
    glTexCoord2f(0, 1); glVertex2f(-0.8f, 0.1f);
    glEnd();
}

void display() {
    glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY,camz, camX, camY, 0, 0, 1, 0);

    glPushMatrix();
    glTranslatef(-0.20f, 0.20f, 0);
    glRotatef(angleRed, 0, 0, 1);
    drawTexturedSquare(textures[0]);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleRed, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0);
    glRotatef(anglePurple, 0, 0, 1);
    drawTexturedSquare(textures[1]);

    glPushMatrix();
    glTranslatef(-0.20f, -0.20f, 0);
    glRotatef(angleCyan, 0, 0, 1);
    drawTexturedSquare(textures[2]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.20f, -0.20f, 0);
    glRotatef(angleGreen, 0, 0, 1);
    drawTexturedSquare(textures[3]);
    glPopMatrix();

    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(0.20f, 0.20f, 0);
    drawTexturedSquare(textures[4]);
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1': angleRed += 5; break;
    case '2': anglePurple += 5; break;
    case '3': angleGreen += 5; break;
    case '4': angleCyan += 5; break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    camY += 0.1f; break;
    case GLUT_KEY_DOWN:  camY -= 0.1f; break;
    case GLUT_KEY_LEFT:  camX -= 0.1f; break;
    case GLUT_KEY_RIGHT: camX += 0.1f; break;
    case GLUT_KEY_F1: camz -= 0.1f; break; // Zoom In
    case GLUT_KEY_F2: camz += 0.1f; break; // Zoom Out
    }
    changeBackgroundColor();
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D); // تفعيل استخدام الـ Texture

    // تحميل كل الصور
    for (int i = 0; i < 5; i++) {
        textures[i] = loadTexture(textureFiles[i]);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Textured Squares - Hierarchy");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}

*/
//########################################
/* 455*/
/*
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdio>

// إعدادات اللاعب والكاميرا
float playerX = 1.5f, playerY = 0.0f, playerZ = 1.5f;
float cameraAngle = 0.0f;
float speed = 0.1f;

int lastMouseX;

// تعريف المتاهة (10x10 مع مسار واضح)
const int mazeWidth = 10;
const int mazeHeight = 10;

int maze[mazeHeight][mazeWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// نقطة البداية والنهاية
int startX = 1, startZ = 1;
int endX = 8, endZ = 8;
bool hasWon = false;

// دالة لرسم مكعب
void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x + 0.5f, y + 0.5f, z + 0.5f);
    glutSolidCube(1.0);
    glPopMatrix();
}

// دالة لرسم الأرضية
void drawFloor() {
    glColor3f(0.6f, 0.6f, 0.6f);
    for (int z = 0; z < mazeHeight; z++) {
        for (int x = 0; x < mazeWidth; x++) {
            glPushMatrix();
            glTranslatef(x + 0.5f, 0.0f, z + 0.5f);
            glBegin(GL_QUADS);
            glVertex3f(-0.5f, 0.0f, -0.5f);
            glVertex3f(0.5f, 0.0f, -0.5f);
            glVertex3f(0.5f, 0.0f, 0.5f);
            glVertex3f(-0.5f, 0.0f, 0.5f);
            glEnd();
            glPopMatrix();
        }
    }
}

// دالة لفحص الفوز
void checkWin() {
    if ((int)playerX == endX && (int)playerZ == endZ) {
        hasWon = true;
        printf("You Win!\n");
    }
}

// دالة لعرض نص
void renderBitmapString(float x, float y, void* font, const char* string) {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// عرض السكور (المسافة إلى الهدف)
void drawScore() {
    float dx = playerX - endX;
    float dz = playerZ - endZ;
    float distance = sqrt(dx * dx + dz * dz);

    char buffer[64];
    sprintf(buffer, "Distance to goal: %.2f", distance);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    renderBitmapString(10, 570, GLUT_BITMAP_HELVETICA_18, buffer);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// العرض
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float camX = playerX - 3.0f * cos(cameraAngle);
    float camZ = playerZ - 3.0f * sin(cameraAngle);
    gluLookAt(camX, 2.5f, camZ, playerX, 0.5f, playerZ, 0.0, 1.0, 0.0);

    GLfloat light_pos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    drawFloor();

    for (int z = 0; z < mazeHeight; z++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (maze[z][x] == 1) {
                glColor3f(0.2f, 0.4f, 0.8f);
                drawCube((float)x, 0, (float)z);
            }
        }
    }

    // نقطة البداية
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(startX, 0.5f, startZ);
    glutSolidCube(1.0);
    glPopMatrix();

    // نقطة النهاية
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(endX, 0.5f, endZ);
    glutSolidCube(1.0);
    glPopMatrix();

    // اللاعب
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(playerX, 0.5f, playerZ);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    checkWin();

    if (hasWon) {
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(mazeWidth / 2, 2.0f, mazeHeight / 2);
        glRasterPos3f(-1.5f, 0.0f, 0.0f);
        for (const char* c = "You Win!"; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        glPopMatrix();
    }

    drawScore(); // عرض السكور

    glutSwapBuffers();
}

// التحكم بلوحة المفاتيح
void keyboard(unsigned char key, int x, int y) {
    float nextX = playerX;
    float nextZ = playerZ;

    if (key == '1') {
        nextX += speed * cos(cameraAngle);
        nextZ += speed * sin(cameraAngle);
    }
    if (key == '2') {
        nextX -= speed * cos(cameraAngle);
        nextZ -= speed * sin(cameraAngle);
    }

    int tileX = (int)nextX;
    int tileZ = (int)nextZ;

    if (maze[tileZ][tileX] == 0) {
        playerX = nextX;
        playerZ = nextZ;
    }

    if (key == 27) { // Esc
        printf("Game exited by user.\n");
        exit(0);
    }

    glutPostRedisplay();
}

// التحكم بالفأرة
void mouseMotion(int x, int y) {
    int dx = x - lastMouseX;
    cameraAngle += dx * 0.005f;
    lastMouseX = x;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN)
        lastMouseX = x;
}

// تهيئة OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

// تغيير حجم النافذة
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// الدالة الرئيسية
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Maze Game");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
*/

/* new */
/*#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Camera settings
float cameraX = 1.5f, cameraY = 0.5f, cameraZ = 1.5f;
float cameraAngle = 0.0f;
float cameraPitch = 0.0f;
float speed = 0.1f;
float mouseSensitivity = 0.001f;
bool mouseCaptured = false;
bool topDownView = false;

// Maze definition
const int mazeWidth = 10;
const int mazeHeight = 10;

int maze[mazeHeight][mazeWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Coin system
struct Coin {
    float x, y, z;
    bool collected;
    float rotation;
};

vector<Coin> coins = {
    {1.5f, 0.3f, 1.5f, false, 0.0f},
    {3.5f, 0.3f, 2.5f, false, 0.0f},
    {5.5f, 0.3f, 1.5f, false, 0.0f},
    {2.5f, 0.3f, 4.5f, false, 0.0f},
    {4.5f, 0.3f, 5.5f, false, 0.0f}
};

int score = 0;
bool gameWon = false;

// Draw a cube
void drawCube(float x, float y, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x + 0.5f, y + 0.5f, z + 0.5f);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Draw a coin
void drawCoin(const Coin& coin) {
    if (coin.collected) return;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
    glTranslatef(coin.x, coin.y, coin.z);
    glRotatef(coin.rotation, 0, 1, 0);
    glutSolidSphere(0.2, 16, 16);
    glColor3f(0.8f, 0.7f, 0.1f);
    glutSolidTorus(0.05, 0.15, 10, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Draw exit marker
void drawExit() {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glTranslatef(5.5f, 0.1f, 5.5f);
    glutSolidSphere(0.3, 10, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Capture mouse for camera control
void captureMouse() {
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    mouseCaptured = true;
}

// Release mouse
void releaseMouse() {
    glutSetCursor(GLUT_CURSOR_INHERIT);
    mouseCaptured = false;
}

// Mouse movement handler
void mouseMotion(int x, int y) {
    if (!mouseCaptured || topDownView) return;

    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    if (x == centerX && y == centerY) return;

    cameraAngle -= (x - centerX) * mouseSensitivity;
    cameraPitch -= (y - centerY) * mouseSensitivity * 0.5f;

    cameraPitch = fmax(fmin(cameraPitch, 1.5f), -1.5f);
    glutWarpPointer(centerX, centerY);
    glutPostRedisplay();
}

// Game update function
void update(int value) {
    for (auto& coin : coins) {
        coin.rotation += 2.0f;
        if (coin.rotation > 360.0f) coin.rotation -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (topDownView) {
        // Top-down view
        gluLookAt(mazeWidth / 2, mazeHeight + 5.0f, mazeHeight / 2,
            mazeWidth / 2, 0.0f, mazeHeight / 2,
            0.0f, 0.0f, -1.0f);
    }
    else {
        // First-person view
        gluLookAt(cameraX, cameraY, cameraZ,
            cameraX + cos(cameraAngle) * cos(cameraPitch),
            cameraY + sin(cameraPitch),
            cameraZ + sin(cameraAngle) * cos(cameraPitch),
            0.0, 1.0, 0.0);
    }

    // Draw floor
    glDisable(GL_LIGHTING);
    glColor3f(0.2f, 0.6f, 0.2f); // Green
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(mazeWidth, 0.0f, 0.0f);
    glVertex3f(mazeWidth, 0.0f, mazeHeight);
    glVertex3f(0.0f, 0.0f, mazeHeight);
    glEnd();

    // Draw walls
    for (int z = 0; z < mazeHeight; z++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (maze[z][x] == 1) {
                drawCube(x, 0, z, 0.7f, 0.2f, 0.2f); // Red walls
            }
        }
    }

    // Draw coins
    for (const auto& coin : coins) {
        drawCoin(coin);
    }

    // Draw exit marker
    drawExit();

    // Draw sun
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-5.0f, 5.0f, -5.0f);
    glutSolidSphere(0.3, 20, 20);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Draw score and messages (using 2D orthographic projection)
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    string scoreText = "Score: " + to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    if (gameWon) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 100, glutGet(GLUT_WINDOW_HEIGHT) / 2);
        string message = "Congratulations! You scored " + to_string(score) + " points!";
        for (char c : message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// Arrow keys control
void specialKeys(int key, int x, int y) {
    if (gameWon || topDownView) return;

    float nextX = cameraX, nextZ = cameraZ;

    switch (key) {
    case GLUT_KEY_UP:
        nextX += speed * cos(cameraAngle);
        nextZ += speed * sin(cameraAngle);
        break;
    case GLUT_KEY_DOWN:
        nextX -= speed * cos(cameraAngle);
        nextZ -= speed * sin(cameraAngle);
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngle += 0.1f;
        break;
    }

    // Wall collision detection
    int tileX = nextX, tileZ = nextZ;
    if (tileX >= 0 && tileX < mazeWidth && tileZ >= 0 && tileZ < mazeHeight) {
        if (maze[tileZ][tileX] == 0) {
            cameraX = nextX;
            cameraZ = nextZ;
        }
    }

    // Coin collection
    for (auto& coin : coins) {
        if (!coin.collected && sqrt(pow(cameraX - coin.x, 2) + pow(cameraZ - coin.z, 2)) < 0.3f) {
            coin.collected = true;
            score += 10;
        }
    }

    // Win condition
    if (!gameWon && fabs(cameraX - 5.5f) < 0.5f && fabs(cameraZ - 5.5f) < 0.5f) {
        gameWon = true;
    }

    glutPostRedisplay();
}

// Keyboard control
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC to exit
        exit(0);
        break;
    case ' ': // Space to toggle mouse capture
        if (mouseCaptured) releaseMouse();
        else captureMouse();
        break;
    case 'v': // V to toggle view
    case 'V':
        topDownView = !topDownView;
        if (topDownView) releaseMouse();
        glutPostRedisplay();
        break;
    }
}

// Initialize OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue

    GLfloat light_pos[] = { -1.0f, 1.0f, -0.5f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

// Window resize handler
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Maze Game with Coins and Top-Down View");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion);
    glutMouseFunc([](int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) captureMouse();
        });
    glutTimerFunc(0, update, 0);

    cout << "Game Controls:" << endl;
    cout << "- Arrow Keys: Move and turn" << endl;
    cout << "- Space: Toggle mouse capture" << endl;
    cout << "- V: Toggle view (first-person/top-down)" << endl;
    cout << "- ESC: Exit game" << endl;

    glutMainLoop();
    return 0;
}
*/
////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <glut.h>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

// Texture variables
GLuint wallTexture;
const int TEXTURE_WIDTH = 256;
const int TEXTURE_HEIGHT = 256;
GLubyte textureImage[TEXTURE_HEIGHT][TEXTURE_WIDTH][3];

// Camera settings
float cameraX = 1.5f, cameraY = 0.5f, cameraZ = 1.5f;
float cameraAngle = 0.0f;
float cameraPitch = 0.0f;
float speed = 0.1f;
float mouseSensitivity = 0.001f;
bool mouseCaptured = false;
bool topDownView = false;

// Maze definition (10x10)
const int mazeWidth = 10;
const int mazeHeight = 10;

int maze[mazeHeight][mazeWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Coin system (4 coins)
struct Coin {
    float x, y, z;
    bool collected;
    float rotation;
};

vector<Coin> coins = {
    {1.5f, 0.3f, 1.5f, false, 0.0f},
    {5.5f, 0.3f, 1.5f, false, 0.0f},
    {7.5f, 0.3f, 1.5f, false, 0.0f},
    {1.5f, 0.3f, 3.5f, false, 0.0f}

};

int score = 0;
bool gameWon = false;
int coinsCollected = 0;
const int totalCoins = 4;

// Load BMP texture
GLuint loadTexture(const char* filename) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Fallback checkerboard pattern
    for (int i = 0; i < TEXTURE_HEIGHT; i++) {
        for (int j = 0; j < TEXTURE_WIDTH; j++) {
            GLubyte c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 255;
            textureImage[i][j][0] = c;
            textureImage[i][j][1] = c;
            textureImage[i][j][2] = c;
        }
    }

    // Try to load actual texture
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        fseek(file, 18, SEEK_SET);
        int width, height;
        fread(&width, sizeof(int), 1, file);
        fread(&height, sizeof(int), 1, file);
        fseek(file, 54, SEEK_SET);

        unsigned char* data = new unsigned char[width * height * 3];
        fread(data, width * height * 3, 1, file);
        fclose(file);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
            GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
        delete[] data;
    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0,
            GL_RGB, GL_UNSIGNED_BYTE, textureImage);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return textureId;
}

// Draw textured wall
void drawTexturedCube(float x, float y, float z) {
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(x + 0.5f, y + 0.5f, z + 0.5f);

    glBegin(GL_QUADS);
    // Front
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);

    // Top
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Right
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);

    // Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Draw coin
void drawCoin(const Coin& coin) {
    if (coin.collected) return;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.84f, 0.0f);
    glTranslatef(coin.x, coin.y, coin.z);
    glRotatef(coin.rotation, 0, 1, 0);
    glutSolidSphere(0.2, 16, 16);
    glColor3f(0.8f, 0.7f, 0.1f);
    glutSolidTorus(0.05, 0.15, 10, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Draw exit
void drawExit() {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(5.5f, 0.1f, 5.5f);
    glutSolidSphere(0.3, 10, 10);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Mouse control
void captureMouse() {
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    mouseCaptured = true;
}

void releaseMouse() {
    glutSetCursor(GLUT_CURSOR_INHERIT);
    mouseCaptured = false;
}

void mouseMotion(int x, int y) {
    if (!mouseCaptured || topDownView) return;

    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    if (x == centerX && y == centerY) return;

    cameraAngle -= (x - centerX) * mouseSensitivity;
    cameraPitch -= (y - centerY) * mouseSensitivity * 0.5f;

    cameraPitch = fmax(fmin(cameraPitch, 1.5f), -1.5f);
    glutWarpPointer(centerX, centerY);
    glutPostRedisplay();
}

// Game loop
void update(int value) {
    for (auto& coin : coins) {
        coin.rotation += 2.0f;
        if (coin.rotation > 360.0f) coin.rotation -= 360.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (topDownView) {
        gluLookAt(mazeWidth / 2, mazeHeight + 5.0f, mazeHeight / 2,
            mazeWidth / 2, 0.0f, mazeHeight / 2,
            0.0f, 0.0f, -1.0f);
    }
    else {
        gluLookAt(cameraX, cameraY, cameraZ,
            cameraX + cos(cameraAngle) * cos(cameraPitch),
            cameraY + sin(cameraPitch),
            cameraZ + sin(cameraAngle) * cos(cameraPitch),
            0.0, 1.0, 0.0);
    }

    // Draw floor
    glDisable(GL_LIGHTING);
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(mazeWidth, 0.0f, 0.0f);
    glVertex3f(mazeWidth, 0.0f, mazeHeight);
    glVertex3f(0.0f, 0.0f, mazeHeight);
    glEnd();

    // Draw walls with texture
    for (int z = 0; z < mazeHeight; z++) {
        for (int x = 0; x < mazeWidth; x++) {
            if (maze[z][x] == 1) {
                drawTexturedCube(x, 0, z);
            }
        }
    }

    // Draw coins
    for (const auto& coin : coins) {
        drawCoin(coin);
    }

    // Draw exit
    drawExit();

    // Draw sun
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-5.0f, 5.0f, -5.0f);
    glutSolidSphere(0.3, 20, 20);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Draw HUD
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Score
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    string scoreText = "Score: " + to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Coins remaining
    glRasterPos2i(10, glutGet(GLUT_WINDOW_HEIGHT) - 40);
    string coinsText = "Coins: " + to_string(coinsCollected) + "/" + to_string(totalCoins);
    for (char c : coinsText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    if (gameWon) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 100, glutGet(GLUT_WINDOW_HEIGHT) / 2);
        string message = "Congratulations! You scored " + to_string(score) + " points!";
        for (char c : message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
    else if (fabs(cameraX - 5.5f) < 0.5f && fabs(cameraZ - 5.5f) < 0.5f && coinsCollected < totalCoins) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) / 2 - 150, glutGet(GLUT_WINDOW_HEIGHT) / 2);
        string message = "Collect all " + to_string(totalCoins - coinsCollected) + " remaining coins first!";
        for (char c : message) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// Keyboard controls
void specialKeys(int key, int x, int y) {
    if (gameWon || topDownView) return;

    float nextX = cameraX, nextZ = cameraZ;

    switch (key) {
    case GLUT_KEY_UP:
        nextX += speed * cos(cameraAngle);
        nextZ += speed * sin(cameraAngle);
        break;
    case GLUT_KEY_DOWN:
        nextX -= speed * cos(cameraAngle);
        nextZ -= speed * sin(cameraAngle);
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngle += 0.1f;
        break;
    }

    // Collision detection
    int tileX = nextX, tileZ = nextZ;
    if (tileX >= 0 && tileX < mazeWidth && tileZ >= 0 && tileZ < mazeHeight) {
        if (maze[tileZ][tileX] == 0) {
            cameraX = nextX;
            cameraZ = nextZ;
        }
    }

    // Coin collection
    for (auto& coin : coins) {
        if (!coin.collected && sqrt(pow(cameraX - coin.x, 2) + pow(cameraZ - coin.z, 2)) < 0.3f) {
            coin.collected = true;
            score += 10;
            coinsCollected++;
        }
    }

    // Win condition - must collect all coins before reaching exit
    if (!gameWon && fabs(cameraX - 5.5f) < 0.5f && fabs(cameraZ - 5.5f) < 0.5f) {
        if (coinsCollected >= totalCoins) {
            gameWon = true;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC
        exit(0);
        break;
    case ' ': // Space
        if (mouseCaptured) releaseMouse();
        else captureMouse();
        break;
    case 'v': case 'V': // V
        topDownView = !topDownView;
        if (topDownView) releaseMouse();
        glutPostRedisplay();
        break;
    }
}

// Initialize OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    // Load texture
    wallTexture = loadTexture("wall.bmp");

    // Lighting
    GLfloat light_pos[] = { -1.0f, 1.0f, -0.5f, 0.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Maze Game - Collect All Coins to Win");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion);
    glutMouseFunc([](int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) captureMouse();
        });
    glutTimerFunc(0, update, 0);

    cout << "Controls:\n";
    cout << "Arrows: Move\n";
    cout << "Space: Toggle mouse look\n";
    cout << "V: Toggle top-down view\n";
    cout << "ESC: Quit\n";
    cout << "Collect all " << totalCoins << " coins before reaching the exit to win!\n";

    glutMainLoop();
    return 0;
}
