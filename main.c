#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "strings.h"

int main(void) {

char* word = "coucou";
int nb_char = str_len(word);
printf("%s : %d\n", word, nb_char);
printf("----------------------------\n");

char* word2 = "cotcot";
printf("Egaux : %d\n", str_equals(word, word2));
printf("Egaux : %d\n", str_equals(word, word));

printf("----------------------------\n");
char dest[256];
str_concat(dest, "bon", "jour");
print_str(dest);

printf("----------------------------\n");
printf("Contain : %d\n", str_contains("bonjour", "jour"));
printf("Nombre de caract : %d\n", str_count_chars(word, 'o'));


printf("----------------------------\n");
str_replace(dest, word, 'u', 't');
printf("Résultat : %s\n", dest);

printf("----------------------------\n");
const char* s = "banane,pomme,fraise";
char parts[3][256];

int count = str_split(s, ',', parts, 3);
printf("%d\n", count);

printf("----------------------------\n");
print_split(parts, count);

printf("----------------------------\n");
char join_parts[3][256] = {"poire", "cerise", "abricot"};
char join_dest[100];
str_join(join_dest, join_parts, 3, ", ");
print_str(join_dest);

printf("----------------------------\n");
char* src = "exercice";
char* new_src = str_dup(src);
src = "cool";

printf("%s\n" "%s\n", new_src, src);
printf("----------------------------\n");
char* result_concat = str_concat_new(src, new_src);
print_str(result_concat);
free(new_src);
free(result_concat);

printf("----------------------------\n");
char* sentence = "Pourtant ça marche sur ma machine !";
char* extracted_string = str_sub(sentence, 0, 19);
print_str(extracted_string);
free(extracted_string);

printf("----------------------------\n");
char* beetle_juice = "Beetle Juice ";
char* repeated_string = str_repeat(beetle_juice, 3);
print_str(repeated_string);
free(repeated_string);



printf("----------------------------\n");
List* new_list = list_create();
new_list->data[0] = 10;
new_list->data[1] = 20;
new_list->data[2] = 30;
new_list->size = 3;
list_print(new_list);

printf("----------------------------\n");
int result = list_get(new_list, 2);
printf("%d \n", result);

printf("----------------------------\n");
list_set(new_list, 0, 40);
list_print(new_list);

printf("----------------------------\n");
list_add(new_list, 50);
list_print(new_list);

printf("----------------------------\n");
list_pop(new_list);
list_print(new_list);

printf("----------------------------\n");
list_remove(new_list, 0);
list_print(new_list);

printf("----------------------------\n");
list_clear(new_list);
list_print(new_list);
list_add(new_list, 60);
list_add(new_list, 70);
list_add(new_list, 80);

list_print(new_list);

list_free(new_list);


return 0;
}