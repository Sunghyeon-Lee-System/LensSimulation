#include <stdio.h>
#include <math.h>

#define REFRA 1.5

struct line
{
	double a;
	double b;
};

struct circle
{
	double x;
	double y;
	double r;
};

struct point
{
	double x;
	double y;
};

struct point getMeetLine(struct line* fo1, struct line* fo2);
struct point getMeetCircle(struct circle* cir, struct line* fo, int dir);
double getAngle(struct line* fo1, struct line* fo2);
struct line getAngleLine(struct point* p, struct line* fo, double angle);
struct line getRefraLine(struct circle* cir, struct line* fo, int dir);

int main(void)
{
	struct circle cir1;
	cir1.x = 0;
	cir1.y = 0;
	cir1.r = 10;


	struct circle cir2;
	cir2.x = sqrt(200-200*cos(0.175));
	cir2.y = 0;
	cir2.r = 10;

	struct circle cir3;
	cir3.x = 0;
	cir3.y = 0;
	cir3.r = 14;

	struct circle cir4;
	cir4.x = 7.4;
	cir4.y = 0;
	cir4.r = 8;

	for (double i = 0.01; i <= 0.3; i += 0.001)
	{
		struct line l1;
		l1.a = 0;
		l1.b = i;

		struct line l2 = getRefraLine(&cir1, &l1, 0);
	    struct line l3 = getRefraLine(&cir2, &l2, 1);

		struct line l4 = getRefraLine(&cir3, &l1, 1);
		struct line l5 = getRefraLine(&cir4, &l4, 1);

		struct line xAxis;
		xAxis.a = 0;
		xAxis.b = 0;

		struct point fsdaa = getMeetLine(&l2, &xAxis);


		struct point p = getMeetLine(&l3, &xAxis);
		struct point p2 = getMeetLine(&l5, &xAxis);
		printf("%f %f\t", i, p.x);
		printf("%f %f\n", i, p2.x);
	}
}

struct point getMeetLine(struct line* fo1, struct line* fo2)
{
	struct point p;

	double a = fo1->a;
	double b = fo1->b;
	double c = fo2->a;
	double d = fo2->b;

	double x = (d - b) / (a - c);
	double y = (d * a - b * c) / (a - c);

	p.x = x;
	p.y = y;

	return p;
}

struct point getMeetCircle(struct circle* cir, struct line* fo, int dir)
{
	struct point p;

	double x = cir->x;
	double y = cir->y;
	double r = cir->r;
	double a = fo->a;
	double b = fo->b;

	double d = fabs(a * x - y + b) / sqrt(a * a + 1);

	if (a == 0)
	{
		if (dir)
		{
			p.x = x + sqrt(r * r - (b - y) * (b - y));
			p.y = b - y;
		}
		else
		{
			p.x = x - sqrt(r * r - (b - y) * (b - y));
			p.y = b - y;
		}
	}
	else
	{
		struct line suzicline;
		suzicline.a = -(1.0 / a);
		suzicline.b = y - (1.0 / a) * x;

		struct point h;
		h = getMeetLine(fo, &suzicline);

		if (r > d)
		{
			
		}
		double angle = atan(a);
		double l = sqrt(r * r - d * d);

		if (dir)
		{
			p.x = h.x + l * cos(angle);
			p.y = h.y + l * sin(angle);
		}
		else
		{
			p.x = h.x - l * cos(angle);
			p.y = h.y - l * sin(angle);
		}
	}

	return p;
}

double getAngle(struct line* fo1, struct line* fo2)
{
	double a1 = fo1->a;
	double a2 = fo2->a;

	if (a1 >= 0 || a2 >= 0)
	{
		return fabs(atan(a1) - atan(a2));
	}
	else
	{
		return fabs(atan(a1)) + fabs(atan(a2));
	}
}

struct line getAngleLine(struct point* p, struct line* fo, double angle)
{
	struct line l;

	double a = fo->a;
	double b = fo->b;
	double x = p->x;
	double y = p->y;

	double xangle = atan(a);

	if (xangle >= 0)
	{
		l.a = tan(xangle - angle);
		l.b = y - (l.a) * x;
	}
	else
	{
		l.a = tan(xangle + angle);
		l.b = y - (l.a) * x;
	}

	return l;
}

struct line getRefraLine(struct circle* cir, struct line* fo, int dir)
{
	double x = cir->x;
	double y = cir->y;
	double r = cir->r;

	struct point p1 = getMeetCircle(cir, fo, dir);

	struct line l;
	l.a = (p1.y - y) / (p1.x - x);
	l.b = (p1.x * y - p1.y * x) / (p1.x - x);

	double angle = getAngle(fo, &l);
	if (dir)
	{
		return getAngleLine(&p1, &l, angle * REFRA*(-1));
	}
	else
	{
		return getAngleLine(&p1, &l, angle * (-1.0/REFRA));
	}
}