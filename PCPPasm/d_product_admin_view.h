#pragma once
#include <vector>

#include "d_base.h"
#include "obj_medicine.h"
#include "f_filestreams.h"

class d_product_admin_view : public d_base
{
private:

	string data_location = "product.txt";
	f_filestreams<vector<obj_medicine>> getlist = f_filestreams<vector<obj_medicine>>(data_location);
	vector<obj_medicine> productlist = getlist.readlist();







public:

	d_product_admin_view()
	{
		
	}

	string header() {
		return "================= Product Page =================\n\n";
	}

	string content() {

		string temp = "";


		for (int i = 0; i < productlist.size(); i++)
		{
			temp += to_string(i + 1) + ". ";
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



	int run(int option) {
		
		if (option == 0)
		{
			return -1;
		}
		//where range in product
		else if (option > 0 && option <= productlist.size())
		{
			obj_medicine new_medicine;
			if (new_medicine.edit(productlist,productlist[option - 1]) == 0)
			{
				productlist[option - 1] = new_medicine;
				getlist.writelist(productlist);
				refresh();
			}
			/*productlist.erase(productlist.begin() + (option - 1));
			getlist.writelist(productlist);
			refresh();*/
		}
		else if (option == 98)
		{
			productlist.

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

			}
			
		}
		else
		{
			return 1;
		}

		return 0;
	}

};

