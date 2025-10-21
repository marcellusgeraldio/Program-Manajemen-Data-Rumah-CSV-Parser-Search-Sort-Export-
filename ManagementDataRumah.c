#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_ROWS 1000
#define FIELD_SIZE 100

// Struktur data rumah
struct RowData {
    char location1[FIELD_SIZE];
    char city[FIELD_SIZE];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[FIELD_SIZE];
    char furnish[FIELD_SIZE];
};

// Deklarasi fungsi
int loadData(FILE *fptr, struct RowData data[]);
void displayData(struct RowData data[], int numRows, int limit);
void searchData(struct RowData data[], int numRows, const char *columnName, const char *searchTerm);
void sortData(struct RowData data[], int numRows, const char *columnName, const char *sortOrder);
void exportData(struct RowData data[], int numRows, const char *filename);
int compare(const void *a, const void *b);
int columnToIndex(const char *columnName);
void trim_newline(char *s);
void read_input(char *buf, int size);

// Variabel global untuk qsort
int sortColumn = 0;

// ====================== MAIN PROGRAM ======================
int main() {
    FILE *fptr = fopen("file.csv", "r");
    if (fptr == NULL) {
        printf("File tidak ditemukan (pastikan file.csv ada di folder yang sama).\n");
        return 1;
    }

    struct RowData data[MAX_ROWS];
    int numRows = loadData(fptr, data);
    fclose(fptr);

    if (numRows == 0) {
        printf("File kosong atau format salah.\n");
        return 1;
    }

    int choice = 0;
    char columnName[FIELD_SIZE];
    char searchTerm[FIELD_SIZE];
    char sortOrder[16];
    char exportFilename[FIELD_SIZE];
    char inputbuf[64];

    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Tampilkan data\n");
        printf("2. Cari data\n");
        printf("3. Urutkan data\n");
        printf("4. Ekspor data\n");
        printf("5. Keluar\n");
        printf("Pilihan Anda: ");
        read_input(inputbuf, sizeof(inputbuf));
        choice = atoi(inputbuf);

        switch (choice) {
            case 1: {
                int limit = 0;
                printf("Tampilkan berapa baris? (0 untuk semua): ");
                read_input(inputbuf, sizeof(inputbuf));
                limit = atoi(inputbuf);
                displayData(data, numRows, limit);
                break;
            }
            case 2:
                printf("Masukkan nama kolom: ");
                read_input(columnName, sizeof(columnName));
                printf("Masukkan kata yang ingin dicari: ");
                read_input(searchTerm, sizeof(searchTerm));
                searchData(data, numRows, columnName, searchTerm);
                break;
            case 3:
                printf("Masukkan nama kolom: ");
                read_input(columnName, sizeof(columnName));
                printf("Urutkan (asc / desc): ");
                read_input(sortOrder, sizeof(sortOrder));
                sortData(data, numRows, columnName, sortOrder);
                break;
            case 4:
                printf("Masukkan nama file hasil ekspor (tanpa .csv): ");
                read_input(exportFilename, sizeof(exportFilename));
                exportData(data, numRows, exportFilename);
                break;
            case 5:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (choice != 5);

    return 0;
}

// ====================== FUNGSI BANTU ======================
void trim_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\r\n")] = '\0';
}

void read_input(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    trim_newline(buf);
}

// ====================== FUNGSI PEMBACA DATA (AMAN) ======================
int loadData(FILE *fptr, struct RowData data[]) {
    char line[MAX_LINE];
    int row = 0;

    // Baca header terlebih dahulu (jika tidak ada header, file mungkin salah format)
    if (fgets(line, sizeof(line), fptr) == NULL) {
        return 0;
    }

    // Jika header kosong -> format salah
    trim_newline(line);
    if (strlen(line) == 0) return 0;

    while (fgets(line, sizeof(line), fptr)) {
        if (row >= MAX_ROWS) {
            fprintf(stderr, "Warning: jumlah baris melebihi MAX_ROWS (%d). Baris sisanya diabaikan.\n", MAX_ROWS);
            break;
        }

        // Hapus newline
        trim_newline(line);

        // Tokenisasi aman berdasarkan delimiter ';'
        char *tmp = strdup(line); // salinan karena strtok mengubah buffer
        if (!tmp) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }
        char *token = strtok(tmp, ";");

        if (!token) { free(tmp); continue; }
        strncpy(data[row].location1, token, FIELD_SIZE - 1); data[row].location1[FIELD_SIZE - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        strncpy(data[row].city, token, FIELD_SIZE - 1); data[row].city[FIELD_SIZE - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        data[row].price = atoi(token);

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        data[row].rooms = atoi(token);

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        data[row].bathrooms = atoi(token);

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        data[row].carParks = atoi(token);

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        strncpy(data[row].type, token, FIELD_SIZE - 1); data[row].type[FIELD_SIZE - 1] = '\0';

        token = strtok(NULL, ";");
        if (!token) { free(tmp); continue; }
        strncpy(data[row].furnish, token, FIELD_SIZE - 1); data[row].furnish[FIELD_SIZE - 1] = '\0';

        free(tmp);
        row++;
    }

    return row;
}

// ====================== FUNGSI TAMPILKAN DATA ======================
void displayData(struct RowData data[], int numRows, int limit) {
    if (numRows <= 0) {
        printf("Tidak ada data untuk ditampilkan.\n");
        return;
    }

    printf("\n%-20s %-15s %-12s %-6s %-10s %-8s %-12s %-12s\n",
           "Lokasi", "Kota", "Harga", "Kamar", "Mandi", "Parkir", "Tipe", "Perabot");
    printf("---------------------------------------------------------------------------------------------------\n");

    int max = (limit == 0 || limit > numRows) ? numRows : limit;
    for (int i = 0; i < max; i++) {
        printf("%-20s %-15s %-12d %-6d %-10d %-8d %-12s %-12s\n",
               data[i].location1, data[i].city, data[i].price, data[i].rooms,
               data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
    }
}

// ====================== FUNGSI PENCARIAN ======================
void searchData(struct RowData data[], int numRows, const char *columnName, const char *searchTerm) {
    int index = columnToIndex(columnName);
    if (index == -1) {
        printf("Nama kolom tidak valid.\n");
        return;
    }

    printf("\nHasil pencarian untuk '%s' pada kolom '%s':\n", searchTerm, columnName);
    int found = 0;

    for (int i = 0; i < numRows; i++) {
        char buffer[FIELD_SIZE*2];
        buffer[0] = '\0';
        switch (index) {
            case 0: strncpy(buffer, data[i].location1, sizeof(buffer)-1); break;
            case 1: strncpy(buffer, data[i].city, sizeof(buffer)-1); break;
            case 6: strncpy(buffer, data[i].type, sizeof(buffer)-1); break;
            case 7: strncpy(buffer, data[i].furnish, sizeof(buffer)-1); break;
            case 2: snprintf(buffer, sizeof(buffer), "%d", data[i].price); break;
            case 3: snprintf(buffer, sizeof(buffer), "%d", data[i].rooms); break;
            case 4: snprintf(buffer, sizeof(buffer), "%d", data[i].bathrooms); break;
            case 5: snprintf(buffer, sizeof(buffer), "%d", data[i].carParks); break;
            default: buffer[0] = '\0'; break;
        }

        if (buffer[0] && strstr(buffer, searchTerm) != NULL) {
            if (!found) {
                printf("\n%-20s %-15s %-12s %-6s %-10s %-8s %-12s %-12s\n",
                       "Lokasi", "Kota", "Harga", "Kamar", "Mandi", "Parkir", "Tipe", "Perabot");
            }
            printf("%-20s %-15s %-12d %-6d %-10d %-8d %-12s %-12s\n",
                   data[i].location1, data[i].city, data[i].price, data[i].rooms,
                   data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
            found = 1;
        }
    }

    if (!found)
        printf("Data tidak ditemukan.\n");
}

// ====================== FUNGSI SORTING ======================
void sortData(struct RowData data[], int numRows, const char *columnName, const char *sortOrder) {
    sortColumn = columnToIndex(columnName);
    if (sortColumn == -1) {
        printf("Nama kolom tidak valid.\n");
        return;
    }

    qsort(data, numRows, sizeof(struct RowData), compare);

    if (strcasecmp(sortOrder, "desc") == 0) {
        for (int i = 0; i < numRows / 2; i++) {
            struct RowData temp = data[i];
            data[i] = data[numRows - i - 1];
            data[numRows - i - 1] = temp;
        }
    }

    printf("\nData berhasil diurutkan berdasarkan '%s' (%s):\n", columnName, sortOrder);
    displayData(data, numRows, 10);
}

// ====================== PEMBANDING UNTUK QSORT ======================
int compare(const void *a, const void *b) {
    const struct RowData *rowA = (const struct RowData *)a;
    const struct RowData *rowB = (const struct RowData *)b;

    switch (sortColumn) {
        case 0: return strcasecmp(rowA->location1, rowB->location1);
        case 1: return strcasecmp(rowA->city, rowB->city);
        case 2: return (rowA->price > rowB->price) - (rowA->price < rowB->price);
        case 3: return (rowA->rooms > rowB->rooms) - (rowA->rooms < rowB->rooms);
        case 4: return (rowA->bathrooms > rowB->bathrooms) - (rowA->bathrooms < rowB->bathrooms);
        case 5: return (rowA->carParks > rowB->carParks) - (rowA->carParks < rowB->carParks);
        case 6: return strcasecmp(rowA->type, rowB->type);
        case 7: return strcasecmp(rowA->furnish, rowB->furnish);
        default: return 0;
    }
}

// ====================== KONVERSI NAMA KOLOM ======================
int columnToIndex(const char *columnName) {
    if (!columnName) return -1;
    if (strcasecmp(columnName, "Lokasi") == 0 || strcasecmp(columnName, "Location") == 0) return 0;
    if (strcasecmp(columnName, "Kota") == 0 || strcasecmp(columnName, "City") == 0) return 1;
    if (strcasecmp(columnName, "Harga") == 0 || strcasecmp(columnName, "Price") == 0) return 2;
    if (strcasecmp(columnName, "Kamar") == 0 || strcasecmp(columnName, "Rooms") == 0) return 3;
    if (strcasecmp(columnName, "Mandi") == 0 || strcasecmp(columnName, "Bathrooms") == 0) return 4;
    if (strcasecmp(columnName, "Parkir") == 0 || strcasecmp(columnName, "CarParks") == 0) return 5;
    if (strcasecmp(columnName, "Tipe") == 0 || strcasecmp(columnName, "Type") == 0) return 6;
    if (strcasecmp(columnName, "Perabot") == 0 || strcasecmp(columnName, "Furnish") == 0) return 7;
    return -1;
}

// ====================== FUNGSI EKSPOR ======================
void exportData(struct RowData data[], int numRows, const char *filename) {
    char fullName[150];
    snprintf(fullName, sizeof(fullName), "%s.csv", filename);

    FILE *exportFile = fopen(fullName, "w");
    if (exportFile == NULL) {
        printf("Gagal membuat file ekspor.\n");
        return;
    }

    fprintf(exportFile, "Location;City;Price;Rooms;Bathrooms;CarParks;Type;Furnish\n");
    for (int i = 0; i < numRows; i++) {
        fprintf(exportFile, "%s;%s;%d;%d;%d;%d;%s;%s\n",
                data[i].location1, data[i].city, data[i].price, data[i].rooms,
                data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
    }

    fclose(exportFile);
    printf("Data berhasil diekspor ke '%s'\n", fullName);
}
