// 1.文件切分  参数1.目标文件  参数2.切片大小(默认256k)
// cc chunk_sha2.c -o chunk_sha2 -L usr/lib/openssl -lssl -lcrypto
// 附: 将每个切片的哈希值顺序放在md.txt中
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <string.h>

void chunk_hash(const char *buffer)
{
    printf("载入函数chunk_hash\n");
    unsigned char file_hash[SHA256_DIGEST_LENGTH];
    EVP_Digest(buffer, strlen(buffer), file_hash, NULL, EVP_sha256(),NULL);
    FILE *fp = fopen("md.txt", "a");
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02x",file_hash[i]);
        fprintf(fp, "%02x", file_hash[i]);
    }
    printf("\n");
    fprintf(fp,"\n");
}

void section(const char *file_name, int size)
{
    FILE *fp1 = fopen(file_name, "rb");
    FILE *fp2 = fopen("md.txt", "w");   // 切片哈希值存储
    if (!fp1)
    {
        printf("文件 %s 打开失败!\n", file_name);
        return;
    }
    printf("文件 %s 打开成功!\n", file_name);

    // 切片大小(Kb)
    unsigned int file_size = size * 1024;
    unsigned int file_read;

    char *buffer = (char *)malloc(file_size);
    if (buffer == NULL)
    {
        printf("内存分配失败\n");
        fclose(fp1);
        return;
    }

    int file_num = 1;
    while ((file_read = fread(buffer, 1, file_size, fp1)) > 0)
    {
        char chunk_file_name[256];
        sprintf(chunk_file_name, "%d_%s", file_num, file_name);

        FILE *fp2 = fopen(chunk_file_name, "wb");
        if (!fp2)
        {
            printf("切片文件 %s 无法创建\n", chunk_file_name);
            free(buffer);
            fclose(fp1);
            return;
        }

        fwrite(buffer, 1, file_read, fp2);
        fclose(fp2);

        printf("生成切片文件: %s\n", chunk_file_name);
        file_num++;

        // 切片哈希值生成
        chunk_hash(buffer);
    }
    free(buffer);
    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char const *argv[])
{
    int size = 256;
    if (argc < 2)
    {
        printf("请提供目标文件。\n格式: .hw1 file [chunk_size]\n");
        return EXIT_FAILURE;
    }

    if (argc > 2)
    {
        if (argv[2] <= 0)
            printf("切片大小<=0,将使用默认切片大小256Kb\n");
        else
            size = strtoul(argv[2], NULL, 10); // 将切片大小转为十进制无符号数据
    }
    printf("使用默认大小%dKb\n", size);

    section(argv[1], size);

    return 0;
}