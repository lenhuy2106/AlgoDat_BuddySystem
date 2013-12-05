#ifndef BLOCK_H
#define BLOCK_H

typedef int POSITION;

class Block {
protected:
	bool reserved;
	unsigned int size;
public:
	ReservedBlock(unsigned int size)
	{
		this.size = size;
	}

	bool isReserved() {
		return reserved;
	}

	setSize(unsigned int size) {
		this.size = size;
	}

	unsigned int getSize() {
		return size;
	}
}

class ReservedBlock: public Block {
public:
	ReservedBlock(unsigned int size): this(size)
	{
		reserved = true;
	}
}

class FreeBlock: public Block {
protected:
	FreeBlock* next;
public:
	ReservedBlock(unsigned int size): this(size)
	{
		reserved = false;
	}

	setNext(FreeBlock* next) {
		this.next = next;
	}

	FreeBlock* getNext() {
		return next;
	}
}

#endif // BLOCK_H
