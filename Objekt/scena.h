#include "objekt.h"
class Okno;
class Scena
{
public:
	std::string ime;
	std::vector<Objekt *> tabObjektov;
	Scena(std::string _ime);
	void nastavi(Okno *oknoKaz);
	void zanka();
	Objekt *dodajObjekt(std::string imeObjekta);
	Objekt *poisciObjekt(std::string imeObjekta);
	void uniciObjekt(Objekt *kateriObjekt);
	~Scena();

private:
	Okno *okno;
};