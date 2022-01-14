#include <stdio.h>
#include <stdlib.h>
#include "seek_records.h"

#define CANT_OPEN_FILE -1
#define TOO_BIG_OFFSET_CODE -2

/**
 * hold the name of file and asci code in the file at offset if available
 */
struct record{
    const char *file_name;
    long offset;
    int asci;/*the asci code in the file at offset if available, information code otherwise.*/
};

void set_asci(record record);

void print_error_msg(record record);

/**
 * delete given record
 * @param record
 */
void delete_record(record record){
    free(record);
}

/**
 * initialize record with path to file and offset
 * @param file_name path to file
 * @param offset
 * @return record
 */
record init_record(const char *file_name, long offset){
    record result;
    result=(record)malloc(sizeof (struct record));
    result->offset=offset;
    result->file_name=file_name;
    set_asci(result);
    return result;
}

/**
 * set the asci atribute of the given record if possible, information otherwise
 * @param record
 */
void set_asci(record record) {
    FILE *file;
    file= fopen(record->file_name,"r");
    if (file==NULL){
        record->asci=CANT_OPEN_FILE;
    } else{
        long file_size;
        fseek(file,0,SEEK_END);
        file_size= ftell(file);
        if (record->offset>file_size){
            record->asci=TOO_BIG_OFFSET_CODE;
        } else{
            fseek(file,record->offset-1,SEEK_SET);
            record->asci= fgetc(file);
        }
        fclose(file);
    }
}

/**
 * print the given record
 * @param record
 */
void print_record(record record) {
    if (record->asci<0){
        print_error_msg(record);
    } else{
        printf("The %ld'th character in the file %s is:     %d\n",record->offset,record->file_name,record->asci);
    }
}

/**
 * print why the wanted asci code is not availble
 * @param record
 */
void print_error_msg(record record) {
    switch (record->asci) {
        case CANT_OPEN_FILE:
            printf("can't open the file %s\n",record->file_name);
            break;
        case TOO_BIG_OFFSET_CODE:
            printf("The file %s has less characters than %ld\n",record->file_name,record->offset);
            break;
        default:
            printf("something went wrong.");
    }
}
