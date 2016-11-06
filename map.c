# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "map.h"

PMap initMap (int width, int height)
{
    int x, y;
    PMap map = malloc(sizeof(Map));
    map->width = width;
    map->height = height;
    map->grid = malloc(sizeof(enum ObjectId *) * height);
    for (x = 0; x < height; x++)
    {
        map->grid[x] = calloc(width, sizeof(enum ObjectId));
    }
    return map;
}

void destroyMap (PMap map)
{
    int x, y;
    for (x = 0; x < map->height; x++)
    {
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

PMap loadMap (char *filename) {
    int width, height;
    int charCount = 0, i, x, y, byteLen;
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL) { perror("Cannot load map"); return NULL; }

    fscanf(file, "%d %d", &width, &height);
    fgetc(file); // Discard the newline
    printf("width %d height %d\n", width, height);

    PMap map = initMap(width, height);

    while ((c = fgetc(file)) != EOF)
    {
        x = charCount / width;
        y = charCount % width;
        //printf("char at (%d,%d): '%c' (0x%X) ", x, y, c, c);
        if (c == '\n' || c == '\r') { putchar('\n'); continue; }
        //retrieve the unicode character
        byteLen = numberOfBytesInChar((unsigned char)c);
        char* s = malloc(sizeof(char)*(byteLen+1));
        s[0] = c;
        for (i = 1; i < byteLen; i++) {
            s[i] = fgetc(file);
            //printf("%c (0x%X) ", map->grid[x][y][i], map->grid[x][y][i]);
        }
        s[byteLen]= '\0';
        printf("%s", s);
        map->grid[x][y] = getObjectId (s);
        charCount++;
    }
    fclose(file);
    printf("width*height %d char_count %d\n", width*height, charCount);
    return map;
}

void displayMap (PMap map)
{
    int x, y;
    printf("Map first char '%d'\n", map->grid[4][0]);
    for (x = 0; x < map->height; x++)
    {
        for (y = 0; y < map->width ; y++)
        {
            enum ObjectId id = map->grid[x][y];
            printf("%s", ID_DISPLAY_MAP[id]);
            //printf("%02d ", id);
            //printf("'%s' (0x%X 0x%X 0x%X 0x%X 0x%X)\n", s, s[0], s[1], s[2], s[3], s[4]);
        }
        putchar('\n');
        //fflush(stdout);
    }
}
