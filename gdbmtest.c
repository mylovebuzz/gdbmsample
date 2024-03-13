#include <gdbm.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#define DB_FILE_BLOCK "book_data"
#define ISBN_MAX 13
#define AUTHOR_MAX 50
#define TITLE_MAX 50
#define FIELD_MAX 50

typedef struct {
    char isbn[ISBN_MAX + 1];
    char author[AUTHOR_MAX + 1];
    char title[TITLE_MAX + 1];
    int numb;
} book_entry;

char *str_con(char *input, int len) {
    int count = 0;
    do {
	input[count] = tolower(input[count]);
	count ++;
    } while (count <= len);
    return input;
}

int main() {
    book_entry newbook;
    datum key, data;
    GDBM_FILE dbm_ptr;
    char isbnarr[ISBN_MAX + 1] = {0};
    char *isbn = isbnarr;
    book_entry vbook, sbook;
    char keyword[FIELD_MAX];
    memset(&newbook, '\0', sizeof(newbook));
    strncpy(newbook.isbn, "1234567890123", ISBN_MAX);
    strncpy(newbook.author, "huawei research china", AUTHOR_MAX);
    strncpy(newbook.title, "huawei dream works", TITLE_MAX);
    newbook.numb = 735;

    key.dptr = (char*)&newbook.isbn;
    key.dsize = ISBN_MAX;
    data.dptr = (char*)&newbook;
    data.dsize = sizeof(newbook);

    dbm_ptr = gdbm_open(DB_FILE_BLOCK, 0, GDBM_WRCREAT, S_IRUSR | S_IWUSR, NULL);
    gdbm_store(dbm_ptr, key, data, GDBM_REPLACE);

    puts("please input your isbn:");
    scanf("%s", isbn);
    key.dptr = (char*)isbn;
    key.dsize = ISBN_MAX;

    data = gdbm_fetch(dbm_ptr, key);
    if (data.dsize == 0) {
	printf("no result\n");
    } else {
	memset(&newbook, 0, sizeof(newbook));
	memcpy(&newbook, data.dptr, data.dsize);
	printf("book title: %s\n", newbook.title);
    }
    gdbm_close(dbm_ptr);
    exit(0);
}
// https://www.shuzhiduo.com/A/l1dyYg96de/
// https://www.cnblogs.com/arely/p/4416106.html
