/*
   @utor Andrés Bonilla Gómez
   Date 24 julio 2018
   Language C, probar en algún linux
   gcc ruta3.c -o ruta3.out
   Programa que lee una cadena que sea una ruta existente, y se desplegara la lista de archivos de cada carpeta
   y sub carpeta
*/




#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

char *inputString(FILE* fp, size_t size);
void listdir(const char *name, int indent);


/*
 @utor Lloyd Macrohon
 From https://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux
*/
void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}


char *inputString(FILE* fp, size_t size)
{
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n')
    {
        str[len++]=ch;
        if(len==size)
        {
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

int main(void) 
{
    char *ruta ;
    printf("Ingresa la ruta: \n");
    ruta = inputString(stdin, 10);
    listdir(ruta, 0);
    return 0;
}
