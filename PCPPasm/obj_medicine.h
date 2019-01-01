#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class obj_medicine
{
private:


	bool is_digits(const std::string &str)
	{
		return str.find_first_not_of("0123456789") == std::string::npos;
	}

	int validate_int(string message)
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

		return stoi(temp);
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
	int date;

	obj_medicine()
	{
	}


	obj_medicine(string name, int stock, int date)
	{
		this->name = name;
		this->stock = stock;
		this->date= date;
	}


	~obj_medicine()
	{
	}






	int create(vector<obj_medicine> list)
	{
		do {
			cout << "\nPlease enter new information: ('cancel' for exit)" << endl;

			name = validate_name("\n\t Medicine Name \t:",list);
			if (name == "-1") { cout << "GG1"; return -1;}
			if (name == "-2") { cout << "GG2"; continue; }
			
			stock = validate_int("\t Medicine Stock \t:");
			if (stock == -1) { cout << "GG3"; return -1;}
			
			date = validate_int("\t Expiry Date \t:");
			if (date == -1) { cout << "GG4"; return -1;}

			return 0;

		} while (1 == 1);
	}

	int edit(vector<obj_medicine> list,obj_medicine original)
	{
		do {
			cout << "\nPlease enter new information: ('cancel' for exit, '-' for unchange.)" << endl;

			name = validate_name("\n\t Medicine Name: \t", list);
			if (name == "-1") { cout << "GG1"; return -1;}
			if (name == "-2") { cout << "GG2";  continue;}
			if (name == "-") { name = original.name; }

			stock = validate_int("\t Medicine Stock: \t");
			if (stock == -1) { cout << "GG3"; return -1;}
			if (stock == -2) { stock=  original.stock; }

			date = validate_int("\t Expiry Date: \t");
			if (date == -1) { cout << "GG4"; return -1; }
			if (date == -2) { date =  original.date; }

			return 0;

		} while (1 == 1);
	}


	//web-https://stackoverflow.com/questions/2239380/what-does-the-operator-string-some-code-do
	operator string() 
	{
		return this->name + "\t" + to_string(this->stock) + "\t" + to_string(this->date);
	}



	// Insertion operator
	friend ostream& operator<<(ostream& os, const obj_medicine& s)
	{
		// write out individual members of s with an end of line between each one
		os << s.name << '\n';
		os << s.stock << '\n';
		os << s.date ;
		return os;
	}



	// Extraction operator
	friend istream& operator >> (istream& is, obj_medicine& s)
	{
		// read in individual members of s
		is >> s.name >> s.stock >> s.date;
		return is;
	}
};

