#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>

int main(int argc, char *argv[], char *envp[]);
void ShowUsage();
int GetOffsetDigitCount();
int GetColumnCount();
const char *GetColorEscapeSequence();

int main(int argc, char *argv[], char *envp[])
{
    (void) envp;

    // get the input stream
    FILE *input_stream = NULL;

    if (isatty(fileno(stdin)) == 0)
        input_stream = stdin;

    else
    {
        if (argc != 2)
        {
            ShowUsage();
            return 1;
        }

        input_stream = fopen(argv[1], "rb");
        if (input_stream == NULL)
        {
            fprintf(stderr, "Failed to open the input file\n");
            return 1;
        }
    }

    // get the configuration
    int offset_digit_count = GetOffsetDigitCount();
    int column_count = GetColumnCount();
    const char *color_escape_sequence = GetColorEscapeSequence();

    // print the top header
    printf("%*s    ", offset_digit_count, "");

    for (int i = 0; i < column_count; i++)
        printf("%02X ", i);

    printf("\n");

    // print each line
    uintptr_t current_offset = 0;
    int current_column = 0;

    while (true)
    {
        uint8_t current_byte;
        if (fread(&current_byte, 1, 1, input_stream) != 1)
            break;

        if (current_column == 0)
            printf("%0*" PRIXPTR "    ", offset_digit_count, current_offset);

        if (isalnum(current_byte) != 0)
            printf("%s.%c%s ", color_escape_sequence, (char) current_byte, "\033[0m");

        else if (isspace(current_byte) != 0)
            printf(".. ");

        else
            printf("%02X ", (int) current_byte);

        current_column++;
        if (current_column >= column_count)
        {
            printf("\n");
            current_column = 0;
        }

        fflush(stdout);
        current_offset++;
    }

    fclose(input_stream);
    printf("\n");

    return 0;
}

void ShowUsage()
{
    const char *usage =
        "Simple tool that dumps binary data in HexII* format.\n"
        "\n"
        "You can tweak how the output is printed using the following environment variables:\n"
        "\n"
        "\tOffset digits:\tHEXLL_OFFSETDIGITCOUNT\n"
        "\tColumn count:\tHEXLL_COLUMNCOUNT\n"
        "\tText color:\tHEXLL_COLORESCAPESEQUENCE\n"
        "\n"
        "Usage:\n"
        "\thexll /path/to/input_file\n"
        "\tcat /path/to/input_file | hexll\n"
        "\n"
        "The HexII notation has been invented by Ange Albertini (https://github.com/corkami)\n";

    fprintf(stderr, "%s", usage);
}

int GetOffsetDigitCount()
{
    const int default_value = 16;

    const char *offset_digit_count = getenv("HEXLL_OFFSETDIGITCOUNT");
    if (offset_digit_count == NULL)
        return default_value;

    char *null_terminator;
    long int value = strtol(offset_digit_count, &null_terminator, 10);
    if (value == 0L && null_terminator[0] != 0)
        return default_value;

    return (int) value;
}

int GetColumnCount()
{
    const int default_value = 16;

    const char *column_count = getenv("HEXLL_COLUMNCOUNT");
    if (column_count == NULL)
        return default_value;

    char *null_terminator;
    long int value = strtol(column_count, &null_terminator, 10);
    if (value == 0L && null_terminator[0] != 0)
        return default_value;

    return (int) value;
}

const char *GetColorEscapeSequence()
{
    // default is red
    const char *default_color = "\x1B[31m";

    const char *color_escape_sequence = getenv("HEXLL_COLORESCAPESEQUENCE");
    if (color_escape_sequence == NULL)
        return default_color;

    return color_escape_sequence;
}
