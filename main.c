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

int getFileInfo()
{

    FILE *fileText;
    char c, check, ch;
    ;
    int functionNameStart, functionNameEnd, functionStart, argumentNum;
    if ((fileText = fopen(text, "r")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    c = fgetc(fileText);

    while (c != '(')
        c = fgetc(fileText);

    functionNameEnd = ftell(fileText);

    check = fgetc(fileText);
    while (check != ' ')
    {
        fseek(fileText, -2, SEEK_CUR);
        check = fgetc(fileText);
    }

    functionNameStart = ftell(fileText);

    ch = fgetc(fileText);
    while (ch != '(')
        ch = fgetc(fileText);

    while (ch != ')')
    {
        if (ch == ',')
            argumentNum++;
        ch = fgetc(fileText);
    }

    fclose(fileText);
}

int editFile()
{
    FILE *fileText, *fileSource;
    char alltext[2000] = "";
    char ch;
    char buf[1000];

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

    ch = fgetc(fileText);
    while (ch != EOF)
    {
        fputc(ch, fileSource);
        ch = fgetc(fileText);
    }

    // while ((ch = fgetc(fileText)) != EOF)
    // {
    //     perror("Message from perror");
    //     fputc(ch, sourceFile);
    //     // perror("Message from perror");
    // }

    // while ((fgets(buf, 1000, file)) != NULL)
    // {
    //     alltext = alltext + buf;
    // }
    // fseek(file, 0, SEEK_SET);
    // fprintf(file, "int counter[20] = {0};\n");
    // printf("%s", alltext);
    fclose(fileText);
    fclose(fileSource);

    if ((fileSource = fopen(sourceFile, "a")) == NULL)
    {
        printf("Error Opening\n");
        return (1);
    }
    fclose(fileSource);
}

int main()
{
    int a[20] = {1, 2, 3, 25, 12, 1, 0, 0, 0};
    int k = findTheLargest(a);
    printf("Hello %d\n", k);
    editFile();

    printf("%d %d %d %d\n", counter[0], counter[1], counter[2], counter[3]);
    int largest;
    for (int k = 10; k < 100000; k = k * 10)
    {
        sumtest(k, k, k);
        for (int j = 0; j < 5; j++)
        {
            printf("size[%d] ->counter[%d]: %d\n", k, j, counter[j]);
        }
        printf("\nsecond set\n\n");
        counter[0] = 0;
        counter[1] = 0;
        counter[2] = 0;
        counter[3] = 0;
        counter[4] = 0;
    }

    return 0;
}
