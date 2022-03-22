#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define text "index.txt"

// Stack vairables
char arr[20];
int top = 0;
int elementNumber = 0;
// complexity stack variables
char bracket[20] = "";
int bigO[20] = {0};
int sumbigO[20][20] = {0};
int pointer = 0;
int totalelements = 0;
int complextyAsInt;
// String arrays are used for searching
char opsCases[20][20] = {"++", "--", "+=", "-=", "/=", "*=", "+", "-", "/", "*"};
char loops[20][20] = {"do", "while", "for", "{", "}", " "};
char functionTypes[20][20] = {"int", "double", "char", "float", " "};
// Finding the functions and store to the array
char functionNames[50][50] = {""};
int functionComplexty[20] = {1};
// Used for space complexity
int spaceComplexty[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int spacecounter = 0;
int functionNumbers = 0;
// getting the main index of main function
int startMainIndex = 0;

// bracket stack function
int isEmpty()
{
    if (elementNumber == 0)
        return 0;
    else
        return 1;
}
void printStack()
{
    printf("Stack:\n");
    for (int i = elementNumber; i >= 0; i--)
    {
        printf("%c\n", arr[i]);
    }
    printf("END Stack\n");
}

int add(char data)
{
    if (elementNumber - 1 >= 0)
    {
        if (arr[elementNumber - 1] != data)
        {
            pop();
            return 1;
        }
        else
        {
            arr[top] = data;
            top++;
            elementNumber++;
            return 0;
        }
    }
    else
    {
        arr[top] = data;
        top++;
        elementNumber++;
        return 0;
    }
}

int pop()
{
    if (!isEmpty())
    {
        printf("stack Empty");
        return 0;
    }
    char data = arr[top - 1];
    top--;
    elementNumber--;
    return data;
}

// complexity Stack part

int isEmptyStack()
{
    if (totalelements == 0)
        return 0;
    else
        return 1;
}

int addToStack(char brack, int complex)
{
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
        complextyAsInt = sumbigO[pointer][0];
    }
    for (i = 0; i < 20; i++)
    {
        sumbigO[pointer][i] = 0;
    }
}

// Help Method
char doesContain(char buf[])
{
    char *ptr1 = strstr(buf, "{");
    char *ptr2 = strstr(buf, "}");

    if (ptr1 != NULL && ptr2 != NULL)
    {
        return '0';
    }
    else if (ptr1 != NULL)
    {
        return '{';
    }
    else if (ptr2 != NULL)
    {
        return '}';
    }
    return '0';
}

char *removeWhiteSpaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

int getWhileInfo(int ptrDo, int ptrWhile)
{
    FILE *fileText;
    char ops[20][20] = {""};
    char buf[100] = "";
    char *ptrs[20];
    char tmp[5];
    int j = 0;
    // char *complexty = malloc(100);
    int complexty;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return 0;
    }
    fseek(fileText, ptrWhile, SEEK_SET);
    fgets(buf, 100, fileText);
    strcpy(buf, removeWhiteSpaces(buf));
    char *ptr2 = strstr(buf, "(");

    for (int i = (ptr2 - buf); buf[i] != ')'; i++)
    {
        tmp[j] = buf[i];
        j++;
    }

    char vaiableName = tmp[1];
    char itrator = tmp[j - 1];
    if (isdigit(vaiableName) || isdigit(itrator))
    {
        fclose(fileText);
        return 1;
    }

    if (ptrDo == 0)
    {
        fseek(fileText, ptrWhile, SEEK_SET);
    }
    else
    {
        fseek(fileText, ptrDo, SEEK_SET);
    }

    for (int i = 0; i < 10; i++)
    {
        ops[i][0] = vaiableName;
        strcat(ops[i], opsCases[i]);
    }

    while ((fgets(buf, 100, fileText)) != NULL)
    {
        removeWhiteSpaces(buf);
        // printf("buf: %s\n", buf);
        // function
        for (j = 0; j < 6; j++)
        {
            ptrs[j] = strstr(buf, ops[j]);
            // printf("ptr: %s\n", ptrs[j]);
            if (ptrs[j] != NULL)
                break;
        }
        if (j < 6)
            break;

        char x = doesContain(buf);

        if (x != '0')
        {
            add(doesContain(buf));
            if (!isEmpty())
                break;
        }
    }
    if (j < 4)
        complexty = 10;
    else if (j > 3 && j < 6)
        complexty = 3;
    // else if (j > 5 && j < 8)
    //     complexty = 10;
    // else if (j > 7 && j < 10)
    //     complexty = 3;
    else
    {
        fclose(fileText);
        return 1;
    }

    // for (int j = 0; j < 10; j++)
    //     printf("%s ", ops[j]);
    // printf("comp1: %d\n", complexty);
    fclose(fileText);
    return complexty;
}

int getDoWhileInfo(int ptr)
{
    FILE *fileText;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return 0;
    }
    fseek(fileText, ptr, SEEK_SET);

    char buf[100];
    int endDoloop;

    while ((fgets(buf, 100, fileText)) != NULL)
    {

        char x = doesContain(buf);

        if (x != '0')
        {
            add(doesContain(buf));
            if (!isEmpty())
                break;
        }
        endDoloop = ftell(fileText);
    }

    // printf("co2: %s\n", getWhileInfo(ptr, endDoloop));

    fclose(fileText);
    return getWhileInfo(ptr, endDoloop);
}

int getForInfo(char buf[])
{
    char *ch = strstr(buf, ";");
    char *ptr[20];
    // char *complexty = malloc(100);
    int complexty;
    int index = ch - buf + 1;
    char tmp = buf[index];
    for (int i = index; buf[i] != ';'; i++)
    {
        if (buf[i] != ' ')
            tmp = buf[i];
    }
    // printf("%c\n", tmp);
    if (isdigit(tmp))
    {
        return 1;
    }
    else
    {
        int k;
        for (k = 0; k < 10; k++)
        {
            ptr[k] = strstr(buf, opsCases[k]);
        }
        for (k = 0; k < 12; k++)
        {
            if (ptr[k] != NULL)
                break;
        }
        if (k < 4)
            complexty = 10;
        else if (k > 3 && k < 6)
            complexty = 3;
        else if (k > 5 && k < 8)
            complexty = 10;
        else if (k > 7 && k < 10)
            complexty = 3;
        else
        {
            return 1;
        }
        // printf("text: %s\n", ptr[k]);
    }
    return complexty;
}

void findRecursive(int ptr, char functionName[])
{
    FILE *fileText;

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    fseek(fileText, ptr, SEEK_SET);
    char buf[100];
    char recursiveLines[20][200];
    int endFunction;
    char *isThere;
    int count = 0;

    while ((fgets(buf, 100, fileText)) != NULL)
    {

        char x = doesContain(buf);
        if (x != '0')
        {
            add(doesContain(buf));
            if (!isEmpty())
                break;
        }
        isThere = strstr(buf, functionName);

        while (isThere != NULL)
        {
            // printf("Found in  index: %d\n\n", isThere - buf);
            strcpy(recursiveLines[count], isThere);
            count++;
            isThere = strstr(isThere + 1, functionName);
        }
        endFunction = ftell(fileText);
    }
    int flag = 0;
    if (count == 2)
    {
        removeWhiteSpaces(recursiveLines[1]);
        for (int k = 0; recursiveLines[1][k] != ')'; k++)
        {
            if (recursiveLines[1][k] == '-')
            {
                functionComplexty[functionNumbers - 1] = 10;
                // printf("O(n)\n");
            }
            if (recursiveLines[1][k] == '/' || recursiveLines[1][k] == '*')
            {
                functionComplexty[functionNumbers - 1] = 3;
                // printf("O(logn)\n");
            }
        }
    }
    else if (count > 2)
    {
        for (int j = 1; j < count; j++)
        {
            removeWhiteSpaces(recursiveLines[j]);
            for (int k = 0; recursiveLines[j][k] != ')'; k++)
            {
                if (recursiveLines[j][k] == '-')
                {
                    flag++;
                }
            }
        }
    }
    if (flag == 2)
    {
        functionComplexty[functionNumbers - 1] = 313;
        // printf("O(2^n)\n");
    }

    else if (flag == 3)
    {
        functionComplexty[functionNumbers - 1] = 409;
        printf("O(3^n)\n");
    }

    fclose(fileText);
}

int searchForFunctions()
{
    FILE *fileText;

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    char buf[100];
    char functionName[20];
    char *ptr[20];
    char *ptrmain;
    int i;
    int startIndex = ftell(fileText);

    while ((fgets(buf, 100, fileText)) != NULL)
    {
        ptrmain = strstr(buf, "main(");
        for (i = 0; i < 5; i++)
        {
            ptr[i] = strstr(buf, functionTypes[i]);
            if (ptr[i] != NULL)
                break;
        }

        if (i == 0 && ptrmain != NULL) // int main()
        {
            startMainIndex = startIndex;
            // printf("No other Function Just main\n");
            fclose(fileText);
            return 1;
        }
        else if (i >= 0 && i < 4)
        {
            int comp = strcmp(buf, ptr[i]);
            if (comp == 0)
            {
                // printf("We have a function %s\n", ptr[i]);
                int k, z;
                for (k = 0; k < strlen(ptr[i]); k++)
                {
                    if (ptr[i][k] == ' ')
                        break;
                }
                int j = 0;
                for (z = k + 1; ptr[i][z] != '('; z++)
                {
                    functionName[j] = ptr[i][z];
                    j++;
                }
                functionName[j] = '\0';
                removeWhiteSpaces(functionName);
                strcpy(functionNames[functionNumbers], functionName);
                functionNumbers++;
                findRecursive(startIndex, functionName);
            }
        }
        startIndex = ftell(fileText);
    }
    fclose(fileText);
}

int getSpaceComplexity(char buf[])
{
    int k;
    for (k = 0; k < strlen(buf); k++)
    {
        if (buf[k] == '[')
        {
            if (!isdigit(buf[k + 1]))
            {
                spaceComplexty[spacecounter] = spaceComplexty[spacecounter] * 10;
                return getSpaceComplexity(buf + k + 1);
            }
        }
        else if (buf[k] == ',')
        {
            spacecounter++;
            return getSpaceComplexity(buf + k + 1);
        }
    }
    spacecounter++;
}

int getSpaceComplexityTotal()
{
    int total = 0;
    for (int i = 0; i < 20; i++)
    {
        if (spaceComplexty[i] > total)
        {
            total = spaceComplexty[i];
        }
    }
    return total;
}

int getFileInfo()
{
    int info[4];
    FILE *fileText;

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    fseek(fileText, startMainIndex, SEEK_SET);
    char buf[100];
    int startIndex = ftell(fileText);
    int flag = 0;
    char *ptrs[20];
    char *ptrFunc[20];
    char *ptrDataTypes[20];
    int i, q, j, answer;
    while ((fgets(buf, 100, fileText)) != NULL)
    {
        // searching for loops in buf
        for (i = 0; i < 6; i++)
        {
            ptrs[i] = strstr(buf, loops[i]);
            if (ptrs[i] != NULL)
                break;
        }
        // searching for fanction calls at every line
        for (q = 0; q < functionNumbers; q++)
        {
            ptrFunc[q] = strstr(buf, functionNames[q]);
            if (ptrFunc[q] != NULL)
            {
                flag++;
                addToStack('{', functionComplexty[q]);
                addToStack('}', 0);
                spaceComplexty[spacecounter] = functionComplexty[q];
                spacecounter++;
                break;
            }
        }
        // search for space complexity
        for (j = 0; j < 4; j++)
        {
            ptrDataTypes[j] = strstr(buf, functionTypes[j]);
            if (ptrDataTypes[j] != NULL)
            {
                getSpaceComplexity(ptrDataTypes[j]);
                break;
            }
        }

        char *semicolin = strstr(buf, ";");
        switch (i)
        {
        case 0:
            //  Do While loop
            flag++;
            answer = getDoWhileInfo(startIndex);
            addToStack('{', answer);
            break;

        case 1:
            //  While loop
            if (semicolin != NULL)
            {
                addToStack('}', 0);
                break;
            }
            flag++;
            answer = getWhileInfo(0, startIndex);
            addToStack('{', answer);
            break;
        case 2:
            //  For loop
            flag++;
            answer = getForInfo(buf);
            addToStack('{', answer);
            break;
        case 3:
            //  { bracket
            addToStack('{', 1);
            break;
        case 4:
            //  } bracket
            addToStack('}', 0);
            break;
        case 5:
            //  not interested
            break;

        default:
            break;
        }

        startIndex = ftell(fileText);
    }
    if (flag == 0)
    {
        complextyAsInt = 1;
    }

    fclose(fileText);
}

char *getComplexity(int complexity)
{
    int counter_n = 0;
    int counter_logn = 0;
    int counter_2n = 0;
    char *complex = malloc(100);
    // printf("comp:%d\n", complextyAsInt);
    // get n
    if (complexity == 1)
    {
        strcpy(complex, "O(1)");
        return complex;
    }
    while (complexity % 10 == 0)
    {
        counter_n++;
        complexity = complexity / 10;
    }
    while (complexity % 3 == 0 && complexity != 1)
    {
        counter_logn++;
        complexity = complexity / 3;
    }
    while (complexity % 313 == 0 && complexity != 1)
    {
        counter_2n++;
        complexity = complexity / 313;
    }
    if (counter_2n == 0)
    {
        // nlogn
        if (counter_n != 0)
        {
            if (counter_logn != 0) // logn
            {
                if (counter_n == 1)
                {
                    if (counter_logn == 1)
                    {
                        sprintf(complex, "n*log(n)");
                    }
                    else
                    {
                        sprintf(complex, "n*log(n)^%d", counter_logn);
                    }
                }
                else
                {
                    if (counter_logn == 1)
                    {
                        sprintf(complex, "n^%d*log(n)", counter_n);
                    }
                    else
                    {
                        sprintf(complex, "n^%d*log(n)^%d", counter_n, counter_logn);
                    }
                }
            }
            else
            {
                if (counter_n == 1)
                {
                    sprintf(complex, "n");
                }
                else
                {
                    sprintf(complex, "n^%d", counter_n);
                }
            }
        }
        else
        {
            if (counter_logn == 1)
            {
                sprintf(complex, "log(n)");
            }
            else
            {
                sprintf(complex, "log(n)^%d", counter_logn);
            }
        }
    }
    // get logn

    return complex;
}

int main()
{
    searchForFunctions();
    getFileInfo();

    int spaceComp = getSpaceComplexityTotal();
    if (startMainIndex != 0)
    {
        printf("---space Complexity: %s\n\n", getComplexity(spaceComp));
        printf("---Time Complexity: %s\n\n", getComplexity(complextyAsInt));
    }
    else
    {
        printf("Error No Main function Found\n\n");
    }

    return 0;
}
