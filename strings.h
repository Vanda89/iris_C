#ifndef OUTILS_H 
#define OUTILS_H 

int str_len(const char* word);
void print_str(const char* word);
int str_equals(const char* a, const char* b);
void str_concat(char* dest, const char* a, const char* b);
int str_contains(const char* haystack, const char* needle);
int str_count_chars(const char* s, char c);
void str_replace(char* dest, const char* src, char from, char to);
int str_split(const char* s, char sep, char parts[][256], int max_parts);
void print_split(const char parts[][256], int nb_parts);
void str_join(char* dest, char parts[][256], int nb_parts, const char* sep);

#endif