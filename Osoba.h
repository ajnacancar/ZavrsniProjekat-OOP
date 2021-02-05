#pragma once

#include <string>
#include <iostream>

class Osoba
{
	private:
		std::string ime, prezime;
	public:
		
		Osoba();

		void setIme();
		void setPrezime();


		std::string getIme();
		std::string getPrezime();


		~Osoba();
};

