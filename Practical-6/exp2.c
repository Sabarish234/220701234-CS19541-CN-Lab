#include <stdio.h>
#include <string.h>

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

void char_to_binary(char ch, int data[]) {
    for (int i = 0; i < 7; i++) {
        data[i] = (ch >> (6 - i)) & 1;
    }
}

char binary_to_char(int data[]) {
    char ch = 0;
    for (int i = 0; i < 7; i++) {
        ch |= (data[i] << (6 - i));
    }
    return ch;
}

int main() {
    char input_text[100]; // Buffer for input text
    printf("Enter a string (up to 99 characters):\n");
    scanf("%99s", input_text);  // Read input string

    int data[7], hamming_code[11], corrupted_code[11];
    char encoded_text[1100] = {0}; // Buffer for storing encoded Hamming code
    char decoded_text[100] = {0};  // Buffer for storing decoded text
    int k = 0;

    // Encode each character in the input text
    for (int i = 0; i < strlen(input_text); i++) {
        char_to_binary(input_text[i], data);
        generate_hamming_code(data, hamming_code);
        
        // Store the Hamming code in the encoded text buffer
        for (int j = 0; j < 11; j++) {
            encoded_text[k++] = hamming_code[j] + '0';  // Convert int to char
        }
    }

    printf("Encoded Hamming code: %s\n", encoded_text);

    // Simulate receiving the encoded text with possible errors
    printf("Enter the received Hamming code (up to 1100 bits, same length as encoded):\n");
    scanf("%s", encoded_text);  // Read the encoded Hamming code

    k = 0;
    // Decode each 11-bit segment to extract the original 7-bit data
    for (int i = 0; i < strlen(encoded_text) / 11; i++) {
        // Extract the 11 bits for this character
        for (int j = 0; j < 11; j++) {
            corrupted_code[j] = encoded_text[k++] - '0';  // Convert char to int
        }

        int error_pos = detect_error(corrupted_code);
        if (error_pos != 0) {
            // Correct the error
            corrupted_code[11 - error_pos] = (corrupted_code[11 - error_pos] == 0) ? 1 : 0;
        }

        // Extract the 7-bit original data
        data[0] = corrupted_code[0];
        data[1] = corrupted_code[1];
        data[2] = corrupted_code[2];
        data[3] = corrupted_code[4];
        data[4] = corrupted_code[5];
        data[5] = corrupted_code[6];
        data[6] = corrupted_code[8];

        // Convert the 7-bit data back to a character and store it in decoded_text
        decoded_text[i] = binary_to_char(data);
    }

    printf("Decoded and corrected text: %s\n", decoded_text);

    return 0;
}
