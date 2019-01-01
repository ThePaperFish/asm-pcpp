#pragma once
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <typeinfo>

template <class T>
class f_filestreams
{
private:
	string location;
	streampos size;
	int *data;

	//web: -https://stackoverflow.com/questions/11310898/how-do-i-get-the-type-of-a-variable
	const string type = typeid(T).name();
	//web: -http://www.cplusplus.com/reference/string/string/find/
	const bool isVector = type.find("vector") == string::npos;

public:

	f_filestreams(string location)
	{
		this->location = location;
	}


	~f_filestreams() {};
	



	T read()
	{
		T temp;
		ifstream file(location, ios::in | ios::binary);

		if (file.is_open())
		{
			file >> temp;
			file.close();
		}

		return temp;
	}


	int append(T data)
	{
		ofstream file(location, ios::out | ios::app | ios::binary);

		if (file.is_open())
		{
			file << data;
			file.close();
		}
		else
		{
			return 1;
		}

		return 0;
	}


	int write(T data)
	{
		ofstream file(location,ios::out | ios::binary | ios::trunc);

		if (file.is_open())
		{
			file << data;
			file.close();
		}
		else
		{
			return 1;
		}

		return 0;
	}




	T readlist()
	{

		T temp;
		ifstream file(location);

		if (file.is_open())
		{
			// Prepare a pair of iterators to read the data from cin
			std::istream_iterator<obj_medicine> eos;
			std::istream_iterator<obj_medicine> iit(file);

			// No loop is necessary, because you can use copy()
			std::copy(iit, eos, std::back_inserter(temp));

			file.close();
		}
		
		return temp;
	}


	int appendlist(T data)
	{
		ofstream file(location, ios::out | ios::app );

		if (file.is_open())
		{
			for (int i = 0; i < data.size(); i++)
			{
				file << data[i];
				file << "\n";
			}
			file.close();
		}
		else
		{
			return 1;
		}

		return 0;
	}
	

	int writelist(T data)
	{
		ofstream file(location, ios::out | ios::trunc);

		if (file.is_open())
		{
			ostream_iterator<obj_medicine> output_iterator(file, "\n");
			copy(data.begin(), data.end(), output_iterator);
			file.close();
		}
		else
		{
			return 1;
		}

		return 0;
	}


};

