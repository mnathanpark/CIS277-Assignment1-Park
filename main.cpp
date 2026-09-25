#include <iostream>
#include <iomanip>
#include "MemoryPool.h"

int main() {

    const size_t BLOCK_SIZE = 512;
    const size_t BLOCK_COUNT = 8;

    void* packet1;
    void* packet2;
    void* packet3;
    unsigned char packet[] =
    {
        0x45, 0x00, 0x00, 0x3C,
        0xAB, 0xCD, 0x12, 0x34
    };
    size_t packetSize = sizeof(packet) / sizeof(packet[0]);

    MemoryPool memPool(BLOCK_SIZE, BLOCK_COUNT);

    std::cout << "Network Packet Buffer Pool" << std::endl << std::endl;

    std::cout << "Block size: " << memPool.blockSize() << std::endl;
    std::cout << "Block count: " << memPool.availableBlocks() << std::endl;
    std::cout << "Total capacity: " << memPool.capacity() << std::endl << std::endl;


    std::cout << "Allocating first block." << std::endl;
    packet1 = memPool.allocate();
    std::cout << "Packet 1 memory address: " << packet1 << std::endl;

    std::cout << "Allocating second block." << std::endl;
    packet2 = memPool.allocate();
    std::cout << "Packet 2 memory address: " << packet2 << std::endl;

    std::cout << "Allocating third block." << std::endl;
    packet3 = memPool.allocate();
    std::cout << "Packet 3 memory address: " << packet3 << std::endl << std::endl;


    std::cout << "Writing binary packet data into packet 1." << std::endl;
    memcpy(packet1, packet, packetSize);

    std::cout << "Reading the written binary data." << std::endl;
    for(size_t i = 0; i < packetSize; i++) {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                  << static_cast<int>(packet[i]) << " ";
    }
    std::cout << std::dec << std::endl << std::endl;

    std::cout << "Deallocating packet 2." << std::endl;
    bool deallocated = memPool.deallocate(packet2);
    std::cout << "Deallocation status: " << (deallocated ? "true" : "false") << std::endl << std::endl;

    void* packetA;
    void* packetB;

    std::cout << "Demonstrating memory reuse by showing the memory addresses are the same" << std::endl;
    std::cout << "Allocating packet A" << std::endl;
    packetA = memPool.allocate();
    std::cout << "Packet A memory address: " << packetA << std::endl;

    std::cout << "Deallocating packet A" << std::endl;
    memPool.deallocate(packetA);

    std::cout << "Allocating packet B" << std::endl;
    packetB = memPool.allocate();
    std::cout << "Packet B memory address: " << packetB << std::endl << std::endl;

    std::cout << "Exhausting memory pool." << std::endl;
    while (memPool.availableBlocks() > 0) {
        (void)memPool.allocate();
    }
    std::cout << "Memory pool exhausted." << std::endl << std::endl;

    std::cout << "Available blocks: " << memPool.availableBlocks() << std::endl;
    std::cout << "Allocated blocks: " << memPool.allocatedBlocks() << std::endl << std::endl;

    std::cout << "Attempting another allocation." << std::endl;
    void* failedptr = memPool.allocate();
    std::cout << "Failed allocation memory address: " << failedptr << std::endl << std::endl;

    std::cout << "Deallocating packet 1." << std::endl;
    deallocated = memPool.deallocate(packet1);
    std::cout << "Deallocation status: " << (deallocated ? "true" : "false") << std::endl;
    std::cout << "Attempting to deallocate packet 1 again." << std::endl;
    deallocated = memPool.deallocate(packet1);
    std::cout << "Deallocation status: " << (deallocated ? "true" : "false") << std::endl;

}