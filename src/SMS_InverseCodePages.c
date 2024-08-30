/*
#     ___  _ _      ___
#    |    | | |    |
# ___|    |   | ___|    PS2DEV Open Source Project.
#----------------------------------------------------------
# (c) 2006 Npl
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
*/

#include "SMS.h"
#include "SMS_GS.h"

typedef struct SMS_InvCodeTable {
 unsigned short m_uniCharacter[128];
 char  m_uniIndex[128];
} SMS_InvCodeTable;

static const SMS_InvCodeTable _invCodeTables[] __attribute__(   (  section( ".data" )  )   ) =
{
 [GSCodePage_WinLatin2] = { /* invCodeTable1250 / GSCodePage_WinLatin2 */
  {
    0x0081, 0x0083, 0x0088, 0x0090, 0x0098, 0x00A0, 0x00A4, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00B0,
    0x00B1, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00BB, 0x00C1, 0x00C2, 0x00C4, 0x00C7, 0x00C9, 0x00CB, 0x00CD, 0x00CE, 0x00D3,
    0x00D4, 0x00D6, 0x00D7, 0x00DA, 0x00DC, 0x00DD, 0x00DF, 0x00E1, 0x00E2, 0x00E4, 0x00E7, 0x00E9, 0x00EB, 0x00ED, 0x00EE, 0x00F3,
    0x00F4, 0x00F6, 0x00F7, 0x00FA, 0x00FC, 0x00FD, 0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D, 0x010E, 0x010F,
    0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B, 0x0139, 0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143, 0x0144, 0x0147, 0x0148,
    0x0150, 0x0151, 0x0154, 0x0155, 0x0158, 0x0159, 0x015A, 0x015B, 0x015E, 0x015F, 0x0160, 0x0161, 0x0162, 0x0163, 0x0164, 0x0165,
    0x016E, 0x016F, 0x0170, 0x0171, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E, 0x02C7, 0x02D8, 0x02D9, 0x02DB, 0x02DD, 0x2013,
    0x2014, 0x2018, 0x2019, 0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A, 0x20AC, 0x2122
  },
  {
      1,   3,   8,  16,  24,  32,  36,  38,  39,  40,  41,  43,  44,  45,  46,  48,
     49,  52,  53,  54,  55,  56,  59,  65,  66,  68,  71,  73,  75,  77,  78,  83,
     84,  86,  87,  90,  92,  93,  95,  97,  98, 100, 103, 105, 107, 109, 110, 115,
    116, 118, 119, 122, 124, 125,  67,  99,  37,  57,  70, 102,  72, 104,  79, 111,
     80, 112,  74, 106,  76, 108,  69, 101,  60,  62,  35,  51,  81, 113,  82, 114,
     85, 117,  64,  96,  88, 120,  12,  28,  42,  58,  10,  26,  94, 126,  13,  29,
     89, 121,  91, 123,  15,  31,  47,  63,  14,  30,  33,  34, 127,  50,  61,  22,
     23,  17,  18,   2,  19,  20,   4,   6,   7,  21,   5,   9,  11,  27,   0,  25
  }
 },
 [GSCodePage_WinCyrillic] = { /* invCodeTable1251 / GSCodePage_WinCyrillic */
  {
    0x0098, 0x00A0, 0x00A4, 0x00A6, 0x00A7, 0x00A9, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00B0, 0x00B1, 0x00B5, 0x00B6, 0x00B7, 0x00BB,
    0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040E, 0x040F, 0x0410, 0x0411,
    0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F, 0x0420, 0x0421,
    0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 0x0430, 0x0431,
    0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F, 0x0440, 0x0441,
    0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F, 0x0451, 0x0452,
    0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x045E, 0x045F, 0x0490, 0x0491, 0x2013, 0x2014,
    0x2018, 0x2019, 0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A, 0x20AC, 0x2116, 0x2122
  },
  {
     24,  32,  36,  38,  39,  41,  43,  44,  45,  46,  48,  49,  53,  54,  55,  59,
     40,   0,   1,  42,  61,  50,  47,  35,  10,  12,  14,  13,  33,  15,  64,  65,
     66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,
     82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,
     98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
    114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,  56,  16,
      3,  58,  62,  51,  63,  60,  26,  28,  30,  29,  34,  31,  37,  52,  22,  23,
     17,  18,   2,  19,  20,   4,   6,   7,  21,   5,   9,  11,  27,   8,  57,  25
  }
 },
 [GSCodePage_WinLatin1] = { /* invCodeTable1252 / GSCodePage_WinLatin1 */
  {
    0x0081, 0x008D, 0x008F, 0x0090, 0x009D, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA,
    0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA,
    0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA,
    0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA,
    0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF, 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA,
    0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA,
    0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF, 0x0152, 0x0153, 0x0160, 0x0161, 0x0178, 0x017D, 0x017E, 0x0192, 0x02C6, 0x02DC, 0x2013,
    0x2014, 0x2018, 0x2019, 0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A, 0x20AC, 0x2122
  },
  {
      1,  13,  15,  16,  29,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,
     43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,
     59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,
     75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,
     91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
    123, 124, 125, 126, 127,  12,  28,  10,  26,  31,  14,  30,   3,   8,  24,  22,
     23,  17,  18,   2,  19,  20,   4,   6,   7,  21,   5,   9,  11,  27,   0,  25
  }
 },
 [GSCodePage_WinGreek] = { /* invCodeTable1253 / GSCodePage_WinGreek */
  {
    0x0081, 0x0088, 0x008A, 0x008C, 0x008D, 0x008E, 0x008F, 0x0090, 0x0098, 0x009A, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A3,
    0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B5, 0x00B6,
    0x00B7, 0x00BB, 0x00BD, 0x0192, 0x0384, 0x0385, 0x0386, 0x0388, 0x0389, 0x038A, 0x038C, 0x038E, 0x038F, 0x0390, 0x0391, 0x0392,
    0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, 0x03A0, 0x03A1, 0x03A3,
    0x03A4, 0x03A5, 0x03A6, 0x03A7, 0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x03AC, 0x03AD, 0x03AE, 0x03AF, 0x03B0, 0x03B1, 0x03B2, 0x03B3,
    0x03B4, 0x03B5, 0x03B6, 0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, 0x03C0, 0x03C1, 0x03C2, 0x03C3,
    0x03C4, 0x03C5, 0x03C6, 0x03C7, 0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0x2013, 0x2014, 0x2015, 0x2018, 0x2019,
    0x201A, 0x201C, 0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039, 0x203A, 0x20AC, 0x2122, 0xF8F9, 0xF8FA, 0xF8FB
  },
  {
      1,   8,  10,  12,  13,  14,  15,  16,  24,  26,  28,  89,  30,  31,  32,  35,
     36,  37,  38,  39,  40,  41,  43,  44,  45,  46,  48,  97,  98,  51,  53,  102,
     55,  59,  61,   3,  52,  33,  34,  56,  57,  58,  60,  62,  63,  64,  11,  114,
     115,  116,  117,  118,  119,  120,  121,  74,  75,  76,  77,  78,  79,  80,  81,  83,
     84,  85,  86,  87,  88,  29,  90,  91,  92,  93,  94,  95,  96,  49,  50,  51,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
    68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,  22,  23,  47,  17,  18,
      2,  19,  20,   4,   6,   7,  21,   5,   9,  65,  27,   0,  25,  42,  82, 127
  }
 }
};

static const char NOT_AVAILABLE_CHAR = '?';

SMS_INLINE char UnicodeToCP( const SMS_InvCodeTable *codeTable, const unsigned short uniCodeChar)
{
	int index = 64, step = 64;
	const unsigned short *searchTable = codeTable->m_uniCharacter;

	if(uniCodeChar < 128)
		return (char)uniCodeChar;

	while(step > 0 )
	{
		const unsigned short temp = searchTable[index];
		step >>=1;

		if( uniCodeChar < temp)
			index -= step;
		else if(uniCodeChar > temp)
			index += step;
		else
			return 128 + codeTable->m_uniIndex[index];
	}

	return NOT_AVAILABLE_CHAR;
}

int TranslateUTF8( GSCodePage codePage, char* outBuff, int bufSize, const char* utfString)
{
	const SMS_InvCodeTable *codeTable = &_invCodeTables[codePage];

	int length = 0;
	unsigned char c = (unsigned char)*utfString++;

	while(length < bufSize)
	{
		if ( c <= 0x7F )
		{ /* ASCII */
			if( c == 0 )
				break;

			*outBuff++ = (char)c;
			++length;
		} else if( c >= 0xC0 && c < 0xF0  )
		{
			/* either 1 or 2 additional Bytes */
			unsigned short uniChar = (c & 0x1F);
			int twoBytes = (c & 0x20) != 0;

			c = (unsigned char)*utfString++;
			if( c == 0 )
				break;

			uniChar = (uniChar << 6) | (c & 0x3F);

			if(twoBytes)
			{
				c = (unsigned char)*utfString++;
				if( c == 0)
					break;

				uniChar = (uniChar << 6) | (c & 0x3F);
			}

			*outBuff++ = UnicodeToCP(codeTable, uniChar);
			++length;

		} else
			; /* either not the start of a Character or out of supported range ( >= 2^16) */

		c = (unsigned char)*utfString++;
	}

	*outBuff = '\0';
	return length < bufSize ? length : -1;
}


