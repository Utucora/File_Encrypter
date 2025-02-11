#include<stdio.h>
#include<stdlib.h>
#include<openssl/evp.h>
#include<openssl/rand.h>
int main(int argc, char *argv[]){
    const char *file_name = argv[1];
    FILE *in = fopen(file_name, "rb");
    const char *file_name_enc = argv[2];
    FILE *out = fopen(file_name_enc, "wb");
    unsigned char key[32];
    unsigned char iv[16];
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    unsigned char buffer[1024];
    unsigned char ciphertext[1024 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, ciphertext_len;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, buffer, bytes_read);
        fwrite(ciphertext, 1, ciphertext_len, out);
    }
    EVP_EncryptFinal_ex(ctx, ciphertext, &ciphertext_len);
    fwrite(ciphertext, 1, ciphertext_len, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);
}