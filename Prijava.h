#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Osoba.h"

class Prijava
{
	protected:
		Osoba osoba;

	public:

		Prijava() {};

		virtual std::string enkriptiraj(std::string lozinka) = 0;
		virtual std::string dekriptiraj(std::string lozinka) = 0;

		virtual bool login(std::string korisnicko_ime, std::string lozinka) = 0;
		virtual bool signup() = 0;

		~Prijava() {};
};

