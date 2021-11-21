#ifndef FETCH
#define FETCH

typedef struct httpResponse
{
    int status;
    char *payload;
} HttpResponse;

HttpResponse fetch(const char *url);

#endif