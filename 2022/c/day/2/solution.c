#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_GAME_STATES 9

typedef struct {
        char *opponent_choice;
        char *my_choice;
        char *result;
        int result_points;
} GameState;

GameState game_states[NUM_GAME_STATES] = {
        { "Rock", "Rock", "Draw", 3 },
        { "Paper", "Paper", "Draw", 3 },
        { "Scissors", "Scissors", "Draw", 3 },

        { "Rock", "Paper", "Win", 6 },
        { "Paper", "Scissors", "Win", 6 },
        { "Scissors", "Rock", "Win", 6 },

        { "Rock", "Scissors", "Lose", 0 },
        { "Paper", "Rock", "Lose", 0 },
        { "Scissors", "Paper", "Lose", 0 }
};

char*
char_to_choice(char c)
{
        switch (c) {
                case 'A':
                case 'X':
                        return "Rock";
                case 'B':
                case 'Y':
                        return "Paper";
                case 'C':
                case 'Z':
                        return "Scissors";
                default:
                        printf("Invalid play: %c\n", c);
                        printf("Valid values are A, X, B, Y, C, or Z");
                        exit(1);
        }

}

int
choice_to_score(char *choice)
{
        if (strcmp(choice, "Rock") == 0) {
                return 1;
        } else if (strcmp(choice, "Paper") == 0) {
                return 2;
        } else if (strcmp(choice, "Scissors") == 0) {
                return 3;
        } else {
                printf("Trying to get score of invalid choice: %s", choice);
                exit(1);
        }
}

char*
char_to_round_outcome(char choice)
{
        switch(choice) {
                case 'X':
                        return "Lose";
                case 'Y':
                        return "Draw";
                case 'Z':
                        return "Win";
        }
}

int
calc_total_score_part_1(char *opponent_choice,
                        char *my_choice)
{
        for (int i = 0; i < NUM_GAME_STATES; i++) {
                GameState state = game_states[i];
                if ( strcmp(state.opponent_choice, opponent_choice) == 0
                                && strcmp(state.my_choice, my_choice) == 0)
                {
                        return state.result_points +
                                choice_to_score(my_choice);
                }

        }

        printf("Could not determine outcome score based on opponent choice: %s and your choice: %s", opponent_choice, my_choice);
        exit(1);

}

int
calc_total_score_part_2(char *opponent_choice,
                        char *round_outcome)
{
        for (int i = 0; i < NUM_GAME_STATES; i++) {
                GameState state = game_states[i];
                if ( strcmp(state.opponent_choice, opponent_choice) == 0
                                && strcmp(state.result, round_outcome) == 0)
                {
                        return state.result_points +
                                choice_to_score(state.my_choice);
                }

        }

        printf("Could not determine outcome score based on opponent choice: %s and round outcome: %s", opponent_choice, round_outcome);
        exit(1);
}

int
main(void)
{
        FILE *strat_guide = fopen("input", "r");

        if (strat_guide == NULL) {
                printf("Could not open file.");
                exit(1);
        }

        char round[3];
        char c;
        int i = 0;
        int total_score_part_1 = 0;
        int total_score_part_2 = 0;

        while ( (c = getc(strat_guide)) != EOF) {
                if (c == ' ') {
                        continue;
                } else if (c == '\n') {
                        i = 0;

                        char *opponent_choice =
                                char_to_choice(round[0]);

                        char *my_choice =
                                char_to_choice(round[1]);

                        char *round_outcome =
                                char_to_round_outcome(round[1]);

                        total_score_part_1 +=
                             calc_total_score_part_1(opponent_choice, my_choice);

                        total_score_part_2 +=
                                calc_total_score_part_2(opponent_choice, round_outcome);
                } else {
                        round[i] = c;
                        i++;
                }

        }

        printf("Part 1\n\tTotal score: %d\n", total_score_part_1);
        printf("Part 2\n\tTotal score: %d\n", total_score_part_2);
}
