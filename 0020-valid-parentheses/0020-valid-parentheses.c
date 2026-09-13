#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    char stack[10000];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {

        // If opening bracket, push it
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[++top] = s[i];
        }

        // If closing bracket
        else {
            // No opening bracket available
            if (top == -1) {
                return false;
            }

            char open = stack[top--];

            // Check if brackets match
            if ((s[i] == ')' && open != '(') ||
                (s[i] == ']' && open != '[') ||
                (s[i] == '}' && open != '{')) {
                return false;
            }
        }
    }

    // Stack must be empty
    return top == -1;
}