## bitIO

bitIO is a easy-to-use bit-oriented stream library.

### `bits_in` & `bits_out` object
`bits_in` & `bits_out` is the central object dealing with reading & writing bits.

#### construct
                        file you want to write      set the default bit size every time you write
                            ^                        ^
                            |           _____________|
                            |           |
    bits_out out(ofstream("temp.bin"), 7);
                           
                            
`bits_in` is the same

### usage



how to write:

example: 
    
    // writing 0x1 (size of 7 bits)
    bits_out out(ofstream("temp.bin"), 7);
    out.write(1);
    
Here we write 7 bits to file temp.bin.

Of cource, we can also write multiple 7-bit to the stream.
    
    for (int i = 0; i < 10; ++i) {
            out.write(i);
    }
 
You can also write different size to the file
    
    // the second parameter of write() method  indicate how may bits should be written
    for (int j = 1; j < 10; ++j) {
        out.write(1, j);
    }
    
Here we write 9 kinds of 1, from 1-bit to 9-bit. The content had written should be like this:

    1,01,001,0001 ...
 
how to read:

example:

    // reading a 7-bit number
    bits_in in(ifstream("temp.bin"), 7);
    unsigned short num = in.read();
    
    
    // reading arbitary size num
    for (int j = 1; j < 10; ++j) {
        unsigned short num = out.read(j);
    }


## implementation
the standard iostreams only provide byte r/w functionality. To achieve bit r/w capability, `bits_out` collects bits to form  bytes, then writes to the stream; while `bits_in` read bytes from stream and split them into bits.

## FAQ
F: What happened when I write only 7-bit `127` to the file? Is the size of content only 7 bits?

A: No, the minial unit of standard iostreams is byte, which mean size of the reading\writing content should be 8's integral	multiples(e.g. 8 bits, 16 bits, 24 bits...), the unused part will be padding with 0.
For this example, the content will be `01111111`.


## download
only `bitio.cpp` & `bitio.h` is essential.

## benchmark
###test on macbook I5 2.7GHz, 256GB SSD

|                                       |  100MB   |
|---------------------------------------|----------|
| bits_out.wirte(1)                     | 1s 481ms |
| ofstream.put(1)                       | 1s 152ms |
| ofstream.write() (1000bytes per time) | 408ms    |

<sub>see benchmark.cpp test1 </sub>


since bits_out.write() put 1 number to buffer per time, compared to ofstream.put(), is about 30%~40% slower.

compared to ofstream.write(), it's 2 times slower. But if I add concurrent strategy to writing multiple set of bits to bitsIO, performance will be better

# todo
* make api stream like
* use device concept: any object has (read, write, put, get) can fit into bitsio