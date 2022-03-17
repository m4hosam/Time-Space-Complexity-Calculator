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

char *getWhileInfo(int ptrDo, int ptrWhile)
{
    FILE *fileText;
    char ops[20][20] = {""};
    char buf[100] = "";
    char *ptrs[20];
    char tmp[5];
    int j = 0;
    char *complexty = malloc(100);

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return "(1)";
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
        return "1";
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
        printf("buf: %s\n", buf);
        // function
        for (j = 0; j < 6; j++)
        {
            ptrs[j] = strstr(buf, ops[j]);
            printf("ptr: %s\n", ptrs[j]);
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
        strcpy(complexty, "O(n)");
    else if (j > 3 && j < 6)
        strcpy(complexty, "O(logn)");
    else if (j > 5 && j < 8)
        strcpy(complexty, "O(n)");
    else if (j > 7 && j < 10)
        strcpy(complexty, "O(logn)");
    else
        return "1";
    // for (int j = 0; j < 10; j++)
    //     printf("%s ", ops[j]);
    printf("comp1: %s\n", complexty);
    return complexty;
}

char *getDoWhileInfo(int ptr)
{
    FILE *fileText;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
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
    return getWhileInfo(ptr, endDoloop);

    fclose(fileText);
}

char *getForInfo(char buf[])
{
    char *ch = strstr(buf, ";");
    char *ptr[20];
    char *complexty = malloc(100);
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
        return "1";
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
            strcpy(complexty, "O(n)");
        else if (k > 3 && k < 6)
            strcpy(complexty, "O(logn)");
        else if (k > 5 && k < 8)
            strcpy(complexty, "O(n)");
        else if (k > 7 && k < 10)
            strcpy(complexty, "O(logn)");
        else
            return "1";
        // printf("text: %s\n", ptr[k]);
    }
    return complexty;
}

int getFileInfo()
{
    int info[4];
    FILE *fileText;
    char c, check, ch;

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }

    char buf[100];
    int startIndex = ftell(fileText);
    int flag = 0;
    char *ptrs[20];
    int i;

    while ((fgets(buf, 100, fileText)) != NULL)
    {
        for (i = 0; i < 6; i++)
        {
            ptr[i] = strstr(buf, loops[k]);
            if (ptrs[i] != NULL)
                break;
        }

        switch (i)
        {
        case 0:
            /* Do While loop */

            break;
        case 1:
            /* While loop */
            break;
        case 2:
            /* For loop */
            break;
        case 3:
            /* { bracket*/
            break;
        case 4:
            /* } bracket*/
            break;
        case 5:
            /* not interested */
            break;

        default:
            break;
        }

        // char *ptr = strstr(buf, "for");
        // if (ptr != NULL)
        // {
        //     // printf("tell: %d\n", ftell(fileText));
        //     printf("complexty3: %s", getForInfo(buf));
        //     flag = 1;
        //     break;
        // }
        startIndex = ftell(fileText);
    }
    // char *zeda = getDoWhileInfo(startIndex);
    // getDoWhileInfo(startIndex);
    // printf("complexty3: %s", getForInfo(buf));
    fclose(fileText);
}

int main()
{
    char input[20] = "   This is my name";

    // char *a = removeWhiteSpaces(input);
    // printf("%s", a);
    // int count = 0;

    // // to continue the new lines
    // while (token != NULL)
    // {
    //     printf("%s\n\n", token);
    //     count++;
    //     token = strtok(NULL, ' ');
    // }
    // printf("\nYour string has been found %d times %s", count, input);

    getFileInfo();

    // printf("input a text: ");
    // gets(input);

    // printf("Search a string in the text: ");
    // gets(input2);

    // printf("\n\n::>>Search for string:::\n\n");

    // // Search for string inside the string
    // char *s_string = strstr(input, input2);

    // if (s_string == NULL)
    // {
    //     printf("NOT FOUND\n\n");
    // }
    // else
    // {
    //     printf("Found in  index: %d\n\n", s_string - input); // Know the first index
    // }
    // char buf[100] = "for(int k = 0 ; k < n ; k *= 2)";
    // char x = doesContain(buf);
    // printf("x: %c\n", x);
    // getForInfo(buf);

    return 0;
}
