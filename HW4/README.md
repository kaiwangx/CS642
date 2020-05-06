sploit 0:

     Since check_fail() in target used strcpy function, we can apply buffer overflow technique here to change the 
return address to the "else" statement so that the grade will be changed to A. 

     Notice that the buffer size is 20 byte, followed by old frame number and return address, so we are trying to
write 28 bytes in total to overwrite the return address.

     By using gdb, we get the address we want to return, which will change the grade, but at the same time, we 
should keep the old frame number unchanged. We can get this number by knowing %ebp of the new frame.

     Then, the final buffer looks like "SSSS SSSS SSSS SSSS SSSS FFFF SSSS", where S stands for the return addr
and F stands for the old frame number.


sploit 1:

    This target is a simple example of buffer overflow. It uses strcpy which don't have bound check so that we can insert 
shellcode and overwrite the return address to the head of the buffer, similar to sploit0.

    Since the buffer size is 160, we need 168 (we need to skip sfp) bytes to overwrite the return address. The composition of
buffer is like NNNNNNNNNNSSSSSSSSSSSSRRRR, where N stands for NOP, S stands for shell codes, and R stands for the 
beginning address of the buffer, here is the first N.

    Instead of guessing, we can figure out the exact address. Like sploit0, by using gdb, we are able to figure out the ebp
esp by using asm helper function. Then it is not hard to find out the exact address, we copied that address to R and we
are done.


sploit 2:

    The vulnerability of this target is we are able to change the last bit of the sfp by using the buffer overflow.
    
    The buffer size is 160 bytes, in order to perform buffer overflow, our buffer should be 161 bytes, the composition will 
be FFFFRRRRNNNNNNNNNNNNSSSSSSSX, where F stands for sfp, R stands for return address, here we set return address
to the first N so that our shellcode can run, N stands for NOP, S stands for shellcode, and X stands for the last bit of sfp we
want to modified, here we modified it to the first F.

    Thus, the flow of the program should be X has been modified into the sfp, and the sfp will point to the first F. This makes
the ebp moves to the address we want, instead of previous one, here ebp moves to the first F. Then it becomes simple, 
the return address is next to sfp and the control flow will be directed to NOP, and then our shellcode.

    Implementation is similar to sploit1, we first figure out the ebp and esp of the bar frame inside target and do some 
calculation to found out the exact address of the begining of the buffer. Finally, we set up our buffer as said above, and 
we are done.


sploit 3:

    Here, notice that in the main function of the target, it has "count = (int)strtoul(argv[1], &in, 10);", witch might have the integer
 overflow problem. The program ask us to input the size of the array, but we can instead, input a large number (here we choose 
2147483810) to make it seems like a negative number when it compares with MAX_WIDGETS, but after, in the memcpy, it overflows 
again so that we get the real size of our buffer. In other word, we need a number X big enough so it will be interpret as a negative
number and 16 * X will overflow and left the real size of buffer, which is 2592. Here we choose X = 2147483810

    We choose the buffer size of 2592, which is enough to overwrite the eip. And the composition of the buffer is similar to sploit1,
besides we have more NOP, NNNNNNNNNNSSSSSSSNNNNRRRR, where N is NOP, S is shellcode, R is modified eip that points to 
the first N. 

    By using the same technique, we get the ebp and esp of foo frame and by doing some calculation, we get the exact address of 
the beginning of the buffer. So no need to guess, we have the exact address and we can fill it in R part. (Here is another trick, the 
count takes 11 bytes, so the calculation here is a little different). By filling out the R, we can choose anywhere between N and R to 
place the shell code. Then, we are done.


sploit 4:

     The weakness of this target is that it uses printf function series without specifying the type. It is a typical format 
string vulnerability. 

     Let's start with the buffer layout: 
	<ADDR, DUMMY><ADDR, DUMMY><ADDR, DUMMY><ADDR, DUMMY><STACKPOP><WRITE-CODE><NOPS>
<SHELLCODE>
	
     <ADDR, DUMMY> pair: addr is the address we'd like to overwrite, like the paper "Exploiting Format String Vulnerabilities" 
said, we can only write one bytes each time. So combining all four ADDR, we will get the actual 4 bytes address we want 
to overwrite. In other words, we split the 4 bytes address to four address and change 1 bytes each time. Here the address
we want to overwrite is the return address, (or %ebp + 4), so after finding ebp in gdb, we can get this address. The dummy
values I choose here is \x01\x01\x01\x01, since late we will use %u%n, we need a dumy value between address to make sure
no address here will be skipped.

    STACKPOP: is %08x, this will increase the internal pointer 4 bytes in printf function, we want this pointer point to the first ADDR, 
or the beginning of the buffer. Try serveral times we can know how many bytes we need to skip.

    WRITE-CODE: in form %xu%n *4, where x is a integer. we need four of this since we need to write to four different address, 1 
bytes each time. Details calculation can be found in the paper. 

     And we want to insert some NOP before SHELLCODE to increase flexibility. Combining all members, we get the buffer.
     
     Note: the return address here is not located in the target frame but in the original buffer frame. The reason of this is by doing
%xu%n, lots of \x20 will be written in to the target frame and the shell code might be overwritten.

