#include <stdio.h>
#include <stdlib.h>

char bracket[20] = "";
int bigO[20] = {0};
int sumbigO[20][20] = {0};
int pointer = 0;
int totalelements = 0;
int complextyAsInt;

int isEmptyStack()
{
    if (totalelements == 0)
        return 0;
    else
        return 1;
}

int addToStack(char brack, int complex)
{
    printf("pointer%c -comp %d: %d\n", brack, complex, pointer);
    if (totalelements - 1 >= 0)
    {
        if (bracket[totalelements - 1] != brack)
        {

            // some work
            popFromStack();
            return 1;
        }
        else
        {
            bracket[pointer] = brack;
            bigO[pointer] = complex;
            pointer++;
            totalelements++;
            return 0;
        }
    }
    else
    {
        bracket[pointer] = brack;
        bigO[pointer] = complex;
        pointer++;
        totalelements++;
        return 0;
    }
}

void popFromStack()
{
    if (!isEmptyStack())
    {
        printf("stack Empty");
        return;
    }
    printf("\npop\n");
    int largest = 0;
    int i;
    for (i = 0; i < 20; i++)
    {
        if (sumbigO[pointer - 1][i] > largest)
        {
            largest = sumbigO[pointer - 1][i];
        }
    }
    int newbigO = bigO[pointer - 1];
    printf("new %d p: %d\n", bigO[pointer - 1], pointer - 1);
    if (largest != 0)
    {
        newbigO = bigO[pointer - 1] * largest;
    }
    pointer--;
    totalelements--;
    for (i = 0; i < 20; i++)
    {
        if (sumbigO[pointer - 1][i] == 0)
        {
            sumbigO[pointer - 1][i] = newbigO;
            break;
        }
    }
    if (!isEmptyStack())
    {
        largest = 0;
        for (i = 0; i < 20; i++)
        {
            if (sumbigO[pointer][i] > largest)
            {
                largest = sumbigO[pointer][i];
            }
        }
        if (largest != 0)
        {
            complextyAsInt = bigO[pointer] * largest;
        }
    }
    for (i = 0; i < 20; i++)
    {
        sumbigO[pointer][i] = 0;
    }
}

void printStacks()
{
    printf("Stack Bracket:\n");
    for (int i = 0; i < totalelements; i++)
    {
        printf(" %c ", bracket[i]);
    }
    printf("\nEND Stack;\n");
    printf("Stack BigO:\n");
    for (int i = 0; i < totalelements; i++)
    {
        printf(" %d ", bigO[i]);
    }
    printf("\nEND Stack;\n");
    printf("Stack sumBigO:\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf(" %d ", sumbigO[i][j]);
        }
        printf("\n");
    }
    printf("\nEND Stack;");
}

int main()
{
    addToStack('{', 10);
    addToStack('{', 10);
    addToStack('{', 3);
    addToStack('{', 0);
    addToStack('}', 0);
    addToStack('}', 0);
    printStacks();
    // addToStack('{', 10);
    addToStack('}', 0);
    printStacks();
    // addToStack('{', 3);
    // addToStack('}', 0);
    // printStacks();
    // addToStack('}', 0);
    // printStacks();
    addToStack('{', 10);
    addToStack('}', 0);
    addToStack('}', 0);
    printStacks();

    printf("\nComplexty: %d\n", complextyAsInt);

    return 0;
}
