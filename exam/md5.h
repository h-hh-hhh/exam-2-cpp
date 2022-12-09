#pragma once
#include <string>

typedef unsigned DigestArray[4];

typedef unsigned(*DgstFctn)(unsigned a[]);

typedef union uwb {
	unsigned w;
	unsigned char b[4];
} MD5union;

std::string GetMD5String(std::string msg);