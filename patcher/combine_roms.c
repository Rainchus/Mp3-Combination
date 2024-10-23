#include <stdio.h>
#include <stdlib.h>

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

int main() {
    FILE *file1, *file2, *output;

    // Open the files mp3.z64 and mp2.z64
    file1 = fopen("mp3.z64", "rb");
    file2 = fopen("mp2.z64", "rb");

    // Check if both files are found
    if (file1 == NULL || file2 == NULL) {
        if (file1 == NULL) {
            printf("Error: mp3.z64 not found.\n");
        }
        if (file2 == NULL) {
            printf("Error: mp2.z64 not found.\n");
        }
        // Close any open files and exit
        if (file1 != NULL) fclose(file1);
        if (file2 != NULL) fclose(file2);
        return 1;
    }

    // Open output file for appending
    output = fopen("mp3-mp2.z64", "wb");
    if (output == NULL) {
        printf("Error: Could not create mp3-mp2.z64.\n");
        fclose(file1);
        fclose(file2);
        return 1;
    }

    // Append mp3.z64 content to mp3-mp2.z64
    append_file(file1, output);
    fclose(file1);

    // Append mp2.z64 content to mp3-mp2.z64
    append_file(file2, output);
    fclose(file2);

    // Close the output file
    fclose(output);

    printf("Files mp3.z64 and mp2.z64 successfully merged into mp3-mp2.z64.\n");

    // Check if flips.exe exists
    if (!file_exists("flips.exe")) {
        printf("Error: flips.exe not found. Exiting.\n");
        return 1;
    }

    // Check if mp3-mp2-combo.bps exists
    if (!file_exists("mp3-mp2-combo.bps")) {
        printf("Error: mp3-mp2-combo.bps not found. Exiting.\n");
        return 1;
    }

    // Apply the patch using flips.exe (Windows compatible)
    printf("Applying mp3-mp2-combo.bps to mp3-mp2.z64...\n");
    if (system("flips.exe --apply \"./mp3-mp2-combo.bps\" \"mp3-mp2.z64\" \"mp3-mp2-combo.z64\"") != 0) {
        printf("Error: Failed to apply the patch.\n");
        return 1;
    }

    printf("Patch applied successfully, output written to mp3-mp2-combo.z64.\n");

    return 0;
}
