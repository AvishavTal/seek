#include <stdio.h>
#include <stdlib.h>
#include "seek_records.h"

#define MIN_ARGC 3

#define TOO_FEW_ARGS_MSG "too few arguments.\n"

#define OFFSET_IDX 1

#define INVALID_OFFSET_MSG "offset should be a positive integer.\n"

#define OFFSET_BASE 10

#define MIN_OFFSET 1

#define FIRST_FILE_IDX 2



void check_number_of_args(int argc);

long set_offset(char *offset_str);

record * set_records(long offset, int n_records, char **file_names);

void print_records(record *records, int n_records);

void delete_records(record *records, int n_records);

int main(int argc, char **argv) {
    long offset;
    char **files;
    int n_files;
    record *records;
    check_number_of_args(argc);
    offset=set_offset(argv[OFFSET_IDX]);
    files=argv+FIRST_FILE_IDX;
    n_files=argc-FIRST_FILE_IDX;
    records=set_records(offset, n_files, files);
    print_records(records, n_files);
    delete_records(records, n_files);
    return 0;
}

/**
 * free the memory used for the records array
 * @param records
 * @param n_records
 */
void delete_records(record *records, int n_records) {
    while (n_records){
        delete_record(records[--n_records]);
    }
    free(records);
}

/**
 * print the records in the given records array
 * @param records records to print
 * @param n_records size of the array
 */
void print_records(record *records, int n_records) {
    int i;
    for ( i = 0; i < n_records; ++i) {
        print_record(records[i]);
    }
}

/**
 * set record that hold the char at the offset and the name of the file for each file.
 * @param offset
 * @param n_records
 * @param file_names
 * @return array of records
 */
record *set_records(long offset, int n_records, char **file_names) {
    record *records;
    int i;
    records=(record *) malloc(n_records*sizeof (record));
    if (records==NULL){
        printf("memory problem.");
        exit(3);
    }
    for (i=0;i<n_records;++i){
        records[i]=init_record(file_names[i],offset);
        if (records[i]==NULL){
            printf("memory problem.");
            exit(3);
        }
    }
    return records;
}

/**
 * set the offset. exit if invalid offset.
 * @param offset_str string representation of the offset
 * @return the offset
 */
long set_offset(char *offset_str) {
    int long offset;
    char *end;
    offset=strtol(offset_str,&end,OFFSET_BASE);
    if (offset < MIN_OFFSET || *end){
        printf(INVALID_OFFSET_MSG);
        exit(2);
    }
    return offset;
}

/**
 * check if the program received enough arguments. exit if not.
 * @param argc number of argument received.
 */
void check_number_of_args(int argc) {
    if (argc<MIN_ARGC){
        printf(TOO_FEW_ARGS_MSG);
        exit(1);
    }
}
