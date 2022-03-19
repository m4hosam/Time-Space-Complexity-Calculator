#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complexty.c"
#define text "index.txt"

// Stack Part
char arr[20];
int top = 0;
int elementNumber = 0;
char opsCases[20][20] = {"++", "--", "+=", "-=", "/=", "*=", "+", "-", "/", "*"};
char loops[20][20] = {"do", "while", "for", "{", "}", " "};
char functionTypes[20][20] = {"int", "double", "char", "float", " "};
char functionNames[20][20] = {""};
int functionComplexty[20] = {1};
int spaceComplexty[20] = {1};
int functionNumbers = 0;
int startMainIndex;

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
// End Of Stack Part

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
            printf("Found in  index: %d\n\n", isThere - buf);
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
                printf("O(n)\n");
            }
            if (recursiveLines[1][k] == '/' || recursiveLines[1][k] == '*')
            {
                functionComplexty[functionNumbers - 1] = 3;
                printf("O(logn)\n");
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
        printf("O(2^n)\n");
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

        if (i == 0 && ptrmain != NULL) // int not main()
        {
            startMainIndex = startIndex;
            printf("No other Function Just main\n");
            fclose(fileText);
            return 1;
        }
        else if (i >= 0 && i < 4)
        {
            int comp = strcmp(buf, ptr[i]);
            if (comp == 0)
            {
                printf("We have a function %s\n", ptr[i]);
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
            // printf("ptr:|%s|\n", ptr[i]);
            // printf("buf:|%s|\n", buf);

            // printf("Function Name -%s- \n", functionName);
        }
        else
        {
            printf("not Interested\n");
        }
        startIndex = ftell(fileText);
    }
    fclose(fileText);
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
    int i, q, answer;
    // printf("debug11\n");
    while ((fgets(buf, 100, fileText)) != NULL)
    {
        // printf("debug22\n");
        for (i = 0; i < 6; i++)
        {
            ptrs[i] = strstr(buf, loops[i]);
            if (ptrs[i] != NULL)
                break;
        }
        for (q = 0; q < functionNumbers; q++)
        {
            ptrFunc[q] = strstr(buf, functionNames[q]);
            if (ptrFunc[q] != NULL)
            {
                printf("\n\nFunction Complextiy: %d\n\n", functionComplexty[q]);
                addToStack('{', functionComplexty[q]);
                addToStack('}', 0);
                break;
            }
        }
        // printf("debug33\n");
        char *semicolin = strstr(buf, ";");
        switch (i)
        {
        case 0:
            //  Do While loop
            // printf("debug44\n");

            answer = getDoWhileInfo(startIndex);
            addToStack('{', answer);
            // printf("debug442\n");
            // printf("\nDo While loop Found %d\n\n", answer);
            break;

        case 1:
            //  While loop
            // printf("debug55\n");
            if (semicolin != NULL)
            {
                addToStack('}', 0);
                break;
            }

            answer = getWhileInfo(0, startIndex);
            addToStack('{', answer);
            // printf("debug552\n");
            // printf("\n--While loop Found %d\n\n", answer);
            break;
        case 2:
            //  For loop
            // printf("debug66\n");
            answer = getForInfo(buf);
            addToStack('{', answer);
            // printf("debug662\n");
            // printf("\nFor loop Found %d\n\n", answer);
            break;
        case 3:
            //  { bracket
            // printf("debug77\n");
            addToStack('{', 1);
            // printf("\nbracket '{' Found\n\n");
            break;
        case 4:
            //  } bracket
            // printf("debug88\n");
            addToStack('}', 0);
            // printf("\nbracket '}' Found\n\n");
            break;
        case 5:
            //  not interested
            // printf("debug99\n");
            printf("\nNot Interested\n\n");
            break;

        default:
            break;
        }

        startIndex = ftell(fileText);
    }

    fclose(fileText);
}

void getComplexity()
{
    int counter_n = 0;
    int counter_logn = 0;
    int counter_2n = 0;
    char complex[100];
    // printf("comp:%d\n", complextyAsInt);
    // get n
    if (complextyAsInt == 1)
    {
        strcpy(complex, "O(1)");
        return;
    }
    while (complextyAsInt % 10 == 0)
    {
        // printf("************");
        counter_n++;
        complextyAsInt = complextyAsInt / 10;
    }
    while (complextyAsInt % 3 == 0 && complextyAsInt != 1)
    {
        // printf("************");
        counter_logn++;
        complextyAsInt = complextyAsInt / 3;
    }
    while (complextyAsInt % 313 == 0 && complextyAsInt != 1)
    {
        // printf("************");
        counter_2n++;
        complextyAsInt = complextyAsInt / 313;
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
                        sprintf(complex, "nlog(n)");
                    }
                    else
                    {
                        sprintf(complex, "nlog(n)^%d", counter_logn);
                    }
                }
                else
                {
                    if (counter_logn == 1)
                    {
                        sprintf(complex, "n^%dlog(n)", counter_n);
                    }
                    else
                    {
                        sprintf(complex, "n^%dlog(n)^%d", counter_n, counter_logn);
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
    }
    // get logn

    printf("\n--------------%s-------------\n", complex);
}

int main()
{
    char input[20] = "   This is my name";
    searchForFunctions();
    getFileInfo();
    printf("\ntotal complexty: %d\n", complextyAsInt);
    getComplexity();

    return 0;
}
