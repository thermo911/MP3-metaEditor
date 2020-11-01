#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT
#include <stdint.h>
#include "ID3v2.h"

void printInfoID3header(ID3header* h);
void printFrameHeaderInfo(FrameHeader* fh);
void printFrame(Frame* frame);
void printTag(ID3v2_Tag* tag);
void printTagInfo(ID3v2_Tag* tag);

#endif 
