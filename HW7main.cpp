#include <iostream>
#include "node.h"

using namespace std;

void one()
{
	// 1)
	int x;
	x = 2;
	int* p;
	p = &x;
	*p = 5;
	cout << x << endl;
}

void two()
{
	// 2)
	int x;
	x = 2;
	int y;
	y = 3;
	int* p = &x;
	int* q = &y;
	*p = *q;
	cout << x << endl;
	cout << y << endl;
}

void three()
{
	// 3)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	cout << *p << endl;
	cout << *q << endl;
}

void four()
{
	// 4)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	p = q;
	cout << *p << endl;
	cout << *q << endl;
}

void five()
{
	// 5)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	delete p;
	p = q;
	cout << *p << endl;
	cout << *q << endl;
}

void six()
{
	// 6)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	delete p;
	p = q;
	*p = 5;
	cout << *p << endl;
	cout << *q << endl;
}

void seven()
{
	// 7)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	delete p;
	p = NULL;
	// *p = 5;
	// cout << *p << endl;
	cout << *q << endl;
}

void eight()
{
	// 8)
	int *p = new int; // A
	int *q = new int; // B
	*p = 3;
	*q = 4;
	delete p;
	//p = NULL;
	// *p = 5;
	// cout << *p << endl;
	cout << *q << endl;
}

void nine()
{
	// 9)
	Node* p = new Node; // “A”
	Node* q = new Node; // “B”
	p->set_next(q);
	p->set_item(1);
	q->set_item(2);

	cout << p->get_item() << endl;
	p = p->get_next();
	cout << p->get_item() << endl;
}

void ten()
{
	// 10)
	Node* p = new Node; // “A”
	Node* q = new Node; // “B”
	p->set_next(q);
	p->set_item(1);
	q->set_item(2);
	Node* r = new Node; // “C”
	r->set_item(3);
	q->set_next(r );

	cout << p->get_item() << " " << p->get_next()->get_item() << " "
	<< p->get_next()->get_next()->get_item() << endl;
}

int main()
{
	// one();
	// two();
	// three();
	// four();
	// five();
	// six();
	seven();
	eight();
	// nine();
	// ten();
	
	return 0;
}