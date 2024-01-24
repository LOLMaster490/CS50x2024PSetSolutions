#include <cs50.h>
#include <stdio.h>

void greetName(string name);

int main(void)
{
    string name;
    do
    {
        name = get_string("What's your name? ");
    }
    while (name[0] == '\0');
    greetName(name);
}

void greetName(string name)
{
    printf("hello, %s\n", name);
}
