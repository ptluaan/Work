#pragma once
#define BUFFER_SIZE	1024
#define HEADER_SIZE	3
enum HeaderType
{
	NOTHING,
	LOGIN,
	FILE,
	FILE_SIZE,
	FILE_NAME,
	MESSEGES,
	LIST_USER
};

void createPackage(unsigned char* buffer, HeaderType header, int size, const unsigned char* messge)
{
	buffer[0] = header;
	size += 3; 
	buffer[1] = (size >> 8) & 0xFF;
	buffer[2] = size & 0xFF;
	for (int i = 0; i < size; ++i)
		buffer[i + 3] = messge[i];
}
