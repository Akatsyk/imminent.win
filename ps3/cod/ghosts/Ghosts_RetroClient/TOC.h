#define TOC (0xA7F3C8)

int Cbuff_AddText_t[2] = { Adr::Cbuff_AddText, TOC };
void(*cBuf_Addtext)(int localClientNum, char* text) = (void(*)(int, char*))&Cbuff_AddText_t;