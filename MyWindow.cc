#include "MyWindow.h"
#include <cmath>
#include <chrono>
#include <ctime>

MyWindow::MyWindow()
:Window(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	SDL_SetWindowTitle(_window.get(), "My OpenGL Window");
}

void MyWindow::draw_clock()
{
	for (double a = 0.0; a < 360.0; a += 360.0 / 12.0) {
				glPushMatrix();
				glRotated(a, 0.0, 0.0, 1.0);
				glTranslated(0.0, 0.9, 0.0);
				glBegin(GL_QUADS);
				glColor3d(0.3, 1.0, 1.0);
				glVertex2d(-0.05, 0.05);
				glVertex2d(0.05, 0.05);
				glVertex2d(0.05, -0.05);
				glVertex2d(-0.05, -0.05);
				glEnd();
				glPopMatrix();
			}
	for (double b = 0.0; b < 360.0; b += (360.0 / 12.0) / 5.0) {
			glPushMatrix();
			glRotated(b, 0.0, 0.0, 1.0);
			glTranslated(0.0, 0.9, 0.0);
			glBegin(GL_QUADS);
			glColor3d(0.3, 1.0, 1.0);
			glVertex2d(-0.015, 0.015);
			glVertex2d(0.015, 0.015);
			glVertex2d(0.015, -0.015);
			glVertex2d(-0.015, -0.015);
			glEnd();
			glPopMatrix();
	}

	double seconds_angles = fmod(_seconds, 60.0) / 60 * 360;
	glPushMatrix();
	glRotated(seconds_angles, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.025, 0.1);
	glVertex2d(0.0, 0.9);
	glVertex2d(0.025, 0.1);
	glEnd();
	glPopMatrix();

	double minutes_angles = fmod((_seconds / 60.0), 60) / 60 * 360.0;
	glPushMatrix();
	glRotated(minutes_angles, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 1.0, 0.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.05, 0.1);
	glVertex2d(0.0, 0.8);
	glVertex2d(0.05, 0.1);
	glEnd();
	glPopMatrix();

	double hours_angles = (_seconds / 3600.0) / 60 * 360;
	glPushMatrix();
	glRotated(hours_angles, 0.0, 0.0, -1.0);
	glBegin(GL_QUADS);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(-0.1, 0.1);
	glVertex2d(0.0, 0.8);
	glVertex2d(0.1, 0.1);
	glEnd();
	glPopMatrix();
}

void MyWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(3.0, 3.0, 2.0,
			0.0, 0.0, 0.5,
			0.0, 0.0, 1.0);

	glRotated(_step, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);

	glColor3d(0.3, 0.3, 0.3);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(-1.0, -1.0, 0.0);

	glColor3d(0.144, 0.64, 0.255);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);

	glColor3d(0.192, 0.128, 0.255);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(-1.0, 1.0, -0.1);

	glColor3d(0.192, 0.224, 0.255);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, -0.1);

	glColor3d(0.255, 0.255, 0.152);
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(-1.0, 1.0, 0.0);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);


	glColor3d(0.2, 0.2, 0.2);
	glVertex3d(-1.0, 1.0, -0.1);
	glVertex3d(1.0, 1.0, -0.1);
	glVertex3d(1.0, -1.0, -0.1);
	glVertex3d(-1.0, -1.0, -0.1);

	glEnd();

	glTranslated(0.0, 0.0, 0.05);
	draw_clock();
}

void MyWindow::setupGL()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.25f, 0.45f, 1.0f);

	double aspect_ratio = double(width()) / double(height());

	glMatrixMode(GL_PROJECTION);
//	gluOrtho2D(-aspect_ratio, aspect_ratio, -1, 1);
	gluPerspective(45.0, aspect_ratio, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::update()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto tt = std::chrono::high_resolution_clock::to_time_t(now);
	auto local_time = *localtime(&tt);
	_seconds = local_time.tm_sec +
			60*local_time.tm_min +
			3600*local_time.tm_hour;
	_step += 0.05;
}
