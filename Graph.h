#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
using namespace std;


typedef string infoTypeInduk;
struct infoTypeAnak{
    double jarak;
    string destination;
};

typedef struct elmListInduk *adrInduk;
typedef struct elmListAnak *adrAnak;

struct elmListAnak{
    infoTypeAnak info;
    adrAnak next;
};
struct listAnak{
    adrAnak firstAnak;
};


struct elmListInduk{
    infoTypeInduk info;
    adrInduk next;
    adrAnak firstAnak;
};
struct listInduk{
    adrInduk firstInduk;
};


void addInduk(listInduk &L, infoTypeInduk dataInduk);
void addAnak(adrInduk indukNode, infoTypeAnak dataAnak, listInduk &L);
adrInduk createInduk(infoTypeInduk dataInduk);
adrAnak createAnak(infoTypeAnak dataAnak);
bool insertLastInduk(listInduk &L, infoTypeInduk dataInduk);
void insertLastAnak(adrInduk indukNode, adrAnak newAnak);
void searchAndDeleteInduk(listInduk &L, infoTypeInduk dataInduk);
void searchAndDeleteAnak(adrInduk indukNode, infoTypeAnak dataAnak);
adrInduk findInduk(listInduk L, infoTypeInduk dataInduk);
adrAnak findAnak(adrInduk indukNode, infoTypeAnak dataAnak);

void displayInduk(listInduk L);
void displayAnak(adrInduk indukNode);

double cariRuteTerpendek(listInduk L, infoTypeInduk indukAwal, infoTypeInduk indukTujuan);

void deAllocateInduk(listInduk &L);
void deAllocateAnak(adrInduk indukNode);

int derajatMasuk(listInduk L, adrInduk kota);
int derajatKeluar(listInduk L, adrInduk indukNode);
int derajat(listInduk L, adrInduk indukNode);

bool isSimpleGraph(listInduk L);




#endif // GRAPH_H_INCLUDED
