#pragma once
#include "Prijava.h"
#include <fstream>
#include <string>
#include <iostream>
using std::cout;
using std::cin;

class Administrator : public Prijava
{
	private:
		static int brojAdministratora;

	public:
		Administrator();

		void setBrojAdministratora();
		static int getBrojAdministratora();

		int brojAdministratore();

		std::string enkriptiraj(std::string lozinka);
		std::string dekriptiraj(std::string lozinka);

		bool login(std::string korisnicko_ime, std::string lozinka);
		bool signup();

		~Administrator();
};

