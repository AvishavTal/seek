
#ifndef MMN23_SEEK_RECORDS_H
#define MMN23_SEEK_RECORDS_H
typedef struct record *record;
/**
 *
 * @param file_name
 * @param offset
 * @return
 */
record init_record(const char *file_name,long offset);
void print_record(record record);
#endif
