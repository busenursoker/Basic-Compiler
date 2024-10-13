#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_REGISTERS 10

int registers[MAX_REGISTERS]; // Yazmaçlar dizisi
char program[MAX_LINES][50];  // Program satırlarını tutan dizi
int programSize = 0;          // Programdaki satır sayısı

// put komutu: Bir değeri bir yazmaca atar
void put(int value, int registerIndex) {
    registers[registerIndex] = value;
    printf("put: %d -> r%d\n", value, registerIndex);  // Hata ayıklama çıktısı
}

// add komutu: İki yazmacı toplar, sonucu ikinci yazmaca atar
void add(int reg1, int reg2) {
    registers[reg2] += registers[reg1];
    printf("add: r%d + r%d -> r%d (sonuc: %d)\n", reg1, reg2, reg2, registers[reg2]);  // Hata ayıklama çıktısı
}

// prn komutu: Bir yazmacın değerini yazdırır
void prn(int registerIndex) {
    printf("prn: r%d: %d\n", registerIndex, registers[registerIndex]);
}

// jmpu komutu: Koşulsuz olarak belirtilen satıra atlar
void jmpu(int targetLine, int *programCounter) {
    printf("jmpu: %d. satıra atlanıyor.\n", targetLine);  // Hata ayıklama çıktısı
    *programCounter = targetLine - 1; // Satır numarası 1'den başlıyor, dizi ise 0'dan
}

// jmpe komutu: İki yazmacın değeri eşitse belirtilen satıra atlar
void jmpe(int reg1, int reg2, int targetLine, int *programCounter) {
    printf("jmpe: r%d (%d) == r%d (%d) kontrol ediliyor.\n", reg1, registers[reg1], reg2, registers[reg2]);
    if (registers[reg1] == registers[reg2]) {
        printf("jmpe: r%d == r%d, %d. satıra atlanıyor.\n", reg1, reg2, targetLine);
        *programCounter = targetLine - 1;  // Atlama gerçekleşirse program sayacını hedef satıra ayarla
    } else {
        printf("jmpe: r%d != r%d, atlama yapılmadı.\n", reg1, reg2);
        (*programCounter)++;  // Atlama yapılmazsa sıradaki komuta geç
    }
}


// halt komutu: Programı sonlandırır
void halt() {
    printf("Program sonlandırıldı.\n");
    exit(0);
}

// Programı çalıştıran ana fonksiyon
void executeProgram() {
    int programCounter = 0;
    
    while (programCounter < programSize) {
        char command[10];
        sscanf(program[programCounter], "%s", command);

        // Komut işleme sırasında hata ayıklama çıktısı
        printf("Komut: %s\n", program[programCounter]);

        if (strcmp(command, "put") == 0) {
            int value, registerIndex;
            sscanf(program[programCounter], "%*s %d,r%d", &value, &registerIndex);
            put(value, registerIndex);
        } 
        else if (strcmp(command, "add") == 0) {
            int reg1, reg2;
            sscanf(program[programCounter], "%*s r%d,r%d", &reg1, &reg2);
            add(reg1, reg2);
        } 
        else if (strcmp(command, "prn") == 0) {
            int registerIndex;
            sscanf(program[programCounter], "%*s r%d", &registerIndex);
            prn(registerIndex);
        } 
        else if (strcmp(command, "jmpu") == 0) {
            int targetLine;
            sscanf(program[programCounter], "%*s %d", &targetLine);
            jmpu(targetLine, &programCounter);
            continue; // Atlamadan sonra başka komut çalıştırma
        } 
        else if (strcmp(command, "jmpe") == 0) {
            int reg1, reg2, targetLine;
            sscanf(program[programCounter], "%*s r%d,r%d,%d", &reg1, &reg2, &targetLine);
            jmpe(reg1, reg2, targetLine, &programCounter);
            continue; // Eğer atlama gerçekleşirse, diğer komutları çalıştırma
        } 
        else if (strcmp(command, "halt") == 0) {
            halt();
        }

        programCounter++; // Sonraki satıra geç
    }
}

// Program dosyasını okuyup satırları program dizisine aktaran fonksiyon
void readProgram(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        exit(1);
    }

    while (fgets(program[programSize], sizeof(program[programSize]), file)) {
        programSize++;
    }

    fclose(file);
}

int main() {
    // Ornek.txt dosyasını oku
    readProgram("Ornek.txt");

    // Programı çalıştır
    executeProgram();

    return 0;
}
