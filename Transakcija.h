#pragma once
#include "Dnevnik.h"
#include <iostream>
#include <vector>
#include "Datum.h"

enum Hitno{Ne = 0, Da};
enum VrstaTransakcije{Uplata = 0, Isplata};

class Transakcija : public Dnevnik
{
	private:
		std::string  imePrimaoca, ImeUplatioca, imeBlagajnikaTransakcije, 
			vrsta_transakcije, brRacuna, svrha, iznos;
		static int brojTransakcija;
		VrstaTransakcije transakcija;
		Hitno hitnost;
		Dnevnik dnevnik;
		Datum datum;

	public:
		Transakcija() {};

		void setImePrimaoca();
		void setImeUplatioca();
		void setImeBlagajnikaTransakcije(std::string ime);
		void setVrstaTransakcije();
		void setBrojRacuna();
		void setHitno();

		std::string getImePrimaoca();
		std::string getImeUplatioca();
		std::string getImeBlagajnikaTransakcije();
		VrstaTransakcije getVrstaTransakcije();
		std::string getBrojRacuna();
		Hitno getHitno();

		void ispisNaloga();

		void uplate_isplate_unos();

		friend std::ostream& operator<<(std::ostream& stream, Transakcija& t);
		friend std::istream& operator>>(std::istream& stream, Transakcija& t);

		~Transakcija();
};

