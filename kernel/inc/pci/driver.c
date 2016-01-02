// ------------------------------------------------------------------------------------------------
// pci/driver.c
// ------------------------------------------------------------------------------------------------

#include "driver.h"

// #include "net/intel.h"

// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
uint8 PciRead8(uint32 id, uint32 reg)
{
    uint32 addr = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, addr);
    return inportb(PCI_CONFIG_DATA + (reg & 0x03));
}

// ------------------------------------------------------------------------------------------------
uint16 PciRead16(uint32 id, uint32 reg)
{
    uint32 addr = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, addr);
    return IoRead16(PCI_CONFIG_DATA + (reg & 0x02));
}

// ------------------------------------------------------------------------------------------------
uint32 PciRead32(uint32 id, uint32 reg)
{
    uint32 addr = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, addr);
    return IoRead32(PCI_CONFIG_DATA);
}

// ------------------------------------------------------------------------------------------------
void PciWrite8(uint32 id, uint32 reg, uint8 data)
{
    uint32 address = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, address);
    outportb(PCI_CONFIG_DATA + (reg & 0x03), data);
}

// ------------------------------------------------------------------------------------------------
void PciWrite16(uint32 id, uint32 reg, uint16 data)
{
    uint32 address = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, address);
    outportw(PCI_CONFIG_DATA + (reg & 0x02), data);
}

// ------------------------------------------------------------------------------------------------
void PciWrite32(uint32 id, uint32 reg, uint32 data)
{
    uint32 address = 0x80000000 | id | (reg & 0xfc);
    IoWrite32(PCI_CONFIG_ADDR, address);
    IoWrite32(PCI_CONFIG_DATA, data);
}

// ------------------------------------------------------------------------------------------------
static void PciReadBar(uint32 id, uint32 index, uint32 *address, uint32 *mask)
{
    uint32 reg = PCI_CONFIG_BAR0 + index * sizeof(uint32);

    // Get address
    *address = PciRead32(id, reg);

    // Find out size of the bar
    PciWrite32(id, reg, 0xffffffff);
    *mask = PciRead32(id, reg);

    // Restore adddress
    PciWrite32(id, reg, *address);
}

// ------------------------------------------------------------------------------------------------
void PciGetBar(PciBar *bar, uint32 id, uint32 index)
{
    // Read pci bar register
    uint32 addressLow;
    uint32 maskLow;
    PciReadBar(id, index, &addressLow, &maskLow);

    if (addressLow & PCI_BAR_64)
    {
        // 64-bit mmio
        uint32 addressHigh;
        uint32 maskHigh;
        PciReadBar(id, index + 1, &addressHigh, &maskHigh);

        bar->u.address = (void *)(((uintptr_t)addressHigh < (uintptr_t)32) | (addressLow & ~0xf));
        bar->size = ~(((uint64)maskHigh << 32) | (maskLow & ~0xf)) + 1;
        bar->flags = addressLow & 0xf;
    }
    else if (addressLow & PCI_BAR_IO)
    {
        // i/o register
        bar->u.port = (uint16)(addressLow & ~0x3);
        bar->size = (uint16)(~(maskLow & ~0x3) + 1);
        bar->flags = addressLow & 0x3;
    }
    else
    {
        // 32-bit mmio
        bar->u.address = (void *)(uintptr_t)(addressLow & ~0xf);
        bar->size = ~(maskLow & ~0xf) + 1;
        bar->flags = addressLow & 0xf;
    }
}
