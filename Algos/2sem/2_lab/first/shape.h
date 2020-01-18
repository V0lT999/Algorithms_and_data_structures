#pragma once
#include <iostream>
#include "Exceptions.h"
char screen[YMAX][XMAX];
enum color { black = '*', white = '.' };
void screen_init()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto &x : screen[y])
			x = white;
}

void screen_destroy()
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto &x : screen[y])
			x = black;
}

bool on_screen(int a, int b) // �������� ��������� �� �����
{
	return 0 <= a && a < XMAX && 0 <= b && b < YMAX;
}

void put_point(int a, int b)
{
	try {
		if (!on_screen(a, b)) throw ExceptionPoint();
		if (!on_screen(a, 0)) throw ExceptionX();
		if (!on_screen(0, b)) throw ExceptionY();
		screen[b][a] = black;
	}
	catch (ExceptionX &a) {
		std::cout << a.what() << std::endl;
	}
	catch (ExceptionY &a) {
		std::cout << a.what() << std::endl;
	}
	catch (ExceptionPoint &a) {
		std::cout << a.what() << std::endl;
	}
}

void put_line(int x0, int y0, int x1, int y1)
/*
��������� ������� ������ �� (x0,y0) �� (x1,y1).
��������� ������: b(x-x0) + a(y-y0) = 0.
�������������� �������� abs(eps),
��� eps = 2*(b(x-x0)) + a(y-y0) (�������� ���������� ��� ������).
*/
{
	try{
		if (!on_screen(x0, y0) || !on_screen(x1, y1)) throw ExceptionPoint();
		if (!on_screen(x0, 0) || !on_screen(x1, 0)) throw ExceptionX();
		if (!on_screen(0, y0) || !on_screen(0, y1)) throw ExceptionY();
		int dx = 1;
		int a = x1 - x0;
		if (a < 0) dx = -1, a = -a;
		int dy = 1;
		int b = y1 - y0;
		if (b < 0) dy = -1, b = -b;
		int two_a = 2 * a;
		int two_b = 2 * b;
		int xcrit = -b + two_a;
		int eps = 0;

		for (;;) { //������������ ������ ����� �� ������
			put_point(x0, y0);
			if (x0 == x1 && y0 == y1) break;
			if (eps <= xcrit) x0 += dx, eps += two_b;
			if (eps >= a || a < b) y0 += dy, eps -= two_a;
		}
	}
	catch (ExceptionPoint &a){
		std::cout << "line: " << a.what() << std::endl;
	}
	catch (ExceptionX &a) {
		std::cout << "line: " << a.what() << std::endl;
	}
	catch (ExceptionY &a) {
		std::cout << "line: " << a.what() << std::endl;
	}
}

void screen_clear() { screen_init(); } //������� ������

void screen_refresh() // ���������� ������
{
	for (int y = YMAX - 1; 0 <= y; --y) { // � ������� ������ �� ������
		for (auto x : screen[y])    // �� ������ ������� �� �������
			std::cout << x;
		std::cout << '\n';
	}
}

//== 2. ���������� ����� ==
struct shape { // ����������� ������� ����� "������"
	static shape* list;	// ������ ������ ����� (���� �� ��� ������!)
	shape* next;
	shape() { next = list; list = this; } //������ �������������� � ������
	virtual point north() const = 0;	//����� ��� ��������
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;	//���������
	virtual void move(int, int) = 0;	//�����������
	virtual void resize(int) = 0;//��������� �������
};

shape * shape::list = nullptr;	//������������� ������ �����

class rotatable : virtual public shape { //������, ��������� � �������� 
public:
	virtual void rotate_left() = 0;	//��������� �����
	virtual void rotate_right() = 0;	//��������� ������
};
class reflectable : virtual public shape { // ������, ���������
				// � ����������� ���������
public:
	virtual void flip_horisontally() = 0;	// �������� �������������
	virtual void flip_vertically() = 0;	// �������� �����������
};
class line : public shape {
	/* ������� ������ ["w", "e" ].
	north( ) ���������� ����� "���� ������ ������� � ��� ������
	�� �����, ��� ����� ��� �������� �����", � �. �. */
protected:
	point w, e;
public:
	line(point a, point b) : w(a), e(b) { };
	line(point a, int L) : w(point(a.x + L - 1, a.y)), e(a) {  };
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point west() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point neast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point seast() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point swest() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	void move(int a, int b) { w.x += a; w.y += b; e.x += a; e.y += b; }
	void draw() { put_line(w, e); }
	void resize(int d) // ���������� � (d) ���
	{
		e.x += (e.x - w.x) * (d - 1); e.y += (e.y - w.y) * (d - 1);
	}
};
// �������������
class rectangle : public rotatable {
	/* nw ------ n ------ ne
	   |		          |
	   |		          |
	   w	     c        e
	   |		          |
	   |		          |
	   sw ------ s ------ se */
protected:
	point sw, ne;
public:
	rectangle(point a, point b) 
	{
		try {
			if (a.x > b.x || a.y > b.y) throw ExceptionShape();
			if (!on_screen(a.x, a.y) || !on_screen(b.x, b.y)) throw ExceptionPoint();
			if (!on_screen(a.x, 0) || !on_screen(b.x, 0)) throw ExceptionX();
			if (!on_screen(0, a.y) || !on_screen(0, b.y)) throw ExceptionY();
			sw = a;
			ne = b;
		}
		catch (ExceptionShape &buf) {
			std::cout << "rectangle: " << buf.what() << std::endl;
		}
		catch (ExceptionPoint &buf) {
			std::cout << "rectangle: " << buf.what() << std::endl;
		}
		catch (ExceptionX &buf) {
			std::cout << "rectangle: " << buf.what() << std::endl;
		}
		catch (ExceptionY &buf) {
			std::cout << "rectangle: " << buf.what() << std::endl;
		}
	}
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point west() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(ne.x, sw.y); }
	point nwest() const { return point(sw.x, ne.y); }
	point swest() const { return sw; }

	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
	}

	void draw();

	void rotate_right() // ������� ������ ������������ se
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		sw.x = ne.x - h * 2; ne.y = sw.y + w / 2;
	}
	void rotate_left() // ������� ����� ������������ sw
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2; ne.y = sw.y + w / 2;
	}
	void resize(int d)
	{
		ne.x += (ne.x - sw.x) * (d - 1); ne.y += (ne.y - sw.y) * (d - 1);
	}
};
void rectangle::draw()
{
	put_line(nwest(), ne);   put_line(ne, seast());
	put_line(seast(), sw);   put_line(sw, nwest());
}

void shape_refresh() // ����������� ���� �����
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) p->draw();
	screen_refresh();
}
void up(shape& p, const shape& q) // ��������� p ��� q
{	//��� ������� �������, � �� ���� ������!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}
