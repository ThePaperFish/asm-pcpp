#pragma once
#include <string>
#include <iostream>

using namespace std;

class d_base
{
protected:
	string empty_string = "";

public:

	d_base()
	{
	}

	~d_base()
	{
	}

	virtual string header() {
		return "================= BASE =================\n\n";
	}

	virtual string content() {
		return "base class: nothing here.";
	}

	virtual string footer() {
		return  "\n\n========================================\n";
	}

	virtual int show() {
		cout << header() << content() << footer() ;
		return 0;
	}

	virtual int run(int option) {
		return 0;
	}

};

