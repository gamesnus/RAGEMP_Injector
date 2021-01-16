#include "MD5.hpp"

/* system implementation headers */
#include <cstdio>

#pragma warning(disable : 4267)
// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

///////////////////////////////////////////////

// F, G, H and I are basic MD5 functions.
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {
	return x & y | ~x & z;
}

inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {
	return x & z | y & ~z;
}

inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {
	return x ^ y ^ z;
}

inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {
	return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
	return (x << n) | (x >> (32 - n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
}

inline void MD5::GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
}

inline void MD5::HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
}

inline void MD5::II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
}

//////////////////////////////////////////////

// default ctor, just initailize
MD5::MD5()
{
	init();
}

//////////////////////////////////////////////

// nifty shortcut ctor, compute MD5 for string and finalize it right away
MD5::MD5(const std::string& text)
{
	init();
	update(text.c_str(), text.length());
	finalize();
}

//////////////////////////////

void MD5::init()
{
	finalized = false;

	count[0] = 0;
	count[1] = 0;

	// load magic initialization constants.
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

//////////////////////////////

// decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint4)input[j]) | (((uint4)input[j + 1]) << 8) |
		(((uint4)input[j + 2]) << 16) | (((uint4)input[j + 3]) << 24);
}

//////////////////////////////

// encodes input (uint4) into output (unsigned char). Assumes len is
// a multiple of 4.
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
	for (size_type i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8) & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}

//////////////////////////////

// apply MD5 algo on a block
void MD5::transform(const uint1 block[blocksize])
{
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	decode(x, block, blocksize);

	/* Round 1 */
	FF(a, b, c, d, x[0], S11, 0xD76AA478); /* 1 */
	FF(d, a, b, c, x[1], S12, 0xE8C7B756); /* 2 */
	FF(c, d, a, b, x[2], S13, 0x242070DB); /* 3 */
	FF(b, c, d, a, x[3], S14, 0xC1BDCEEE); /* 4 */
	FF(a, b, c, d, x[4], S11, 0xF57C0FAF); /* 5 */
	FF(d, a, b, c, x[5], S12, 0x4787C62A); /* 6 */
	FF(c, d, a, b, x[6], S13, 0xA8304613); /* 7 */
	FF(b, c, d, a, x[7], S14, 0xFD469501); /* 8 */
	FF(a, b, c, d, x[8], S11, 0x698098D8); /* 9 */
	FF(d, a, b, c, x[9], S12, 0x8B44F7AF); /* 10 */
	FF(c, d, a, b, x[10], S13, 0xFFFF5BB1); /* 11 */
	FF(b, c, d, a, x[11], S14, 0x895CD7BE); /* 12 */
	FF(a, b, c, d, x[12], S11, 0x6B901122); /* 13 */
	FF(d, a, b, c, x[13], S12, 0xFD987193); /* 14 */
	FF(c, d, a, b, x[14], S13, 0xA679438E); /* 15 */
	FF(b, c, d, a, x[15], S14, 0x49B40821); /* 16 */

	/* Round 2 */
	GG(a, b, c, d, x[1], S21, 0xF61E2562); /* 17 */
	GG(d, a, b, c, x[6], S22, 0xC040B340); /* 18 */
	GG(c, d, a, b, x[11], S23, 0x265E5A51); /* 19 */
	GG(b, c, d, a, x[0], S24, 0xE9B6C7AA); /* 20 */
	GG(a, b, c, d, x[5], S21, 0xD62F105D); /* 21 */
	GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
	GG(c, d, a, b, x[15], S23, 0xD8A1E681); /* 23 */
	GG(b, c, d, a, x[4], S24, 0xE7D3FBC8); /* 24 */
	GG(a, b, c, d, x[9], S21, 0x21E1CDE6); /* 25 */
	GG(d, a, b, c, x[14], S22, 0xC33707D6); /* 26 */
	GG(c, d, a, b, x[3], S23, 0xF4D50D87); /* 27 */
	GG(b, c, d, a, x[8], S24, 0x455A14ED); /* 28 */
	GG(a, b, c, d, x[13], S21, 0xA9E3E905); /* 29 */
	GG(d, a, b, c, x[2], S22, 0xFCEFA3F8); /* 30 */
	GG(c, d, a, b, x[7], S23, 0x676F02D9); /* 31 */
	GG(b, c, d, a, x[12], S24, 0x8D2A4C8A); /* 32 */

	/* Round 3 */
	HH(a, b, c, d, x[5], S31, 0xFFFA3942); /* 33 */
	HH(d, a, b, c, x[8], S32, 0x8771F681); /* 34 */
	HH(c, d, a, b, x[11], S33, 0x6D9D6122); /* 35 */
	HH(b, c, d, a, x[14], S34, 0xFDE5380C); /* 36 */
	HH(a, b, c, d, x[1], S31, 0xA4BEEA44); /* 37 */
	HH(d, a, b, c, x[4], S32, 0x4BDECFA9); /* 38 */
	HH(c, d, a, b, x[7], S33, 0xF6BB4B60); /* 39 */
	HH(b, c, d, a, x[10], S34, 0xBEBFBC70); /* 40 */
	HH(a, b, c, d, x[13], S31, 0x289B7EC6); /* 41 */
	HH(d, a, b, c, x[0], S32, 0xEAA127FA); /* 42 */
	HH(c, d, a, b, x[3], S33, 0xD4EF3085); /* 43 */
	HH(b, c, d, a, x[6], S34, 0x4881D05); /* 44 */
	HH(a, b, c, d, x[9], S31, 0xD9D4D039); /* 45 */
	HH(d, a, b, c, x[12], S32, 0xE6DB99E5); /* 46 */
	HH(c, d, a, b, x[15], S33, 0x1FA27CF8); /* 47 */
	HH(b, c, d, a, x[2], S34, 0xcC4AC5665); /* 48 */

	/* Round 4 */
	II(a, b, c, d, x[0], S41, 0xF4292244); /* 49 */
	II(d, a, b, c, x[7], S42, 0x432AFF97); /* 50 */
	II(c, d, a, b, x[14], S43, 0xAB9423A7); /* 51 */
	II(b, c, d, a, x[5], S44, 0xFC93A039); /* 52 */
	II(a, b, c, d, x[12], S41, 0x655B59C3); /* 53 */
	II(d, a, b, c, x[3], S42, 0x8F0CCC92); /* 54 */
	II(c, d, a, b, x[10], S43, 0xFFEFF47D); /* 55 */
	II(b, c, d, a, x[1], S44, 0x85845DD1); /* 56 */
	II(a, b, c, d, x[8], S41, 0x6FA87E4F); /* 57 */
	II(d, a, b, c, x[15], S42, 0xFE2CE6E0); /* 58 */
	II(c, d, a, b, x[6], S43, 0xA3014314); /* 59 */
	II(b, c, d, a, x[13], S44, 0x4E0811A1); /* 60 */
	II(a, b, c, d, x[4], S41, 0xF7537E82); /* 61 */
	II(d, a, b, c, x[11], S42, 0xBD3AF235); /* 62 */
	II(c, d, a, b, x[2], S43, 0x2AD7D2BB); /* 63 */
	II(b, c, d, a, x[9], S44, 0xEB86D391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	// Zeroize sensitive information.
	memset(x, 0, sizeof x);
}

//////////////////////////////

// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const unsigned char input[], size_type length)
{
	// compute number of bytes mod 64
	size_type index = count[0] / 8 % blocksize;

	// Update number of bits
	if ((count[0] += (length << 3)) < (length << 3))
		count[1]++;
	count[1] += (length >> 29);

	// number of bytes we need to fill in buffer
	size_type firstpart = 64 - index;

	size_type i;

	// transform as many times as possible.
	if (length >= firstpart)
	{
		// fill buffer first, transform
		memcpy(&buffer[index], input, firstpart);
		transform(buffer);

		// transform chunks of blocksize (64 bytes)
		for (i = firstpart; i + blocksize <= length; i += blocksize)
			transform(&input[i]);

		index = 0;
	}
	else
		i = 0;

	// buffer remaining input
	memcpy(&buffer[index], &input[i], length - i);
}

//////////////////////////////

// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length)
{
	update((const unsigned char*)input, length);
}

//////////////////////////////

// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5& MD5::finalize()
{
	static unsigned char padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	if (!finalized) {
		// Save number of bits
		unsigned char bits[8];
		encode(bits, count, 8);

		// pad out to 56 mod 64.
		size_type index = count[0] / 8 % 64;
		size_type padLen = (index < 56) ? (56 - index) : (120 - index);
		update(padding, padLen);

		// Append length (before padding)
		update(bits, 8);

		// Store state in digest
		encode(digest, state, 16);

		// Zeroize sensitive information.
		memset(buffer, 0, sizeof buffer);
		memset(count, 0, sizeof count);

		finalized = true;
	}

	return *this;
}

//////////////////////////////

// return hex representation of digest as string
std::string MD5::hexdigest() const
{
	if (!finalized)
		return "";

	char buf[33];
	for (int i = 0; i < 16; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	buf[32] = 0;

	return std::string(buf);
}

//////////////////////////////

/*std::ostream& operator<<(std::ostream& out, MD5 md5)
{
	return out << md5.hexdigest();
}*/

//////////////////////////////

std::string md5(const std::string str)
{
	MD5 md5 = MD5(str);

	return md5.hexdigest();
}