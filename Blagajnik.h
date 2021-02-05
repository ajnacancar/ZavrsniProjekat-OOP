#pragma once
#include "Prijava.h"
#include <fstream>
#include <string>
#include <iostream>
using std::cout;
using std::cin;

class Blagajnik : public Prijava
{
	public:

		Blagajnik();

		std::string enkriptiraj(std::string lozinka);
		std::string dekriptiraj(std::string lozinka);

		bool login(std::string korisnicko_ime, std::string lozinka);
		bool signup();
		bool Provjera_Korisnickog_Imena(std::string korisnicko_ime);
		~Blagajnik() {};
};

