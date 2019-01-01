// PCPPasm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <typeinfo>

#include "d_base.h"
#include "d_product_admin_view.h"

#include "f_filestreams.h"

#include "obj_medicine.h"

using namespace std;

//ADEU data

//Admin User
//	•	Validate Login credentials & Roles
//	•	To add a new medicine
//	•	To delete an existing medicine
//	•	To modify an existing medicine
//	•	Search for an existing medicine
//	•	List out expiry dates of the medicines based on months

//Customers
//	•	Can search for a medicine if available or not
//	•	Can able to find out the respective details related to that medicine such as company name, Date of Manufacture, Date of Expiry and Price
//	•	Display the bill based on the quantity you have entered



int main()
{

	d_base *menu = NULL;
	int option;

	menu = new d_product_admin_view();

	while (true)
	{
		menu->show();
		cin >> option;
		int result = menu->run(option);

		if (result  == 0)
		{
			system("cls");
			continue;
		}
		else if (result == -1)
		{
			system("cls");
			cout << "\nYou are proceed to exit. \n";
			break;
		}
		else
		{
			cout << "Error: Please enter a valid option.\n";
			system("cls");
			continue;
		}

	}


	//system("pause");

    return 0;
}

