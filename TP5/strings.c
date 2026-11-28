#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
// manipuler pointeur via const, ce qui a l interieur ne vas pas etre modifier
// '/0' = char NULL donc tant qu'on rencontre pas l'octet null on continue sinon on return
int str_len(const char* word) {
    int count = 0;
    while (word[count] != '\0') {
        count++;
    }
    return count;
}

void print_str(const char* word) {
    printf("%s\n", word);
}

int str_equals(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

void str_concat(char* dest, const char* a, const char* b) {
    int i = 0;
    int j = 0;

    while (a[i] != '\0') {
        dest[i] = a[i];
        i++;
    }
    while (b[j] != '\0') {
        //i+j pour ne pas ecraser le debut du mot
        dest[i + j] = b[j];
        j++;
    }
    dest[i + j] = '\0';
}

int str_contains(const char* haystack, const char* needle) {
    int i = 0;
    while (haystack[i] != '\0') {
      int j = 0;
      while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
          j++;
      }
      if (needle[j] == '\0') {
          return 1;
      }
      i++;
    }
    return 0;
}

int str_count_chars(const char* s, char c) {
    int i = 0;
    int count = 0;
    while (s[i] != '\0')
    {
        if (s[i] == c) {
            count++;
        }
        i++;
    }
    return count;
}

void str_replace(char* dest, const char* src, char from, char to) {
    int i = 0;
    int j = 0;
    
    while (src[i] != '\0') {
        if (src[i] == from)
        {
            dest[j] = to;
        }
        else
        {
            dest[j] = src[i];
        }
        i++;
        j++;
    }
    dest[j] = '\0';
}

int str_split(const char* s, char sep, char parts[][256], int max_parts) {
    int i = 0; 
    int j = 0;
    int k = 0;

    while (s[i] != '\0') {
        // on copie dans le tableau si c est pas un separateur
        if(s[i] != sep) {
            parts[j][k] = s[i];
            i++;
            k++;
        } else {
            //sinon on copie le caractere null
            parts[j][k] = '\0';
            i++;
        
            // si on est arrivé au max du tableau on copie plus
            if (j == max_parts - 1) {
                break;
            }
            j++;
            k = 0;
        }
    }
    parts[j][k] = '\0';
    return j + 1;
}

void print_split(const char parts[][256], int nb_parts) {
    int i = 0;

    while (i < nb_parts) {
        printf("%s\n", parts[i]);
        i++;
    }
}

void str_join(char* dest, char parts[][256], int nb_parts, const char* sep) {
    int i = 0; 
    int j = 0;
    int k = 0;

    while (i < nb_parts) {
        //Remise à zéro sinon début lecture du mot suivant à l'indice de fin du premier
        j = 0;
        while (parts[i][j] != '\0')
        {
            dest[k] = parts[i][j];
            j++;
            k++;
        }
        //-1 pour eviter sep à la fin
        if (i < nb_parts - 1) {
            j = 0;
            while (sep[j] != '\0')
            {
                dest[k] = sep[j];
                j++;
                k++;    
            }
        }
        i++;
    }    
    dest[k] = '\0';

}

char* str_dup(const char* src) {
    int len = str_len(src);
    char* dup = malloc((len + 1) * sizeof(char));

    if (dup == NULL)
    {
        return NULL;
    }
    
    for(int i = 0; i < len ; i++) {
        dup[i] = src[i];
    }
    dup[len] = '\0';
    return dup;
}


char* str_concat_new(const char* a, const char* b) {
    int i = 0;
    int j = 0;
    int len_a = (str_len(a));
    int len_b = (str_len(b));
    char* dest = malloc((len_a + len_b + 1) * sizeof(char));

    if (dest == NULL)
    {
        return NULL;
    }

    while (a[i] != '\0') {
        dest[i] = a[i];
        i++;
    }

    while (b[j] != '\0') {
        dest[i + j] = b[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}



char* str_sub(const char* src, int start, int length) {
    int i = start;
    int j = 0;
    char* dest = malloc((length + 1) * sizeof(char));

    if (dest == NULL)
    {
        return NULL;
    }

    while (src[i] != '\0' && j != length) {
        dest[j] = src[i];

        i++;
        j++;
    }
    dest[j] = '\0';
    return dest;
}



char* str_repeat(const char* src, int n) {
    int i = 0;
    int j = 0;
    int count = 0;

    if (n == 0)
    {
        return "";
    }
    if (n < 0)
    {
        return NULL;
    }
    
    int len = str_len(src) * n;
    char* dest = malloc((len + 1) * sizeof(char));
    if (dest == NULL)
    {
        return NULL;
    }

    while (count != n)
    {
        while (src[i] != '\0') 
        {
            dest[j] = src[i];

            i++;
            j++;
        }
        i = 0;
        count++;
    }
    
    dest[j] = '\0';

    return dest;
}
