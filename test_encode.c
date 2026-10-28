#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "common.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    if(argc<4)
    {
        printf("Invalid argument");
        return 1;
    }
    if(check_operation_type(argv[1][1])==e_encode)
    {
        if(read_and_validate_encode_args(argv,&encInfo)==e_success)
        {
            if(do_encoding(&encInfo)==e_success)
            {
                printf("Encoding successful\n");
            }
            else{
                printf("Encoding failure\n");
            }
        }
        else
        {
            printf("Error:Invalid encoding arguments\n");
        }
    }
    else
    {
        printf("Invalid operator,use -e for encoding\n");

    }
    return 0;
    //(call check_operation_type(argv[1][1])==e_encode)
    /*
      call read_and_validate_encode_args(argv,&encinfo)==e_succes
      { 
             ->do_encoding(&encInfo)==e_sucess
      }
    */
}
OperationType check_operation_type(char opt)
{
    if(opt=='e')
    {
        return e_encode;
    }
    else if(opt=='d'){
        return e_decode;
    }
    else{
        return e_unsupported;
    }
    //if opt is 'e'
       //return e_encode
    //if opt is 'd'
       //return e_decode
    //return e_unsupported
}
Status do_encoding(EncodeInfo *encInfo){
    if(check_capacity(encInfo)==e_failure)
    {
        printf("Error:Image capacity is less\n");
        return e_failure;
    }
    if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure)
    {
        printf("Error Copying bmp header\n");
        return e_failure;
    }
    if(encode_magic_string(MAGIC_STRING ,encInfo)==e_failure)
    {
        printf("Error occured while encoding Magic string\n");
        return e_failure;
    }
    char *dot=strchr(encInfo->secret_fname,'.');
    strcpy(encInfo->extn_secret_file,dot);
    if(encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo)==e_failure)
    {
        printf("Error occured while encoding extension size\n");
        return e_failure;
    }
    if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_failure)
    {
        printf("Error occured while encoding extension\n");
        return e_failure;
    }
    encInfo->size_secret_file=get_file_size(encInfo->fptr_secret);
    if(encode_secret_file_size(encInfo->size_secret_file,encInfo)==e_failure)
    {
        printf("Error occured while encoding file size\n");
        return e_failure;
    }
    rewind(encInfo->fptr_secret);
    if(encode_secret_file_data(encInfo)==e_failure)
    {
        printf("Error occured while encoding file data\n");
        return e_failure;
    }
    if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failure){
        printf("Error occured while copying remaining data\n");
        return e_failure;
    }
    return e_success;

    /* 
    ->check_capacity(enc_info)==e_failure
       print error msg,return e_failure
    ->copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)==e_failur
    print err msg,
         return e_failur

    ->encode_magic_string(MAGIC_STRING ,encInfo)==e_failur
        return e_failur

    ->char *dot=strchr(argv[3],'.')(use strchar and find .)
    ->strcy(extn_secret_file,dot)
    ->encode_secret_file_extn_size(strlen(extn_secret_file),encInfo)
    ->Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);
    ->copy_reaminig image_data(fptr_src_image,fptr_stego_image)==e_failure
      print err msg,
    return e_failur
    */
}
Status check_capacity(EncodeInfo *encInfo)
{
    if(get_image_size_for_bmp(encInfo->fptr_src_image)>
          ((get_file_size(encInfo->fptr_secret)+14)*8))
          {
            return e_success;
          }
    else{
        return e_failure;
    }
    /*

        ->
          get_image_size_for_bmp(encInfo)->fptr_src_image)>
          ((get_file_size(encInfo->fptr_secret)+14)*8)
          ==>return e_succes
        ->return e_failur
     */
}
uint get_file_size(FILE *fptr)
{
    fseek(fptr,0,SEEK_END);
    return (ftell(fptr));
    /*
       ->fseek()to SEEK_END
       ->return ftell()
    */
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    rewind(fptr_src_image);
    rewind(fptr_stego_image);
    char buff[54];
    if(fread(buff,54,1,fptr_src_image)!=1){
        return e_failure;
    }
    if(fwrite(buff,54,1,fptr_stego_image)!=1){
        return e_failure;
    }
    return e_success;

    /*
       *rewind src image and secret file
       *Declare a buff of 54bytes,char buff[54]
       *Read 54bytes from source image(use fread and fwrite)
       *Write 54 bytes frm buff to dest image
    */
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char buff[8];
    int len=strlen(magic_string);
    for(int i=0;i<len;i++){
        if(fread(buff,8,1,encInfo->fptr_src_image)!=1){
            return e_failure;
        }
        encode_byte_to_lsb(magic_string[i],buff);
        if(fwrite(buff,8,1,encInfo->fptr_stego_image)!=1){
            return e_failure;
        }
    }
    
    return e_success;

    /*
     encode char by char
     ->Declare a buff of 8 bytes
     ==>Run a loop for length of magic string
     ->Read 8 bytes from src_image into buff
     ->encode_byte_to_lsb(magic_string[],buff)(first 0 and 1)
     ->write 8 bytes od encoded data from buff to dest_image(use fwrite)
    ==>return e_succes
    */

}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for(int i=0;i<8;i++){
        int mask=1<<i;
        if(data&mask){
            image_buffer[i]=image_buffer[i]|1;

        }
        else{
            image_buffer[i]=image_buffer[i]&(~1);
        }

    }
    return e_success;
    /*
    ==>Loop for 8 time 
       *check nth bit is set or not
       ->if set,set the lsb of image_buffer[]
       ->if claer,clear lsb of image_buffer[]

    ==>return e_succes
      
    */
}
Status encode_secret_file_extn_size(uint size, EncodeInfo *encInfo)
{
    char buff[32];
    if(fread(buff,32,1,encInfo->fptr_src_image)!=1){
        return e_failure;
    }
    encode_size_to_lsb(size,buff);
    if(fwrite(buff,32,1,encInfo->fptr_stego_image)!=1){
        return e_failure;
    }
    return e_success;


    /*
      ->Declare a buff of 32 bytes
      ->Read 32 bytes of buff from src_images
      ->encode_size_to_lsb(size,buf)
      ->write buff to dest_image
    ->return e_success
    */

}
Status encode_size_to_lsb(uint data, char *image_buffer)
{
    for(int i=31;i>=0;i--){
        int mask=1<<i;
        if(data&mask){
            image_buffer[i]=image_buffer[i]|1;

        }
        else{
            image_buffer[i]=image_buffer[i]&(~1);
        }

    }
    return e_success;
     /*==>Loop for 32 time 
       *check nth bit is set or not
       ->if set,set the lsb of image_buffer[]
       ->if claer,clear lsb of image_buffer[]

    ==>return e_succes
      
    */

}
/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char buff[8];
    int len=strlen(file_extn);
    for(int i=0;i<len;i++){
        if(fread(buff,8,1,encInfo->fptr_src_image)!=1){
            return e_failure;
        }
        encode_byte_to_lsb(file_extn[i],buff);
        if(fwrite(buff,8,1,encInfo->fptr_stego_image)!=1){
            return e_failure;
        }
    }
    return e_success;
    /*
     ->Declare a buff of 8 bytes
     ==>Run a loop for length of file extn
     ->Read 8 bytes from src_image into buff
     ->encode_byte_to_lsb(file_extn[],buff)(first 0 and 1)
     ->write 8 bytes od encoded data from buff to dest_image(use fwrite)
    ==>return e_succes
    */
      


}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buff[32];
    if(fread(buff,32,1,encInfo->fptr_src_image)!=1)
    {
        return e_failure;
    }
    encode_size_to_lsb(file_size,buff);
    if(fwrite(buff,32,1,encInfo->fptr_stego_image)!=1)
    {
        return e_failure;
    }
    return e_success;



    /*->Declare a buff of 32 bytes
      ->Read 32 bytes of buff from src_images
      ->encode_size_to_lsb(size,buf)
      ->write buff to dest_image
    ->return e_success
    */

}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char buff[8];
    char data;
    for(int i=0;i<encInfo->size_secret_file;i++)
    {
        if(fread(buff,8,1,encInfo->fptr_src_image)!=1){
            return e_failure;
        }
        if(fread(&data,1,1,encInfo->fptr_secret)!=1){
            return e_failure;
        }
        encode_byte_to_lsb(data,buff);
        if(fwrite(buff,8,1,encInfo->fptr_stego_image)!=1){
            return e_failure;
        }
    }
    return e_success;

    /*
       /*
     ->Declare a buff of 8 bytes
     char buff[8],data(ibyte of data frm secretimg);
     ==>Run a loop for length of secret_file_size times
     ->Read 8 bytes from src_image into buff
     ->read char from secret_file to data
     ->encode_byte_to_lsb(data,buff)
     ->write 8 bytes od encoded data from buff to dest_image(use fwrite)


    ==>return e_succe
    */
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch;
        while(fread(&ch,1,1,fptr_src)==1){
            if(fwrite(&ch,1,1,fptr_dest)!=1){
                return e_failure;
            }
        }
    return e_success;
   /*
   loop 
   ->read 1 byte char  from fptr_src source 
   -> write that to destination image
   */
}
