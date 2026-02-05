
/*
 * SpeedQuiz - A simple quiz game*/

#include <stdio.h>
#include <time.h>
#include <ctype.h>  // Required for toupper() function

// Function declarations
void showMenu();
void showResults(int correctCount);
int askQuestion(char *question, char options[4][30], char correctAnswer);

int main() {
    // Variables
    int choice;
    int correctCount = 0;
    int i;

    // Quiz categories and questions
    char *questions[3][5] = {
        // General Knowledge Questions
        {
            "What is the capital of Turkey?",
            "What is the largest ocean in the world?",
            "What is the largest organ in the human body?",
            "Which of these is not a neighbor of Turkey?",
            "Who is the founder of the Ottoman Empire?"
        },
        // Math Questions
        {
            "What is the result of 3 x 8 + 4?",
            "What is the sum of interior angles in a triangle?",
            "What is the square root of 9?",
            "What is 25%% of 80?",
            "What is the result of 2^4?"
        },
        // Computer Questions
        {
            "Which character starts a comment line in C language?",
            "Which of the following is not a loop?",
            "What does RAM stand for?",
            "Which of the following is not an operating system?",
            "How many bits are in a byte?"
        }
    };

    // Multiple choice options - each row for one question
    char *options[3][5][4] = {
        // General Knowledge options
        {
            {"A) Istanbul", "B) Ankara", "C) Izmir", "D) Bursa"},
            {"A) Atlantic", "B) Indian", "C) Pacific", "D) Arctic"},
            {"A) Heart", "B) Brain", "C) Skin", "D) Liver"},
            {"A) Iraq", "B) Syria", "C) Ukraine", "D) Iran"},
            {"A) Fatih", "B) Kanuni", "C) Osman Bey", "D) Bayezid"}
        },
        // Math options
        {
            {"A) 28", "B) 36", "C) 24", "D) 32"},
            {"A) 90", "B) 180", "C) 270", "D) 360"},
            {"A) 3", "B) 2", "C) 4", "D) 6"},
            {"A) 20", "B) 16", "C) 8", "D) 40"},
            {"A) 8", "B) 16", "C) 32", "D) 64"}
        },
        // Computer options
        {
            {"A) //", "B) /*", "C) #", "D) --"},
            {"A) for", "B) while", "C) if", "D) do-while"},
            {"A) Random Access Memory", "B) Read Access Memory", "C) Random Array Memory", "D) Read Array Method"},
            {"A) Windows", "B) Ubuntu", "C) Excel", "D) macOS"},
            {"A) 4", "B) 8", "C) 16", "D) 32"}
        }
    };

    // Correct answers table - for each category and question
    char correctAnswers[3][5] = {
        {'B', 'C', 'C', 'C', 'C'},  // General Knowledge
        {'A', 'B', 'A', 'A', 'B'},  // Math
        {'A', 'C', 'A', 'C', 'B'}   // Computer
    };

    // Introduction and rules at the beginning of the program
    printf("***** SpeedQuiz Game *****\n\n");
    printf("RULES:\n");
    printf("- Choose one of the categories\n");
    printf("- Each category has 5 questions\n");
    printf("- Answer each question within 30 seconds\n");
    printf("- Then you can see your result\n\n");

    // Main loop
    do {
        // Call the show menu function
        showMenu();
        scanf("%d", &choice);

        // Invalid selection check
        if(choice < 1 || choice > 4) {
            printf("Invalid choice! Please enter a number between 1 and 4.\n");
            continue;
        }

        // Exit selected?
        if(choice == 4) {
            printf("Exiting the program...\n");
            break;
        }

        // Let's start the quiz
        printf("\n***** Quiz Starting *****\n");
        correctCount = 0;  // Reset correct count

        // Ask 5 questions
        for(i = 0; i < 5; i++) {
            printf("\nQuestion %d: ", i+1);

            // Ask each question using the function
            char tempOptions[4][30];
            int j;
            for(j = 0; j < 4; j++) {
                // Copy options
                int k = 0;
                while(options[choice-1][i][j][k] != '\0' && k < 29) {
                    tempOptions[j][k] = options[choice-1][i][j][k];
                    k++;
                }
                tempOptions[j][k] = '\0';
            }

            int result = askQuestion(questions[choice-1][i], tempOptions, correctAnswers[choice-1][i]);
            if(result == 1) {
                correctCount++;
            }
        }

        // Call the show results function
        showResults(correctCount);

    } while(1);  // Infinite loop, exits with break when exit is selected

    return 0;
}

// Show menu function
void showMenu() {
    printf("\nCHOOSE CATEGORY:\n");
    printf("1. General Knowledge\n");
    printf("2. Math\n");
    printf("3. Computer\n");
    printf("4. Exit\n");
    printf("Your choice (1-4): ");
}

// Show results function
void showResults(int correctCount) {
    printf("\n***** QUIZ RESULTS *****\n");
    printf("Total Questions: 5\n");
    printf("Correct Answers: %d\n", correctCount);
    printf("Wrong Answers: %d\n", 5-correctCount);
    printf("Success Rate: %.1f%%\n", (float)correctCount/5*100);

    // Add a simple comment
    if(correctCount == 5) {
        printf("Perfect! You got all of them right!\n");
    } else if(correctCount >= 3) {
        printf("Good! You can do even better with a bit more study.\n");
    } else {
        printf("You need to study more!\n");
    }
}

// Ask question function - returns 1 if correct, 0 if wrong/time's up
int askQuestion(char *question, char options[4][30], char correctAnswer) {
    char answer;
    time_t start, now;
    double duration;
    int i;

    // Show the question and options
    printf("%s\n", question);
    for(i = 0; i < 4; i++) {
        printf("%s\n", options[i]);
    }

    // Start timing
    time(&start);

    // Get the answer
    printf("Your answer (A/B/C/D): ");
    scanf(" %c", &answer);
    answer = toupper(answer);  // Convert lowercase to uppercase

    // Check the time
    time(&now);
    duration = difftime(now, start);

    // Time's up?
    if(duration > 30) {
        printf("TIME'S UP! You must answer within 30 seconds.\n");
        return 0;  // Consider as wrong
    }

    // Check the answer
    if(answer == correctAnswer) {
        printf("CORRECT! You answered in %.1f seconds.\n", duration);
        return 1;  // Correct
    } else {
        printf("WRONG! The correct answer was: %c.\n", correctAnswer);
        return 0;  // Wrong
    }
}
