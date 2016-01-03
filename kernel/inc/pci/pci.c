// ------------------------------------------------------------------------------------------------
// pci/pci.c
// ------------------------------------------------------------------------------------------------

#include "pci.h"
#include "driver.h"
#include "registry.h"


// ------------------------------------------------------------------------------------------------
static void PciVisit(uint32 bus, uint32 dev, uint32 func)
{
    uint32 id = PCI_MAKE_ID(bus, dev, func);

    PciDeviceInfo info;
    info.vendorId = PciRead16(id, PCI_CONFIG_VENDOR_ID);
    if (info.vendorId == 0xffff)
    {
        return;
    }

    info.deviceId = PciRead16(id, PCI_CONFIG_DEVICE_ID);
    info.progIntf = PciRead8(id, PCI_CONFIG_PROG_INTF);
    info.subclass = PciRead8(id, PCI_CONFIG_SUBCLASS);
    info.classCode = PciRead8(id, PCI_CONFIG_CLASS_CODE);

    printf("%x:%x:%d 0x%x/0x%x: %s\n",
        bus, dev, func,
        info.vendorId, info.deviceId,
        PciClassName(info.classCode, info.subclass, info.progIntf)
        );


}

// ------------------------------------------------------------------------------------------------
void pciInit()
{
    printf("\nPCI Initialization\n");
    for (uint32 bus = 0; bus < 256; ++bus)
    {
        for (uint32 dev = 0; dev < 32; ++dev)
        {
            uint32 baseId = PCI_MAKE_ID(bus, dev, 0);
            uint8 headerType = PciRead8(baseId, PCI_CONFIG_HEADER_TYPE);
            uint32 funcCount = headerType & PCI_TYPE_MULTIFUNC ? 8 : 1;

            for (uint32 func = 0; func < funcCount; ++func)
            {
                PciVisit(bus, dev, func);
            }
        }
    }

    char mac_addr[6];
    for(int i = 0; i < 6; ++i)
    {
        mac_addr[i] = inportb(0x0200 + i); /*ioaddr is the base address obtainable from the PCI device configuration space.*/
    }


}
