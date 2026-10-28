#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;//width*height*3 byte for each pixel
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo){

    if((strstr(argv[2],".bmp"))!=NULL){
        char *dot=strstr(argv[2],".bmp");
        if(strlen(dot)!=4)
        {
            return e_failure;
        }
        encInfo->src_image_fname=argv[2];
        encInfo->fptr_src_image=fopen(argv[2],"r");
        if(encInfo->fptr_src_image==NULL)
        {
            return e_failure;
        }
    }
    else{
        return e_failure;
    }
    if(strstr(argv[3],".txt")!=NULL)
    {
    char *tdot=strstr(argv[3],".txt");
    if(strlen(tdot)!=4){
        return e_failure;
    }
    encInfo->secret_fname=argv[3];
    encInfo->fptr_secret=fopen(argv[3],"r");
    if(encInfo->fptr_secret==NULL){
        return e_failure;
    }
    }
    else{
        return e_failure;
    }

    if(argv[4]!=NULL){
        if(strstr(argv[4],".bmp")!=NULL){
            char *odot=strstr(argv[4],".bmp");
            if(strlen(odot)!=4){
                return e_failure;
            }
        encInfo->stego_image_fname=argv[4];
        }
        else{
            return e_failure;
        }
    }
    else{
        encInfo->stego_image_fname="defalut.bmp";

    }
    encInfo->fptr_stego_image=fopen(encInfo->stego_image_fname,"w");
    if(  encInfo->fptr_stego_image==NULL){
        return e_failure;
    }

    return e_success;
}
    
    /*
      ->check the argv[2] must be having ".bmp" extn
      validate check last 4 char should be .bmp
      if yes, (store file name into structure member) encInfo->src_image_fname=argv[2]
          . open the file in read mode argv[2]
          encInfo ->fptr_src_image=fopen()
          if file not present,return e_failure
      if not, return e_failure

      ->check the argv[3] is a valid file
      encInfo->secret_fname=argv[3]
       is the file present or not
       If present, encInfo->fptr_secret=fopen()
       if not,return e_failure



       ->Check argv[4] is Null or not 
       if it is not null output file is give,encInfo->stego_image_fname=argv[4]
       if NULL ,encInfo->stego_image_fname="defalut.bmp"

       check the file extn is only of ".bmp".
       If not ,return e_failure


       OPEN the file in write mode,and store the file pointer to structure member.

    */

