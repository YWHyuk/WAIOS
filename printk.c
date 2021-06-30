#include "printk.h"
#include "uart.h"

void* memset(void* dest, int data, long unsigned int size)
{
	for(long unsigned int i=0; i<size;i++)
		((char*) dest)[i]=(char)data;
	return dest;
}

void* memcpy(void* dest, const void* src, long unsigned int size)
{
	for(long unsigned int i=0; i<size; i++)
		((char*) dest)[i]=((char*) src)[i];

	return dest;
}

int memcmp(const void* dest, const void* src, long unsigned int size)
{
	char c;
	for(long unsigned int i=0; i<size; i++){
		c = ((char*) dest)[i]-((char*) src)[i];
		if(c!=0){
			return (int) c;
		}
	}
	return 0;
}

long unsigned int strlen(const char* pcBuffer)
{
	int ret=0;
	uint64_t temp;

	while(1){
		temp = ((uint64_t*)(pcBuffer))[ret/sizeof(uint64_t)];
		for(int i=0; i<sizeof(uint64_t); i++){
			if((temp & 0xFF) == 0x00)
				return ret;
			temp>>=8;
			ret++;
		}
	}
}

static void reverse_str( char* buffer)
{
	int buffer_len = strlen(buffer);
	char c;

	for (int i=0; i<buffer_len/2; i++) {
		c = buffer[buffer_len-1-i];
		buffer[buffer_len-1-i ] = buffer[i];
		buffer[i] = c;
	}
}

static uint64_t hex2int( const char* buffer)
{
	int len;
	uint64_t ret = 0L;
	char c;

	len = strlen(buffer);
	for (int i=0; i<len; i++) {
		ret <<= 4;
		c= buffer[i];

		if (c>='0' && c<='9')
			c -= '0';
		else if (c>='A' && c<='Z')
			c = c - 'A' + 10;
		else if (c>='a' && c<= 'z')
			c = c - 'a' + 10;
		else
			return -1;

		if (c>=16) {
			printk("hex2int() Wrong value...\n");
			return -1;
		}
		ret += c;
	}
	return ret;
}

static long dec2int( const char* buffer)
{
	int len;
	long ret = 0L;
	char c;
	bool is_minus=FALSE;

	if (buffer[0]=='-')
		is_minus=TRUE;

	len = strlen(buffer);
	for (int i=is_minus; i<len; i++) {
		ret *= 10;
		c = buffer[i];

		if (c>='0' && c<='9')
			c -= '0';
		else{
			printk("dec2int() Wrong value...\n");
			return -1;
		}
		ret += c;

	}
	if (is_minus == TRUE)
		ret *= -1;
	return ret;
}


static int hex2str(uint64_t value, char* buffer)
{
	int index=0;
	long temp;

	if (value == 0)
		buffer[index++] = '0';

	while (value > 0) {
		temp = value % 16;
		value /= 16;
		if (temp>=10)
			buffer[index++] = 'A'+temp-10;
		else
			buffer[index++] = '0'+temp;
	}
	buffer[index] = '\0';
	reverse_str(buffer);
	return index;
}

static int dec2str(long value, char* buffer)
{
	int index=0;
	long temp;
	bool is_minus=FALSE;

	if (value == 0)
		buffer[index++] = '0';

	if (value < 0){
		is_minus = TRUE;
		buffer[0] = '-';
		value *= -1;
	}
	while (value > 0) {
		temp = value % 10;
		value /= 10;
		buffer[index++] = '0'+temp;
	}
	buffer[index] = '\0';
	reverse_str(buffer+ is_minus);
	return index;
}

long atoi(const char* buffer, int radix, long* ret)
{
	switch(radix) {
	case 16:
		*ret = hex2int(buffer);
		break;
	case 10:
	default:
		*ret = dec2int(buffer);
	}
	return *ret;
}

int itoa(long value, char* buffer, int radix)
{
	int ret;
	switch(radix) {
	case 16:
		ret = hex2str(value, buffer);
		break;
	case 10:
	default:
		ret = dec2str(value, buffer);
		break;
	}
	return ret;
}

static int vsprintk(char* buffer, const char* format_string, va_list ap)
{
	int index=0;
	int format_len;
	char* copy_string;
	uint64_t value;
	int int_value;

	format_len = strlen(format_string);
	for (int i=0; i<format_len; i++) {
		if (format_string[i]=='%') {
			i++;
			switch(format_string[i])
			{
			case 's'://문자열 출력
				copy_string = (char*) (va_arg(ap,char*));
				int_value = strlen(copy_string);
				memcpy(buffer+index, copy_string, int_value);
				index += int_value;
				break;
			case 'c'://문자 출력
				buffer[index] = (char) (va_arg(ap,int));
				index++;
				break;
			case 'd'://정수 출력
			case 'i':
				int_value = (int) (va_arg(ap,int));
				index += itoa(int_value, buffer+index, 10);
				break;
			case 'x'://4byte Hex 출력
			case 'X':
				value = (uint32_t) (va_arg(ap,uint32_t)) & 0xFFFFFFFF;
				index += itoa(value, buffer+index, 16);
				break;
			case 'q'://8byte Hex 출력
			case 'Q':
			case 'p':
				value = (uint64_t) (va_arg(ap,uint64_t));
				index += itoa(value, buffer+index, 16);
				break;
			case 'f':
			case 'F':
				break;
			default:
				buffer[index++] = format_string[i];
				break;
			}
		}else{
			buffer[index++] = format_string[i];
		}
	}
	buffer[index] ='\0';
	return index;
}

void printk(const char* format_string, ...)
{
	va_list ap;
	static char buffer[1024*2];
	int len;

	va_start(ap, format_string);
	vsprintk(buffer, format_string, ap);
	va_end(ap);

	len = strlen(buffer);
	for (int i=0; i<len; i++)
		putchar(buffer[i]);
}
