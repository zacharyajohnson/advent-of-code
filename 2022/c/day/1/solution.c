#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int compare_ints(const void* a, const void* b) {
        int arg1 = *(const int*)a;
        int arg2 = *(const int*)b;
        
        if (arg1 < arg2) return -1;
        if (arg1 > arg2) return 1;
        return 0;
}

int main(void) {
        FILE *file = fopen("input", "r");
        char line[100];
        char c;
        int i = 0;
        
        int elf_total = 0;

        int *total_elf_calories = NULL; 
        int num_of_total_elf_calories = 0;

        while( (c = fgetc(file)) != EOF) {
                // If c is newline
                // we have reached the end of
                // the line. 
                if(c == '\n') {
                        line[i] = c;
                        line[i+1] = '\0';

                        // If line = '\n'
                        // We know thats the end for
                        // the elf we are on.
                        // Add it to the total array and reset
                        // the elf total to 0 for the next elf
                        if (strcmp(line, "\n") == 0) {
                                num_of_total_elf_calories++;
                                total_elf_calories = 
                                        realloc(total_elf_calories, sizeof(int) * num_of_total_elf_calories);
                                total_elf_calories[num_of_total_elf_calories - 1] = elf_total;

                                elf_total = 0;
                        // If line isn't '\n' we are still on
                        // the same elf so we parse the total
                        // out and add it to the elfs total
                        } else {
                                elf_total += atoi(line);
                        }
                        // Reset i to 0 to the beginning of line
                        i = 0;
                // If c isn't line, continue parsing the line of the file
                // into the line variable
                } else {
                        line[i] = c;
                        i++;
                }
        }

        // Sort so highest counts are at the end of the array
        qsort(total_elf_calories, num_of_total_elf_calories, sizeof(int), compare_ints);

        int highest_elf_calorie_count = total_elf_calories[num_of_total_elf_calories - 1];

        int top_3_elf_calorie_count_sum = total_elf_calories[num_of_total_elf_calories - 1]
                + total_elf_calories[num_of_total_elf_calories - 2]
                +total_elf_calories[num_of_total_elf_calories - 3];

        printf("Highest Elf Calorie Count: %d\n", highest_elf_calorie_count);
        printf("Top 3 Elf Calorie Count Sum: %d\n", top_3_elf_calorie_count_sum);
}
