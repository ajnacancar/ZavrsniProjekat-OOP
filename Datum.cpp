#include "Datum.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Datum::Datum()
{
	this->dan = 1;
	this->mjesec = 1;
	this->godina = 1900;
}

void Datum::setDan()
{
	switch (this->mjesec)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		do
		{
			std::cout << "\nUnesite dan: ";
			std::cin >> this->dan;
			if (this->dan>31)
			{
				std::cout << "[GRESKA]" << this->mjesec << ". mjesec ima samo 31 dan!\n";
			}
			else if (this->dan < 1)
			{
				std::cout << "[GRESKA] Dan u datumu ne moze biti manji od 1!\n";
			}
		} while (this->dan < 1 || this->dan>31);
		break;

		case 4: case 6: case 9: case 11:
		do
		{
			std::cout << "\nUnesite dan: ";
			std::cin >> this->dan;
			if (this->dan > 30)
			{
				std::cout << "[GRESKA]" << this->mjesec << ".mjesec ima samo 30 dan!\n";
			}
			else if (this->dan < 1)
			{
				std::cout << "[GRESKA] Dan u datumu ne moze biti manji od 1!\n";
			}
		} while (this->dan < 1 || this->dan > 30);
		break;

		case 2:
		if (this->godina % 4 == 0)
		{
			do
			{
				std::cout << "\nUnesite dan: ";
				std::cin >> this->dan;
				if (this->dan > 29)
				{
					std::cout << "[GRESKA] Prestupna godina 2. mjesec ima samo 29 dana!\n";
				}
				else if (this->dan < 1)
				{
					std::cout << "[GRESKA] Dan u datumu ne moze biti manji od 1!\n";
				}
			} while (this->dan < 1 || this->dan>29);
		}
		else
		{
			do
			{
				std::cout << "\nUnesite dan: ";
				std::cin >> this->dan;
				if (this->dan > 28)
				{
					std::cout << "[GRESKA] Nije prestupna godina 2. mjesec ima samo 28 dana!\n";
				}
				else if (this->dan < 1)
				{
					std::cout << "[GRESKA] Dan u datumu ne moze biti manji od 1!\n";
				}
			} while (this->dan < 1 || this->dan > 28);

		}
		break;

		default:
			std::cout << "Pogresan mjesec!\n";
	}
}

void Datum::setMjesec()
{
	do
	{
		std::cout << "Unesite mjesec: ";
		std::cin >> this->mjesec;
		if (this->mjesec < 1 || this->mjesec > 12)
		{
			std::cout << "[GRESKA] Pogresno unesen mjesec!\n";
		}
	} while (this->mjesec < 1 || this->mjesec > 12);
}

void Datum::setGodina()
{
	do
	{
		std::cout << "Unesite godinu: ";
		std::cin >> this->godina;
		if (this->godina < 1900)
		{
			std::cout << "[GRESKA] Pogresno unesena godina!\n";
		}
	} while (this->godina < 1900);
}

int Datum::getDan()
{
	return this->dan;
}

int Datum::getMjesec()
{
	return this->mjesec;
}

int Datum::getGodina()
{
	return this->godina;
}

void Datum::postaviDatum()
{
	this->setDan();
	this->setMjesec();
	this->setGodina();
}

void Datum::ispisiDatum()
{
	std::cout << std::setw(2) << std::setfill('0') << this->getDan() << "." << std::setw(2) << std::setfill('0') << this->getMjesec() << "." << this->getGodina() << "."  << std::endl;
}


