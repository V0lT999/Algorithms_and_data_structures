#include "pch.h"
#include <iostream>
#include <locale.h>
#include <exception>
#include "screen.h"
#include "shape.h"

// Пример добавки: дополнительный фрагмент - полуокружность
class h_circle : public rectangle, public reflectable{
	bool reflected;
public:
	h_circle(point a, point b, bool r = true): rectangle(a,b)
	{
		try {
			if (a.x > b.x || a.y > b.y) throw ExceptionShape();
			if (!on_screen(a.x, a.y) || !on_screen(b.x, b.y)) throw ExceptionPoint();
			if (!on_screen(a.x, 0) || !on_screen(b.x, 0)) throw ExceptionX();
			if (!on_screen(0, a.y) || !on_screen(0, b.y)) throw ExceptionY();
			reflected = r;
		}
		catch (ExceptionShape &buf) {
			std::cout << "h_circle: " << buf.what() << std::endl;
		}
		catch (ExceptionPoint &buf) {
			std::cout << "h_circle: " << buf.what() << std::endl;
		}
		catch (ExceptionX &buf) {
			std::cout << "h_circle: " << buf.what() << std::endl;
		}
		catch (ExceptionY &buf) {
			std::cout << "h_circle: " << buf.what() << std::endl;
		}
	}
	void draw();
	void flip_horisontally() { };	// Отразить горизонтально
	void flip_vertically() { reflected = !reflected; };	// Отразить вертикально
	void rotate_right() { }; //my
	void rotate_left() { }; //my
};

void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{
	try {
		int x0 = (sw.x + ne.x) / 2;
		int y0 = reflected ? sw.y : ne.y;
		int radius = (ne.x - sw.x) / 2;
		int x = 0;
		int y = radius;
		int delta = 2 - 2 * radius;
		int error = 0;
		while (y >= 0) {
			if (reflected) { 
				put_point(x0 + x, y0 + y * 0.7);
				put_point(x0 - x, y0 + y * 0.7); 
			}
			else{ 
				put_point(x0 + x, y0 - y * 0.7); 
				put_point(x0 - x, y0 - y * 0.7);
			}
			error = 2 * (delta + y) - 1;
			if (delta < 0 && error <= 0) { ++x; delta += 2 * x + 1; continue; }
			error = 2 * (delta - x) - 1;
			if (delta > 0 && error > 0) { --y; delta += 1 - 2 * y; continue; }
			++x; delta += 2 * (x - y);  --y;
		}
	}
	catch (char &buf) {
		std::cout << "h_circle: " << buf << std::endl;
	}
}

// Пример добавки: дополнительная функция присоединения…
void down(shape &p, const shape &q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}

void right_up(shape &p, const shape &q) //my
{
	point w = p.swest();
	point ne = q.neast();
	p.move(ne.x - w.x + 1, ne.y - w.y);
}

void left_up(shape &p, const shape &q) //my
{
	point e = p.seast();
	point nw = q.nwest();
	p.move(nw.x - e.x, nw.y - e.y);
}

void right_down(shape &p, const shape &q) //my
{
	point nw = p.nwest();
	point se = q.seast();
	p.move(se.x - nw.x + 1, se.y - nw.y);
}

void left_down(shape &p, const shape &q) //my
{
	point ne = p.neast();
	point sw = q.swest();
	p.move(sw.x - ne.x, sw.y - ne.y);
}

// Cборная фигура - физиономия
class myshape : public rectangle {
	//Моя фигура ЯВЛЯЕТСЯ прямоугольником
	int w, h;
	line l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
	line r_eye; // правый глаз
	line mouth; // рот
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(int) { }
};
myshape::myshape(point a, point b)
	: rectangle(a, b),
	w(neast().x - swest().x + 1),
	h(neast().y - swest().y + 1),
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{ }

void myshape::draw()
{
	rectangle::draw();
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b));
}
void myshape::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b);
	r_eye.move(a, b);
	mouth.move(a, b);
}
int main() //только для Visual C++ (иначе – main( )) 
{
	setlocale(LC_ALL, "Rus");
	screen_init();
	//== 1.Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 8); //17
	myshape face(point(15, 10), point(27, 18));
	h_circle beard(point(40, 10), point(50, 20));
	h_circle rog1(point(70, 10), point(80, 20)); //my
	h_circle rog2(point(50, 10), point(60, 20)); //my
	h_circle rog3(point(10, 10), point(15, 15)); //my
	h_circle rog4(point(30, 10), point(35, 15)); //my
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор
//== 2.Ориентация ==
	hat.rotate_right();
	brim.resize(2);
	face.resize(2);
	beard.flip_vertically();
	rog3.flip_vertically();//my
	rog4.flip_vertically();//my
	shape_refresh();
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть ориентацию
//== 3.Сборка изображения ==
//	face.move(0, -10); // В исходное положение
	up(brim, face);
	up(hat, brim);
	down(beard, face);
	right_up(rog1, face);
	left_up(rog2, face);
	right_down(rog3, face);
	left_down(rog4, face);
	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}

