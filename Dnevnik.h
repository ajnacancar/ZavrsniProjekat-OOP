#pragma once
#include <string>

class Dnevnik
{
	private:
		static std::string trenutniDnevnik;

	public:

		Dnevnik();

		void setImetrenutnogDnevnika();
		static std::string getImeTrenutnogDnevnika();

		void napraviDnevnik();
		void izbrisiDnevnik();

		~Dnevnik();
};

