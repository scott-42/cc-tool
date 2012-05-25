AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(DEPS_CFLAGS) -O3 -Iprogrammer -Icommon -Iusb -Idata -Iapplication
AM_LDFLAGS = \
	$(BOOST_FILESYSTEM_LDFLAGS) \
	$(BOOST_REGEX_LDFLAGS) \
	$(BOOST_SYSTEM_LDFLAGS) \
	$(BOOST_PROGRAM_OPTIONS_LDFLAGS)

#	$(BOOST_THREADS_LDFLAGS)
      
LDADD = $(DEPS_LIBS) 

LIBS = -s \
	$(BOOST_FILESYSTEM_LIBS) \
	$(BOOST_REGEX_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	$(BOOST_PROGRAM_OPTIONS_LIBS)
   
#	$(BOOST_THREADS_LIBS)

bin_PROGRAMS=cc-tool
cc_tool_SOURCES=main.cpp application/cc_flasher.cpp application/cc_base.cpp \
		common/log.cpp common/common.cpp common/timer.cpp \
		usb/usb_device.cpp \
		data/binary_file.cpp data/data_section.cpp data/data_section_store.cpp \
		data/file.cpp data/hex_file.cpp data/read_target.cpp \
		data/progress_watcher.cpp \
		programmer/cc_253x_2540.cpp programmer/cc_251x_111x.cpp \
		programmer/cc_243x.cpp programmer/cc_programmer.cpp \
		programmer/cc_unit_driver.cpp  programmer/cc_unit_info.cpp

