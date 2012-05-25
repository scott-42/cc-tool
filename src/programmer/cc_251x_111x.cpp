/*
 * cc_251x_111x.cpp
 *
 * Created on: Nov 10, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include "cc_251x_111x.h"
#include "cc_debug_interface.h"

//==============================================================================
CC_251x_111x::CC_251x_111x(USB_Device &programmer, ProgressWatcher &pw) :
		CC_UnitDriver(programmer, pw)
{
	UnitCoreInfo reg_info;

	reg_info.flash_word_size	= 2;
	reg_info.verify_block_size	= 512;
	reg_info.write_block_size	= 512;
	reg_info.xbank_offset		= 0;
	reg_info.dma0_cfg_offset	= 0xFF00;
	reg_info.dma_data_offset	= 0xF000;

	reg_info.rndh		= 0xDFBD;
	reg_info.rndl		= 0xDFBC;
	reg_info.dma0_cfgh	= 0xDFD5;
	reg_info.dma0_cfgl	= 0xDFD4;
	reg_info.dma_arm	= 0xDFD6;
	reg_info.dma_req	= 0xDFD7;
	reg_info.dma_irq	= 0xDFD1;
	reg_info.fctl		= 0xDFAE;
	reg_info.fwdata		= 0xDFAF;
	reg_info.faddrl		= 0xDFAC;
	reg_info.faddrh		= 0xDFAD;

	reg_info.fctl_write	= 0x02;

	set_reg_info(reg_info);
}

//==============================================================================
void CC_251x_111x::supported_units(Unit_ID_List &units)
{
	units.push_back(Unit_ID(0x2510, "CC2510"));
	units.push_back(Unit_ID(0x2511, "CC2511"));
	units.push_back(Unit_ID(0x1111, "CC1110"));
	units.push_back(Unit_ID(0x1110, "CC1111"));
}

//==============================================================================
void CC_251x_111x::find_unit_info(UnitInfo &unit_info)
{
	unit_info.lock_size = 1;
	unit_info.max_flash_size = 32;
	unit_info.flash_page_size = 1024;
	unit_info.mac_address_count = 1;

	ByteVector sfr;

	read_xdata_memory(0xDF36, 2, sfr);
	unit_info.revision = sfr[0];
	unit_info.internal_ID = sfr[1];

	unit_info_ = unit_info;
}

//==============================================================================
bool CC_251x_111x::erase_check_comleted()
{
	uint8_t status = 0;

	read_debug_status(status);
	return (status & DEBUG_STATUS_CHIP_ERASE_BUSY);
}

//==============================================================================
void CC_251x_111x::flash_read_block(size_t offset, size_t size, ByteVector &data)
{	flash_read_32k(offset, size, data); }

//==============================================================================
void CC_251x_111x::flash_write(const DataSectionStore &sections)
{	write_flash_slow(sections); }

//==============================================================================
bool CC_251x_111x::lock_write(const ByteVector &data)
{
	write_lock_to_info_page(data[0]);
	return true;
}
