# 📘 **PROGRAM MANAJEMEN DATA RUMAH (CSV DATA MANAGER)**

👤 **Dibuat oleh:**
**Nama:** Marcellus Geraldio Florenta  
**NIM:** 2702262816  

🏷️ **Deskripsi Singkat:**
Program ini dirancang untuk membantu pengguna mengelola data rumah dari file CSV dengan mudah.
Melalui antarmuka berbasis teks (menu interaktif), pengguna dapat menampilkan, mencari, mengurutkan, dan mengekspor data sesuai kebutuhan.

Aplikasi ini memanfaatkan konsep **file handling**, **struktur data (struct)**, serta **algoritma sorting dan searching** dalam bahasa C.

---

⚙️ **Fitur Utama:**

1. **Menampilkan Data**

   * Menampilkan semua data atau sejumlah baris tertentu sesuai permintaan pengguna.
2. **Pencarian Data**

   * Mencari data berdasarkan kolom dan kata kunci tertentu (misal: Kota, Harga, Tipe).
3. **Pengurutan Data (Sorting)**

   * Mengurutkan data berdasarkan kolom tertentu dalam urutan **ascending** atau **descending**.
4. **Ekspor Data**

   * Menyimpan data hasil pengolahan ke dalam file `.csv` baru.
5. **Antarmuka Menu Interaktif**

   * Pengguna dapat memilih operasi secara langsung melalui menu yang mudah dipahami.

---

📂 **Struktur Data yang Digunakan:**
Setiap baris data dalam file CSV direpresentasikan dengan struktur berikut:

```
struct RowData {
    char location1[100];
    char city[100];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[100];
    char furnish[100];
};
```

---

📄 **Format File CSV yang Didukung:**
File input harus bernama `file.csv` dan dipisahkan dengan tanda titik koma (`;`).

Contoh isi file:

```
Location;City;Price;Rooms;Bathrooms;CarParks;Type;Furnish
Mont-Kiara;Kuala-Lumpur;1000000;2;2;0;Built-up;Partly
Cheras;Kuala-Lumpur;310000;3;2;0;Built-up;Partly
```

---

🖥️ **Cara Menjalankan Program:**

1. Pastikan file `file.csv` berada di direktori yang sama dengan program.
2. Kompilasi program menggunakan GCC:

   ```
   gcc main.c -o rumah
   ```
3. Jalankan program:

   ```
   ./rumah
   ```

---

📋 **Navigasi Menu Program:**

| No | Menu               | Deskripsi                                      |
| -- | ------------------ | ---------------------------------------------- |
| 1  | **Tampilkan Data** | Menampilkan isi file CSV dalam format tabel.   |
| 2  | **Cari Data**      | Mencari data berdasarkan kolom tertentu.       |
| 3  | **Urutkan Data**   | Mengurutkan data berdasarkan kolom (asc/desc). |
| 4  | **Ekspor Data**    | Menyimpan hasil ke file CSV baru.              |
| 5  | **Keluar**         | Menutup program.                               |

---

🔍 **Contoh Penggunaan:**

* **Menampilkan 5 baris pertama data:**
  Pilih menu 1 → Masukkan `5`

* **Mencari rumah di kota “Kuala-Lumpur”:**
  Pilih menu 2 → Kolom: `Kota` → Kata kunci: `Kuala-Lumpur`

* **Mengurutkan berdasarkan harga descending:**
  Pilih menu 3 → Kolom: `Harga` → Urutkan: `desc`

* **Mengekspor hasil ke file baru:**
  Pilih menu 4 → Nama file: `hasil` → Output: `hasil.csv`

---

💡 **Catatan Penting:**

* Kolom bisa ditulis dalam bahasa Indonesia atau Inggris (contoh: `Lokasi` atau `Location`).
* File CSV harus menggunakan **delimiter semicolon (;)**.
* Jika format tidak sesuai, program akan menampilkan pesan kesalahan.
* Program ini mendukung hingga **1000 baris data** secara default.

---

🧠 **Konsep Pemrograman yang Diterapkan:**

* File Handling (`fopen`, `fgets`, `fprintf`, `fclose`)
* Struct dan Array of Struct
* String Manipulation (`strtok`, `strcpy`, `strcasecmp`, `strstr`)
* Sorting menggunakan `qsort()`
* Searching berbasis substring matching
* Control flow menggunakan menu interaktif

---

🎯 **Tujuan Pembuatan Program:**
Program ini dibuat untuk memenuhi tugas praktikum mata kuliah **Algorithm and Programming**, dengan fokus pada penerapan struktur data dan pengolahan file eksternal.
