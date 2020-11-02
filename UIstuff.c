#include "UIstuff.h"

void printFrames(ID3v2_Tag* tag, const char* frameID)
{
	if (strcmp(frameID, "all"))
	{
		Frame* frame = getFrameByID(tag, frameID);
		if (frame == NULL || frame->mayBeShown == 0)
		{
			printf("  frame %s not found or can't be shown\n", frameID);
		}
		else
		{
			char* str = getFrameDataAsString(frame);
			printf("  %s->%s\n", frameID, str);
			free(str);
		}
	} 
	else
	{
		for (int i = 0; i < tag->numOfFrames; i++)
		{
			Frame* frame = tag->frames[i];
			if (frame->mayBeShown)
			{
				char* str = getFrameDataAsString(frame);
				printf("  %s->%s\n", frame->frameHeader->frameID, str);
				free(str);
			}
		}
	}
}