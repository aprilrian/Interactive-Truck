 // === TUGAS BESAR ===
// === Praktikum GKV ===
/*
1. Aprilyanto Setiyawan Siburian - 24060121120022
2. Adri Audifirst - 24060121140152
3. Naufal Arya Ramadhan - 24060121110042
4. Firdian Rahmawan - 24060121120018
*/

#include <math.h> 
#include <GL/glut.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#define PI 3.14

float angle=0.0, deltaAngle = 0.0, ratio; 
float x=0.0f,y=20.0f,z=100.0f; // posisi awal kamera 
float lx=0.0f,ly=0.0f,lz=-1.0f; 

int deltaMove = 0,h,w; 

static int rotAngleX =0, rotAngleY =0, rotAngleZ =0;
float posXBadan=10, posXKotak=0, posYBadan=7, posYKotak=6;
float rotTangan1=0.0, rotTangan2=0.0,rotTangan3=0.0, rotTangan4=0.0;
int kick=0, roll=0,hit=0, gerakTangan=0, drop=0, bring=0, grab=0, tabrak=0;
float jarak=1;

const double PHI = 3.14;

void Roda(float alas,float atas,float tinggi);

GLUquadricObj *IDquadric;

// Variable untuk pencahayaan 
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f }; 
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; 
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 100.0f }; 

void init(void) 
{ 
	glEnable (GL_DEPTH_TEST); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	IDquadric=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals ( NEW )
	gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords ( NEW )
} 

void Reshape(int w1, int h1) 
{ 
	// Fungsi reshape 
	if(h1 == 0) 
	h1 = 1; 
	w = w1; 
	h = h1; 
	ratio = 1.0f * w / h; 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glViewport(0, 0, w, h); 
	gluPerspective(45,ratio,0.1,1000); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

void orientMe(float ang) 
{
	// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan) 
	lx = sin(ang/10); 
	lz = -cos(ang/10); 
	glLoadIdentity(); 
	gluLookAt(x, y, z,x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

void moveMeFlat(int i) 
{
	// Fungsi ini untuk maju mundur kamera 
	x = x + i*(lx)*0.1; 
	z = z + i*(lz)*0.1; 
	glLoadIdentity(); 
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f); 
} 

void keyboard(unsigned char key, int x, int y) 
{
	switch (key)
	{
 	case 'w': 
 	rotAngleX += 2; break; 
 	case 's': 
 	rotAngleX -= 2; break;
	case 'a': 
	rotAngleY += 2; break; 
	case 'd': 
	rotAngleY -= 2; break;
	case 'q': 
	rotAngleZ += 2; break; 
	case 'e': 
	rotAngleZ -= 2; break; 
	case 'o':
		
	if(drop==0)
	{ //kondisi jika kotak tidak jatuh ke tanah
		if (posXBadan > -122)//kondisi jika tidak menabrak dinding
		{ 
			posXBadan -= 1;
			if (bring == 1 )
			{
				posXKotak -= 1;
			}
 		}
 	}
	else
	{
 		if (posXBadan >posXKotak+3)
		{ //kondisi jika tidak menabrak kotak
 			posXBadan -= 1;
 		}
 	}
	break; 
	
 	case 'p': 
 	posXBadan += 1; 
 	
 	if (bring == 1)
	{
 		posXKotak += 1;
 	} 
	break; 
	
 	case 'g': 
 	gerakTangan = 1; break; 
 	
 	case 't': 
 	if (posXBadan>=8)
	{ //kondisi kotak telah diluar meja
 		drop = 1; 
 		gerakTangan =3;
	}
	break; 
 
 	case 32:
 	rotAngleX=rotAngleY=rotAngleZ=0;
	posXBadan=10, posXKotak=0, posYBadan=7, posYKotak=6;
	rotTangan1=rotTangan2=rotTangan3=rotTangan4=kick=roll=gerakTangan=drop=hit=bring=grab=0;
	break;
	
 	case 27: 
 	exit(0); 
 	default:
 	break;
 	}
	
	glutPostRedisplay();
}

void pressKey(int k, int x, int y) 
{
	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas 
	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak 
 	switch (k) 
	{ 
		case GLUT_KEY_UP : deltaMove = 5;break; 
 		case GLUT_KEY_DOWN : deltaMove = -5;break; 
 		case GLUT_KEY_LEFT : deltaAngle = -0.05f;break; 
 		case GLUT_KEY_RIGHT : deltaAngle = 0.05f;break;
 	} 
}

void releaseKey(int key, int x, int y) 
{
	// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas 
	// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti 
 	switch (key) 
	{ 
 	case GLUT_KEY_UP : if (deltaMove > 0) 
 	deltaMove = 0; 
 	break;
 	
 	case GLUT_KEY_DOWN : if (deltaMove < 0) 
 	deltaMove = 0; 
 	break;
 	
 	case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) 
 	deltaAngle = 0.0f; 
 	break; 
 	
 	case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) 
 	deltaAngle = 0.0f; 
 	break; 
 	} 
}

void lighting()
{
	// Fungsi mengaktifkan pencahayaan 
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS); 
	glEnable(GL_LIGHT0); 
	glEnable(GL_NORMALIZE); 
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_LIGHTING); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
} 
//----------------------------------------------------------------------
// OBJEK

void Strip() // Membuat garis putih
{
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS); 
	glVertex3f(-10, 0, 2); 
	glVertex3f(-10, 0, -2); 
	glVertex3f(10, 0, -2);
	glVertex3f(10, 0, 2); 
	glEnd(); 
	glPopMatrix();
}

void Grid2()
{
	// Tempat Parkir
	glPushMatrix();
	glColor3f(0.25f,0.25f,0.25f);
	glBegin(GL_QUADS); 
	glVertex3f(-200, 0, 200); 
	glVertex3f(-200, 0, -200); 
	glVertex3f(200, 0, -200);
	glVertex3f(200, 0, 200); 
	glEnd(); 
	glPopMatrix();
	
	// Jalan
	glPushMatrix();
	glTranslatef(350, 0, 0);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS); 
	glVertex3f(-150, 0, 50); 
	glVertex3f(-150, 0, -50); 
	glVertex3f(150, 0, -50);
	glVertex3f(150, 0, 50); 
	glEnd(); 
	glPopMatrix();
	
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslatef(0, 0, 350);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS); 
	glVertex3f(-500, 0, 50); 
	glVertex3f(-500, 0, -50); 
	glVertex3f(500, 0, -50);
	glVertex3f(500, 0, 50); 
	glEnd(); 
	glPopMatrix();
}

void Marka() // Mebuat marka (strip berjejer)
{
	glPushMatrix();
	glTranslatef(225, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(265, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(305, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(345, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(385, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(425, 0.1, 0);
	Strip();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(465, 0.1, 0);
	Strip();
	glPopMatrix();
}

void Grid3() // Rumput
{
	glColor3f(0.0f,0.75f,0.0f);
	glBegin(GL_QUADS); 
	glVertex3f(-500, -0.1, 500); 
	glVertex3f(-500, -0.1, -500); 
	glVertex3f(500, -0.1, -500);
	glVertex3f(500, -0.1, 500); 
	glEnd(); 
}

void Kabin(float panjang,float lebar,float tinggi)
{
	// === KEMUDI ===
	glPushMatrix();
	float p=panjang;
	float l=lebar;
	float t=tinggi;
	
	//Kanan
	glBegin(GL_POLYGON); 
	glVertex3f(0,0,l);
	glVertex3f(p,0,l);
	glVertex3f(p,t/2,l);
	glVertex3f(p*5/6,t,l); 
	glVertex3f(0,t,l); 
	glEnd();
	
	// Kiri
	glBegin(GL_POLYGON);
	glVertex3f(0,t,-l);
	glVertex3f(p*5/6,t,-l); 
	glVertex3f(p,t/2,-l);
	glVertex3f(p,0,-l);
	glVertex3f(0,0,-l);
	glEnd();
	
	// atas 
	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(0,t,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p*5/6,t,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p*5/6,t,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(0,t,l);
	glEnd();
 
 	// bawah 
 	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(0,0,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,0,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,0,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(0,0,l);
	glEnd();
	
 	// Depan
 	glBegin(GL_QUADS); 
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p,0,l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,t/2,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,t/2,-l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p,0,-l);
	glEnd();
	
	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p,t/2,l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p*5/6,t,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p*5/6,t,-l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p,t/2,-l);
	glEnd();
	
	
	// Belakang
 	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(0,0,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(0,t,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(0,t,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(0,0,l); 
	glEnd();
	
	// Lampu
	// Lampu Kanan
	glBegin(GL_QUADS); 
	glColor3f(0.5, 0.5, 0);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t/6,l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p+0.1,t*2/6,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p+0.1,t*2/6,l*9/10); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t/6,l*8/10);
	glEnd();
	
	// Lampu Kiri
	glBegin(GL_QUADS); 
	glColor3f(0.5, 0.5, 0);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t/6,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p+0.1,t*2/6,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p+0.1,t*2/6,-l*9/10); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t/6,-l*8/10);
	glEnd();
	
	// Barrel
	glBegin(GL_POLYGON); 
	glColor3f(0.3, 0.3, 0.3);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t/6,l*7/10); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p+0.1,t*1.3/6,l*7.3/10); 
 	glVertex3f(p+0.1,t*1.05/6,-4); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p+0.1,t*1.3/6,-l*7.3/10); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t/6,-l*7/10);
 	glVertex3f(p+0.1,t*0.8/6,0); 
	glEnd();
	
	glBegin(GL_POLYGON); 
	glColor3f(0.3, 0.3, 0.3);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t*1.4/6,l*7/10); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p+0.1,t*1.7/6,l*7.3/10); 
 	glVertex3f(p+0.1,t*1.45/6,-4); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p+0.1,t*1.7/6,-l*7.3/10); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t*1.4/6,-l*7/10);
 	glVertex3f(p+0.1,t*1.2/6,0); 
	glEnd();
	
	glBegin(GL_POLYGON); 
	glColor3f(0.3, 0.3, 0.3);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t*1.8/6,l*7/10); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p+0.1,t*2.1/6,l*7.3/10); 
 	glVertex3f(p+0.1,t*1.85/6,-4); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p+0.1,t*2.1/6,-l*7.3/10); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t*1.8/6,-l*7/10);
 	glVertex3f(p+0.1,t*1.6/6,0); 
	glEnd();
	
	// Kaca Depan
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p+0.1,t/2+0.1,l-1); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p*5/6+0.3,t-1,l-1);
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p*5/6+0.3,t-1,-l+1); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p+0.1,t/2+0.1,-l+1);
	glEnd();
	
	// Kaca Kanan
	glBegin(GL_POLYGON);
	glVertex3f(1,t/2,l+0.1);
	glVertex3f(p-1,t/2,l+0.1);
	glVertex3f(p*5/6-1,t-1,l+0.1); 
	glVertex3f(1,t-1,l+0.1); 
	glEnd();
 
	// Kaca Kanan
	glBegin(GL_POLYGON);
	glVertex3f(1,t/2,-l-0.1);
	glVertex3f(p-1,t/2,-l-0.1);
	glVertex3f(p*5/6-1,t-1,-l-0.1); 
	glVertex3f(1,t-1,-l-0.1); 
	glEnd();
	
	glPopMatrix();
}

void Balok(float panjang,float lebar,float tinggi)
{
	glPushMatrix();
	float p=panjang/2;
	float l=lebar/2;
	float t=tinggi/2;
	
	//depan 
	glBegin(GL_QUADS); 
	glVertex3f(-p,0,l); 
	glVertex3f(p,0,l); 
	glVertex3f(p,-t*2,l); 
	glVertex3f(-p,-t*2,l); 
	glEnd();
	
	// belakang 
	glBegin(GL_QUADS);
	glVertex3f(-p,0,-l); 
	glVertex3f(p,0,-l); 
	glVertex3f(p,-t*2,-l); 
	glVertex3f(-p,-t*2,-l);
	glEnd();
	
	// atas 
	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(-p,0,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,0,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,0,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(-p,0,l);
	glEnd();
 
 	// bawah 
 	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(-p,-t*2,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,-t*2,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,-t*2,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(-p,-t*2,l);
	glEnd();
	
 	// kanan 
 	glBegin(GL_QUADS); 
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(-p,-t*2,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(-p,-t*2,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(-p,0,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(-p,0,-l);
	glEnd();
 
	// kiri 
 	glBegin(GL_QUADS);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(p,-t*2,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,-t*2,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,0,l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p,0,-l); 
	glEnd();
	
	glPopMatrix();
}

void Segitiga(float panjang,float tinggi,float lebar)
{
	glPushMatrix();
	float p=panjang/2;
	float l=lebar/2;
	float t=tinggi/2;
	
	//depan 
	glBegin(GL_TRIANGLES); 
	glVertex3f(-p,0,l); 
	glVertex3f(p,0,l); 
	glVertex3f(0,t,l);
	glEnd();
	
	// belakang 
	glBegin(GL_TRIANGLES);
	glVertex3f(-p,0,-l); 
	glVertex3f(p,0,-l); 
	glVertex3f(0,t,-l);
	glEnd();
	
 	// bawah 
 	glBegin(GL_POLYGON);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(-p,0,l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(-p,0,-l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(p,0,-l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p,0,l);
	glEnd();
	
 	// kanan 
 	glBegin(GL_POLYGON); 
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(0,t,l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(0,t,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(p,0,-l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(p,0,l);
	glEnd();
 
	// kiri 
 	glBegin(GL_POLYGON);
 	glTexCoord2f(0.0f, 0.0f); 
 	glVertex3f(-p,0,l); 
 	glTexCoord2f(1.0f, 0.0f); 
 	glVertex3f(-p,0,-l); 
 	glTexCoord2f(0.0f, 1.0f); 
 	glVertex3f(0,t,-l); 
 	glTexCoord2f(1.0f, 1.0f); 
 	glVertex3f(0,t,l); 
	glEnd();
	
	glPopMatrix();
}

void Roda(float alas,float up,float height)
{
     float i;
     glPushMatrix();
     glTranslatef(1.0,0.0,-alas/8); // perpindahan dari X,Y,Z
     glutSolidCone(alas,0,32,4);
     for(i=0;i<=height;i+=alas/24)
     {
	      glTranslatef(0.0,0.0,alas/24);
	      glutSolidTorus(alas/4,alas-((i*(alas-up))/height),16,16);
     }
     glTranslatef(0.0,0.0,alas/4);
     glutSolidCone(height,0,20,1);
     glColor3f(0.,0.,0.);
     glPopMatrix();
}

void Truk()
{
		// === Truk ===
	glPushMatrix();
	
	// Bak Belakang
	glPushMatrix();
	glColor3f(0.0,0.0,0.3);
	glTranslatef(posXBadan+24,posYBadan-0.5 ,0);
	Balok(50,20,-22); 
	glPopMatrix(); 
	
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(posXBadan+24,posYBadan-4.5,0);
	Balok(52,20,-4);
	glPopMatrix(); 
	
	// Sambungan
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(posXBadan+54,posYBadan-3.5,0);
	Balok(10,5,-2); 
	glPopMatrix(); 
	
	// Bak Depan
	glPushMatrix();  
	glColor3f(0.0,0,0.3);
	glTranslatef(posXBadan+84,posYBadan-0.5,0);
	Balok(50,20,-22); 
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(posXBadan+84,posYBadan-4.5,0);
	Balok(52,20,-4);
	glPopMatrix(); 
	
	// Kabin Sopir
	glPushMatrix();
	glColor3f(0.3,0.0,0.0);
	glTranslatef(posXBadan+110,posYBadan-4.5,0);
	Kabin(15, 10, 20); 
	glPopMatrix();
	
	// Roda
	// Belakang Kanan
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+10,posYBadan-2,11);
	Roda(4, 4, 1); 
	glPopMatrix();
	
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+40,posYBadan-2,11);
	Roda(4, 4, 1); 
	glPopMatrix();
	
	// Belakang Kiri
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+10,posYBadan-2,-11);
    Roda(4, 4, 1);
	glPopMatrix();
	
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+40,posYBadan-2,-11);
    Roda(4, 4, 1);
	glPopMatrix();
	
	// Depan Kanan
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+70,posYBadan-2,11);
	Roda(4, 4, 1); 
	glPopMatrix();
	
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+115,posYBadan-2,11);
	Roda(4, 4, 1); 
	glPopMatrix();
	
	// Belakang Kiri
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+70,posYBadan-2,-11);
    Roda(4, 4, 1);
	glPopMatrix();
	
	glPushMatrix(); 
	glColor3f(0.0,0.0,0.0);
	glTranslatef(posXBadan+115,posYBadan-2,-11);
    Roda(4, 4, 1);
	glPopMatrix();
	
	glPopMatrix();
}

void Atap()
{
	glPushMatrix();
	glColor3f(0.3,0.0,0.0);
	glRotated(90, 0, 1, 0);
	glRotated(60, 0, 0, 1);
	glTranslatef(0,0,0);// Kiri
	Balok(2,275,-120);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.3,0.0,0.0);
	glRotated(90, 0, 1, 0);
	glRotated(-60, 0, 0, 1);
	glTranslatef(0,0,0);// Kiri
	Balok(2,275,-120);
	glPopMatrix();
}

void Gudang()
{
	// Dinding Belakang
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(-125,0,0);
	Balok(2,100,-100);
	glPopMatrix();
	
	// Depan
	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(125,50,0);
	Balok(2,100,-50);
	glPopMatrix();
	
	// Dinding samping
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glColor3f(0.5,0.5,0.5);
	glTranslatef(50,0,-1); // Kiri
	Balok(2,250,-100);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glColor3f(0.5,0.5,0.5);
	glTranslatef(-50,0,-1); // Kanan
	Balok(2,250,-100);
	glPopMatrix();
	
	// Segitiga
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glColor3f(0.0,0.0,0.0);
	glTranslatef(0,100,125);
	Segitiga(100,62.5,2);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glColor3f(0.0,0.0,0.0);
	glTranslatef(0,100,-125);
	Segitiga(100,62.5,2);
	glPopMatrix();
	
	// Atap
	glPushMatrix();
	glRotated(180, 1, 0, 0);
	glTranslatef(0, -130, 0);
	Atap();
	glPopMatrix;
}


void Pembatas()
{
	// Depan
	glPushMatrix(); // Kanan
	glColor3f(0.75,0.75,0.75);
	glTranslatef(200,0,125);
	Balok(2,150,-2);
	glPopMatrix();
	
	glPushMatrix(); // Kiri
	glColor3f(0.75,0.75,0.75);
	glTranslatef(200,0,-125);
	Balok(2,150,-2);
	glPopMatrix();
	
	// Belakang
	glPushMatrix();
	glColor3f(0.75,0.75,0.75);
	glTranslatef(-200,0,0);
	Balok(2,398,-2);
	glPopMatrix();
	
	// Kanan
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glColor3f(0.75,0.75,0.75);
	glTranslatef(-200,0,0);
	Balok(2,402,-2);
	glPopMatrix();
	
	// Kiri
	glPushMatrix();
	glRotated(-90, 0, 1, 0);
	glColor3f(0.75,0.75,0.75);
	glTranslatef(-200,0,0);
	Balok(2,402,-2);
	glPopMatrix();
}

void Pohon()
{
	//Kanan
	glPushMatrix(); // Batang Kanan
	glColor3f(0.2f, 0.0f, 0.0f);
	glTranslatef(290, 0, 70);
	Balok(10, 10, -50);
	glPopMatrix();
	
	glPushMatrix(); // Daun Kanan
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(290, 50, 70);
	Balok(30, 30, -30);
	glPopMatrix();
	
	//Kiri
	glPushMatrix(); // Batang Kiri
	glColor3f(0.2f, 0.0f, 0.0f);
	glTranslatef(290, 0, -70);
	Balok(10, 10, -50);
	glPopMatrix();
	
	glPushMatrix(); // Daun Kiri
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(290, 50, -70);
	Balok(30, 30, -30);
	glPopMatrix();
}

void Palang()
{
	glPushMatrix();
	glRotated(45, 1, 0, 0);
	glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
	glTranslatef(210, 40, -70);
	Balok(5, 125, -5);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
	glTranslatef(205, -60, -120);
	Balok(5, 20, -5);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor4f(0.5f, 0.5f, 0.5f, 0.0f);
	glTranslatef(215, -60, -120);
	Balok(5, 20, -5);
	glPopMatrix();
}

void Object()
{
	glPushMatrix();
	Truk();
	Gudang();
	Palang();
	glPopMatrix();
} 

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 	// Kalau move dan angle tidak nol, gerakkan kamera... 
 	if (deltaMove) 
 	moveMeFlat(deltaMove);
 	
 	if (deltaAngle) 
	{ 
	 	angle += deltaAngle; 
	 	orientMe(angle); 
	} 
 
 	glPushMatrix();
	glRotated(rotAngleX+10, 1, 0, 0); 
 	glRotated(rotAngleY, 0, 1, 0);
 	glRotated(rotAngleZ, 0, 0, 1);
 	
	// Gambar grid 
 	Grid2();
 	Marka();
 	Grid3();
 	
	// Gambar objek di sini... 
	Pembatas();
 	Pohon();
 	Object(); 
	glPopMatrix(); 
	glFlush(); 
	glutSwapBuffers();
}

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(640,480); 
	glutCreateWindow("Tugas Besar - Praktikum GKV - Truk Gandeng Parkir"); 
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey); 
	glutDisplayFunc(display); 
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display); 
	glutReshapeFunc(Reshape);
	lighting();
	init();
	glutMainLoop();
	return(0);
}
