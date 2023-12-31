include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=thermo_guide
PKG_VERSION:=1.0
PKG_RELEASE:=142

# Source settings (i.e. where to find the source codes)
# This is a custom variable, used below
SOURCE_DIR:=./src
include $(INCLUDE_DIR)/package.mk
# Package definition; instructs on how and where our package will appear in the overall configuration menu ('make menuconfig')
define Package/$(PKG_NAME)
  SECTION:=examples
  CATEGORY:=Examples
  TITLE:=Thermo client
  DEPENDS:=+libpthread
endef
  
# Package description; a more verbose description on what our package does
define Package/$(PKG_NAME)/description
  Client for thermo
endef

# Package preparation instructions; create the build directory and copy the source code.
# The last command is necessary to ensure our preparation instructions remain compatible with the patching system.
define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	cp -r $(SOURCE_DIR)/* $(PKG_BUILD_DIR)
	$(Build/Patch)
endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
define Build/Compile
        $(MAKE) -C $(PKG_BUILD_DIR) \
                CC="$(TARGET_CC)" \
                CFLAGS="$(TARGET_CFLAGS) -Wall" \
                LDFLAGS="$(TARGET_LDFLAGS)"
endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/app/thermo_client $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ServoController/servo_test $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/Camera/camera_test $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/SocketClient/client_test $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ImageProcessor/processor_test $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,$(PKG_NAME)))
