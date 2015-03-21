//
//  main.cpp
//  Graphics
//
//  Created by Vikram on 1/19/15.
//  Copyright (c) 2015 Vikram. All rights reserved.
//

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include<cstdlib>
#include<cstdio>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define dist(x1,y1,x2,y2) sqrt(((x1-x2)*(x1-x2)) + ((y1-y2)*(y1-y2)))
#define gravity 9.8

// Function Declarations
void drawScene();
void set_everything();
void set_everything2();
void start();
void timer(int value);
void set();
void drawFilledSun();
void DrawCircle();
void update(int value);
void update1(int value);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void collision(int one,int two);


// Global Variables
int space_state=0;
int speed_factor=1;
float ball_radius=0.14f;
float striker_radius=0.17f;
float hole_rad=0.2f;
float box_len=6.0f;

float ball_velx = 0.025f;
float ball_vely = 0.025f;

float friction = 0.2f;
float ox1=0;
float oy1=-1.125;
float theta=0;
int factor=0;
float s__x[10]={0},s__y[10]={0};


//Point Class
class point{
	float x_cord,y_cord;
	public:
	void set_values (float,float);
	float get_x(){return x_cord;}
	float get_y(){return y_cord;}
};

void point::set_values (float x, float y) {
	x_cord = x;
	y_cord = y;
}


//Color Class
class color{
	int r,b,g;
	public:
	void set_value(int ca,int cb,int cc){
		r=ca;
		g=cb;
		b=cc;
	}
	int get_r(){ return r;}
	int get_b(){ return b;}
	int get_g(){ return g;}
};



class draw_quad{
	point p1,p2,p3,p4;
	color c ;
	public:
	void draw(point a1,point b1, point c1,point d1 ,color co,int flag) {
		p1=a1,p2=b1,p3=c1,p4=d1,c=co;


		glColor3ub(c.get_r(), c.get_g(), c.get_b());
		if(flag==0){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		glBegin(GL_QUADS);
		glVertex2f(p1.get_x(), p1.get_y());
		glVertex2f(p2.get_x(), p2.get_y());
		glVertex2f(p3.get_x(), p3.get_y());
		glVertex2f(p4.get_x(), p4.get_y());
		glEnd();


	}
};


class draw_balls{
	float rad,v_x,v_y;
	point p;
	color c;
	public:
	void set_point(point po)
	{
		p=po;
	}

	void set_velocity(float x, float y){
		v_x=x;
		v_y=y;
	}

	float get_rad(){ return rad;}
	point get_p(){ return p;}
	color get_c(){ return c;}
	float get_vx(){return v_x;}
	float get_vy(){return v_y;}

	void draw(float r,point po,color co,int flag,float v1,float y1){
		if(flag==1){
			glBegin(GL_LINE_LOOP);
		}
		else{
			glBegin(GL_TRIANGLE_FAN);
		}

		rad=r,p=po,c=co,v_x=v1,v_y=y1;
		glColor3ub(c.get_r(), c.get_g(), c.get_b());
		double twicePi = 2.0 * PI;
		float x = p.get_x(), y = p.get_y();
		glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
		glVertex2f(x, y); // center of circle
		int i;
		for (i = 0; i <= 20; i++)   {
			glVertex2f ((x + (rad * cos(i * twicePi / 20))), (y + (rad * sin(i * twicePi / 20))));
		}
		glEnd(); //END
	}
};

class draw_circle{
	float rad;
	point p;
	color c;
	public:
	void set_point(point po)
	{
		p=po;
	}

	float get_rad(){ return rad;}
	point get_p(){ return p;}
	color get_c(){ return c;}

	void draw(float r,point po,color co,int flag){
		if(flag==1){
			glBegin(GL_LINE_LOOP);
		}
		else{
			glBegin(GL_TRIANGLE_FAN);
		}

		rad=r,p=po,c=co;
		glColor3ub(c.get_r(), c.get_g(), c.get_b());
		double twicePi = 2.0 * PI;
		float x = p.get_x(), y = p.get_y();
		glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
		glVertex2f(x, y); // center of circle
		int i;
		for (i = 0; i <= 20; i++)   {
			glVertex2f ((x + (rad * cos(i * twicePi / 20))), (y + (rad * sin(i * twicePi / 20))));
		}
		glEnd(); //END
	}
};

class draw_lines{
	point p1,p2;
	color c;
	public:
	point get_p1(){ return p1;}
	point get_p2(){ return p2;}

	void draw(point a,point b,color co){
		p1=a,p2=b,c=co;
		glColor3ub(c.get_r(), c.get_g(), c.get_b());
		// glLineWidth(2.5);
		glBegin(GL_LINES);
		glVertex2f(p1.get_x(), p1.get_y());
		glVertex2f(p2.get_x(), p2.get_y());
		glEnd();
	}
};


point p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p[10];
draw_lines angle;
//p5.set_values(0,-2.125);
draw_quad b1,b2,b3,b4,box,s_box,ss_box,speed1,speed2;
draw_circle c1,c2,c3,c4,in_c1,in_c2,in_c3,in_c4,centre_circle;
color black,brown,brown2,grey,white,red,angle_color,yello,striker_color;
float striker_x,striker_y;
draw_balls queen,bl1,bl2,bl3,bl4,w1,w2,w3,w4;
draw_balls b[10],striker;
//float dist(point p1,point p2);


int main(int argc, char **argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// p5.set_values(0,-2.125);
	set();
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w ;
	int windowHeight = h ;
	white.set_value(255, 255, 255);
	grey.set_value(71, 67, 62);
	black.set_value(0, 0, 0);
	p[0].set_values(0, 0);
	p[1].set_values(0, 0.4);
	p[2].set_values(0, -0.4);
	p[3].set_values(0.4,0);
	p[4].set_values(-0.4,0);

	p[5].set_values(0.3, 0.3);
	p[6].set_values(-0.3, 0.3);
	p[7].set_values(-0.3, -0.3);
	p[8].set_values(0.3, -0.3);
	srand ( time(NULL) );
	int v1=rand() %100;
	//printf("v1=%d\n",v1);
	v1=v1%2;
	//printf("v1=%d\n",v1);
	if (v1==0){
		striker_color=white;
	}
	else{
		striker_color=black;
	}

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	timer(0);
	initRendering();
	start();
	// Register callbacks

	return 0;
}



void start(){
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	// glutTimerFunc(10, update, 0);
	//   glutTimerFunc(1000,timer,0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
}

void set(){
	yello.set_value(232, 193, 37);
	angle_color=black;
	red.set_value(242, 10, 48);

	brown.set_value(173, 110, 26);
	brown2.set_value(242, 235, 225);
	//striker coord
	p[9].set_values(0,-2.125);
	//speed1 cord
	p6.set_values(4, -2);
	p7.set_values(4.31, -2);
	p8.set_values(4.3, -1.6);
	p9.set_values(4, -1.6);
	//speed2 cord
	p10.set_values(4.3, 2);
	p11.set_values(4, 2);
	// angle line
	p12.set_values(0, -2.125);
	p13.set_values(0, -1.125);

	p14.set_values(0, 0);
	p15.set_values(0, 1);
	//queen

	s__x[9] =ball_velx;
	s__y[9] =ball_vely;
	theta=0;
	speed_factor=1;
	//for()
	int i;
	for(i=0;i<9;i++){
		s__x[i]=0;
		s__y[i]=0;
		b[i].set_velocity(s__x[i], s__y[i]);
		// b[i].set_velocity(, <#float y#>)
	}
	// s__x[i]=b[i].get_p();

	b[0]=queen,b[1]=bl1,b[2]=bl2,b[3]=bl3,b[4]=bl4,b[5]=w1,b[6]=w2,b[7]=bl3,b[8]=w3,b[9]=w4,b[10]=striker;

}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	point p1,p2,p3,p4;

	glTranslatef(0.0f, 0.0f, -8.0f);
	//  glColor3f(1.0f, 0.0f, 0.0f);

	p1.set_values(- box_len/2 , -box_len/2);
	p2.set_values( box_len/2 , -box_len/2);
	p3.set_values( box_len/2 , box_len/2);
	p4.set_values(- box_len/2 , box_len/2);
	box.draw(p1,p2,p3,p4,brown2,1);

	p1.set_values(- (box_len/2 - 0.75) , -(box_len/2 - 0.75));
	p2.set_values( box_len/2 - 0.75 , -(box_len/2 -0.75));
	p3.set_values( box_len/2 - 0.75 , box_len/2 - 0.75);
	p4.set_values(- (box_len/2 - 0.75) , box_len/2 - 0.75);
	s_box.draw(p1,p2,p3,p4,brown,0);

	p1.set_values(- (box_len/2 - 1) , -(box_len/2 - 1));
	p2.set_values( box_len/2 - 1 , -(box_len/2 -1));
	p3.set_values( box_len/2 - 1 , box_len/2 - 1);
	p4.set_values(- (box_len/2 - 1) , box_len/2 - 1);
	ss_box.draw(p1,p2,p3,p4,brown,0);

	p1.set_values(-3.3, -3.3);
	p2.set_values(-3, -3.3);
	p3.set_values(-3, 3.3);
	p4.set_values(-3.3, 3.3);
	b1.draw(p1, p2, p3, p4,brown,1);

	p1.set_values(-3.3, -3.3);
	p2.set_values(3.3, -3.3);
	p3.set_values(3.3, -3);
	p4.set_values(-3.3, -3);
	b2.draw(p1, p2, p3, p4,brown,1);

	p1.set_values(3.3, -3.3);
	p2.set_values(3, -3.3);
	p3.set_values(3, 3.3);
	p4.set_values(3.3, 3.3);
	b3.draw(p1, p2, p3, p4,brown,1);

	p1.set_values(3.3, 3.3);
	p2.set_values(3.3, 3);
	p3.set_values(-3.3, 3);
	p4.set_values(-3.3, 3.3);
	b4.draw(p1, p2, p3, p4,brown,1);

	p1.set_values(2.8, 2.8);
	p2.set_values(-2.8, 2.8);
	p3.set_values(-2.8, -2.8);
	p4.set_values(2.8, -2.8);

	c1.draw(hole_rad,p1,grey,0);
	c2.draw(hole_rad,p2,grey,0);
	c3.draw(hole_rad,p3,grey,0);
	c4.draw(hole_rad,p4,grey,0);

	p1.set_values(2.125, 2.125);
	p2.set_values(-2.125, 2.125);
	p3.set_values(-2.125, -2.125);
	p4.set_values(2.125, -2.125);

	float rad=0.125;
	rad=2*rad*rad;
	rad=sqrt(rad);

	in_c1.draw(rad,p1,red,0);
	in_c2.draw(rad,p2,red,0);
	in_c3.draw(rad,p3,red,0);
	in_c4.draw(rad,p4,red,0);


	p1.set_values(0, 0);
	centre_circle.draw(0.5,p1,black,1);

	draw_lines l1,l2,l3;
	p2.set_values(0, 0.5);
	l1.draw(p1, p2, black);

	p2.set_values(0, -0.5);
	l2.draw(p1,p2,black);

	p2.set_values(-0.5,0);
	l3.draw(p1, p2, black);
	glTranslatef(0.0f, 0.0f, 0.0f);
	angle.draw(p12, p13, angle_color);

	striker.draw(striker_radius,p[9],striker_color,0,s__x[9],s__y[9]);
	queen.draw(ball_radius,p[0],red,0,s__x[0],s__y[0]);

	bl1.draw(ball_radius, p[1], black, 0,s__x[1],s__y[1]);
	bl2.draw(ball_radius, p[2], black, 0, s__x[2],s__y[2]);
	bl3.draw(ball_radius, p[3], black, 0, s__x[3],s__y[3]);
	bl4.draw(ball_radius, p[4], black, 0, s__x[4],s__y[4]);

	w1.draw(ball_radius, p[5], white, 0, s__x[5],s__y[5]);
	w2.draw(ball_radius, p[6], white, 0, s__x[6],s__y[6]);
	w3.draw(ball_radius, p[7], white, 0, s__x[7],s__y[7]);
	w4.draw(ball_radius, p[8], white, 0, s__x[8],s__y[8]);
	b[0]=queen,b[1]=bl1,b[2]=bl2,b[3]=bl3,b[4]=bl4,b[5]=w1,b[6]=w2,b[7]=w3,b[8]=w4,b[9]=striker;

	speed1.draw(p6, p7, p8, p9, brown, 1);
	speed2.draw(p9, p8, p10, p11, brown, 0);



	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
int times=30;
//GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
void timer(int value){
	if(times>0)
		times--;
	if(times==0){
		exit(0);
	}
	   printf("time_left=%d\n",times);
	// glRasterPos2f (4.0 , 2.0);

	//glutBitmapCharacter(font_style1, 30);

	glutTimerFunc(1000, timer, 0);
}

void update(int value) {

	glutTimerFunc(1000, update, 0);
}

void update1(int value) {
	if(space_state==1){
		int iter1,iter2;
		float vx, vy;
		for(iter1=0;iter1<10;iter1++){
			float x,y;
			x=b[iter1].get_p().get_x();
			y=b[iter1].get_p().get_y();
			if ((x<-2.6 && y>2.6) || (x<-2.6 && y<-2.6) || (x>2.6 && y<-2.6)|| (x>2.6 && y>2.6)) {
				if(b[iter1].get_c().get_r() == striker.get_c().get_r() && b[iter1].get_c().get_b()== striker.get_c().get_b()&& b[iter1].get_c().get_g() == striker.get_c().get_g())
					times +=10;
				else
					times -=5;
				b[iter1].set_velocity(0, 0);
				point p1;
				p1.set_values(0, -4);
				b[iter1].set_point(p1);
				s__x[iter1]=0;
				s__y[iter1]=0;
				queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
			}
		}
		for( iter1=0 ;iter1<10;iter1++){
			if (b[iter1].get_p().get_x() + b[iter1].get_rad() >= box_len/2 || b[iter1].get_p().get_x() - b[iter1].get_rad() <= -box_len/2 ) {
				vx=b[iter1].get_vx();
				vy=b[iter1].get_vy();
				vx *=-1;
				s__x[iter1] *=-1;

				b[iter1].set_velocity(vx, vy);
				queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
			}

			if (b[iter1].get_p().get_y() + b[iter1].get_rad() >= box_len/2 || b[iter1].get_p().get_y() - b[iter1].get_rad() <= -box_len/2 ) {
				vx=b[iter1].get_vx();
				vy=b[iter1].get_vy();
				vy *=-1;
				s__y[iter1] *=-1;
				b[iter1].set_velocity(vx, vy);
				queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
			}
		}

		if(p12.get_x() == p13.get_x()){
			// striker.set_velocity(<#float x#>, <#float y#>)
			//printf("equal");
			s__x[9]=0;
			s__y[9]=b[9].get_vy();
			b[9].set_velocity(s__x[9], s__y[9]);
			striker=b[9];
		}


		for(iter1=0;iter1<10;iter1++){
			//   s__x[iter1]=0;
			float x,y;
			x=b[iter1].get_p().get_x();
			y=b[iter1].get_p().get_y();
			//         printf("y= %f vely=%f, vely=%f\n",y,b[iter1].get_vy(),s__y[iter1]);
			// y +=ball_vely;
			y+=b[iter1].get_vy();
			x+=b[iter1].get_vx();
			//  printf("y=%f\n",y);
			p[iter1].set_values(x, y);

			b[iter1].set_point(p[iter1]);
			queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
			//    b[0]=queen,b[1]=bl1,b[2]=bl2,b[3]=bl3,b[4]=bl4,b[5]=w1,b[6]=w2,b[7]=w3,b[8]=w4,b[9]=striker;


			if(s__y[iter1]<0.001 && s__y[iter1]> -0.001)
			{
				s__y[iter1]=0;
				//     p5.set_values(x, s__y[9]);
			}

			if(s__x[iter1]<0.001 && s__x[iter1]> -0.001)
			{
				s__x[iter1]=0;
				//     p5.set_values(x, s__y[9]);
			}
			if( s__y[iter1] > 0.0)
				s__y[iter1]=s__y[iter1] - (0.1*10*0.001);
			else if (s__y[iter1]<0.0)
				s__y[iter1]=s__y[iter1]+ (0.1*10*0.001);
			else
				s__y[iter1]=0.0;

			if( s__x[iter1] > 0.0)
				s__x[iter1]=s__x[iter1] - (0.1*10*0.001);
			else if (s__x[iter1]<0.0)
				s__x[iter1]=s__x[iter1]+ (0.1*10*0.001);
			else
				s__x[iter1]=0.0;

			//p5.set_values(x, s__y[9]);
			b[iter1].set_velocity(s__x[iter1], s__y[iter1]);
		}
		queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
		//   b[0]=queen,b[1]=bl1,b[2]=bl2,b[3]=bl3,b[4]=bl4,b[5]=w1,b[6]=w2,b[7]=w3,b[8]=w4,b[9]=striker;
		int flag=0;
		for(iter2=0;iter2<10;iter2++){
			// printf("x=%f y=%f\n",s__x[iter2],s__y[iter2]);
			if(s__x[iter2]!=0 || s__y[iter2]!=0){
				flag=1;
				break;
			}
		}
		//   printf("flag=%d\n",flag);
		if(flag==0){
			space_state=0;
			set_everything2();   //    set_everything();
		}

		//  int iter1,iter2,flag=0;
		flag=0;
		iter1=0;
		for(iter1=0;iter1<9;iter1++)
		{
			for(iter2=iter1+1;iter2<=9;iter2++)
			{
				float xa= dist(b[iter1].get_p().get_x(), b[iter1].get_p().get_y(), b[iter2].get_p().get_x(), b[iter2].get_p().get_y());

				float ya = b[iter1].get_rad() + b[iter2].get_rad();
				//   if(iter1==2 && iter2==9)

				if(xa<=ya){

					collision(iter1,iter2);

				}
			}
		}

		//    printf("%f\n",ball_vely);

		glutTimerFunc(5, update1, 0);
	}
}



void collision(int iter1,int iter2){
	float vx1,vx2,vy1,vy2;
	vx1=b[iter1].get_vx();
	vy1=b[iter1].get_vy();
	vx2=b[iter2].get_vx();
	vy2=b[iter2].get_vy();
	//   printf("iter1=%d iter2=%d\n",iter1,iter2);
	//   printf("vx1=%f vy1=%f vx2=%f vy2=%f\n",vx1,vy1,vx2,vy2);
	float fv1,fv2,fy1,fy2;
	int m=1,m9=2;
	if(iter1 ==9 || iter2 ==9){
		if(iter1==9){
			fy1=(vy1*(m9-m) + (2* m *vy2))/(m+m9);
			fy2=((vy2)*(m-m9) + 2*m9*vy1)/(m+m9);

			fv1=(vx1*(m9-m) + (2* m *vx2))/(m+m9);
			fv2=((vx2)*(m-m9) + 2*m9*vx1)/(m+m9);
		}
		else if(iter2==9){
			fv2=vx1;
			//  fy2=vy2/-3;
			fv1=vx2;
			fy1=(vy1*(m-m9) + (2* m9 *vy2))/(m+m9);
			fy2=((vy2)*(m9-m) + 2*m*vy1)/(m+m9);

			fv1=(vx1*(m-m9) + (2* m9 *vx2))/(m+m9);
			fv2=((vx2)*(m9-m) + 2*m*vx1)/(m+m9);
		}
		//  fv1=vx2,fy1=vy2,fv2=vx1,fy2=vy1;
	}
	else{
		//same mass velocity exchanged
		fv1=vx2,fy1=vy2,fv2=vx1,fy2=vy1;
	}
	//  printf("fv1=%f fy1=%f fv2=%f fy2=%f\n",fv1,fy1,fv2,fy2);
	s__x[iter1]=fv1;
	s__y[iter1]=fy1;
	s__x[iter2]=fv2;
	s__y[iter2]=fy2;
	b[iter1].set_velocity(fv1, fy1);
	b[iter2].set_velocity(fv2, fy2);
	queen=b[0], bl1=b[1], bl2=b[2], bl3=b[3], bl4=b[4], w1=b[5],w2=b[6], w3=b[7], w4=b[8],striker=b[9];
	return;

}


// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
}




// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void set_everything(){
	angle_color=brown2;
	angle.draw(p12, p13, angle_color);
	// update1(0);
	space_state=1;
	update1(0);
	// return;
}

void set_everything2(){
	angle_color=black;
	angle.draw(p12, p13, angle_color);
	p[9].set_values(0,-2.125);
	striker.set_point(p[9]);
	theta=0;
	speed_factor=1;
	b[9]=striker;
	factor=0;
	set();

	return;
	// update1(factor);
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}

	if(key == ' '){
		set_everything();

	}
	if(key== 'd')
	{
		if (theta < 60){
			theta +=10;
			// printf("theta=%f\n",theta);

			float x2=p12.get_x();
			float y2=p12.get_y();

			float x3,y3,vx,vy;
			x3=x2+(1*sin(theta*PI/180));
			y3=y2+(1*cos(theta*PI/180));
			vx=b[9].get_vx();
			vy=b[9].get_vy();
			vx=ball_velx* speed_factor*sin(theta*PI/180);
			vy=ball_vely* speed_factor*cos(theta*PI/180);
			b[9].set_velocity(vx, vy);
			s__x[9]=vx;
			s__y[9]=vy;
			striker=b[9];
			// printf("%f %f\n",vx,vy);
			p13.set_values(x3, y3);
		}
	}
	if(key== 'a')
	{
		if (theta  > -60){
			theta -=10;
			//  printf("theta=%f\n",theta);

			float x2=p12.get_x();
			float y2=p12.get_y();
			float x3,y3,vx,vy;

			x3=x2+(1*sin(theta*PI/180));
			y3=y2+(1*cos(theta*PI/180));
			vx=b[9].get_vx();
			vy=b[9].get_vy();
			vx=ball_velx* speed_factor*sin(theta*PI/180);
			vy=ball_vely* speed_factor*cos(theta*PI/180);
			b[9].set_velocity(vx, vy);
			s__x[9]=vx;
			s__y[9]=vy;
			striker=b[9];

			//   printf("%f %f\n",vx,vy);
			p13.set_values(x3, y3);
		}
	}
}

void handleKeypress2(int key, int x, int y) {



	if (key == GLUT_KEY_LEFT){
		float x1=p12.get_x();
		float y1=p12.get_y();

		float x2=p13.get_x();
		float y2=p13.get_y();

		striker_x=p[9].get_x();
		striker_y=p[9].get_y();
		//  printf("striker_x=%f striker_y=%f\n",striker_x,striker_y);
		if(striker_x > -2.1){
			x1 -=0.1;
			x2 -=0.1;
			striker_x -=0.10;
		}
		p12.set_values(x1, y1);
		p13.set_values(x2, y2);
		p[9].set_values(striker_x, striker_y);
		striker.set_point(p[9]);
		b[9]=striker;

	}

	if (key == GLUT_KEY_RIGHT){
		float x1=p12.get_x();
		float y1=p12.get_y();

		float x2=p13.get_x();
		float y2=p13.get_y();
		striker_x=p[9].get_x();
		striker_y=p[9].get_y();
		//  printf("striker_x=%f striker_y=%f\n",striker_x,striker_y);
		if(striker_x < 2.1){
			x1 +=0.1;
			x2 +=0.1;
			striker_x +=0.10;
		}
		p12.set_values(x1, y1);
		p13.set_values(x2, y2);
		p[9].set_values(striker_x, striker_y);
		striker.set_point(p[9]);
		b[9]=striker;
	}

	if (key == GLUT_KEY_UP){
		float x1=p8.get_x();
		float y1=p8.get_y();
		float x2=p9.get_x();
		float y2=p9.get_y();
		if(y1 <1.9 || y2<1.9){
			y1 +=0.4;
			y2 +=0.4;
			speed_factor +=1;
			float x,y;
			//    printf("velx=%f vely%f\n",striker.get_vx(),striker.get_vy());
			x=striker.get_vx();
			y=striker.get_vy();
			s__x[9] = ball_velx *speed_factor  *sin(theta*PI/180);;
			s__y[9] = ball_vely* speed_factor *cos(theta*PI/180);;
			//    vx=ball_velx* speed_factor*sin(theta*PI/180);
			//   vy=ball_vely* speed_factor*cos(theta*PI/180);
			x =ball_velx* speed_factor *sin(theta*PI/180);;
			y =ball_vely* speed_factor *cos(theta*PI/180);;
			striker.set_velocity(x, y);
			b[9]=striker;
		}
		p8.set_values(x1, y1);
		p9.set_values(x2, y2);
		//      printf("velx=%f vely%f\n",striker.get_vx(),striker.get_vy());

	}
	if (key == GLUT_KEY_DOWN){
		float x1=p8.get_x();
		float y1=p8.get_y();
		float x2=p9.get_x();
		float y2=p9.get_y();
		if(y1 > -1.6 || y2 > -1.6){
			y1 -=0.4;
			y2 -=0.4;
			speed_factor -=1;
			float x,y;
			// printf("velx=%f vely%f\n",striker.get_vx(),striker.get_vy());
			x=striker.get_vx();
			y=striker.get_vy();
			s__x[9] = ball_velx *speed_factor *sin(theta*PI/180);;
			s__y[9] = ball_vely* speed_factor *cos(theta*PI/180);;
			x =ball_velx* speed_factor *sin(theta*PI/180);;
			y =ball_vely* speed_factor *cos(theta*PI/180);;
			striker.set_velocity(x, y);
			b[9]=striker;
			b[9]=striker;
		}
		p8.set_values(x1, y1);
		p9.set_values(x2, y2);
		//printf("velx=%f vely%f\n",ball_velx,ball_vely);
	}

}

void handleMouseclick(int button, int state, int x, int y) {
	/*
	   if (state == GLUT_DOWN)
	   {
	   if (button == GLUT_LEFT_BUTTON)
	   theta += 15;
	   else if (button == GLUT_RIGHT_BUTTON)
	   theta -= 15;
	   }
	 */



}



