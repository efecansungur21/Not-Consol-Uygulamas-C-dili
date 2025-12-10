#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOT 1000
#define MAX_LEN 256
#define DOSYA_ADI "notes.txt"

char notes[MAX_NOT][MAX_LEN];
int count = 0;

// --- Dosyadan yükleme ---
void loadNotes() {
    FILE *file = fopen(DOSYA_ADI, "r");
    if (!file) return;

    while (fgets(notes[count], MAX_LEN, file)) {
        // satır sonundaki '\n' karakterini temizle
        notes[count][strcspn(notes[count], "\n")] = 0;
        count++;
    }

    fclose(file);
}

// --- Dosyaya kaydetme ---
void saveNotes() {
    FILE *file = fopen(DOSYA_ADI, "w");
    if (!file) return;

    for (int i = 0; i < count; i++)
        fprintf(file, "%s\n", notes[i]);

    fclose(file);
}

// --- Notları listele ---
void listNotes() {
    if (count == 0) {
        printf("Hiç not yok!\n");
        return;
    }

    printf("---- NOTLAR ----\n");
    for (int i = 0; i < count; i++)
        printf("%d) %s\n", i, notes[i]);
}

// --- Arama ---
void searchNote() {
    char query[MAX_LEN];
    printf("Aramak istediğiniz not: ");
    getchar(); // önceki enter karakterini temizle
    fgets(query, MAX_LEN, stdin);
    query[strcspn(query, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(notes[i], query)) {
            printf("%d) %s\n", i, notes[i]);
            found = 1;
        }
    }
    if (!found) printf("Bulunamadı.\n");
}

// --- Ana program ---
int main() {
    loadNotes();

    while (1) {
        printf("\n============== NOT MENUSU ==============\n");
        printf("1 - Yeni not ekle\n");
        printf("2 - Not sil\n");
        printf("3 - Not guncelle\n");
        printf("4 - Tum notlari goruntule\n");
        printf("5 - Not ara\n");
        printf("6 - cikis\n");
        printf("========================================\n");
        printf("Seçiminiz: ");

        int secim;
        if (scanf("%d", &secim) != 1) {
            printf("Geçersiz giriş!\n");
            while (getchar() != '\n'); // buffer temizle
            continue;
        }

        getchar(); // Enter karakterini temizle

        switch (secim) {
            case 1:
                if (count >= MAX_NOT) {
                    printf("Not kapasitesi dolu!\n");
                } else {
                    printf("Yeni notu girin: ");
                    fgets(notes[count], MAX_LEN, stdin);
                    notes[count][strcspn(notes[count], "\n")] = 0; // \n sil
                    count++;
                    saveNotes();
                    printf("Not kaydedildi!\n");
                }
                break;

            case 2:
                if (count == 0) { printf("Silinecek not yok!\n"); break; }

                printf("Silmek istediğiniz notun indexini girin (0-%d): ", count-1);
                int del;
                if (scanf("%d", &del) != 1 || del < 0 || del >= count) {
                    printf("Geçersiz index!\n");
                    while (getchar() != '\n'); // buffer temizle
                    break;
                }
                for (int i = del; i < count - 1; i++)
                    strcpy(notes[i], notes[i + 1]);
                count--;
                saveNotes();
                printf("Not silindi!\n");
                getchar(); // Enter temizle
                break;

            case 3:
                if (count == 0) { printf("Güncellenecek not yok!\n"); break; }

                printf("Güncellemek istediğiniz notun indexini girin (0-%d): ", count-1);
                int idx;
                if (scanf("%d", &idx) != 1 || idx < 0 || idx >= count) {
                    printf("Geçersiz index!\n");
                    while (getchar() != '\n'); // buffer temizle
                    break;
                }
                getchar(); // Enter temizle
                printf("Yeni değeri girin: ");
                fgets(notes[idx], MAX_LEN, stdin);
                notes[idx][strcspn(notes[idx], "\n")] = 0;
                saveNotes();
                printf("Not güncellendi!\n");
                break;

            case 4:
                listNotes();
                break;

            case 5:
                searchNote();
                break;

            case 6:
                printf("Çıkış yapılıyor...\n");
                saveNotes();
                return 0;

            default:
                printf("Geçersiz seçim!\n");
        }
    }
}
