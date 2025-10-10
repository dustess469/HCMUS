#include <iostream>
#include "DiaDiem.h"

using namespace std;

DiaDiem::DiaDiem()
{
	ten = "";
	toado = "";
	mota = "";
}

DiaDiem::DiaDiem(string name, string coor, string descripe)
{
	ten = name;
	toado = coor;
	mota = descripe;
}
