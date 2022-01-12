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

#define OPEN_FILE_MSG "can not open the file: \n"

#define BIG_OFFSET_MSG "the offset recived is grater than the size of the file.\n"

void check_input(int argc, char **argv);

void check_number_of_args(int argc);

void check_offset(long offset, const char *end);

void print_char_in_all_files(long offset, char **files, int n_files);

void print_char_in_file(long int offset, const char *file_name);

void set_records(record *records, long offset, int n_records, char **file_names);

void print_records(record *records, int n_records);

int main(int argc, char **argv) {
    int long offset;
    char *end;
    char **files;
    int n_files;
    record *records;
    check_number_of_args(argc);
    offset= strtol(argv[OFFSET_IDX],&end,OFFSET_BASE);
    check_offset(offset, end);
    files=argv+FIRST_FILE_IDX;
    n_files=argc-FIRST_FILE_IDX;
    records=(record *) malloc(n_files*sizeof (record));
    set_records(records, offset, n_files, files);
    print_records(records, n_files);
    return 0;
}

void print_records(record *records, int n_records) {
    int i;
    for ( i = 0; i < n_records; ++i) {
        print_record(records[i]);
    }
}

void set_records(record *records, long offset, int n_records, char **file_names) {
    int i;
    for (i=0;i<n_records;++i){
        records[i]= init_record(file_names[i],offset);
    }
}

void print_char_in_all_files(long offset, char **files, int n_files) {
    int i;
    for (i = 0; i < n_files; ++i) {
        print_char_in_file(offset-1, files[i]);
    }
}

void print_char_in_file(long offset, const char *file_name) {
    FILE *fp;
    printf("%s\n",file_name);
    fp= fopen(file_name,"r");
    if (fp==NULL){
        printf(OPEN_FILE_MSG);
    } else{
        long file_size;
        long int start;
        start= ftell(fp);
        fseek(fp,0,SEEK_END);
        file_size= ftell(fp);
        fseek(fp,start,SEEK_SET);
        printf("the begining in %ld\n", ftell(fp));

        printf("the size of %s is %ld\n",file_name,file_size);
        printf("the offset is: %ld\n",offset);
        if (offset>file_size){
            printf(BIG_OFFSET_MSG);
        } else{
            int res;
            fseek(fp,offset,SEEK_SET);
            res= fgetc(fp);
            printf("%c\n",res);
        }
    }
}

void check_offset(long offset, const char *end) {
    if (offset<MIN_OFFSET || *end){
        printf(INVALID_OFFSET_MSG);
        exit(2);
    }
}

void check_input(int argc, char **argv) {


}

void check_number_of_args(int argc) {
    if (argc<MIN_ARGC){
        printf(TOO_FEW_ARGS_MSG);
        exit(1);
    }
}
