/*
 * cc_253x_2540.h
 *
 * Created on: Aug 4, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_253X_2540_H_
#define _CC_253X_2540_H_

#include "cc_debug_interface.h"
#include "cc_unit_driver.h"

class CC_253x_2540 : public CC_UnitDriver
{
public:
	virtual void supported_units(Unit_ID_List &units);
	virtual void find_unit_info(UnitInfo &info);
	virtual void read_info_page(ByteVector &info_page);
	virtual bool erase_check_comleted();
	virtual void mac_address_read(size_t index, ByteVector &mac_address);
	virtual void mac_address_write(ByteVector &mac_address);
	virtual void flash_write(const DataSectionStore &sections);
	virtual bool lock_write(const ByteVector &data);

	CC_253x_2540(USB_Device &programmer, ProgressWatcher &pw);

private:
//	virtual bool read_info_page(ByteVector &info_page);
//	virtual bool flash_write(uint_t offset, const ByteVector &flash_data);

	//virtual void flash_read(ByteVector &flash_data);

//	uint16_t calc_block_crc();
	//void flash_lock_bits_read(ByteVector &lock_data);

	virtual void flash_read_block(size_t offset, size_t size, ByteVector &flash_data);

//	void flash_read_page(uint16_t address, ByteVector &flash_data);
	void flash_select_bank(uint_t bank);
//	void flash_read_start();
//	void flash_read_end();

};

#endif // !_CC_253X_2540_H_
