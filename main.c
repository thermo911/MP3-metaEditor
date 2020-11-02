#include <stdio.h>
#include "ID3v2.h"
#include "service.h"
#include <string.h>
#include "UIstuff.h"
#include "mem_debugger.h"
#include "DebugOutput.h"

int main()
{
	char* command1 = (char*)malloc(12 * sizeof(char));
	char* command2 = (char*)malloc(40 * sizeof(char));
	char* command3 = (char*)malloc(40 * sizeof(char));
	char* filename = (char*)malloc(40 * sizeof(char));
	short fileRead = 0;
	short changes = 0;
	FILE* file = NULL;
	ID3v2_Tag* tag = NULL;
	

	printf("Welcome to MP3 MetaEdidor by S&D company!\n");

	while (1)
	{
		short reading = 0;
		short changing = 0;
		short printing = 0;
		short saving = 0;
		short help = 0;

		if (fileRead)
			printf("%s>>> ", filename);
		else
			printf(">>> ");

		scanf("%s", command1);
		if (!strcmp(command1, "open")) reading = 1;
		else if (!strcmp(command1, "change")) changing = 1;
		else if (!strcmp(command1, "print")) printing = 1;
		else if (!strcmp(command1, "save")) saving = 1;
		else if (!strcmp(command1, "help")) help = 1;
		else if (!strcmp(command1, "exit"))
		{
			if (!fileRead)
			{
				printf("  exit\n");
				break;
			}
			else if (!changes)
			{
				if (tag != NULL) freeMemory(tag);
				if (file != NULL) fclose(file);
				printf("  exit\n");
				break;
			}
			else
			{
				printf("  There are not saved changes!\n");
				printf("  tip: use 'save' to save changes or 'EXIT' to exit without saving\n");
				continue;
			}
		}
		else if (!strcmp(command1, "EXIT"))
		{
			if (tag != NULL) freeMemory(tag);
			if (file != NULL) fclose(file);
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
				//printTagInfo(tag);
				//printInfoID3header(tag->header);
				//printTag(tag);
				if (tag == NULL || tag->header->version[0]<3)
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
			else printf("  no file to print frames from\n");
		}

		if (changing)
		{
			if (fileRead)
			{
				scanf("%s", command2);
				gets(command3);
				if (changeFrameData(tag, command2, command3 + 1, strlen(command3 + 1)))
				{
					printf("  frame %s successfully changed\n", command2);
					changes = 1;
				}
				else
				{
					printf("  no such frame or incorrect frame format\n");
				}
			}
			else printf("  no file to change\n");
			
		}

		if (saving)
		{
			if (!changes)
			{
				printf("  no changes to save\n");
				continue;
			}
			if (fileRead)
			{
				writeTagIntoFileStart(file, tag);
				printf("  changes saved\n");
				freeMemory(tag);
				tag = NULL;
				fclose(file);
				printf("  file closed\n");
				fileRead = 0;
				changes = 0;
			}
			else
			{
				printf("  no file to save\n");
			}
		}

		if (help)
		{
			printf("  User's commands:\n");
			printf("  1) help\n");
			printf("  - printing commands list\n\n");
			printf("  2) open <filename>.mp3\n");
			printf("  - opening the file\n\n");
			printf("  3) print <frameID>\n");
			printf("  - printing frame data (or all frames if <frameID> = all)\n\n");
			printf("  4) change <frameID> <new frame data>\n");
			printf("  - changing frame with <frameID> data to <new frame data>\n\n");
			printf("  5) save\n");
			printf("  - saving the changes\n\n");
			printf("  6) exit\n");
			printf("  - exiting\n\n");
		}
	}
	free(command1);
	free(command2);
	free(command3);
	free(filename);
	mem_debugger_dump_info(0, NULL);
}