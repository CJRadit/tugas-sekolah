#include <stdio.h>
#include <string.h>
// #include <unistd.h>

int main()
{
    char text[32] = "Test";
    char text2[32] = "Texts";

    // pwd = getpass("Password: ");
    // printf("Your password: %s\n", pwd);

    printf("%s, %s, %d\n", text, text2, strcmp(text, text2));

    if (strcmp(text, text2))
    {
        printf("aa");
    }
    else
    {
        printf("bb");
    }

    return 0;
}