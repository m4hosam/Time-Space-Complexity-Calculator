#include <stdio.h>
#include <stdlib.h>
#include "source.c"
#define text "index.txt"
#define sourceFile "source.c"

int findTheLargest(int arr[])
{
    int largest = 0;
    for (int i = 0; i < 20; i++)
    {
        if (largest < arr[i])
        {
            largest = arr[i];
        }
    }
    return largest;
}

int getFileInfo(int info[])
{

    FILE *fileText;
    char c, check, ch;
    ;
    // int functionNameStart, functionNameEnd, functionStart, argumentNum = 1;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    c = fgetc(fileText);

    while (c != '(')
        c = fgetc(fileText);

    info[1] = ftell(fileText);

    check = fgetc(fileText);
    while (check != ' ')
    {
        fseek(fileText, -2, SEEK_CUR);
        check = fgetc(fileText);
    }

    info[0] = ftell(fileText);

    ch = fgetc(fileText);
    while (ch != '(')
        ch = fgetc(fileText);

    while (ch != '{')
    {
        if (ch == ',')
            info[3]++;
        ch = fgetc(fileText);
    }
    info[2] = ftell(fileText);
    info[3]++;

    fclose(fileText);
}

int editFile()
{
    FILE *fileText, *fileSource;
    char ch;
    char buf[100];
    int info[4] = {0};
    int indexf;

    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }

    if ((fileSource = fopen(sourceFile, "w+")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }

    fprintf(fileSource, "int counter[20] = {0};\n\n");

    // Getting the pointer information

    ch = fgetc(fileText);
    while (ch != ' ')
    {
        fputc(ch, fileSource);
        ch = fgetc(fileText);
        // indexf = ftell(fileText);
    }

    fprintf(fileSource, " basicFunction(");

    while (ch != '(')
        ch = fgetc(fileText);

    ch = fgetc(fileText);
    while (ch != '{')
    {
        fputc(ch, fileSource);
        ch = fgetc(fileText);
    }

    fprintf(fileSource, "\n{\n\tcounter[0]++;\n");

    int i = 1;
    ch = fgetc(fileText);
    while (ch != EOF)
    {

        fputc(ch, fileSource);
        if (ch == '{')
        {
            fprintf(fileSource, "\n\tcounter[%d]++;\n", i);
            i++;
        }
        ch = fgetc(fileText);
        if (ch == '}')
        {
            fprintf(fileSource, "\n\tcounter[%d]++;\n", i);
            i++;
        }
    }

    fclose(fileText);
    fclose(fileSource);
}

int main()
{
    int a[20] = {1, 2, 3, 25, 12, 1, 0, 0, 0};
    int k = findTheLargest(a);
    printf("Hello %d\n", k);
    editFile();

    // printf("%d %d %d %d\n", counter[0], counter[1], counter[2], counter[3]);
    // int largest;
    // for (int k = 10; k < 100000; k = k * 10)
    // {
    //     sumtest(k, k, k);
    //     for (int j = 0; j < 5; j++)
    //     {
    //         printf("size[%d] ->counter[%d]: %d\n", k, j, counter[j]);
    //     }
    //     printf("\nsecond set\n\n");
    //     counter[0] = 0;
    //     counter[1] = 0;
    //     counter[2] = 0;
    //     counter[3] = 0;
    //     counter[4] = 0;
    // }

    return 0;
}
