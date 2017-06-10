#ifndef TABLES_H
#define TABLES_H
struct FIO{ char F[20], I[20], O[20]; };
struct ahuman{ char number[14], mark[30]; FIO name; };
struct hesh { ahuman man; hesh *next; };
void molodcy(hesh *&c, ahuman M);
void create(hesh *&b, ahuman M);
int key(ahuman T);
#endif