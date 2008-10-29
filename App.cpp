#include "stdafx.h"
#include "App.h"
#include "MainFrame.h"
#include "CopyProtectionDialog.h"
#include "keygen/sha2.h"
#include "EXECryptor.h"

IMPLEMENT_APP(MyApp);

#ifndef LITEVERSION
// public key
extern unsigned int pub[16384];

static void sha256_rounds(unsigned char *s, unsigned char *d, unsigned int r) {    
    int j;
    
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
    
    memcpy(d, s, 32);
}

static void sha256_16k(char *in, unsigned char *out, unsigned int r) {
    unsigned char s[32];
    unsigned char d[32];    
    
    sha256((unsigned char*)in, strlen(in), s);    
    
    sha256_rounds((unsigned char*)s, (unsigned char*)d, r);
    
    memcpy(out, d, 32);
}

bool Verify_Serial(wxString p_regname, wxString p_serial) {                    
    char regbuff[256];
    char bregname[256], bserial[256];
    char *regname = bregname;
    char *serial = bserial;
    unsigned int check1, check2, seal1, seal2;        
    
    CRYPT_START
        
    memset(regbuff, 0, sizeof(regbuff));
    memset(bregname, 0, sizeof(bregname));
    memset(bserial, 0, sizeof(bserial));
    
    strncpy(regname, p_regname.c_str(), 256);
    strncpy(serial, p_serial.c_str(), 256);
            
    char *s = regname;
    int len = strlen(s);
    
    if (len > 255) {
        return false;
    }
    
    if (strlen(serial) > 255) {
        return false;
    }
    
    /*
        strip starting whitespace
    */                                   
    while(*s == ' ') {
        s++;
        len--;
    }         
    
    strncpy(regbuff, s, len);
    
    /*
        axe trailing spaces, newlines
    */
    int len2 = strlen(regbuff);
    int pos = len2 - 1;
    
    while ((regbuff[pos] == ' ' || regbuff[pos] == 13 || regbuff[pos] == 11) && pos > 0) {
        regbuff[pos] = 0;
        pos--;
    }
    
    int len3 = strlen(regbuff);
    int j;        
    
    for (j = 0; j < len3; j++) {
        if (regbuff[j] > 126 || regbuff[j] < 32) {
            regbuff[j] = '_';
        }
        regbuff[j] = toupper(regbuff[j]);
    }             
    
    unsigned char dg[32];
    
    sha256_16k(regbuff, dg, 0);
    
    unsigned int idx1 = ((dg[30] << 8) | dg[31]) & 0x3FFF;
    unsigned int idx2 = ((dg[28] << 8) | dg[29]) & 0x3FFF;
    
    check1 = pub[idx1];
    check2 = pub[idx2];
    
    char keychars[32] = { '1', '3', '4', '5', '6', '7', '8', '9',
                          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
                          'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 
                          'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};    
        
    unsigned int dcount = 0;
    seal1 = 0;
    seal2 = 0;
    
    while (*serial != 0 && dcount < 7) {
        for (j = 0; j < 32; j++) {
            if (toupper(*serial) == keychars[j]) {
                dcount++;
                seal1 <<= 5;
                seal1 |= j; 
            }
        }                            
        serial++;
    }
    
    dcount = 0;
    
    while (*serial != 0 && dcount < 7) {
        for (j = 0; j < 32; j++) {
            if (toupper(*serial) == keychars[j]) {
                dcount++;
                seal2 <<= 5;
                seal2 |= j; 
            }
        }                            
        serial++;
    }
            
    unsigned char sr[32];
    unsigned char or[32];
    
    memset(sr, 0, 32);
    sr[28] = (seal1 >> 24) & 0xFF;
    sr[29] = (seal1 >> 16) & 0xFF;
    sr[30] = (seal1 >>  8) & 0xFF;
    sr[31] = (seal1 >>  0) & 0xFF;
    
    sha256_rounds(sr, or, idx1);

    seal1 = (or[28] << 24)
           | (or[29] << 16)
           | (or[30] <<  8)
           | (or[31]      );
           
    if (check1 != seal1) {
        return false;
    }           
           
    memset(sr, 0, 32);
    sr[28] = (seal2 >> 24) & 0xFF;
    sr[29] = (seal2 >> 16) & 0xFF;
    sr[30] = (seal2 >>  8) & 0xFF;
    sr[31] = (seal2 >>  0) & 0xFF;
    
    sha256_rounds(sr, or, idx2);

    seal2 = (or[28] << 24)
           | (or[29] << 16)
           | (or[30] <<  8)
           | (or[31]      );           
    
    if (check1 != seal1 || check2 != seal2) {
        return false;
    }                    
        
    return true;     
    
    CRYPT_END                    
}
#endif

bool MyApp::OnInit()
{   
    wxConfig * config = new wxConfig(wxT("Leela"), wxT("Sjeng.Org"));    
    wxConfig::Set(config);
    	
#ifndef LITEVERSION
    CRYPT_START
    wxString name = config->Read(wxT("Name"));
    wxString code = config->Read(wxT("Code"));        
    
    while (!Verify_Serial(name, code)) {        
        CopyProtectionDialog dialog(NULL);                
        if (dialog.ShowModal() == wxID_OK) {
            name = dialog.getName();
            code = dialog.getCode();
            config->Write(wxT("Name"), name);
            config->Write(wxT("Code"), code);
            if (!Verify_Serial(name, code)) {
                ::wxMessageBox(_("The registration info you entered is not correct.\nPlease enter the name and code you received\nwhen you bought the program."),
                               _("Copyprotection check"));
            }
        } else {        
            return false;
        }                
    }
    CRYPT_END
#endif     

    MainFrame* frame = new MainFrame(NULL, _("Leela"));    
    frame->Show();
    
    SetTopWindow(frame);

    return true;
}
