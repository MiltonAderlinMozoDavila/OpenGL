#include<GL/glew.h>
#include<GL/glut.h>
#include<stdio.h>
#include <cmath>

void Plot(int ix, int iy)
{
	glBegin(GL_POINTS); //- -- dibuja puntos
	glVertex2i(ix, iy);
	glEnd();
}
//--	--- PUNTO MEDIO

void PtoMedio(int x0, int y0, int x1, int y1)
{
	int delta_x, delta_y;
	int dm, dm_p1, dm_p2;
	int x, y;
	delta_x = x1 - x0;
	delta_y = y1 - y0;
	dm = 2 * delta_y - delta_x;
	dm_p1 = 2 * delta_y;
	dm_p2 = 2 * delta_y - 2 * delta_x;
	y = y0;
	for (x = x0; x <= x1; x++)
	{
		Plot(x, y);
		if (dm <= 0)
			dm = dm + dm_p1;
		else
		{
			dm = dm + dm_p2;
			y = y + 1;
		}
	}
}
// --- BREENHAN
void swap(int* x, int* y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}
void Bresenham(int x0, int y0, int x1, int y1)
{
	int dy, x, y, error;
	int delta_x, delta_y;
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep == true)
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	if (y0 > y1)
		dy = -1;
	else
		dy = 1;
	delta_x = x1 - x0;
	delta_y = abs(y1 - y0);
	y = y0;
	error = 0;
	for (x = x0; x <= x1; x++)
	{
		if (steep == true)
			Plot(y, x);
		else
			Plot(x, y);
		error = error + delta_y;
		if (2 * error >= delta_x)
		{
			y = y + dy;
			error = error - delta_x;
		}
	}
}

//	---- DDA

void DDA(int x0, int y0, int x1, int y1)
{
	int m = (y1 - y0) / (x1 - x0);
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		Plot(x, floor(y));
		y = y + m;
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // --- limpiamos la memoria de gl
	//DDA(0, 300, 300, 300); // ---  se dibuja
	//Bresenham(100, 100, 450, 450); // ---  se dibuja
	PtoMedio(100, 100, 450, 450); // ---  se dibuja
	glFlush(); // fuerza que todo los puntos se pinten en pantalla
}
void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // limpia la pantalla

	glColor3f(1.0, 0.0, 0.0); // color para dibujar la linea
	glPointSize(2.0); // tamaño del punto que dibuja en la ventana
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0); // proyeccion ortografiaca en 2D --- se define el sistema de coordenadas
}
void main(int argc, char** argv)
{
	/*Inicializacion GLUT estándar*/
	glutInit(&argc, argv); // inicializa la libreria 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500); //  Crear una ventana 500x500 pixeles
	glutInitWindowPosition(500,100); // coloca la ventana de despliegue en esq. sup. izq
	glutCreateWindow("Algoritmo DDA"); // título de la ventana*/
	glutDisplayFunc(display);/*llama a la función display cuando se abre

	la ventana */
	myinit(); /* fija o establece los atributos */
	glutMainLoop(); /* entra a un ciclo de evento */
}