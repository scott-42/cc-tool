/*
 * cc_unit_driver.h
 *
 * Created on: Aug 4, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_UNIT_DRIVER_H_
#define _CC_UNIT_DRIVER_H_

#include "data/data_section_store.h"
#include "data/progress_watcher.h"
#include "usb/usb_device.h"
#include "cc_unit_info.h"

const size_t XDATA_READ_CHUNK_SIZE = 128;
const size_t FLASH_READ_CHUNK_SIZE = 128;
const size_t FLASH_BANK_SIZE = 1024 * 32;
const size_t FLASH_MAPPED_BANK_OFFSET = 1024 * 32;

class CC_UnitDriver : boost::noncopyable
{
public:
	virtual void supported_units(Unit_ID_List &units) = 0;
	virtual void find_unit_info(UnitInfo &info) = 0;

	virtual void read_info_page(ByteVector &info_page);

	/// @param index 0 - primary address, 1 - secondary address
	virtual void mac_address_read(size_t index, ByteVector &mac_address);
	virtual void mac_address_write(ByteVector &mac_address);

	virtual void erase_start();
	virtual bool erase_check_comleted() = 0;
	virtual void flash_write(const DataSectionStore &sections) = 0;
	virtual bool flash_verify_by_crc(const DataSectionStore &sections);
	virtual bool flash_verify_by_read(const DataSectionStore &sections);
	virtual void flash_read_block(size_t offset, size_t size, ByteVector &data) = 0;
	virtual bool lock_write(const ByteVector &data) = 0;

	void read_debug_status(uint8_t &status);
	void read_debug_config(uint8_t &config);
	void write_debug_config(uint8_t config);

	void read_sfr(uint8_t address, uint8_t &value);
	void write_sfr(uint8_t address, uint8_t value);

	void write_xdata_memory(uint16_t address, const ByteVector &data);
	void write_xdata_memory(uint16_t address, const uint8_t data[], size_t size);
	void write_xdata_memory(uint16_t address, uint8_t data);

	void read_xdata_memory(uint16_t address, size_t count, ByteVector &out);
	uint8_t read_xdata_memory(uint16_t address);

	void reset(bool debug_mode);

	void flash_read_start();
	void flash_read_end();

	CC_UnitDriver(USB_Device &programmer, ProgressWatcher &pw);

protected:
	// some procedures is valid only for subset of targets
	void select_info_page_flash(bool select_info_page);

	// Out data will be put in the end of data
	void flash_read_32k(size_t address, size_t size, ByteVector &data);
	void flash_large_read_block(size_t offset, size_t size, ByteVector &data);
	void set_reg_info(const UnitCoreInfo &);
	void write_flash_slow(const DataSectionStore &sections);
	void write_lock_to_info_page(uint8_t lock_byte);

	USB_Device &usb_device_;
	ProgressWatcher &pw_;
	UnitInfo unit_info_;

private:
	uint16_t calc_block_crc();

	UnitCoreInfo reg_info_;
};

typedef boost::shared_ptr<CC_UnitDriver> CC_UnitDriverPtr;
typedef std::list<CC_UnitDriverPtr> CC_UnitDriverPtrList;

#endif // !_CC_UNIT_DRIVER_H_

