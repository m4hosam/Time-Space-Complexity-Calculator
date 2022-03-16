#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define text "index.txt"

// Stack Part
char arr[20];
int top = 0;
int elementNumber = 0;
char opsCases[20][20] = {"++", "--", "+=", "-=", "/=", "*=", "+", "-", "/", "*"};

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

int getWhileInfo(int ptr, char varName)
{
    FILE *fileText;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    fseek(fileText, ptr, SEEK_SET);
    char ops[20][20] = {""};
    for (int i = 0; i < 10; i++)
    {
        ops[i][0] = varName;
        strcat(ops[i], opsCases[i]);
    }

    char buf[100];
    char *ptrs[20];
    int k, endDoloop;
    int j;

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
        endDoloop = ftell(fileText);
    }
    if (j < 4)
        printf("O(n)\n");
    else if (j > 3 && j < 6)
        printf("O(log(n))");
    else if (j > 5 && j < 8)
        printf("O(n)");
    else if (j > 7 && j < 10)
        printf("O(log(n))");
    else
        printf("ERROR READING FOR %d", j);
    // for (int j = 0; j < 10; j++)
    //     printf("%s ", ops[j]);
}

int getDoWhileInfo(int ptr)
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

    fseek(fileText, endDoloop, SEEK_SET);
    fgets(buf, 100, fileText);
    char *chr = strstr(buf, "while");
    char *ptr2 = strstr(buf, "(");
    char tmp[5];
    int j = 0;
    if (chr != NULL)
    {
        for (int i = (ptr2 - buf); buf[i] != ')'; i++)
        {
            if (buf[i] != ' ')
            {
                tmp[j] = buf[i];
                j++;
            }
        }
    }
    char vaiableName = tmp[1];
    char itrator = tmp[j - 1];
    if (isdigit(vaiableName) || isdigit(itrator))
    {
        printf("digit means O(1) :) \n");
    }
    else
    {
        printf("O(?) :) \n");
        getWhileInfo(ptr, vaiableName);
    }

    fclose(fileText);
}

void getForInfo(char buf[])
{
    char *ch = strstr(buf, ";");
    char *ptr[20];

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
        printf("digit means O(1) :) \n");
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
            printf("O(n)\n");
        else if (k > 3 && k < 6)
            printf("O(log(n))");
        else if (k > 5 && k < 8)
            printf("O(n)");
        else if (k > 7 && k < 10)
            printf("O(log(n))");
        else
            printf("ERROR READING FOR");
        // printf("text: %s\n", ptr[k]);
    }
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
    int startIndex;
    int flag = 0;

    while ((fgets(buf, 100, fileText)) != NULL)
    {
        char *ptr = strstr(buf, "do{");
        if (ptr != NULL)
        {
            // printf("tell: %d\n", ftell(fileText));
            flag = 1;
            break;
        }
        startIndex = ftell(fileText);
    }
    getDoWhileInfo(startIndex);

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
