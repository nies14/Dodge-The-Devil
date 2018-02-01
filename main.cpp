#include <windows.h>
#include <bits/stdc++.h>
#include<GL/gl.h>
#include <GL/glut.h>

#include "imageloader.h"

using namespace std;

char quote[6][80];
int window_1,window_2;

float _angle = 0.0;
float _angle1=0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float devilTranslate=0.0;
float devilLeft=0;
int life=0,score=0;
int firstOb=1,firstOb2=1,scndob=1,scndob2=1,thrdOb=1,thrdOb2=1,fourOb=1,fourOb2=1,fiveOb=1,fiveOb2=1,six0b=1,sevenOb=1,six0b2=1,sevenOb2=1;
int flag = 1,stopMain=1;
double humanx=0.0,humanXflag=0.0,humany=0.0,hymanyFlag=0.0,devilx=0,devily=0;;
double move_unit = .1;


//Texture Starts

GLuint _textureId;
GLuint _textureId1;



void drawTexture()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

	glTranslatef(0.0, 0.0, -1.0f);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 5.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(5.0, 5.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(5.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();

    glPopMatrix();

    /*glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, _textureId1);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(0.0, 2.0, -5.0f);

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);

	glTexCoord2f(0.0, 5.0);
	glVertex3f(-1.0, 1.0, 0.0);

	glTexCoord2f(5.0, 5.0);
	glVertex3f(1.0, 1.0, 0.0);

	glTexCoord2f(5.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);

	glEnd();


    glPopMatrix();*/

	glutSwapBuffers();
}

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void lightSetting(int x,int y,int z, int a)
{
	//GLfloat ambientIntensity[4] = {0.6, 0.0, 1.0, 0.0};
	GLint ambientIntensity[4] = {x,y,z,a};
	GLint position[4] = {20,0,200};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	glLightiv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

	glLightiv(GL_LIGHT0, GL_POSITION, position);
}

void initialize() {

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	//glEnable(GL_COLOR_MATERIAL);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.00, 1.0, 200.0);
	lightSetting(0,255,0,0);

	Image* image = loadBMP("G:\\Varsity Files\\Semester 8\\Final Term\\Graphics\\Project\\Nies\\game.bmp");
	//Image* image1 = loadBMP("C:\\Users\\DELL\\Desktop\\Nies\\aiub.bmp");
	_textureId = loadTexture(image);
	//_textureId1 = loadTexture(image1);
	delete image;
}



//Texture Ends


//Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void menu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(-3.5, -4.0, -7.0); //Move forward 5 units
    glClearColor(0.1,0.5,0.2,0);


    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex3i(0,0,0);
    glVertex3i(400,0,0);
    glVertex3i(400,400,0);
    glVertex3i(0,400,0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void sky()
{
    glPushMatrix(); //Save the current state of transformations
	glTranslatef(-7.0, -3.3, 0.0); //Move to the center of the triangle
	//glRotatef(_angle, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)

    glBegin(GL_POLYGON); //Sky
    glColor3ub(30,144,255);
    //glColor3ub(0,206,255);
    glVertex3i(0,0,0);
    glVertex3i(1342,0,0);
    glVertex3i(1342,680, 0);
    glVertex3i(0,680,0);
    glEnd();

    glPopMatrix();
}

void cloud_front2()
{
	// cloud 1     0, 140, 68


	glPushMatrix();
	glTranslatef(0.0,0.0,.5);

	glPushMatrix();
	glColor3ub(255,255,153);
    //glColor3ub(0, 140, 68);
    glTranslatef(-4.8,0.0,0);
    //glEnable(GL_LIGHT_MODEL_TWO_SIDE);
    glutSolidSphere(.95,20,20);
    glPopMatrix();

    // cloud 2

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-4.0,0.4,.35);
    glutSolidSphere(0.55,20,20);
    glPopMatrix();


// cloud 3

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-2.9,0.2,0);
    //glEnable(GL_LIGHT3);
    glutSolidSphere(0.8,20,20);
    glPopMatrix();

// cloud 4

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-1.8,.7,0);
    glutSolidSphere(0.60,20,20);
    glPopMatrix();

    // cloud 5

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-1.1,.05,-.50);
    glutSolidSphere(.9,20,20);
    glPopMatrix();

    // cloud 6

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(.15,.5,0);
    glutSolidSphere(.78,20,40);
    glPopMatrix();

    // cloud 7

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(1.3,-.35,0.0);
    glutSolidSphere(.9,20,40);
    glPopMatrix();

    // cloud 8

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(2.35,.0,0.0);
    glutSolidSphere(.6,20,40);
    glPopMatrix();

    // cloud 9

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(3.5,.40,0.0);
    glutSolidSphere(.9,20,40);
    glPopMatrix();

    // cloud 10
    glPushMatrix();
    //glColor3ub(176,196,222);
    glColor3ub(255,255,153);
    glTranslatef(5.05,.25,0.0);
    glutSolidSphere(.85,20,40);
    glPopMatrix();

	glPopMatrix();


}

void cloud_front()
{
	// cloud 1
    glPushMatrix();
	glTranslatef(0.0,0.0,-.20);

	glPushMatrix();
//    lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-5,1.2,0);
    glutSolidSphere(.65,20,20);
    glPopMatrix();

    // cloud 2

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-4.0,1.1,0);
    glutSolidSphere(0.45,20,20);
    glPopMatrix();


// cloud 3

    glPushMatrix();
//    lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-2.9,1.2,0);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();

// cloud 4

    glPushMatrix();
//    lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-1.8,1.3,0);
    glutSolidSphere(0.60,20,20);
    glPopMatrix();

    // cloud 5

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-.8,1.3,0);
    glutSolidSphere(0.45,20,20);
    glPopMatrix();

    // cloud 6

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(.15,1.3,0);
    glutSolidSphere(.78,20,40);
    glPopMatrix();

    // cloud 7

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(1.3,1.3,0.5);
    glutSolidSphere(.4,20,40);
    glPopMatrix();

    // cloud 8

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(2.35,1.3,0.0);
    glutSolidSphere(.8,20,40);
    glPopMatrix();

    // cloud 9

    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(3.9,1.15,0.0);
    glutSolidSphere(.8,20,40);
    glPopMatrix();

    // cloud 10
    glPushMatrix();
    //lightSetting();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(5.15,1.15,0.0);
    glutSolidSphere(.5,20,40);
    glPopMatrix();

	glPopMatrix();

}

void cloud_upground()
{
    glPushMatrix();
    glTranslatef(0.0,.5,1.60);

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-4.8,-2.0,0);
    //glEnable(GL_LIGHT_MODEL_TWO_SIDE);
    glutSolidSphere(.95,20,20);
    glPopMatrix();

    // cloud 2

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-4.0,-1.6,0);
    glutSolidSphere(0.65,20,20);
    glPopMatrix();


// cloud 3

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-2.9,-1.8,0);
    //glEnable(GL_LIGHT3);
    glutSolidSphere(0.9,20,20);
    glPopMatrix();

// cloud 4

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-1.8,-1.8,0);
    glutSolidSphere(0.60,20,20);
    glPopMatrix();

    // cloud 5

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(-1.1,-1.95,0);
    glutSolidSphere(1.1,20,20);
    glPopMatrix();

    // cloud 6

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(.15,-1.5,0);
    glutSolidSphere(.78,20,40);
    glPopMatrix();

    // cloud 7

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(1.3,-1.75,0.0);
    glutSolidSphere(.9,20,40);
    glPopMatrix();

    // cloud 8

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(2.35,-2.0,0.0);
    glutSolidSphere(.6,20,40);
    glPopMatrix();

    // cloud 9

    glPushMatrix();
    glColor3ub(255,255,153);
    glTranslatef(3.5,-1.60,0.0);
    glutSolidSphere(.9,20,40);
    glPopMatrix();

    // cloud 10
    glPushMatrix();
    //glColor3ub(176,196,222);
    glColor3ub(255,255,153);
    glTranslatef(5.05,-1.85,0.0);
    glutSolidSphere(.85,20,40);
    glPopMatrix();

    glPopMatrix();

}

void cloud_back()
{
	// cloud 1
	glPushMatrix();
	glTranslatef(0.0,0.0,1.0);
	glPushMatrix();
    lightSetting(176,196,222,0);
    //glColor3ub(176,196,222);
    glTranslatef(-4.8,1.9,0);
    glutSolidSphere(.75,20,20);
    glPopMatrix();

    // cloud 2

    glPushMatrix();
    lightSetting(176,196,222,0);
    //glColor3ub(176,196,222);
    glTranslatef(-4.0,1.8,0);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();


// cloud 3

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(-2.9,1.9,0);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();

// cloud 4

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(-1.8,2.3,0);
    glutSolidSphere(0.65,20,20);
    glPopMatrix();

    // cloud 5

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(-.85,1.7,-.4);
    glutSolidSphere(0.62,20,20);
    glPopMatrix();

    // cloud 6

    glPushMatrix();
    lightSetting(176,196,222,.9);;
    //glColor3ub(176,196,222);
    glTranslatef(.15,2.3,0);
    glutSolidSphere(.9,20,40);
    glPopMatrix();

    // cloud 7

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(1.3,1.7,0.0);
    glutSolidSphere(.5,20,40);
    glPopMatrix();

    // cloud 8

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(2.35,2.0,0.0);
    glutSolidSphere(.8,20,40);
    glPopMatrix();

    // cloud 9

    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(3.7,1.72,0.5);
    glutSolidSphere(.7,20,40);
    glPopMatrix();

    // cloud 10
    glPushMatrix();
    lightSetting(176,196,222,0);;
    //glColor3ub(176,196,222);
    glTranslatef(3.8,1.6,1.0);
    glutSolidSphere(.2,20,40);
    glPopMatrix();
	glPopMatrix();


}

void ground()
{

    /*// y-axis-ground
    glPushMatrix();

	glScalef(0.5,1.7,0.5);
	glTranslatef(-12.0, -.5, 0.0);
	glBegin(GL_POLYGON);

    glColor3f(.7,.5,.1);
	glVertex3f(0.5,0,0);
	glVertex3f(23.5,0,0);
	glVertex3f(20.5,.5, 0);
	glVertex3f(3,.5,0);
	glEnd();
	glPopMatrix();*/

    glPushMatrix();
    glTranslatef(.05,.1,.5);

    glPushMatrix();
	glTranslatef(0.0, -.56, 1.7);
    glScalef(7.10,.8,1.6);
    glColor3ub(184,134,11);
    glutSolidCube(.94);
    glPopMatrix();

  // ground1_Layer
    glPushMatrix();
	glTranslatef(0.0, -.38, 1.7);
    glScalef(8,0.01,1.6);
    glColor3ub(255,228,196);
    glutSolidCube(0.94);
    glPopMatrix();


    //ground_2
    glPushMatrix();
	glTranslatef(-1.55, .32, 1.10);
    glScalef(2.2,0.56,0.3);
    glColor3f(.7,.5,.1);
    glutSolidCube(0.8);
    glPopMatrix();

// ground_2 Layer
    glPushMatrix();
	glTranslatef(-1.55, .55, 1.10);
    glScalef(2.2,0.02,0.3);
    glColor3f(.7,.5,.1);
    glutSolidCube(0.8);
    glPopMatrix();

// ground_3
    glPushMatrix();
	glTranslatef(1.3, 1.4, 1.70);
    glScalef(1.7,0.6,0.3);
    glColor3f(.7,.5,.1);
    glutSolidCube(0.7);
    glPopMatrix();
// ground_3Layer

    glPushMatrix();
	glTranslatef(1.05, 1.44, 2.70);
    glScalef(2.0,0.01,0.3);
    glColor3ub(255,228,196);
    glutSolidCube(.48);
    glPopMatrix();


    glPopMatrix();
    // ground1

}

void Human()
{
    //printf("Human x: %f\n",humanx);
    //printf("Human y: %f\n",humany);
    glPushMatrix();
	glTranslatef( humanx- 4.2,humany-.12, 0.0);
    glScalef(2.0,0.6,0.3);
    glColor3ub(0,255,255);
    glutSolidCube(0.4);
    glPopMatrix();

    if(humany>-.12)
        humany -=.018;

}

void good()
{
    //-------------------------ear
    /*glPushMatrix();
    glTranslatef(-4.42,-1.96,0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-0.15,2.0,0.0);
    glVertex3f(-0.4,2.5,0.0);
    glVertex3f(-0.1,2.0,0.0);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4.22,-1.96,0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(0.15,2.0,0.0);
    glVertex3f(0.4,2.5,0.0);
    glVertex3f(0.1,2.0,0.0);
    glEnd();
    glPopMatrix();*/

    //--------------------body-------------------


   // glTranslatef(0.0,-2.3,0.0);
    //glRotatef(_angle,0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(1.0,0.35,1.65);

    glPushMatrix();
    glTranslatef(humanx-4.3,humany-.15,0.0);

    glColor3ub(212,120,15);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.28,20,20);
    glPopMatrix();

     //--------------------eye---------------------
    glPushMatrix();
    glTranslatef(humanx-4.3,humany-0.1,.26);
    glColor3ub(0,0,0);
    glutSolidSphere(.05,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(humanx-4.15,humany-0.1,.26);
    glColor3ub(0,0,0);
    glutSolidSphere(.05,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(humanx-4.22,humany-0.25,.26);
    glColor3ub(0,0,0);
    glutSolidSphere(.035,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(humanx-4.20,humany-0.235,.26);
    glColor3ub(0,0,0);
    glutSolidSphere(.035,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(humanx-4.24,humany-0.235,.26);
    glColor3ub(0,0,0);
    glutSolidSphere(.035,20,20);
    glPopMatrix();

    if(humanx>=-1.3 && humanx<=.6)
    {
        if(humany>.05)
            humany -=.022;

    }
    else if(humanx>.6 && humanx <=2.9)
    {
        if(humany>.8)
            humany -= .022;
        //cout<<"sesh"<<endl;
    }

    else if(humanx>2.9 && humanx <=4.1)
    {
        //cout<<"ata"<<endl;
        if(humany>=.05)
            humany -= .022;
    }
    else if(humanx>4.1 && humanx <=5.8)
    {
        if(humany>1.95 && humany<=2.7)
            humany -= 0.022;
        if(humany>=.9 && humany<=1.8)
            humany -=.1;
        else if(humany>.05 && humany<.9)
            humany -= 0.022;
    }

    /*else if(humanx>=4.1 && humanx <5.5)
    {
        if(humany>1.96)
            humany -= .022;
        else if(humany>=.5 && humany<1.3)
        {
            //cout<<"hoise"<<endl;
            humany -= .022;
        }

    }*/
    else if(humany>=.05)
        humany -=.022;


    glPopMatrix();

}

void object()
{
    //glTranslatef(enemyTranslate,0.0,0.0);
    glPushMatrix();
    glTranslatef(1.0,0.3,2.0);


    if(firstOb==1)
    {
        glPushMatrix();
        glTranslatef(-2.9,0.72,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(1.0,1.0,0.0);
        glScalef(.30,0.30,.30);
        glutSolidTetrahedron();
        glPopMatrix();
    }

    if(firstOb2==1)
    {
        glPushMatrix();
        glTranslatef(-2.0,0.72,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(0.0,0.0,1.0);
        glScalef(.30,0.30,.30);
        glutSolidTorus(.2,.5,4,4);
        glPopMatrix();

    }

    if(scndob==1)
    {
        glPushMatrix();
        glTranslatef(.03,1.70,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(1.0,0.0,1.0);
        glScalef(.30,0.30,.30);
        glutSolidTeapot(.6);
        glPopMatrix();
    }


    if(scndob2==1)
    {
        glPushMatrix();
        glTranslatef(.9,1.70,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(.5,1.0,0.0);
        glScalef(.30,0.30,.30);
        glutSolidSphere(.6,4,4);
        glPopMatrix();
    }

    if(thrdOb==1)
    {
        glPushMatrix();
        glTranslatef(.4,-.1,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(0.0,0.0,0.0);
        glScalef(.30,0.30,.30);
        glutSolidCone(.9,.9,3,2);
        glPopMatrix();

    }
    if(thrdOb2==1)
    {
        glPushMatrix();
        glTranslatef(1.9,-.1,0.0);
        glRotatef(_angle,0.0,1.0,0.0);
        glColor3f(1.0,0.0,0.0);
        glScalef(.30,0.30,.30);
        glutSolidTeapot(.7);
        glPopMatrix();
    }


    glPopMatrix();


}

void keyboardGame2(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        cout<<"EXIT"<<endl;
        exit(1);
        break;
    default:
        break;
    }
}

void letterText()
{

    char text[150];
    if(score==0)
    {
        cout<<"In 0"<<endl;
        memset(text,'\0',sizeof(text));
        sprintf(text, "                                                                             UNLUCKY. TRY AGAIN\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.8 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        //cout<<score<<endl;
        //sky();
    }
    else if(score >0 && score <=2)
    {
        sprintf(text, "                                                          NOT SO GOOD. TRY AGAIN TO LEARN MORE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.8 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "A = APPLE; B = BALL; C = CAT; D = DOG; E = EGG; F = FAT; G = GOAT; H = HAND; I = ICE-CREAM; J = JAGUAR\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.5 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    //text[150];
    else if(score >2 && score <=4)
    {
        sprintf(text, "                                                          GOOD. TAKE ANOTHER CHANCE TO LEARN MORE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.8 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "A = APPLE; B = BALL; C = CAT; D = DOG; E = EGG; F = FAT; G = GOAT; H = HAND; I = ICE-CREAM; J = JAGUAR\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , .5 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "K = KANGAROO; L = LAMP; M = MAGIC; N = NAME; O = ORANGE; P = PINEAPPLE; Q = QUEEN; R = RABBIT; S = SANDWICH; T = TREE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , -.2 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    else if(score >4 && score <=5)
    {
        sprintf(text, "                                                          WELLDONE. YOU CAN LEARN MORE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.8 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "A = APPLE; B = BALL; C = CAT; D = DOG; E = EGG; F = FAT; G = GOAT; H = HAND; I = ICE-CREAM; J = JAGUAR\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , .5 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "K = KANGAROO; L = LAMP; M = MAGIC; N = NAME; O = ORANGE; P = PINEAPPLE; Q = QUEEN; R = RABBIT; S = SANDWICH; T = TREE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , -.2 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        sprintf(text, "U = UMBRELLA; V = VIOLIN\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , -.9 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

    }

    else if(score>=6)
    {
        sprintf(text, "                                                          YOU ARE A CHAMPION KID\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , 1.8 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "A = APPLE; B = BALL; C = CAT; D = DOG; E = EGG; F = FAT; G = GOAT; H = HAND; I = ICE-CREAM; J = JAGUAR\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , .5 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

        sprintf(text, "K = KANGAROO; L = LAMP; M = MAGIC; N = NAME; O = ORANGE; P = PINEAPPLE; Q = QUEEN; R = RABBIT; S = SANDWICH; T = TREE\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , -.2 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        sprintf(text, "U = UMBRELLA; V = VIOLIN; W = WINDOW; X=X-RAY; Z = ZEBRA\0");
        glColor3f(0.0,0.0,0.0);
        glRasterPos3f(-4.4 , -.9 , 1);
        for(int i = 0; text[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    else
    {
        cout<<"another"<<endl;
        sky();
    }


}

void lastDisplay()
{
	sky();
	letterText();
	glutKeyboardFunc(keyboardGame2);

}


void PlayerLifeText()
{
    char text[32];
    sprintf(text, "Player Life : ");
    glColor3f(0.0,0.0,0.0);
    glRasterPos3f(-4.1 , 3.08 , 1);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void PlayerLifeBar()
{
    glPushMatrix();
    glTranslatef(0.0,0.0,0.0);

    glPushMatrix();
    glTranslatef(-2.3,3.5,0.0);
    glColor3f(.5,.6,.1);
    glScalef(3.0,0.15,0.0);
    glutWireCube(.9);
    glPopMatrix();
    if(life==3)
    {
        glPushMatrix();
        glTranslatef(-2.3,3.5,0.0);
        glColor3f(0.0,1.0,0.0);
        glScalef(2.98,0.132,0.0);
        glutSolidCube(.9);
        glPopMatrix();
    }
    if(life==2)
    {
        glPushMatrix();
        glTranslatef(-2.85,3.5,0.0);
        glColor3f(1.0,1.0,0.0);
        glScalef(1.75,0.132,0.0);
        glutSolidCube(.9);
        glPopMatrix();
    }

    if(life==1)
    {
        glPushMatrix();
        glTranslatef(-3.33,3.5,0.0);
        glColor3f(1.0,0.0,0.0);
        glScalef(0.70,0.132,0.0);
        glutSolidCube(.9);
        glPopMatrix();
    }

    glPopMatrix();


}

void drawcollision_effect()
{
    //body
    glPushMatrix();
    glTranslatef(.5,0.0,.50);

    glPushMatrix();
    glTranslatef(devilTranslate,0.10,0.0);
    glColor3ub(255, 255, 0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.2,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(devilTranslate+.2,0.20,0.0);
    glColor3ub(255, 255, 0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.2,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(devilTranslate,0.28,0.0);
    glColor3ub(255, 255, 0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.2,20,20);
    glPopMatrix();

    //horn
    glPushMatrix();
    glTranslatef(devilTranslate,-1.7,0.0);
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex3f(-0.15,2.0,0.0);
    glVertex3f(-0.4,2.5,0.0);
    glVertex3f(-0.1,2.0,0.0);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(devilTranslate,-1.82,0.0);
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex3f(0.2,2.0,0.0);
    glVertex3f(0.7,2.3,0.0);
    glVertex3f(0.1,2.0,0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(devilTranslate,-2.0,0.0);
    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex3f(-0.15,2.0,0.0);
    glVertex3f(-0.4,1.5,0.0);
    glVertex3f(-0.1,2.0,0.0);
    glEnd();
    glPopMatrix();

    glPopMatrix();


}

void Devil_1()
{
    glPushMatrix();
    glTranslatef(0.0,0.3,2.3);

    //-------------------------ear
    glPushMatrix();
    glTranslatef(devilTranslate,0.0,0.0);
    glPushMatrix();
    glTranslatef(-0.12,-1.96,0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(-0.15,2.0,0.0);
    glVertex3f(-0.4,2.5,0.0);
    glVertex3f(-0.1,2.0,0.0);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.12,-1.96,0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(0.15,2.0,0.0);
    glVertex3f(0.4,2.5,0.0);
    glVertex3f(0.1,2.0,0.0);
    glEnd();
    glPopMatrix();

    //--------------------body-------------------


   // glTranslatef(0.0,-2.3,0.0);
    //glRotatef(_angle,0.0,1.0,0.0);
    glPushMatrix();
    glTranslatef(0.0,-.12,0.0);

    glColor3ub(255,0,0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.3,20,20);
    glPopMatrix();

     //--------------------eye---------------------
    glPushMatrix();
    glTranslatef(-0.070,-.07,.315);
    glColor3ub(0,0,0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.05,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.075,-.07,.315);
    glColor3ub(0,0,0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.05,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.002,-.199,.315);
    glColor3ub(0,0,0);
    //glScalef(.30,0.30,.30);
    glutSolidSphere(.05,20,20);
    glPopMatrix();
    glPopMatrix();

   // flag++;
  //  cout<<flag<<endl;

    double distance = devilTranslate-humanx+3.4;
    if(distance >=.01 && distance <= .5)
    {
        if(flag>=0 && flag < 1 && humany<=.58)
        {
            life--;
            drawcollision_effect();
            cout<<"life: "<<life<<endl;
            //cout<<"humany: "<<humany<<endl;
        }

        flag++;
    }

    glPopMatrix();

}

//Draws the 3D scene

void drawScene()
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, -0.8, -7.0); //Move forward 5 units
    glClearColor(0.1,0.5,0.2,0);

    if(life>0 && score<6)
    {
        ground();
        PlayerLifeText();
        cloud_front2();
        Devil_1();
        object();
        good();

        cloud_upground();

        cloud_front();
        cloud_back();
        PlayerLifeBar();
        sky();


    }

	else
    {
        //stopMain=0;
        lastDisplay();

    }

	glutSwapBuffers();
}

void update(int value)
{
	_angle += 5.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}
	if(devilLeft==0)
    {
        devilTranslate-=0.012f;
        if(devilTranslate<=-3.7f)
        {
            devilLeft=1;
            flag=0;
        }
    }
    if(devilLeft==1)
    {
        devilTranslate+=0.012f;
        if(devilTranslate>=3.7f)
        {
            devilLeft=0;
            flag=0;
        }
    }


	glutPostRedisplay(); //Tell GLUT that the display has changed
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}


void KeyboardGame(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            //cout<<humanx<<endl;
            if(humanx>=3.9 && humanx <6)
            {
                if(humany>1.95 && humany<2.5)
                     humany += move_unit;
                else if(humany>=.5 && humany<.8)
                     humany +=move_unit;
            }
            if(humany<2.5)
                humany += move_unit;
            cout<<"y: "<<humany<<endl;
            glutPostRedisplay();
            break;

        case GLUT_KEY_DOWN:
            //collision wirh 2nd ground
            if(humanx>=3.7 && humanx <5.7)
            {
                if(humany>1.95 && humany<2.5)
                     humany -= move_unit;
                if(humany>.03 && humany<.11)
                     humany -= move_unit;
            }
             if(humany>2.5)
                humany -= move_unit;
            /*if(humanx>.4 && humanx<2.9)
            {
                cout<<"in first "<<endl;
                if(humany>.8)
                    humany -=move_unit;
            }
            else if(humanx>3.2 && humanx <6.0)
            {
                if(humany>2.8)
                    humany -= move_unit;
            }
            else if(humany>.05)
            {
                cout<<"in 2nd "<<endl;
                humany -= move_unit;
            }*/

            cout<<"y: "<<humany<<endl;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            cout<<devilTranslate<<endl;
            cout<<humanx<<endl;
            //collision wirh 2nd ground
            if(humanx>=-1.3 && humanx<=.4)
            {
                cout<<"in first "<<endl;
                humanx+=move_unit;
            }

            else if(humanx>.4 && humanx<3)
            {
                if(humanx>=1.3 && humanx <= 1.4 && humany>=.5 && humany<=1.2)
                {
                    if(firstOb==1 && score <=6)
                        score++;
                     cout<<score<<endl;
                     firstOb=0;
                }
                if(humanx>=2.2 && humanx <= 2.4 && humany>=.5 && humany<=1.4)
                {
                    if(firstOb2==1 && score<=6)
                        score++;
                     cout<<score<<endl;
                     firstOb2=0;
                }
                //cout<<"in 2nd "<<endl;
                if(humany>=.72)
                    humanx += move_unit;

            }

            else if(humanx>=3 && humanx<=3.9)
            {
                cout<<"dukhlam"<<endl;
                humanx += move_unit;
            }

            else if(humanx>3.9 && humanx <5.7)
            {
                if(humanx>=4.3 && humanx <= 4.55 && humany>=1.6 && humany<=2.05)
                {
                    if(scndob==1 && score <=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob=0;
                }

                if(humanx>=5.2 && humanx <= 5.5 && humany>=1.6 && humany<=2.05)
                {
                    if(scndob2==1 && score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob2=0;
                }

                if(humanx>=4.35 && humanx <= 4.7 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb==1 && score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb=0;
                }



                if(humany>1.85 && humany<2.5)
                    humanx += move_unit;
                if(humany>.015 && humany<1.1)
                    humanx += move_unit;
                //else if(humany>2.6)
                  //  humanx += move_unit;
            }
            else if(humanx>=2.5 && humanx<7.3)
            {
                if(humanx>=6.1 && humanx <= 6.5 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb2==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb2=0;
                }

               /* if(humanx>=8.3 && humanx <= 8.5 && humany>=.5 && humany<=1.3)
                {
                    if(fourOb==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     fourOb=0;
                }*/

                cout<<"in 3rd "<<endl;
                humanx +=move_unit;
            }

            if(flag>0 && devilLeft==1)
            {
                flag=0;
            }

            //else //if(humanx >=2.9)
                //humanx += move_unit;
            //else if(humanx<=.3)
              //
            cout<<"x: "<<humanx<<endl;
            glutPostRedisplay();
            break;

        case GLUT_KEY_LEFT:

            if(humanx>=-.7 && humanx<=.4)
            {
                cout<<"in first "<<endl;
                humanx-=move_unit;
            }

            else if(humanx>.4 && humanx<=3)
            {
                if(humanx>=1.3 && humanx <= 1.4 && humany>=.7 && humany<=1.2)
                {
                    if(firstOb==1 && score <=6)
                        score++;
                     cout<<score<<endl;
                     firstOb=0;
                }
                if(humanx>=2.2 && humanx <= 2.5 && humany>=.7 && humany<=1.4)
                {
                    if(firstOb2==1 && score<=6)
                        score++;
                     cout<<score<<endl;
                     firstOb2=0;
                }
                //cout<<"in 2nd "<<endl;
                if(humany>=.72)
                    humanx -= move_unit;

            }

            else if(humanx>=3.1&& humanx<=4)
            {
                cout<<"dukhlam"<<endl;
                humanx -= move_unit;
            }

            else if(humanx>4 && humanx <5.8)
            {
                if(humanx>=4.3 && humanx <= 4.55 && humany>=1.6 && humany<=2.05)
                {
                    if(scndob==1 && score <=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob=0;
                }

                if(humanx>=5.2 && humanx <= 5.5 && humany>=1.6 && humany<=2.05)
                {
                    if(scndob2==1 && score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob2=0;
                }

                if(humanx>=4.35 && humanx <= 4.7 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb==1 && score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb=0;
                }



                if(humany>1.85 && humany<2.5)
                    humanx -= move_unit;
                if(humany>.015 && humany<1.1)
                    humanx -= move_unit;
                //else if(humany>2.6)
                  //  humanx += move_unit;
            }
            else if(humanx>=2.5 && humanx<7.3)
            {
                if(humanx>=6.1 && humanx <= 6.5 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb2==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb2=0;
                }

               /* if(humanx>=8.3 && humanx <= 8.5 && humany>=.5 && humany<=1.3)
                {
                    if(fourOb==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     fourOb=0;
                }*/

                cout<<"in 3rd "<<endl;
                humanx -=move_unit;
            }

            if(flag>0 &&devilLeft==0)
            {
                flag=0;
            }

            //else //if(humanx >=2.9)
                //humanx += move_unit;
            //else if(humanx<=.3)
              //
            cout<<"x: "<<humanx<<endl;
            glutPostRedisplay();
            break;
            /*cout<<devilTranslate<< " "<<humanx<<endl;
            if(humanx>=-.9 && humanx<=.6)
                humanx -= move_unit;
            else if(humanx>.6 && humanx<3.1)
            {
                if(humanx>=1.1 && humanx <= 1.6 && humany>=.8 && humany<=1.4)
                {
                    if(firstOb==1 && score <=6)
                        score++;
                     cout<<score<<endl;
                     firstOb=0;
                }
                if(humanx>=2.2 && humanx <= 2.5 && humany>=.8 && humany<=1.4)
                {
                    if(firstOb2==1 && score<=6)
                        score++;
                     cout<<score<<endl;
                     firstOb2=0;
                }
                if(humany>.72)
                    humanx -= move_unit;
            }
            else if(humanx>=3.1 && humanx<=3.4)
            {
                humanx -= move_unit;
            }
            else if(humanx>3.4 && humanx<5.7)
            {
                if(humanx>=3.9 && humanx <= 4.2 && humany>=2.7 && humany<=3.2)
                {
                    if(scndob==1 && score <=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob=0;
                }

                if(humanx>=4.9 && humanx <= 5.4 && humany>=2.7 && humany<=3.2)
                {
                    if(scndob2==1 && score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     scndob2=0;
                }

                if(humanx>=4.35 && humanx <= 4.7 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb=0;
                }
               if(humany<1.9)
                    humanx -= move_unit;
                else if(humany>2.6)
                    humanx -= move_unit;
            }
            else if(humanx>=5.7 && humanx<9.7)
            {
                if(humanx>=6.0 && humanx <= 6.5 && humany>=-.04 && humany<=.4)
                {
                    if(thrdOb2==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     thrdOb2=0;
                }

                if(humanx>=8.3 && humanx <= 8.5 && humany>=.5 && humany<=1.3)
                {
                    if(fourOb==1&& score<=6)
                        score++;
                     cout<<"score: "<<score<<endl;
                     fourOb=0;
                }
                //cout<<"in 3rd "<<endl;
                humanx -=move_unit;
            }

            cout<<"left x: "<<humanx<<endl;
            //if(humanx>2.8 && humany<=.4)
              //  humany -= 0;
            if(flag>0 && devilLeft==0)
            {
                flag=0;
            }
            glutPostRedisplay();
            break;*/




        case GLUT_KEY_F3:
            exit(1);
            break;
        case GLUT_KEY_F1:
            glutFullScreen();
            break;
        case GLUT_KEY_F2:
            glutReshapeWindow(1342,680);
            glutInitWindowPosition(100, 100);
            break;
        default:
            break;
    }
    //humany -=.05;
    //glutPostRedisplay();

}

void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {

        case 's':
        case 'S':
            life =3;
            glutInitWindowSize (1342,680);
            glutInitWindowPosition (10, 10);
            window_2 = glutCreateWindow ("2");
            glutSetWindowTitle("GAME");
            //glutFullScreen();
            glutDisplayFunc(drawScene);
            glutReshapeFunc(handleResize);
            glutSpecialFunc(KeyboardGame);
        case 'd':
            //humany -= move_unit;
            //glutPostRedisplay();
            break;

            break;
        case 27:
            exit(1); // exit program when [ESC] key presseed
            break;
        default:
            break;
    }
}


int main(int argc, char** argv)
{
    humanx=0.0,humanXflag=0.0,humany=0.0,hymanyFlag=0.0;
    life =3;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize (500, 500);
    glutInitWindowPosition (400, 160);
	glutTimerFunc(25, update, 0); //Add a timer
    window_1 = glutCreateWindow ("Window 1");
    glutSetWindowTitle("MENU");
	//initRendering();
	initialize();
	//lightSetting(176,196,222,0);;

    glutDisplayFunc(drawTexture);

	//Set handler functions
	//glutDisplayFunc(menu);
	glutReshapeFunc(handleResize);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
	return 0;
}
