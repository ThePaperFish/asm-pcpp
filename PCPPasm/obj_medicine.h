#pragma once
#include <string>
#include <iostream>
#include <vector>

#include <iomanip> 
#include <sstream> 

using namespace std;

class obj_medicine
{
private:


	bool is_digits(const std::string &str)
	{
		return str.find_first_not_of("0123456789.") == std::string::npos;
	}

	double validate_int(string message)
	{
		string temp;
		do {
			cout << message;
			cin >> temp;

			if (temp == "cancel")
			{
				return -1;
				break;
			}
			else if (temp == "-")
			{
				return -2;
				break;
			}
			else if (!is_digits(temp))
			{
				cout << "\nError: Please enter a valid input.\n\n";
			}

		} while (!is_digits(temp));

		return roundf(stod(temp) * 20) / 20;
	}



	string validate_name(string message, vector<obj_medicine> list)
	{
		string temp;
		bool flag;

		do {
			cout << message;
			cin >> temp;

			if (temp == "cancel")
			{
				return "-1";
			}

			flag = false;
			for (int i = 0; i < list.size(); i++)
			{
				if (flag = (list[i].name == temp))
				{
					return "-2";
					break;
				}
			}

		} while (flag);

		return temp;
	}


public:
	string name;
	string description;
	int stock;
	int month, year;
	double price;

	obj_medicine()
	{
	}


	obj_medicine(string name, int stock, int month, int year, double price)
	{
		this->name = name;
		this->stock = stock;
		this->price = price;
		this->month= month;
		this->year = year;
	}


	~obj_medicine()
	{
	}






	int create(vector<obj_medicine> list)
	{
		do {
			cout << "\nPlease enter new information: ('cancel' for exit)" << endl;

			name = validate_name("\n\t Medicine Name \t:",list);
			if (name == "-1") {  return -1;}
			if (name == "-2") {  continue; }
			
			stock = validate_int("\t Medicine Stock \t:");
			if (stock == -1) { return -1;}

			price = validate_int("\t Price \t:");
			if (price == -1) { return -1; }

			month = validate_int("\t Expiry Date (month) \t:");
			if (month == -1 || month > 12) { return -1;}

			year = validate_int("\t Expiry Date (year) \t:");
			if (year == -1 ) { return -1; }


			return 0;

		} while (1 == 1);
	}



	int edit(vector<obj_medicine> list,obj_medicine original)
	{
		do {
			cout << "\nPlease enter new information: ('cancel' for exit, '-' for unchange.)" << endl;

			name = validate_name("\n\t Medicine Name: \t", list);
			if (name == "-1") { return -1;}
			if (name == "-2") {  continue;}
			if (name == "-") { name = original.name; }

			stock = validate_int("\t Medicine Stock: \t");
			if (stock == -1) { return -1; }
			if (stock == -2) { stock = original.stock; }

			price = validate_int("\t Price \t:");
			if (price == -1) { return -1; }
			if (price == -2) { price = original.price; }

			month = validate_int("\t Expiry Date (month) \t:");
			if (month == -1 || month > 12) { return -1; }
			if (month == -2) { month = original.month; }

			year = validate_int("\t Expiry Date (year) \t:");
			if (year == -1) { return -1; }
			if (year == -2) { year = original.year; }

			return 0;

		} while (1 == 1);
	}


	//web-https://stackoverflow.com/questions/2239380/what-does-the-operator-string-some-code-do
	operator string() 
	{
		double price = this->price;
		stringstream ss;
		ss << fixed << setprecision(2) << price;

		return this->name + "\t" + to_string(this->stock) + "\t" + ss.str() + "\t" + to_string(this->month) + "/" + to_string(this->stock) ;
	}



	// Insertion operator
	friend ostream& operator<<(ostream& os, const obj_medicine& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.name << '\n';
		os << s.stock << '\n';
		os << s.price << '\n';
		os << s.month << '\n';
		os << s.year;
		return os;
	}

	// Extraction operator
	friend istream& operator >> (istream& is, obj_medicine& s)
	{
		// read in individual members of s
		is >> s.name >> s.stock >> s.price >> s.month >> s.year;
		return is;
	}
};

