#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct processinfo {
    int pid;
    float cpu;
    float mem;
    char command[256];
};

int main() {
    FILE *fp_aux, *fp_elf;
    char line[1024];

    // --- STEP 1: Execute Commands ---
    // Note: Use -eLf (Capital L) for Threads/LWP info
    system("ps aux --no-headers > temp_aux.txt");
    system("ps -eLf --no-headers > temp_elf.txt");

    // --- STEP 2: Store ps aux data into Array ---
    struct processinfo aux_data[2000]; // Increased size just in case
    int aux_i = 0;

    fp_aux = fopen("temp_aux.txt", "r");
    if (fp_aux == NULL) {
        perror("Error opening aux file");
        return 1;
    }

    int pidt;
    float cput, memt;
    // Reading Loop
    while (fscanf(fp_aux, "%*s %d %f %f %*s %*s %*s %*s %*s %*s %[^\n]", &pidt, &cput, &memt, aux_data[aux_i].command) != EOF) {
        aux_data[aux_i].pid = pidt;
        aux_data[aux_i].cpu = cput;
        aux_data[aux_i].mem = memt;
        aux_i++;
    }
    fclose(fp_aux);

    // --- STEP 3: Read ps -eLf and Merge ---
    
    printf("\n=================================================================================\n");
    printf("%-8s %-8s %-8s %-8s %-6s %-6s %-20s\n", "PID", "PPID", "LWP", "NLWP", "%CPU", "%MEM", "COMMAND");
    printf("=================================================================================\n");

    fp_elf = fopen("temp_elf.txt", "r");
    if (fp_elf == NULL) {
        perror("Error opening elf file");
        return 1;
    }

    int pid, ppid, lwp, nlwp;
    char uid_dummy[50]; // To store UID string temporarily

    // ps -eLf format: UID PID PPID LWP C NLWP ...
    while (fscanf(fp_elf, "%s %d %d %d %*s %d", uid_dummy, &pid, &ppid, &lwp, &nlwp) != EOF) {
        
        // Skip the rest of the line (Time, CMD in elf file)
        fgets(line, sizeof(line), fp_elf);

        // Merging logic
        float cpu_per = 0.0;
        float mem_per = 0.0;
        char command_found[256] = "N/A";

        // Search in aux_data array
        for (int i = 0; i < aux_i; i++) {
            if (pid == aux_data[i].pid) {
                cpu_per = aux_data[i].cpu;
                mem_per = aux_data[i].mem;
                strcpy(command_found, aux_data[i].command);
                break; 
            }
        }

        // Final Print (Added \n at the end)
        printf("%-8d %-8d %-8d %-8d %-6.1f %-6.1f %-20.20s\n", pid, ppid, lwp, nlwp, cpu_per, mem_per, command_found);
    }
    fclose(fp_elf);

    // STEP 4: Cleanup 
    system("rm temp_aux.txt temp_elf.txt");
    return 0;
}