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

// Function to generate a simple checksum (XOR-based)
unsigned int generate_checksum(FILE *file) {
    unsigned char buffer[1024];
    size_t bytesRead;
    unsigned int checksum = 0xFFFFFFFF; // Start with all bits set to ensure more variation

    // Read the file in chunks and accumulate the checksum using XOR and bit shifts
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            checksum ^= buffer[i];        // XOR the byte into the checksum
            checksum = (checksum << 5) | (checksum >> (32 - 5)); // Rotate left by 5 bits
        }
    }

    return checksum;
}

// Function to byte swap the contents of a file in memory (fix byte swap logic)
void byte_swap_file(FILE *file, FILE *destination) {
    unsigned char buffer[1024];
    size_t bytesRead;

    // Read and byte swap in chunks
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        // Iterate through the buffer and swap every 4 bytes for a 32-bit value
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

        // Write swapped buffer to the destination file
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

    // Generate the checksum for the file
    unsigned int checksum = generate_checksum(file);
    fclose(file);

    // Check if the checksum matches big-endian or little-endian
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

    unsigned int checksum_mp3_be = 4290596117;
    unsigned int checksum_mp2_be = 2872400212;
    unsigned int checksum_mp1_be = 1449849582;

    unsigned int checksum_mp3_le = 3489976595;
    unsigned int checksum_mp2_le = 2699277926;
    unsigned int checksum_mp1_le = 3341454040;

    // Open the files mp3.z64, mp2.z64, and mp1.z64
    file1 = fopen("roms/mp3.z64", "rb");
    file2 = fopen("roms/mp2.z64", "rb");
    file3 = fopen("roms/mp1.z64", "rb");

    // Check if all files are found
    if (file1 == NULL || file2 == NULL || file3 == NULL) {
        if (file1 == NULL) printf("Error: roms/mp3.z64 not found.\n");
        if (file2 == NULL) printf("Error: roms/mp2.z64 not found.\n");
        if (file3 == NULL) printf("Error: roms/mp1.z64 not found.\n");
        if (file1 != NULL) fclose(file1);
        if (file2 != NULL) fclose(file2);
        if (file3 != NULL) fclose(file3);
        return 1;
    }

    // Open output file for appending
    output = fopen("mp3-mp2-mp1.z64", "wb");
    if (output == NULL) {
        printf("Error: Could not create mp3-mp2-mp1.z64.\n");
        fclose(file1);
        fclose(file2);
        fclose(file3);
        return 1;
    }

    // Validate checksums for each file and handle byte swapping if necessary
    if (!validate_checksum_and_swap("roms/mp3.z64", checksum_mp3_be, checksum_mp3_le, output) ||
        !validate_checksum_and_swap("roms/mp2.z64", checksum_mp2_be, checksum_mp2_le, output) ||
        !validate_checksum_and_swap("roms/mp1.z64", checksum_mp1_be, checksum_mp1_le, output)) {
        fclose(output);
        return 1; // Exit if any checksum does not match
    }

    fclose(output);

    printf("Files mp3.z64, mp2.z64, and mp1.z64 successfully merged into mp3-mp2-mp1.z64.\n");

    // Check if flips.exe exists
    if (!file_exists("flips.exe")) {
        printf("Error: flips.exe not found. Exiting.\n");
        return 1;
    }

    // Check if mp3-mp2-mp1-combo.bps exists
    if (!file_exists("mp3-mp2-mp1-combo.bps")) {
        printf("Error: mp3-mp2-mp1-combo.bps not found. Exiting.\n");
        return 1;
    }

    // Apply the patch using flips.exe (Windows compatible)
    printf("Applying mp3-mp2-mp1-combo.bps to mp3-mp2-mp1.z64...\n");
    if (system("flips.exe --apply \"./mp3-mp2-mp1-combo.bps\" \"mp3-mp2-mp1.z64\" \"mp3-mp2-mp1-combo.z64\"") != 0) {
        printf("Error: Failed to apply the patch.\n");
        return 1;
    }

    printf("Patch applied successfully, output written to mp3-mp2-mp1-combo.z64.\n");

    return 0;
}
