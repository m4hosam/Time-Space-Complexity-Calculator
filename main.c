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
    int sequence[20];
    int k = findTheLargest(a);
    printf("Hello %d\n", k);
    editFile();

    printf("%d %d %d %d\n", counter[0], counter[1], counter[2], counter[3]);
    int largest;
    int index = 0;
    for (int k = 10; k < 100000; k = k * 10)
    {
        // function Call
        basicFunction(k);
        // Function Call

        largest = findTheLargest(counter);
        sequence[index] = largest;
        index++;
        printf("%d %d %d %d\n", counter[0], counter[1], counter[2], counter[3]);

        for (int i = 0; i < 20; i++)
            counter[i] = 0;
    }
    float average;
    int totalNum, z;
    for (z = 0; z < 4; z++)
    {
        totalNum = totalNum + sequence[z];
        printf("sequence: %d\n", sequence[z]);
    }

    average = totalNum / z;
    printf("Average: %f, totalnum: %d , z: %d\n", average, totalNum, z);

    if (sequence[0] == sequence[1] && sequence[1] == sequence[2])
        printf("Time Complexty: O(1)\n");

    else if (average > 5 && average < 50)
        printf("Time Complexty: O(logn)\n");
    else if (average > 1000 && average < 10000)
        printf("Time Complexty: O(n)\n");
    else if (average > 100000 && average < 1000000)
        printf("Time Complexty: O(nlogn)\n");
    else
        printf("Time Complexty: Not Specific\n");

    return 0;
}
