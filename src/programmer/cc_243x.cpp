/*
 * cc_243x.cpp
 *
 * Created on: Nov 9, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include "log.h"
#include "cc_debug_interface.h"
#include "cc_243x.h"

const uint16_t XREG_FMAP = 0xDF9F;

//==============================================================================
CC_243x::CC_243x(USB_Device &programmer, ProgressWatcher &pw) :
		CC_UnitDriver(programmer, pw)
{
	UnitCoreInfo reg_info;

	reg_info.flash_word_size	= 4;
	reg_info.write_block_size	= 1024;
	reg_info.verify_block_size	= 1024;
	reg_info.xbank_offset		= 0x8000;
	reg_info.dma0_cfg_offset	= 0x0800;
	reg_info.dma_data_offset	= 0x0000;

	reg_info.memctr		= 0xDFC7;
	reg_info.fmap		= XREG_FMAP;
	reg_info.faddrh		= 0xDFAD;
	reg_info.faddrl		= 0xDFAC;
	reg_info.fctl		= 0xDFAE;
	reg_info.fwdata		= 0xDFAF;//
	reg_info.rndh		= 0xDFBD;
	reg_info.rndl		= 0xDFBC;
	reg_info.dma0_cfgh	= 0xDFD5;
	reg_info.dma0_cfgl	= 0xDFD4;
	reg_info.dma_arm	= 0xDFD6;
	reg_info.dma_req	= 0xDFD7;
	reg_info.dma_irq	= 0xDFD1;

	reg_info.fctl_write	= 0x02;

	set_reg_info(reg_info);
}

//==============================================================================
void CC_243x::supported_units(Unit_ID_List &units)
{
	units.push_back(Unit_ID(0x2430, "CC2430"));
	units.push_back(Unit_ID(0x2431, "CC2431"));
}

//==============================================================================
void CC_243x::find_unit_info(UnitInfo &unit_info)
{
	unit_info.flags = UnitInfo::SUPPORT_MAC_ADDRESS;
	unit_info.lock_size = 1;
	unit_info.max_flash_size = 128;
	unit_info.flash_page_size = 2048;
	unit_info.mac_address_count = 1;

	ByteVector sfr;

	read_xdata_memory(0xDF60, 2, sfr);
	unit_info.revision = sfr[0];
	unit_info.internal_ID = sfr[1];

	// Possible flash sizes: 32, 64, 128
	log_info("! getting flash size");///

	unit_info.flash_size = 32;
	for (uint8_t i = 1; i < 3; i++)
	{
		write_xdata_memory(XREG_FMAP, i);
		uint8_t result = read_xdata_memory(XREG_FMAP);
		if (result != i)
		{
			log_info("%02Xh, n: %02Xh", i, result);
			break;
		}
		unit_info.flash_size = 32 << i;
	}

	unit_info_ = unit_info;
}

//==============================================================================
bool CC_243x::erase_check_comleted()
{
	uint8_t status = 0;

	read_debug_status(status);
	return (status & DEBUG_STATUS_CHIP_ERASE_BUSY);
}

//==============================================================================
void CC_243x::mac_address_read(size_t index, ByteVector &mac_address)
{	read_xdata_memory(0xDF43, 8, mac_address); }

//==============================================================================
void CC_243x::mac_address_write(ByteVector &mac_address)
{ }

//==============================================================================
void CC_243x::flash_write(const DataSectionStore &sections)
{	write_flash_slow(sections); }

//==============================================================================
void CC_243x::flash_read_block(size_t offset, size_t size, ByteVector &data)
{	flash_large_read_block(offset, size, data); }

//==============================================================================
bool CC_243x::lock_write(const ByteVector &data)
{
	write_lock_to_info_page(data[0]);
	return true;
}
