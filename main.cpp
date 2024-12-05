#include "Graph.h"

int main() {
    listInduk graph;
    graph.firstInduk = nullptr;

    int pilihan, x;
    string indukNama, tujuanNama, dest;
    double jarak, ruteTerpendek;
    adrInduk indukNode, searchTemp;
    infoTypeInduk kota;





    do {
        cout << "\n===================================" << endl;
        cout << "=============== MENU ==============" << endl;
        cout << "===================================" << endl;
        cout << "1. Tambah Kota" << endl;
        cout << "2. Tambah Jalan" << endl;
        cout << "3. Cari Kota" << endl;
        cout << "4. Cari Jalan" << endl;
        cout << "5. Hapus Kota" << endl;
        cout << "6. Hapus Jalan" << endl;
        cout << "7. Tampilkan Kota dan Jalan" << endl;
        cout << "8. Cari Rute antar Kota Terpendek" << endl;
        cout << "9. Cari derajat masuk(Kota)" << endl;
        cout << "10. Cari derajat keluar(Kota)" << endl;
        cout << "11. Cari derajat(Kota)" << endl;
        cout << "12. Keluar" << endl;

        cout << "===================================" << endl;
        cout << "Pilih pilihan (1-12): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama Kota: ";
                cin >> indukNama;
                addInduk(graph, indukNama);
                break;

            case 2:
                cout << "Masukkan nama Kota untuk menambah Jalan: ";
                cin >> indukNama;
                indukNode = findInduk(graph, indukNama);
                if (indukNode == nullptr) {
                    cout << "Kota " << indukNama << " tidak ditemukan!" << endl;
                } else {
                    cout << "Masukkan tujuan (Jalan): ";
                    cin >> dest;
                    cout << "Masukkan jarak(Km): ";
                    cin >> jarak;
                    infoTypeAnak anak = {jarak, dest};
                    addAnak(indukNode, anak, graph);
                }
                break;

            case 3:
                cout << "Masukkan nama Kota yang ingin dicari: ";
                cin >> indukNama;
                indukNode = findInduk(graph, indukNama);
                if (indukNode != nullptr) {
                    cout << "Kota " << indukNama << " ditemukan!" << endl;
                } else {
                    cout << "Kota " << indukNama << " tidak ditemukan!" << endl;
                }
                break;

            case 4:
                cout << "Masukkan nama Kota untuk mencari Jalan: ";
                cin >> indukNama;
                indukNode = findInduk(graph, indukNama);
                if (indukNode == nullptr) {
                    cout << "Kota " << indukNama << " tidak ditemukan!" << endl;
                } else {
                    cout << "Masukkan tujuan (Jalan) yang ingin dicari: ";
                    cin >> dest;

                    cout << "Masukkan jarak (Jalan) yang ingin dicari: ";
                    cin >> jarak;
                    infoTypeAnak anak = {jarak, dest};
                    adrAnak anakNode = findAnak(indukNode, anak);
                    if (anakNode != nullptr) {
                        cout << "Jalan dengan tujuan " << dest << " ditemukan!" << endl;
                    } else {
                        cout << "Jalan dengan tujuan " << dest << " tidak ditemukan!" << endl;
                    }
                }
                break;

            case 5:
                cout << "Masukkan nama Kota yang ingin dihapus: ";
                cin >> indukNama;
                searchAndDeleteInduk(graph, indukNama);
                cout << "Kota " << indukNama << " dan semua rute Jalan-nya telah dihapus!" << endl;
                break;

            case 6:
                cout << "Masukkan nama Kota untuk menghapus Jalan: ";
                cin >> indukNama;
                indukNode = findInduk(graph, indukNama);
                if (indukNode == nullptr) {
                    cout << "Kota " << indukNama << " tidak ditemukan!" << endl;
                } else {
                    cout << "Masukkan tujuan (Jalan) yang ingin dihapus: ";
                    cin >> dest;
                    cout << "Masukkan jarak (Jalan) yang ingin dihapus: ";
                    cin >> jarak;
                    infoTypeAnak anak = {jarak, dest};
                    searchAndDeleteAnak(indukNode, anak);
                    cout << "Rute dengan tujuan " << dest << " dan jarak " << jarak << " telah dihapus!" << endl;
                }
                break;

            case 7:
                displayInduk(graph);
                break;

            case 8:
                cout << "Masukkan nama Induk asal: ";
                cin >> indukNama;
                cout << "Masukkan nama Induk tujuan: ";
                cin >> tujuanNama;
                ruteTerpendek = cariRuteTerpendek(graph, indukNama, tujuanNama);
                if (ruteTerpendek != -1) {
                    cout << "Rute terpendek dari " << indukNama << " ke " << tujuanNama << " adalah " << ruteTerpendek << " km." << endl;
                } else {
                    cout << "Rute tidak ditemukan." << endl;
                }
                break;

            case 9:
                cout << "Masukkan nama kota(induk) yang dicari: ";
                cin >> kota;
                searchTemp = findInduk(graph, kota);
                if (searchTemp != nullptr){
                    indukNode = createInduk(kota);
                    x = derajatMasuk(graph, indukNode);
                    cout << "Jalan yang masuk menuju kota " << kota << " adalah sejumlah: " << x << endl;
                } else {
                    cout << "Kota yang anda masukkan tidak terdaftar!\n";
                }


                break;
            case 10:
                cout << "Masukkan nama kota(induk) yang dicari: ";
                cin >> kota;
                searchTemp = findInduk(graph, kota);
                if(searchTemp != nullptr){
                    indukNode = createInduk(kota);
                    x = derajatKeluar(graph, indukNode);
                    cout << "Rute yang keluar menuju kota " << kota << " adalah sejumlah: " << x << endl;
                } else {
                    cout << "Kota yang anda masukkan tidak terdaftar!\n";
                }


                break;
            case 11:
                cout << "Masukkan nama kota(induk) yang dicari: ";
                cin >> kota;
                searchTemp = findInduk(graph, kota);
                if (searchTemp != nullptr){
                    indukNode = createInduk(kota);
                    x = derajat(graph, indukNode);
                    cout << "Rute yang keluar & masuk menuju kota " << kota << " secara total adalah sejumlah: " << x << endl;
                } else {
                    cout << "Kota yang anda masukkan tidak terdaftar!\n";
                }


                break;

            default:
                cout << "Pilihan tidak valid! Silakan pilih antara 1-12." << endl;
        }

    } while (pilihan != 12);
    deAllocateInduk(graph);
    return 0;
}
