/*
 * cc_programmer.h
 *
 * Created on: Aug 2, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_PROGRAMMER_H_
#define _CC_PROGRAMMER_H_

#include "cc_unit_driver.h"
#include "usb/usb_device.h"
#include "data/data_section_store.h"

const size_t CC_BREAKPOINT_COUNT	= 4;

struct CC_ProgrammerInfo
{
	String name;
	String descripton;
	String debugger_id; // 4 unique digits
	uint16_t fw_version;
	uint16_t fw_revision;
};

struct USB_DeviceID
{
	uint16_t vendor_id;
	uint16_t product_id;
	char description[256];
};

struct CC_Breakpoint
{
	size_t number;
	size_t address;
};

typedef std::vector<CC_Breakpoint> CC_BreakpointVector;
typedef std::vector<USB_DeviceID> USB_DeviceIDVector;

///
class CC_Programmer : boost::noncopyable
{
public:
	enum OpenResult { OR_OK, OR_NOT_FOUND, OR_NOT_SUPPORTED };

	OpenResult open();
	OpenResult open(uint_t bus, uint_t device);
	bool opened() const;
	void close();

	bool programmer_info(CC_ProgrammerInfo &info);

	StringVector supported_unit_names() const;
	USB_DeviceIDVector supported_devices() const;

	enum InterfaceSpeed { IS_SLOW, IS_FAST };
	bool set_debug_interface_speed(InterfaceSpeed speed);

	void unit_status(String &name, bool &supported) const;
	bool unit_connect(UnitInfo &info);
	void unit_close();
	bool unit_reset();

	bool unit_locked();
	bool unit_erase();

	void unit_read_info_page(ByteVector &info_page);

	void unit_mac_address_read(size_t index, ByteVector &mac_address);
	void unit_mac_address_write(ByteVector &mac_address);

	void unit_flash_read(ByteVector &flash_data);
	void unit_flash_write(const DataSectionStore &sections);

	enum VerifyMethod { VM_BY_CRC, VM_BY_READ };
	bool unit_flash_verify(const DataSectionStore &sections, VerifyMethod method);
	bool unit_lock_write(const ByteVector &lock_data);

	void do_on_flash_read_progress(const ProgressWatcher::OnProgress::slot_type&);
	void do_on_flash_write_progress(const ProgressWatcher::OnProgress::slot_type&);

	CC_Programmer();

private:
	void request_device_info();
	void enter_debug_mode();
	void init_device();

	CC_ProgrammerInfo programmer_info_;
	UnitInfo unit_info_;
	USB_Device usb_device_;
	CC_UnitDriverPtrList unit_drviers_;
	CC_UnitDriverPtr driver_;
	ProgressWatcher pw_;
	CC_Breakpoint bps_[CC_BREAKPOINT_COUNT];
};

#endif // !_CC_PROGRAMMER_H_
