#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

// Variabel Global untuk menyimpan data
vector<int> dataUtama;
vector<int> dataTerurut;

// ==================== MODUL UTILITY / PEMBANTU ====================
void cetakArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

// ==================== MODUL A: INPUT DATA ====================
void inputManual() {
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        int nilai;
        cout << "Data ke-" << i + 1 << ": ";
        cin >> nilai;
        dataUtama.push_back(nilai);
    }
    cout << "=> Data berhasil disimpan secara manual.\n";
}

void generateAcak() {
    int n, minVal, maxVal;
    cout << "Masukkan jumlah data: ";
    cin >> n;
    cout << "Masukkan nilai minimal acak: ";
    cin >> minVal;
    cout << "Masukkan nilai maksimal acak: ";
    cin >> maxVal;
    
    dataUtama.clear();
    for (int i = 0; i < n; i++) {
        int acak = minVal + (rand() % (maxVal - minVal + 1));
        dataUtama.push_back(acak);
    }
    cout << "=> " << n << " data acak berhasil digenerate.\n";
}

void bacaDariFile() {
    string namaFile;
    cout << "Masukkan nama file (contoh: data.txt): ";
    cin >> namaFile;
    
    ifstream file(namaFile);
    if (!file.is_open()) {
        cout << "[Error] File tidak ditemukan! Buat file " << namaFile << " dulu di folder yang sama.\n";
        return;
    }
    
    dataUtama.clear();
    int nilai;
    while (file >> nilai) {
        dataUtama.push_back(nilai);
    }
    file.close();
    cout << "=> Berhasil membaca " << dataUtama.size() << " data dari file.\n";
}

void menuInput() {
    int pil;
    cout << "\n=== MENU 1: INPUT DATA ===\n";
    cout << "1. Input Manual\n";
    cout << "2. Generate Acak\n";
    cout << "3. Baca dari File Teks (.txt)\n";
    cout << "Pilih metode (1-3): ";
    cin >> pil;
    
    if (pil == 1) inputManual();
    else if (pil == 2) generateAcak();
    else if (pil == 3) bacaDariFile();
    else cout << "Pilihan salah!\n";
}

// ==================== MODUL B: SORTING ====================
void shellSortCore(vector<int>& arr, int& comparisons, int& swaps, bool verbose) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        if (verbose && n <= 20) cout << "\n-> Jarak (Gap) = " << gap << "\n";
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparisons++;
                if (arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    swaps++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            if (verbose && n <= 20) {
                cout << "   Kondisi array: ";
                cetakArray(arr);
            }
        }
    }
}

void bubbleSortCore(vector<int>& arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
}

void menuSorting() {
    if (dataUtama.empty()) {
        cout << "[Peringatan] Data kosong! Isi data dulu di Menu 1.\n";
        return;
    }
    dataTerurut = dataUtama;
    int comps = 0, swps = 0;
    
    cout << "\n=== MENU 2: PROSES SHELL SORT ===\n";
    cout << "Data Sebelum diurutkan:\n";
    cetakArray(dataTerurut);
    
    auto start = chrono::high_resolution_clock::now();
    shellSortCore(dataTerurut, comps, swps, true);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> elapsed = end - start;
    
    cout << "\nData Setelah diurutkan:\n";
    cetakArray(dataTerurut);
    cout << "-----------------------------------------\n";
    cout << "Waktu Eksekusi : " << elapsed.count() << " milidetik\n";
    cout << "Jumlah Operasi Perbandingan : " << comps << "\n";
    cout << "Jumlah Operasi Pertukaran (Swap) : " << swps << "\n";
}

// ==================== MODUL C: SEARCHING ====================
int jumpSearchCore(const vector<int>& arr, int target, int& steps) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    steps = 0;
    
    cout << "Langkah Lompatan (sqrt(" << n << ")) = " << step << "\n";
    
    while (arr[min(step, n) - 1] < target) {
        steps++;
        cout << "Iterasi " << steps << ": Lompat ke indeks " << min(step, n) - 1 << " (Nilai: " << arr[min(step, n) - 1] << ")\n";
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    
    cout << "Target berada di kisaran indeks " << prev << " sampai " << min(step, n) - 1 << ". Mulai pencarian linear...\n";
    while (arr[prev] < target) {
        steps++;
        prev++;
        if (prev == min(step, n)) return -1;
    }
    
    steps++;
    if (arr[prev] == target) return prev;
    
    return -1;
}

void menuSearching() {
    if (dataTerurut.empty()) {
        cout << "[Peringatan] Urutkan data dulu di Menu 2 sebelum melakukan pencarian!\n";
        return;
    }
    int target, steps = 0;
    cout << "\n=== MENU 3: PROSES JUMP SEARCH ===\n";
    cout << "Masukkan angka yang dicari: ";
    cin >> target;
    
    auto start = chrono::high_resolution_clock::now();
    int hasilIndeks = jumpSearchCore(dataTerurut, target, steps);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> elapsed = end - start;
    
    if (hasilIndeks != -1) {
        cout << "=> HASIL: Angka " << target << " DITEMUKAN pada indeks ke-" << hasilIndeks << "\n";
    } else {
        cout << "=> HASIL: Angka " << target << " TIDAK DITEMUKAN.\n";
    }
    cout << "Waktu Pencarian  : " << elapsed.count() << " milidetik\n";
    cout << "Jumlah Langkah   : " << steps << " iterasi\n";
}

// ==================== MODUL D: BENCHMARK & EKSPOR ====================
void menuBenchmark() {
    int ukuranData[] = {100, 500, 1000, 2000};
    int nUkuran = sizeof(ukuranData) / sizeof(ukuranData[0]);
    
    string csvContent = "Ukuran Data,Waktu Shell (ms),Comp Shell,Swap Shell,Waktu Bubble (ms),Comp Bubble,Swap Bubble\n";
    
    cout << "\n=== MENU 4: BENCHMARK (SHELL SORT VS BUBBLE SORT) ===\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    cout << "N\t| Shell (ms)\t| Comp Shell\t| Bubble (ms)\t| Comp Bubble\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < nUkuran; i++) {
        int n = ukuranData[i];
        
        vector<int> dataUjiShell, dataUjiBubble;
        for (int j = 0; j < n; j++) {
            int val = rand() % 10000;
            dataUjiShell.push_back(val);
            dataUjiBubble.push_back(val);
        }
        
        int compShell, swapShell, compBubble, swapBubble;
        
        auto s1 = chrono::high_resolution_clock::now();
        shellSortCore(dataUjiShell, compShell, swapShell, false);
        auto e1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tShell = e1 - s1;
        
        auto s2 = chrono::high_resolution_clock::now();
        bubbleSortCore(dataUjiBubble, compBubble, swapBubble);
        auto e2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tBubble = e2 - s2;
        
        cout << n << "\t| " << tShell.count() << "\t| " << compShell << "\t\t| " << tBubble.count() << "\t| " << compBubble << "\n";
        
        csvContent += to_string(n) + "," + to_string(tShell.count()) + "," + to_string(compShell) + "," + to_string(swapShell) + "," +
                      to_string(tBubble.count()) + "," + to_string(compBubble) + "," + to_string(swapBubble) + "\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
    
    ofstream fileKeluar("hasil_perbandingan.csv");
    fileKeluar << csvContent;
    fileKeluar.close();
    cout << "=> BERHASIL: Hasil perbandingan otomatis disimpan ke file 'hasil_perbandingan.csv'!\n";
}

// ==================== MAIN PROGRAM ====================
int main() {
    int pilihan;
    do {
        cout << "\n==================================================\n";
        cout << "      APLIKASI TUGAS PROYEK STRUKTUR DATA         \n";
        cout << "      TEKNIK: SHELL SORT & JUMP SEARCH            \n";
        cout << "==================================================\n";
        cout << "1. Input / Generate Data\n";
        cout << "2. Jalankan Shell Sort (Urutkan Data + Trace)\n";
        cout << "3. Jalankan Jump Search (Cari Angka)\n";
        cout << "4. Jalankan Analisis Perbandingan (Benchmark vs Bubble)\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "--------------------------------------------------\n";
        cout << "Pilih Menu (0-4): ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: menuInput(); break;
            case 2: menuSorting(); break;
            case 3: menuSearching(); break;
            case 4: menuBenchmark(); break;
            case 0: cout << "Keluar dari program. Terima kasih!\n"; break;
            default: cout << "Pilihan tidak ada. Coba lagi.\n";
        }
    } while (pilihan != 0);
    
    return 0;
}
