
#ifndef MMN23_SEEK_RECORDS_H
#define MMN23_SEEK_RECORDS_H
/**
 * hold the information of what asci code there is in a certain position in a certian file
 */
typedef struct record *record;
/**
 * initialize record with path to file and offset
 * @param file_name path to file
 * @param offset
 * @return record
 */
record init_record(const char *file_name,long offset);
/**
 * print the given record
 * @param record
 */
void print_record(record record);
/**
 * delete given record
 * @param record
 */
void delete_record(record record);
#endif
