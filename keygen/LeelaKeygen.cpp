#include "sha2.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*
#include "cryptopp55/cryptlib.h"
#include "cryptopp55/filters.h"
#include "cryptopp55/files.h"
#include "cryptopp55/randpool.h"
#include "cryptopp55/osrng.h"
#include "cryptopp55/eccrypto.h"
#include "cryptopp55/oids.h"
#include "cryptopp55/base64.h"
#include "cryptopp55/integer.h"
#include "cryptopp55/hex.h"
*/

extern unsigned int priv[16384];
extern unsigned int pub[16384];

#if (_MSC_VER >= 1400) /* VC8+ Disable all deprecation warnings */
    #pragma warning(disable : 4996) 
#endif /* VC8+ */

enum KeyGenReturnCode {
    // success
    ERC_SUCCESS     = 00,
    ERC_SUCCESS_BIN = 01,
    // failure
    ERC_ERROR       = 10,
    ERC_MEMORY      = 11,
    ERC_FILE_IO     = 12,
    ERC_BAD_ARGS    = 13,
    ERC_BAD_INPUT   = 14,
    ERC_EXPIRED     = 15,
    ERC_INTERNAL    = 16
};

void sha256_16k(char *in, int isize, unsigned char *out, unsigned int r) {
    unsigned char s[32];
    unsigned char d[32];
    int j;
    
    sha256((unsigned char*)in, isize, s);    
        
    for (j = 0; j < 8192; j++) {                
        s[28] ^= (r & 0xFF00) >> 8;
        s[29] ^=  r &   0xFF;
        s[30] ^= (j & 0xFF00) >> 8;            
        s[31] ^=  j &   0xFF;               
        sha256((unsigned char*)s,   32, (unsigned char*)d);
        d[28] ^= (r & 0xFF00) >> 8;
        d[29] ^=  r &   0xFF;
        d[30] ^= (j & 0xFF00) >> 8;            
        d[31] ^=  j &   0xFF;                          
        sha256((unsigned char*)d,   32, (unsigned char*)s);            
    }        
    
    memcpy(out, s, 32);
}

/*
using namespace CryptoPP;

void main(void) {       
    unsigned char s[32];
    unsigned char dig[32];
    clock_t start, end;
    int j;
    AutoSeededRandomPool rng;    
    FILE *fp;
    FILE *fpp;
    
    fp  = fopen("private.dat", "w");                     
    fpp = fopen("public.dat", "w");   
    
    for (int i = 0; i < 16384; i++) {
        unsigned int v;
        
        rng.GenerateBlock((byte*)&v, 4);
        
        fprintf(fp, "0x%X,\n", v);
        
        memset(s, 0, 32);        
        s[28] = (v >> 24) & 0xFF;        
        s[29] = (v >> 16) & 0xFF;
        s[30] = (v >>  8) & 0xFF;
        s[31] = (v >>  0) & 0xFF;                        
    
        for (j = 0; j < 8192; j++) {                
            s[28]   ^= (i & 0xFF00) >> 8;
            s[29]   ^=  i &   0xFF;
            s[30]   ^= (j & 0xFF00) >> 8;            
            s[31]   ^=  j &   0xFF;               
            sha256((unsigned char*)s,   32, (unsigned char*)dig);
            dig[28] ^= (i & 0xFF00) >> 8;
            dig[29] ^=  i &   0xFF;
            dig[30] ^= (j & 0xFF00) >> 8;            
            dig[31] ^=  j &   0xFF;                          
            sha256((unsigned char*)dig, 32, (unsigned char*)s);            
        }        
        
        v = 0;
        v |= s[28] << 24;        
        v |= s[29] << 16;        
        v |= s[30] <<  8;        
        v |= s[31] <<  0;        
        
        fprintf(fpp, "0x%X,\n", v);
    }
    
    fclose(fp);
    fclose(fpp);
                                 
    return;   
}
*/

int main(int argc, char** argv) {
    FILE *inf;
    FILE *keyf;
    FILE *logf;
    bool registerok;             
                            
    if (argc != 4) {
        return ERC_BAD_ARGS;
    }
    
    inf = fopen(argv[1], "r");
    
    if (inf == NULL) {
        return ERC_FILE_IO;
    }
    
    keyf = fopen(argv[2], "w");
    
    if (keyf == NULL) {
        return ERC_FILE_IO;
    }
    
    logf = fopen(argv[3], "w"); 
    
    if (logf == NULL) {
        return ERC_FILE_IO;
    }
    
    registerok = false;
    
    char linebuff[256];
    char regname[256];
    char orgname[256];
    
    memset(regname, 0, sizeof(regname));
    
    while (fgets(linebuff, 256, inf) != NULL) {
        if (strncmp(linebuff, "REG_NAME=", 9) == NULL) {
            char *s = linebuff + 9;
            int len = strlen(s);
            
            /*
                strip starting whitespace
            */                                   
            while(*s == ' ') {
                s++;
                len--;
            } 
            
            /*
                axe newline
            */
            s[len - 1] = 0;
            
            strncpy(regname, s, len);
            
            /*
                axe trailing spaces
            */
            int len2 = strlen(regname);
            int pos = len2 - 1;
            
            while (regname[pos] == ' ' && pos > 0) {
                regname[pos] = 0;
                pos--;
            }
            
            int len3 = strlen(regname);
            int j;
            
            memcpy(orgname, regname, sizeof(orgname));
            
            for (j = 0; j < len3; j++) {
                if (regname[j] > 126 || regname[j] < 32) {
                    regname[j] = '_';
                }
                regname[j] = toupper(regname[j]);
            }            
            
            if (strlen(regname) < 4) {
                fprintf(keyf, "Value for REG_NAME must contain at least 4 characters.\n");
                return ERC_BAD_INPUT;
            }
                        
            registerok = true;                                               
        } 
    }
    
    if (!registerok) {
        fprintf(keyf, "Failed to find REG_NAME in input.\n");
        return ERC_BAD_INPUT;
    }        
    
    /*
        generate serial
    */    
    unsigned char dg[32];          
    char SerialNumber[256];
        
    char keychars[32] = { '1', '3', '4', '5', '6', '7', '8', '9',
                          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                          'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 
                          'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};    
     
    sha256_16k(regname, strlen(regname), dg, 0);
    
    unsigned int idx1 = ((dg[30] << 8) | dg[31]) & 0x3FFF;
    unsigned int idx2 = ((dg[28] << 8) | dg[29]) & 0x3FFF;
    
    unsigned int seal1 = priv[idx1];
    unsigned int seal2 = priv[idx2];
    
    SerialNumber[0]  = keychars[(seal1 >> 30) & 0x1F];
    SerialNumber[1]  = keychars[(seal1 >> 25) & 0x1F];
    SerialNumber[2]  = keychars[(seal1 >> 20) & 0x1F];
    SerialNumber[3]  = keychars[(seal1 >> 15) & 0x1F];
    SerialNumber[4]  = '-';
    SerialNumber[5]  = keychars[(seal1 >> 10) & 0x1F];
    SerialNumber[6]  = keychars[(seal1 >>  5) & 0x1F];
    SerialNumber[7]  = keychars[(seal1      ) & 0x1F];    
    SerialNumber[8]  = keychars[(seal2 >> 30) & 0x1F];
    SerialNumber[9]  = '-';
    SerialNumber[10] = keychars[(seal2 >> 25) & 0x1F];
    SerialNumber[11] = keychars[(seal2 >> 20) & 0x1F];
    SerialNumber[12] = keychars[(seal2 >> 15) & 0x1F];
    SerialNumber[13] = keychars[(seal2 >> 10) & 0x1F];
    SerialNumber[14] = '-';
    SerialNumber[15] = keychars[(seal2 >>  5) & 0x1F];
    SerialNumber[16] = keychars[(seal2      ) & 0x1F];                   
    SerialNumber[17] = 0;
 
    /*
        generate digest extension
    */           
    char combined[512];
    unsigned char digest[32];
    char checksum[8];
    
    strncpy(combined, regname, 256);
    strncat(combined, SerialNumber, 256);
    
    sha256((unsigned char*)combined, strlen(combined), digest);                  
    
    unsigned int val = ((digest[30] << 8) | digest[31]);
            
    checksum[0] = keychars[(val >> 5) & 0x1F];
    checksum[1] = keychars[(val     ) & 0x1F];           
    checksum[2] = 0;
                                  
    strcat(SerialNumber, checksum);
    
    fprintf(keyf, "Name: %s\n", orgname);
    fprintf(keyf, "Code: %s\n", SerialNumber);    
    
    fprintf(logf, "Name: %s\n", orgname);
    fprintf(logf, "Regn: %s\n", regname);    
    //fprintf(logf, "Idx1: %d, Idx2: %d\n", idx1, idx2);
    //fprintf(logf, "Sea1: %u, Sea2: %u\n", seal1, seal2);
    fprintf(logf, "Code: %s\n", SerialNumber);    
    
    if (SerialNumber[0] == '*' || SerialNumber[0] == '-') {
        fprintf(keyf, "Internal failure when trying to generate a valid key.\n");
        return ERC_INTERNAL;
    }
    
    fclose(inf);
    fclose(keyf);
    fclose(logf);

    return ERC_SUCCESS;
}
