#include "DebugOutput.h"

void printInfoID3header(ID3header* h)
{
    printf("====================\n");
    printf("ID3 HEADER:\n");
    printf("\tsignature:       %s\n", h->signature);
    printf("\tversion:         %d.%d\n", h->version[0], h->version[1]);
    printf("\tflags byte:      %x\n", h->flagData);
    printf("\tsize:            %d\n", h->size);
    printf("====================\n");
}

void printFrameHeaderInfo(FrameHeader* fh)
{
    printf("======================\n");
    printf("FRAME HEADER:\n");
    printf("\tframeID:                       %s\n", fh->frameID);
    printf("\tframe data size :              %d\n", fh->dataSize);
    printf("STATUS FLAGS:\n");
    printf("\ttag alter preservation:        %d\n", fh->fs.fileAlterPreservation);
    printf("\tfile alter preservation:       %d\n", fh->fs.fileAlterPreservation);
    printf("\tread only:                     %d\n", fh->fs.readOnly);
    printf("FORMAT FLAGS:\n");

    printf("\tgrouping identity:             %d\n", fh->ff.groupingIdentity);
    printf("\tcompression:                   %d\n", fh->ff.compression);
    printf("\tencryption:                    %d\n", fh->ff.encryption);
    printf("\tunsynchronisation:             %d\n", fh->ff.unsynchronisation);
    printf("\tdata length:                   %d\n", fh->ff.dataLengthIndicator);
    printf("======================\n");
}

void printFrame(Frame* frame)
{
    printf("======================\n");
    printf("%s\n", frame->frameHeader->frameID);
    printf("encoding: %d\n", frame->encoding);
    printf("data size: %d\n", frame->frameHeader->dataSize);
    printf("offset: %d\n", frame->dataOffset);
    /*for (int i = frame->dataOffset; i < frame->frameHeader->dataSize; i++)
    {
        printf("%c", frame->data[i]);
    }
    printf("\n");
    if (frame->mayBeShown != 1)
    {
        printf("DATA WILL NOT BE SHOWN\n");
    }*/
    printf("======================\n");
}

void printTag(ID3v2_Tag* tag)
{
    printInfoID3header(tag->header);
    for (int i = 0; i < tag->numOfFrames; i++)
    {
        printFrame(tag->frames[i]);
    }
}

void printTagInfo(ID3v2_Tag* tag)
{
    printf("ID3v2 TAG:\n");
    printf("\tnumber of frames: %d\n", tag->numOfFrames);
    printf("\ttotal size:       %d\n", tag->totalSize);
}
