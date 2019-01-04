#pragma once
#include <vector>
#include <ctime>
#include <iostream>

#include "d_base.h"
#include "obj_medicine.h"
#include "f_filestreams.h"

class d_product_admin_view : public d_base
{
private:

	bool is_digits(const std::string &str)
	{
		return str.find_first_not_of("0123456789") == std::string::npos;
	}

	string data_location = "product.txt";
	f_filestreams<vector<obj_medicine>> getlist = f_filestreams<vector<obj_medicine>>(data_location);
	vector<obj_medicine> productlist = getlist.readlist();




	inline std::tm localtime_xp(std::time_t timer)
	{
		std::tm bt{};
#if defined(__unix__)
		localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
		localtime_s(&bt, &timer);
#else
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		bt = *std::localtime(&timer);
#endif
		return bt;
	}

	// default = "YYYY-MM-DD HH:MM:SS"
	inline std::string time_stamp(const std::string& fmt = "%F %T")
	{
		auto bt = localtime_xp(std::time(0));
		char buf[64];
		return{ buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
	}



public:

	d_product_admin_view()
	{
		
	}

	string header() {
		return "================= Product Page =================\n\n";
	}

	string content() {

		string temp = "";

		time_t t = time(0);
		tm now = localtime_xp(t);

		for (int i = 0; i < productlist.size(); i++)
		{
			temp += to_string(i + 1) + ". ";

			if (productlist[i].year < (now.tm_year + 1900) || ((productlist[i].year == (now.tm_year + 1900))&&(productlist[i].month == (now.tm_mon + 1))))
			{
				temp += "-- expired --";
			}

			temp += (string) productlist[i];
			temp += "\n";
		}

		temp += "98. Search Product\n";
		temp += "99. Add Product\n";
		temp += "0. Return";
		
		return temp;
	}

	string footer()
	{
		return d_base::footer() + "\n\nPlease enter your option: ";
	}



	void refresh()
	{
		productlist = getlist.readlist();
		show();
	}


	int run(string input) {
		
		int option;

		if (!is_digits(input))
		{
			return 1;
		}
		else
		{
			option = stoi(input);
		}


		if (option == 0)
		{
			return -1;
		}
		/*
			EDIT PRODUCT
		*/
		else if (option > 0 && option <= productlist.size())
		{
			obj_medicine new_medicine;
			if (new_medicine.edit(productlist,productlist[option - 1]) == 0)
			{
				productlist[option - 1] = new_medicine;
				getlist.writelist(productlist);
				refresh();
			}
			/*
				THIS IS FOR DELETE:
				productlist.erase(productlist.begin() + (option - 1));
				getlist.writelist(productlist);
				refresh();
			*/
		}
		/*
			SEARCH PRODUCT
		*/
		else if (option == 98)
		{
			string temp;
			int tempoption;
			cout << "Please enter the name you want to search: ";
			cin >> temp;

			cout << "Here are the results: " << endl << endl;

			for (int i = 0; i < productlist.size(); i++)
			{
				if (productlist[i].name.find(temp) != string::npos)
				{
					cout << to_string(i + 1) + ". ";
					cout << (string)productlist[i];
					cout << "\n";
				}
			}

			cout << endl << "Enter option no to edit them: ";

			cin >> tempoption; 

			/*
				EDIT PRODUCT AGAIN...
			*/

			if (productlist[--tempoption].name.find(temp) != string::npos)
			{
				obj_medicine new_medicine;
				if (new_medicine.edit(productlist, productlist[tempoption]) == 0)
				{
					productlist[tempoption] = new_medicine;
					getlist.writelist(productlist);
					refresh();
				}
				else
				{
					cout << "Please enter a valid option." << endl;
					system("pause > NULL");
					refresh();
				}
			}
			else
			{
				cout << "Please enter a valid option." << endl; 
				system("pause > NULL");
				refresh();
			}

		}
		//seleceted add product
		else if (option == 99)
		{
			obj_medicine new_medicine;
			if (new_medicine.create(productlist) == 0)
			{
				productlist.push_back(new_medicine);
				getlist.writelist(productlist);
				refresh();
			}
			else
			{
				cout << "Please enter a valid option." << endl;
				system("pause > NULL");
				refresh();
			}
			
		}
		else
		{
			return 1;
		}

		return 0;
	}

};

