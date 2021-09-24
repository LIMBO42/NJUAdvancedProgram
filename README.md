# NJU-AdvancedProgramming21Fall

## P3 An in-memory reliable byte stream



If you know something about TCP,you may know how the abstraction of a reliable  byte stream can be useful in com-municating across the Internet, even though the Internet itself only provides the service of“best-effort” (unreliable) datagrams. But It's okay as well if you have never heared of TCP. To finish off this week’s project, you will implement, in memory on a single computer, an object that provides this abstraction. Bytes are written on the “input” side and can be read, in the same sequence, from the “output”side.  The byte stream is finite:  the writer can end the input, and then no more bytes can be written.  When the reader has read to the end of the stream, it will reach “EOF” (end of file)and no more bytes can be read. Your byte stream will also be flow-controlled to limit its memory consumption at any given time.  The object is initialized with a particular “capacity”:  the maximum number of bytes it’s willing to store in its own memory at any given point.  The byte stream will limit the writer in how much it can write at any given moment, to make sure that the stream doesn’t exceed its storage capacity.  As the reader reads bytes and drains them from the stream, the writer is allowed to write more.  Your byte stream is for use in a single thread—you don’t have to worry about concurrent writers/readers, locking, or race conditions.


To be clear: the byte stream is finite, but it can be almost arbitrarily long4 before the writer ends the input and finishes the stream.  Your implementation must be able to handle streams that are much longer than the capacity.  The capacity limits the number of bytes that are held in memory (written but not yet read) at a given point, but does not limit the length of the stream.  An object with a capacity of only one byte could still carry a stream that is terabytes and terabytes long, as long as the writer keeps writing one byte at a time and the reader reads each byte before the writer is allowed to write the next byte.

Here’s what the interface looks like for the writer:

```C++
// Write a string of bytes into the stream. Write as many
// as will fit, and return the number of bytes written.
size_t write(const std::string &data);
// Returns the number of additional bytes that the stream has space for
size_t remaining_capacity() const;
// Signal that the byte stream has reached its ending
void end_input();
// Indicate that the stream suffered an error
void set_error();


```


And here is the interface for the reader:
```C++
// Peek at next "len" bytes of the stream
std::string peek_output(const size_t len) const;
// Remove ``len'' bytes from the buffer
void pop_output(const size_t len);

// Read (i.e., copy and then pop) the next "len" bytes of the stream
std::string read(const size_t len);

bool input_ended() const;// `true` if the stream input has ended

bool eof() const;// `true` if the output has reached the ending

bool error() const;// `true` if the stream has suffered an error

size_t buffer_size() const;// the maximum amount that can currently be peeked/read

bool buffer_empty() const;// `true` if the buffer is empty

size_t bytes_written() const;// Total number of bytes written

size_t bytes_read() const;// Total number of bytes popped

```