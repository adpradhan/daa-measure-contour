#ifndef INTERVAL_H
#define INTERVAL_H
///Interval class. 
///
///Detailed description
class Interval
{
	public:
		int bottom; //left
		int top; //right
		int ID;
	/**
	 * A brief history of JavaDoc-style (C-style) comments.
	 *
	 * This is the typical JavaDoc-style C-style comment. It starts with two
	 * asterisks.
	 *
	 * @param theory Even if there is only one possible unified theory. it is just a
	 *               set of rules and equations.
	 */
	void makeInterval(int a,int b);

	void makeInterval(int a,int b,int id);
	
	void printInterval();
	
};

#endif