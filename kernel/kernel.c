/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void main() {
    char *vid_buff = (char *)0xb8000;
    *vid_buff = 'C';
    while (1);
}