#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "strings.h"
#include "recursion.h"
#include "dom.h"

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

printf("---------------------------- \n");
print_binary(13);
printf("\n");
print_binary(25);
printf("\n");
print_binary(42);
printf("\n");

printf("---------------------------- \n");
Element* html = create_element("html", NULL, NULL);
Element* body = create_element("body", NULL, NULL);
Element* h1 = create_element("h1", "titre", "Mon titre");
Element* div = create_element("div", "contenu", NULL);
Element* p1 = create_element("p", NULL, "Bonjour");
Element* p2 = create_element("p", NULL, "Au revoir");


append_child(html, body);
append_child(body, h1);
append_child(body, div);
append_child(div, p1);
append_child(div, p2);


if (html != NULL) {
    printf("Tag : %s\n", html->tag);
    printf("Id : %s\n", html->id);
    printf("Nombre d'enfants : %d\n", html->nb_children);
}
if (body != NULL) {
    printf("Tag : %s\n", body->tag);
    printf("Id : %s\n", body->id);
    printf("Nombre d'enfants : %d\n", body->nb_children);
}
if (h1 != NULL) {
    printf("Tag : %s\n", h1->tag);
    printf("Id : %s\n", h1->id);
    printf("Nombre d'enfants : %d\n", h1->nb_children);
}
if (div != NULL) {
    printf("Tag : %s\n", div->tag);
    printf("Id : %s\n", div->id);
    printf("Nombre d'enfants : %d\n", div->nb_children);
}
if (p1 != NULL) {
    printf("Tag : %s\n", p1->tag);
    printf("Id : %s\n", p1->id);
    printf("Nombre d'enfants : %d\n", p1->nb_children);
}
if (p2 != NULL) {
    printf("Tag : %s\n", p2->tag);
    printf("Id : %s\n", p2->id);
    printf("Nombre d'enfants : %d\n", p2->nb_children);
}

printf("---------------------------- \n");
Element* html2 = create_element("html", NULL, NULL);
Element* body2 = create_element("body", NULL, NULL);
Element* h1_bis = create_element("h1", "titre", "Mon titre");
Element* div2 = create_element("div", "test", NULL);


append_child(html2, body2);
append_child(body2, h1_bis);
append_child(body2, div2);


for (int i = 0; i < 20; i++) {
    Element* p = create_element("p", NULL, "p test");

    if (p == NULL) {
        return 1;
    }

    append_child(div2, p);
    printf("p %d \n", i);

}
printf("Nombre d'enfants du div : %d\n", div2->nb_children);

printf("---------------------------- \n");
printf("Nombre d'éléments dans le DOM : %d \n", count_elements(html));
printf("Nombre d'éléments dans le DOM qui sont de type %s : %d \n", p1->tag ,count_by_tag(html, "p"));
printf("Nombre d'éléments dans le DOM 2 qui sont de type %s : %d \n", p1->tag ,count_by_tag(html2, "p"));
printf("Hauteur du DOM : %d \n", dom_height(html));

printf("---------------------------- \n");
Element* resultFindByID = find_by_id(html, "titre");
if (resultFindByID != NULL) {
    printf("L'élément avec l'id titre : %s\n", resultFindByID->tag);
} else {
    printf("Élément non trouvé\n");
}
Element* resultFindByID2 = find_by_id(html, "cisgood");
if (resultFindByID2 != NULL) {
    printf("L'élément avec l'id cisgood : %s\n", resultFindByID2->tag);
} else {
    printf("L'élément avec l'id cisgood : Élément non trouvé\n");
}

printf("---------------------------- \n");
int depth = depth_of(html, "titre");
if (depth != -1) {
    printf("L'élément avec l'id titre a une profondeur de : %d\n", depth);
}

printf("---------------------------- \n");
render(html, 0);

printf("---------------------------- \n");

free_element(html);
free_element(html2);


return 0;
}