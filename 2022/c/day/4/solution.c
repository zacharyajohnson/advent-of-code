#include <stdio.h>
#include <stdlib.h>

typedef struct {
        int e1s;
        int e1e;
        int e2s;
        int e2e;
} ElfPair;

int
assignment_contains_another(ElfPair *pair)
{
        return
                (pair->e1s <= pair->e2s && pair->e1e >= pair->e2e) ||
                (pair->e2s <= pair->e1s && pair->e2e >= pair->e1e);
}

int
assignments_overlap(ElfPair *pair)
{
        int e1s = pair->e1s;
        int e1e = pair->e1e;
        int e2s = pair->e2s;
        int e2e = pair->e2e;

        return
                // If elf two start is in elf one range ||
                // If elf two end is in elf one range
                ( (e2s <= e1e && e2s >= e1s) || (e2e >= e1s && e2e <= e1e) )

                ||

                // If elf one start is in elf two range ||
                // If elf one end is in elf two range
                ( (e1s <= e2e && e1s >= e2s) || (e1e >= e2s && e1e <= e2e) );

}

int
main(void)
{
        FILE *file = fopen("input", "r");

        if (file == NULL) {
                printf("Could not open input file");
                exit(1);
        }

        int assignment_contains_another_count = 0;
        int assignments_overlap_count = 0;

        ElfPair pair = {0};

        while (fscanf(file, "%d-%d,%d-%d ", &pair.e1s, &pair.e1e, &pair.e2s, &pair.e2e) == 4) {
                printf("Elf one parsed %d-%d\n", pair.e1s, pair.e1e);
                printf("Elf two parsed %d-%d\n", pair.e2s, pair.e2e);

                if (assignment_contains_another(&pair)) {
                        assignment_contains_another_count++;
                }

                if (assignments_overlap(&pair)) {
                        assignments_overlap_count++;
                }
        }

        printf("Assignments containing other assignments count: %d\n",
                        assignment_contains_another_count);

        printf("Assignment Overlap Count: %d\n", assignments_overlap_count);
}
