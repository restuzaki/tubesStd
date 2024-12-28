#include "Graph.h"
#include <map>

void addInduk(listInduk &L, infoTypeInduk dataInduk) {
    bool check = insertLastInduk(L, dataInduk);
    if(check) {
        cout << "Kota " << dataInduk << " sudah terdaftar!\n";
    } else {
        cout << "Kota " << dataInduk << " berhasil didaftarkan!\n";
    }
}

void addAnak(adrInduk indukNode, infoTypeAnak dataAnak, listInduk &L) {
    if (indukNode->info == dataAnak.destination) {
        cout << "Anak dengan tujuan " << dataAnak.destination << " tidak dapat memiliki kota induk yang sama sebagai tujuan!\n";
        return;
    }

    bool validDestination = false;
    adrInduk temp = L.firstInduk;
    while (temp != nullptr) {
        if (temp->info == dataAnak.destination) {
            validDestination = true;
            break;
        }
        temp = temp->next;
    }
    if (validDestination) {
        adrAnak newAnak = createAnak(dataAnak);
        insertLastAnak(indukNode, newAnak);
        cout << "Anak dengan tujuan " << dataAnak.destination << " berhasil ditambahkan!\n";
    } else {
        cout << "Kota tujuan " << dataAnak.destination << " tidak valid!\n";
    }
}


adrInduk createInduk(infoTypeInduk dataInduk) {
    adrInduk newInduk = new elmListInduk;
    newInduk->info = dataInduk;
    newInduk->next = nullptr;
    newInduk->firstAnak = nullptr;
    return newInduk;
}

adrAnak createAnak(infoTypeAnak dataAnak) {
    adrAnak newAnak = new elmListAnak;
    newAnak->info = dataAnak;
    newAnak->next = nullptr;
    return newAnak;
}

bool insertLastInduk(listInduk &L, infoTypeInduk dataInduk) {
    adrInduk newInduk = createInduk(dataInduk);
    if (L.firstInduk == nullptr) {
        L.firstInduk = newInduk;
        return false;
    } else {
        adrInduk temp = L.firstInduk;
        while (temp != nullptr) {
            if (temp->info == dataInduk) {
                return true;
            }
            temp = temp->next;
        }
        temp = L.firstInduk;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newInduk;
        return false;
    }
}

void insertLastAnak(adrInduk indukNode, adrAnak newAnak) {
    if (indukNode->firstAnak == nullptr) {
        indukNode->firstAnak = newAnak;
    } else {
        adrAnak temp = indukNode->firstAnak;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newAnak;
    }
}

void searchAndDeleteInduk(listInduk &L, infoTypeInduk dataInduk) {
    adrInduk temp = L.firstInduk, prev = nullptr;
    while (temp != nullptr && temp->info != dataInduk) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr){
        return;
    }
    if (prev == nullptr) {
        L.firstInduk = temp->next;
    } else {
        prev->next = temp->next;
    }
    deAllocateAnak(temp);
    delete temp;
}

void searchAndDeleteAnak(adrInduk indukNode, infoTypeAnak dataAnak) {
    adrAnak temp = indukNode->firstAnak, prev = nullptr;
    while (temp != nullptr && temp->info.jarak != dataAnak.jarak) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr){
        return;
    }
    if (prev == nullptr) {
        indukNode->firstAnak = temp->next;
    } else {
        prev->next = temp->next;
    }
    delete temp;
}

adrInduk findInduk(listInduk L, infoTypeInduk dataInduk) {
    adrInduk temp = L.firstInduk;
    while (temp != nullptr) {
        if (temp->info == dataInduk) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

adrAnak findAnak(adrInduk indukNode, infoTypeAnak dataAnak) {
    adrAnak temp = indukNode->firstAnak;
    while (temp != nullptr) {
        if (temp->info.jarak == dataAnak.jarak) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void displayInduk(listInduk L) {
    adrInduk temp = L.firstInduk;
    while (temp != nullptr) {
        cout << "Kota: " << temp->info << " -> ";
        displayAnak(temp);
        temp = temp->next;
    }
}

void displayAnak(adrInduk indukNode) {
    adrAnak temp = indukNode->firstAnak;
    if (temp == nullptr) {
        cout << "Tidak ada rute." << endl;
        return;
    }
    while (temp != nullptr) {
        cout << "(Tujuan: " << temp->info.destination << ", Jarak: " << temp->info.jarak << ") ";
        temp = temp->next;
    }
    cout << endl;
}



double cariRuteTerpendek(listInduk L, infoTypeInduk indukAwal, infoTypeInduk indukTujuan) {
     adrInduk start = findInduk(L, indukAwal);
    if (start == nullptr) {
        cout << "Kota asal tidak ditemukan.\n";
        return -1;
    }

    double minDistance = -1;
    string kotaTerlewati = indukAwal;

    adrAnak currentAnak = start->firstAnak;
    while (currentAnak != nullptr) {
        if (currentAnak->info.destination == indukTujuan) {

            if (minDistance == -1 || currentAnak->info.jarak < minDistance) {
                minDistance = currentAnak->info.jarak;
                kotaTerlewati = indukAwal + " -> " + indukTujuan;
            }
        } else {

            adrInduk nextInduk = findInduk(L, currentAnak->info.destination);
            if (nextInduk != nullptr) {
                adrAnak nextAnak = nextInduk->firstAnak;
                while (nextAnak != nullptr) {
                    if (nextAnak->info.destination == indukTujuan) {
                        double totalJarak = currentAnak->info.jarak + nextAnak->info.jarak;
                        if (minDistance == -1 || totalJarak < minDistance) {
                            minDistance = totalJarak;
                            kotaTerlewati = indukAwal + " -> " + currentAnak->info.destination + " -> " + indukTujuan;
                        }
                    }
                    nextAnak = nextAnak->next;
                }
            }
        }
        currentAnak = currentAnak->next;
    }

    if (minDistance != -1) {
        cout << "Kota yang dilewati: " << kotaTerlewati << endl;
    }
    return minDistance;
}



void deAllocateInduk(listInduk &L) {
    adrInduk temp = L.firstInduk;
    while (temp != nullptr) {
        adrInduk next = temp->next;
        deAllocateAnak(temp);
        delete temp;
        temp = next;
    }
    L.firstInduk = nullptr;
}

void deAllocateAnak(adrInduk indukNode) {
    adrAnak temp = indukNode->firstAnak;
    while (temp != nullptr) {
        adrAnak next = temp->next;
        delete temp;
        temp = next;
    }
    indukNode->firstAnak = nullptr;
}

int derajatKeluar(listInduk L, adrInduk indukNode) {
    int count = 0;
    infoTypeInduk infoInduk = indukNode->info;
    adrInduk tempInduk = findInduk(L, infoInduk);
    if (tempInduk != nullptr) {
        adrAnak tempAnak = tempInduk->firstAnak;
        while (tempAnak != nullptr) {
            count++;
            tempAnak = tempAnak->next;
        }
    }
    return count;
}

int derajatMasuk(listInduk L, adrInduk kota) {
    int count = 0;
    adrInduk tempInduk = L.firstInduk;
    while (tempInduk != nullptr) {
        adrAnak tempAnak = tempInduk->firstAnak;
        while (tempAnak != nullptr) {
            if (tempAnak->info.destination == kota->info) {
                count++;
            }
            tempAnak = tempAnak->next;
        }
        tempInduk = tempInduk->next;
    }
    return count;
}

int derajat(listInduk L, adrInduk indukNode) {
    return derajatMasuk(L, indukNode) + derajatKeluar(L, indukNode);
}

bool isSimpleGraph(listInduk L) {
    adrInduk induk = L.firstInduk;
    while (induk != nullptr) {
        adrAnak anak1 = induk->firstAnak;
        while (anak1 != nullptr) {
            adrAnak anak2 = anak1->next;
            while (anak2 != nullptr) {
                if (anak1->info.destination == anak2->info.destination) {
                    return false;
                }
                anak2 = anak2->next;
            }
            anak1 = anak1->next;
        }

        induk = induk->next;
    }

    return true;
}
