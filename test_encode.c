#include <stdio.h>
#include "encode.h"
#include "types.h"

int main()
{
    EncodeInfo encInfo;
    //(call check_operation_type(argv[1][1])==e_encode)
    /*
      call read_and_validate_encode_args(argv,&encinfo)==e_succes
      { 
             ->do_encoding(&encInfo)==e_sucess
      }
    */
   

    return 0;
}
OperationType check_operation_type(char opt){
    if opt is 'e'
       return e_encode
    if opt is 'd'
       return e_decode
    return e_unsupported
}
Status do_encoding(EncodeInfo *encInfo){
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
Status check_capacity(EncodeInfo *encInfo){
    /*

        ->
          get_image_size_for_bmp(encInfo)->fptr_src_image)>
          ((get_file_size(encInfo->fptr_secret)+14)*8)
          ==>return e_succes
        ->return e_failur
     */
}
uint get_file_size(FILE *fptr){
    /*
       ->fseek()to SEEK_END
       ->return ftell()
    */
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image){
    /*
       *rewind src image and secret file
       *Declare a buff of 54bytes,char buff[54]
       *Read 54bytes from source image(use fread and fwrite)
       *Write 54 bytes frm buff to dest image
    */
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo){
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
    /*
    ==>Loop for 8 time 
       *check nth bit is set or not
       ->if set,set the lsb of image_buffer[]
       ->if claer,clear lsb of image_buffer[]

    ==>return e_succes
      
    */
}
Status encode_secret_file_extn_size(unit size, EncodeInfo *encInfo){
    /*
      ->Declare a buff of 32 bytes
      ->Read 32 bytes of buff from src_images
      ->encode_size_to_lsb(size,buf)
      ->write buff to dest_image
    ->return e_success
    */

}
Status encode_size_to_lsb(uint data, char *image_buffer){
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
    /*
     ->Declare a buff of 8 bytes
     ==>Run a loop for length of file extn
     ->Read 8 bytes from src_image into buff
     ->encode_byte_to_lsb(file_extn[],buff)(first 0 and 1)
     ->write 8 bytes od encoded data from buff to dest_image(use fwrite)
    ==>return e_succe
    */
      


}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo){

    /*->Declare a buff of 32 bytes
      ->Read 32 bytes of buff from src_images
      ->encode_size_to_lsb(size,buf)
      ->write buff to dest_image
    ->return e_success
    */

}
Status encode_secret_file_data(EncodeInfo *encInfo){

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
   /*
   loop 
   ->read 1 byte char  from fptr_src source 
   -> write that to destination image
   */
}
