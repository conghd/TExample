/*
 * DataBuffer.cpp
 * Copyright (c) 2012 HanoiLabs
 *
 */

#include "DataBuffer.h"

DataBuffer::DataBuffer() {
	this->filename[0] = '\0';
	this->size = 0;
	this->position = 0;
	this->buffer = NULL;
}

DataBuffer::DataBuffer(DataBuffer *dataBuffer, unsigned int size) {

}

DataBuffer::~DataBuffer() {
	if (this->filename != NULL) this->filename[0] = '\0';
	this->size = 0;
	this->position = 0;
	if (this->buffer != NULL) this->buffer = NULL;
}

void DataBuffer::read(char *filename, unsigned char relativePath) {
	if (this->filename != NULL) this->filename[0] = '\0';
	this->size = 0;
	this->position = 0;
	if (this->buffer != NULL) free(this->buffer);

	#ifdef __IPHONE_4_0
		FILE *f;
		char fname[MAX_PATH] = {""};

		if(relativePath)
		{
			get_file_path(getenv("FILESYSTEM"), fname);
			strcat(fname, filename);
		}
		else strcpy(fname, filename);

		f = fopen(fname, "rb");
		if(!f) return NULL;

//		DataBuffer *dataBuffer = (DataBuffer *) calloc(1, sizeof(DataBuffer));

		strcpy(this->filename, fname);


		fseek(f, 0, SEEK_END);
		this->size = ftell(f);
		fseek(f, 0, SEEK_SET);

		this->buffer = (unsigned char *) calloc(1, this->size + 1);
		fread(this->buffer, this->size, 1, f);
		this->buffer[this->size] = 0;

		fclose(f);

		return ;


	#else
		char fpath[MAX_PATH] = {""},
			 fname[MAX_PATH] = {""};

		unzFile		    uf;
		unz_file_info   fi;
		unz_file_pos    fp;

		strcpy(fpath, getenv("FILESYSTEM"));

		uf = unzOpen(fpath);

		if(!uf) return ;

		if(relativePath) sprintf(fname, "assets/%s", filename);
		else strcpy(fname, filename);

		unzGoToFirstFile(uf);

//		DataBuffer *dataBuffer = (DataBuffer *) calloc(1, sizeof(DataBuffer));

		unzGetFilePos(uf, &fp);

		if(unzLocateFile(uf, fname, 1) == UNZ_OK)
		{
			unzGetCurrentFileInfo( uf,
								   &fi,
									this->filename,
									MAX_PATH,
									NULL, 0,
									NULL, 0);

			if(unzOpenCurrentFilePassword(uf, NULL) == UNZ_OK)
			{
				this->position = 0;
				this->size	 = fi.uncompressed_size;
				this->buffer   = (unsigned char *) realloc(this->buffer, fi.uncompressed_size + 1);
				this->buffer[fi.uncompressed_size] = 0;

				while(unzReadCurrentFile(uf, this->buffer, fi.uncompressed_size) > 0){}

				unzCloseCurrentFile(uf);

				unzClose(uf);

				return;
			}
		}

		unzClose(uf);

		return ;

	#endif
}

unsigned int DataBuffer::write(void *buffer, unsigned int size) {
	if (this->position + size > this->size) {
		size = this->size - this->position;
	}

	memcpy(buffer, &this->buffer[this->position], size);
	this->position += size;

	return size;
}

void DataBuffer::insert(char *str, unsigned int position) {
	unsigned int s1 = strlen(str);
	unsigned int s2 = this->size + s1 + 1;

	char *buffer = (char *)this->buffer;
	char *tmp	 = (char *)calloc(1, s2);

	if(position)
	{ strncpy( &tmp[0], &buffer[0], position ); }

	strcat(&tmp[position], str );

	strcat(&tmp[position + s1], &buffer[position]);

	this->size = s2;

	free(this->buffer );
	this->buffer = ( unsigned char * )tmp;
}

unsigned int DataBuffer::getSize() {
	return this->size;
}

unsigned int DataBuffer::getPosition() {
	return this->position;
}

char *DataBuffer::getFilename() {
	return this->filename;
}
