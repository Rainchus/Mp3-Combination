#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Function to append the contents of one file to another
void append_file(FILE *source, FILE *destination) {
    char buffer[1024];
    size_t bytesRead;

    // Read from source and write to destination
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, destination);
    }
}

// Function to check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to delete a file
void delete_file(const char *filename) {
    if (remove(filename) != 0) {
        printf("Error: Could not delete file %s.\n", filename);
    }
}

// Function to generate a simple checksum (XOR-based)
unsigned int generate_checksum(FILE *file) {
    unsigned char buffer[1024];
    size_t bytesRead;
    unsigned int checksum = 0xFFFFFFFF;

    // Read the file in chunks and accumulate the checksum using XOR and bit shifts
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            checksum ^= buffer[i];
            checksum = (checksum << 5) | (checksum >> (32 - 5));
        }
    }

    return checksum;
}

// Function to byte swap the contents of a file in memory
void byte_swap_file(FILE *file, FILE *destination) {
    unsigned char buffer[1024];
    size_t bytesRead;

    // Read and byte swap in chunks
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; i += 4) {
            if (i + 3 < bytesRead) {
                unsigned char temp = buffer[i];
                buffer[i] = buffer[i + 3];
                buffer[i + 3] = temp;
                temp = buffer[i + 1];
                buffer[i + 1] = buffer[i + 2];
                buffer[i + 2] = temp;
            }
        }
        fwrite(buffer, 1, bytesRead, destination);
    }
}

// Function to validate checksum and handle byte-swapping if needed
int validate_checksum_and_swap(const char *filename, unsigned int big_endian_checksum, unsigned int little_endian_checksum, FILE *destination) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open file %s.\n", filename);
        return 0;
    }

    unsigned int checksum = generate_checksum(file);
    fclose(file);

    if (checksum == big_endian_checksum) {
        printf("Checksum for %s is valid (big-endian).\n", filename);
        file = fopen(filename, "rb");
        append_file(file, destination);
        fclose(file);
        return 1;
    } else if (checksum == little_endian_checksum) {
        printf("Checksum for %s is valid (little-endian). Byte-swapping file...\n", filename);
        file = fopen(filename, "rb");
        byte_swap_file(file, destination);
        fclose(file);
        return 1;
    } else {
        printf("Checksum for %s is invalid! Expected: %u, Got: %u\n", filename, big_endian_checksum, checksum);
        return 0;
    }
}

int main() {
    FILE *file1, *file2, *file3, *output;
    const char *output_file = "mp3-mp2-mp1.z64";
    const char *combo_file = "mp3-mp2-mp1-combo.z64";

    unsigned int checksum_mp3_be = 4290596117;
    unsigned int checksum_mp2_be = 2872400212;
    unsigned int checksum_mp1_be = 1449849582;

    unsigned int checksum_mp3_le = 3489976595;
    unsigned int checksum_mp2_le = 2699277926;
    unsigned int checksum_mp1_le = 3341454040;

    file1 = fopen("roms/mp3.z64", "rb");
    file2 = fopen("roms/mp2.z64", "rb");
    file3 = fopen("roms/mp1.z64", "rb");

    if (file1 == NULL || file2 == NULL || file3 == NULL) {
        if (file1 == NULL) printf("Error: roms/mp3.z64 not found.\n");
        if (file2 == NULL) printf("Error: roms/mp2.z64 not found.\n");
        if (file3 == NULL) printf("Error: roms/mp1.z64 not found.\n");
        if (file1 != NULL) fclose(file1);
        if (file2 != NULL) fclose(file2);
        if (file3 != NULL) fclose(file3);
        return 1;
    }

    output = fopen(output_file, "wb");
    if (output == NULL) {
        printf("Error: Could not create %s.\n", output_file);
        fclose(file1);
        fclose(file2);
        fclose(file3);
        return 1;
    }

    if (!validate_checksum_and_swap("roms/mp3.z64", checksum_mp3_be, checksum_mp3_le, output) ||
        !validate_checksum_and_swap("roms/mp2.z64", checksum_mp2_be, checksum_mp2_le, output) ||
        !validate_checksum_and_swap("roms/mp1.z64", checksum_mp1_be, checksum_mp1_le, output)) {
        fclose(output);
        delete_file(output_file);  // Delete output file on failure
        return 1;
    }

    fclose(output);
    printf("Files mp3.z64, mp2.z64, and mp1.z64 successfully merged into %s.\n", output_file);

    if (!file_exists("flips.exe") || !file_exists("mp3-mp2-mp1-combo.bps")) {
        printf("Error: Necessary files not found. Exiting.\n");
        delete_file(output_file);  // Clean up on failure
        return 1;
    }

    printf("Applying mp3-mp2-mp1-combo.bps to %s...\n", output_file);
    if (system("flips.exe --apply \"./mp3-mp2-mp1-combo.bps\" \"mp3-mp2-mp1.z64\" \"mp3-mp2-mp1-combo.z64\"") != 0) {
        printf("Error: Failed to apply the patch.\n");
        delete_file(output_file);  // Clean up on failure
        return 1;
    }

    printf("Patch applied successfully, output written to %s.\n", combo_file);
    delete_file(output_file);  // Delete after successful creation of combo file

    return 0;
}
