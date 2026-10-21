#include <stdio.h>
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









int main(void) {

char* word = "coucou";
int nb_char = str_len(word);
printf("%s : %d\n", word, nb_char);
char* word2 = "cotcot";
printf("Egaux : %d\n", str_equals(word, word2));
printf("Egaux : %d\n", str_equals(word, word));

char dest[256];
str_concat(dest, "bon", "jour");
printf("%s\n", dest);

printf("Contain : %d\n", str_contains("bonjour", "jour"));
printf("Nombre de caract : %d\n", str_count_chars(word, 'o'));


str_replace(dest, word, 'u', 't');
printf("Résultat : %s\n", dest);

const char* s = "banane,pomme,fraise";
char parts[3][256];

int count = str_split(s, ',', parts, 3);
printf("%d\n", count);

print_split(parts, count);

char join_parts[3][256] = {"poire", "cerise", "abricot"};
char join_dest[100];
str_join(join_dest, join_parts, 3, ", ");
printf("%s\n", join_dest);

return 0;
}