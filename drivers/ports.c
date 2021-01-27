
unsigned char port_byte_in(unsigned short port)
{
	unsigned char res;
	__asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
	return res;
}
void  port_byte_out(unsigned short port, unsigned char byte_out)
{
	__asm__("out %%al, %%dx" : : "a" (byte_out), "d" (port));
}
unsigned short port_word_in(unsigned short port)
{
	unsigned short res;
	__asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
	return res;
}
unsigned char port_word_out(unsigned short port, unsigned short byte_out)
{
	__asm__("out %%ax, %%dx" : : "a" (byte_out), "d" (port));
}