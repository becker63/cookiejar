//#include <libwebsockets.h>
//#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "../include/ahocorasick.h"

void callback_match_total(void *arg, struct aho_match_t* m)
{
    long long int* match_total = (long long int*)arg;
    (*match_total)++;
}

void callback_match_pos(void *arg, struct aho_match_t* m)
{
    char* text = (char*)arg;

    printf("match text:");
    for(unsigned int i = m->pos; i < (m->pos+m->len); i++)
    {
        printf("%c", text[i]);
    }

    printf(" (match id: %d position: %llu length: %d)\n", m->id, m->pos, m->len);
}

void sample_code(char * input)
{
    struct ahocorasick aho;
    long long int match_total = 0;
    int id[10] = {0};

    aho_init(&aho);

    id[0] = aho_add_match_text(&aho, "ab", 2);
    id[1] = aho_add_match_text(&aho, "c", 1);
    id[2] = aho_add_match_text(&aho, "a", 1);
    id[3] = aho_add_match_text(&aho, "acd", 3);

    aho_create_trie(&aho);
    aho_register_match_callback(&aho, callback_match_total, &match_total);

    //printf("try: %s\n", "dabcacdfc");
    printf("\nmatch:%u\n", aho_findtext(&aho, input, strlen(input)));

    aho_destroy(&aho);
}

int main(){
    char line[] = "dabcacdfc";
    printf("%s", line);
    sample_code(line);
}
