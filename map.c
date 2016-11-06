# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "map.h"

Map* initMap (int width, int height)
{
    int x, y;
    Map *map = malloc(sizeof(Map));
    map->width = width;
    map->height = height;
    map->grid = malloc(sizeof(char**) * height);
    for (x = 0; x < height; x++)
    {
        map->grid[x] = malloc(sizeof(char*) * width);
        for (y = 0; y < width; y++)
            map->grid[x][y] = calloc(5, sizeof(char));
    }
    return map;
}

void destroyMap (Map *map)
{
    int x, y;
    for (x = 0; x < map->height; x++)
    {
        for (y = 0; y < map->width; y++)
            free(map->grid[x][y]);
        free(map->grid[x]);
    }
    free(map->grid);
    free(map);
}

/* Returns the number of bytes in the unicode char based on current code unit */
int numberOfBytesInChar (unsigned char val) {
    if (val < 128) return 1;
    else if (val < 224) return 2;
    else if (val < 240) return 3;
    else return 4;
}

Map* loadMap (char *filename) {
    int width, height;
    int charCount = 0, i, x, y, byteLen;
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL) { perror("Cannot load map"); return NULL; }

    fscanf(file, "%d %d", &width, &height);
    fgetc(file); // Discard the newline
    printf("width %d height %d\n", width, height);

    Map* map = initMap(width, height);

    while ((c = fgetc(file)) != EOF)
    {
        x = charCount / width;
        y = charCount % width;
        //printf("char at (%d,%d): '%c' (0x%X) ", x, y, c, c);
        if (c == '\n' || c == '\r') { putchar('\n'); continue; }
        byteLen = numberOfBytesInChar((unsigned char)c);
        //map->grid[x][y] = malloc(sizeof(char)*(byteLen+1));
        map->grid[x][y][0] = c;
        for (i = 1; i < byteLen; i++) {
            map->grid[x][y][i] = fgetc(file);
            //printf("%c (0x%X) ", map->grid[x][y][i], map->grid[x][y][i]);
        }
        map->grid[x][y][byteLen] = '\0';
        printf("%s", map->grid[x][y]);
        charCount++;
    }
    fclose(file);
    printf("width*height %d char_count %d\n", width*height, charCount);
    return map;
}

void displayMap (Map *map)
{
    int x, y;
    printf("Map first char '%s'\n", map->grid[4][0]);
    for (x = 0; x < map->height; x++)
    {
        for (y = 0; y < map->width ; y++)
        {
            char *s = map->grid[x][y];
            printf("%s", s);
            //printf("'%s' (0x%X 0x%X 0x%X 0x%X 0x%X)\n", s, s[0], s[1], s[2], s[3], s[4]);
        }
        putchar('\n');
        //fflush(stdout);
    }
}

void loadDisplayMap (char * filename)
{
    FILE * file = fopen(filename, "r");
    if (file == NULL) { perror("Cannot load map"); return; }

    char c;
    while ((c = fgetc(file)) != EOF)
    {
        putchar(c);
    }
}
