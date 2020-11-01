#include <stdio.h>
#include "ID3v2.h"
#include "service.h"
#include <string.h>
#include "UIstuff.h"

int main()
{
	char* command1 = (char*)malloc(12 * sizeof(char));
	char* command2 = (char*)malloc(40 * sizeof(char));
	char* command3 = (char*)malloc(40 * sizeof(char));
	char* filename = (char*)malloc(40 * sizeof(char));
	short fileRead = 0;
	FILE* file = NULL;
	ID3v2_Tag* tag = NULL;

	printf("Welcome to MP3 MetaEdidor by S&D company!\n");

	while (1)
	{
		short reading = 0;
		short changing = 0;
		short printing = 0;
		short saving = 0;

		if (fileRead)
			printf("%s>>> ", filename);
		else
			printf(">>> ");

		scanf("%s", command1);
		if (!strcmp(command1, "open")) reading = 1;
		else if (!strcmp(command1, "change")) changing = 1;
		else if (!strcmp(command1, "print")) printing = 1;
		else if (!strcmp(command1, "save")) saving = 1;
		else if (!strcmp(command1, "exit"))
		{
			printf("  exit\n");
			break;
		}
		else
		{
			printf("  uncknown command\n");
			continue;
		}

		if (reading)
		{
			scanf("%s", command2);
			if ((file = fopen(command2, "r+b")) == NULL)
			{
				printf("  file not found\n");
				continue;
			}
			else
			{
				strcpy(filename, command2);
				fileRead = 1;
				printf("  file reading completed\n");
				tag = getTag(file);
				if (tag == NULL)
				{
					printf("  no mp3 tag or incorrect tag format\n");
					fclose(file);
					fileRead = 0;
					continue;
				}
				else
				{
					printf("  tag successfully read\n");
					continue;
				}
			}
		}

		if (printing)
		{
			if (fileRead)
			{
				scanf("%s", command2);
				printFrames(tag, command2);
			}
			else printf("  source not found\n");
		}

		if (changing)
		{
			scanf("%s", command2);
			gets(command3);
			if (changeFrameData(tag, command2, command3+1, strlen(command3+1)))
			{
				printf("  frame %s successfully changed\n", command2);
			}
			else
			{
				printf("  no such frame or incorrect frame format\n");
			}
		}

		if (saving)
		{
			writeTagIntoFileStart(file, tag);
			printf("  changes saved\n");
			fclose(file);
			printf("  file closed\n");
			fileRead = 0;
		}
	}
}