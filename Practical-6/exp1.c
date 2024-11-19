#include <stdio.h>

void calculate_parity_bits(int data[], int* p1, int* p2, int* p4, int* p8) {
    *p1 = (data[0] + data[2] + data[3] + data[5] + data[6]) % 2;
    *p2 = (data[0] + data[1] + data[3] + data[4] + data[6]) % 2;
    *p4 = (data[3] + data[4] + data[5]) % 2;
    *p8 = (data[1] + data[0] + data[2]) % 2;
}

void parity_bits(int data[], int* p1, int* p2, int* p4, int* p8) {
    *p1 = (data[10] + data[8] + data[6] + data[4] + data[2] + data[0]) % 2;
    *p2 = (data[9] + data[8] + data[5] + data[4] + data[1] + data[0]) % 2;
    *p4 = (data[7] + data[6] + data[5] + data[4]) % 2;
    *p8 = (data[0] + data[3] + data[2] + data[1]) % 2;
}

void generate_hamming_code(int data[], int hamming_code[]) {
    int p1, p2, p4, p8;
    calculate_parity_bits(data, &p1, &p2, &p4, &p8);
    hamming_code[0] = data[0];
    hamming_code[1] = data[1];
    hamming_code[2] = data[2];
    hamming_code[3] = p8;
    hamming_code[4] = data[3];
    hamming_code[5] = data[4];
    hamming_code[6] = data[5];
    hamming_code[7] = p4;
    hamming_code[8] = data[6];
    hamming_code[9] = p2;
    hamming_code[10] = p1;
}

int detect_error(int hamming_code[]) {
    int p1, p2, p4, p8;
    parity_bits(hamming_code, &p1, &p2, &p4, &p8);
    int error_position = p1 * 1 + p2 * 2 + p4 * 4 + p8 * 8;
    return error_position;
}

int main() {
    int data[7];
    printf("Enter 7 bits of data one by one:\n");
    for (int i = 0; i < 7; i++) {
        printf("Bit %d: ", i + 1);
        scanf("%d", &data[i]);
    }

    printf("Data after appending all bits: ");
    for (int i = 0; i < 7; i++) {
        printf("%d", data[i]);
    }
    printf("\n");

    int hamming_code[11];
    generate_hamming_code(data, hamming_code);

    printf("The 11-bit Hamming code is: ");
    for (int i = 0; i < 11; i++) {
        printf("%d", hamming_code[i]);
    }
    printf("\n");

    int corrupted_code[11];
    printf("Enter the 11-bit Hamming code with a possible error (bit by bit):\n");
    for (int i = 0; i < 11; i++) {
        printf("Bit %d: ", i + 1);
        scanf("%d", &corrupted_code[i]);
    }

    int error_pos = detect_error(corrupted_code);
    printf("Calculated error position: %d\n", 11 - error_pos + 1);

    if (corrupted_code[11 - error_pos] == 0) {
        corrupted_code[11 - error_pos] = 1;
    } else {
        corrupted_code[11 - error_pos] = 0;
    }

    printf("Data after error-correcting all bits: ");
    for (int i = 0; i < 11; i++) {
        printf("%d", corrupted_code[i]);
    }
    printf("\n");

    return 0;
}
