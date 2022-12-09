#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define MAX_UNIQUE_ITEMS 52
#define NUM_RUCKSACKS_IN_GROUP 3

typedef struct {
        int num_items;

        // Enough to store each item ten times
        // in a rucksack
        char items[MAX_UNIQUE_ITEMS * 10];
        int item_map[MAX_UNIQUE_ITEMS * 2];
} Rucksack;

int get_item_priority(char item) {
       if (item >= 'a' && item <= 'z') {
              return item - 96;
       } else if (item >= 'A' && item <= 'Z') {
              return item - 38;
       } else {
              return 0;
       }
}

int main(void) {
        FILE *file = fopen("input", "r");
        Rucksack rucksacks[NUM_RUCKSACKS_IN_GROUP] = {0};

        int total = 0;
        int group_badge_total = 0;
        int line_count = 0;
        if (file == NULL) {
                printf("Could not open input file");
                exit(1);
        }

        while(fscanf(file, "%s", rucksacks[line_count].items) == 1) {

                Rucksack *rucksack = &rucksacks[line_count];

                // Needed so we don't keep previous iteration values
                memset(rucksack->item_map, false, sizeof(int) * MAX_UNIQUE_ITEMS * 2);

                rucksack->num_items = strlen(rucksack->items);

                if (rucksack->num_items % 2 != 0) {
                       printf("Rucksack %s compartments are not even."
                                       "Aborting", rucksack);
                       exit(1);
                }

                int first_comp_size = rucksack->num_items / 2;
                int second_comp_size = rucksack->num_items;

                printf("Rucksack: %s\n", rucksack->items);
                for (int i = 0; i < first_comp_size; i++) {
                        char item = rucksack->items[i];
                        int priority = get_item_priority(item);
                        int index = priority - 1;
                        printf("First loop: %c,%d\n",item,priority);
                        if (priority == 0) {
                                printf("Could not get priority"
                                                "Invalid item %c",
                                                item);
                        }

                        rucksack->item_map[index] = true;
                }

                for (int i = first_comp_size; i < second_comp_size; i++) {
                        char item = rucksack->items[i];
                        int priority = get_item_priority(item);
                        int index = priority - 1;
                        printf("Second loop: %c,%d\n", item,priority);
                        if (rucksack->item_map[index] == true &&
                                        rucksack->item_map[index + MAX_UNIQUE_ITEMS] == false)
                        {
                                printf("Match: %c,%d\n", item,priority);
                                total+= priority;
                        }
                        rucksack->item_map[index + MAX_UNIQUE_ITEMS] = true;
                }

                if (line_count == 2) {
                        for(int i = 0; i < MAX_UNIQUE_ITEMS; i++) {
                                int is_group_badge_priority = true;
                                for(int j = 0; j < NUM_RUCKSACKS_IN_GROUP; j++) {
                                        Rucksack rucksack = rucksacks[j];
                                        if (rucksack.item_map[i] == false &&
                                                        rucksack.item_map[i + MAX_UNIQUE_ITEMS] == false)
                                        {
                                                is_group_badge_priority = false;
                                                break;
                                        }
                                }

                                if (is_group_badge_priority == true) {
                                        group_badge_total += i + 1;
                                        break;
                                }
                        }
                }

                line_count = line_count == 2 ? 0: ++line_count;

        }

        printf("Total: %d\n", total);
        printf("Group badge total: %d\n", group_badge_total);
}
