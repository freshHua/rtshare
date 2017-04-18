CXX := clang++

#链接头文件
PRIVATE_C_INCLUDES := 

PRIVATE_DEBUG_CFLAGS := 

PRIVATE_CFLAGS :=

PRIVATE_CPPFLAGS :=

PRIVATE_LDFLAGS := -lgflags \
		   -lpthread 

PRIVATE_LDLIBS	:=

MAIN_MODULE := rtshd

#回显命令
hide:=@

# 代码文件
src_sources :=  main/main.cpp

# objects文件 .cpp -> .o 
src_objects := $(src_sources:.cpp=.o)


###########################################################
## Commands for munging the dependency files GCC generates
###########################################################
# $(1): the input .d file
# $(2): the output .P file
define transform-d-to-p-args
$(hide) cp $(1) $(2); \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(1) > $(2); \
	rm -f $(1)
endef

define transform-d-to-p
$(call transform-d-to-p-args,$(@:%.o=%.d),$(@:%.o=%.P))
endef


###########################################################
## Commands for running gcc to compile a C++ file
###########################################################
define transform-cpp-to-o
	@mkdir -p $(dir $@)
    	@echo "target C++: $@ <= $<"
	$(hide) $(CXX) \
	$(addprefix -I , $(PRIVATE_C_INCLUDES)) \
	-c \
	$(PRIVATE_CFLAGS) \
	$(PRIVATE_CPPFLAGS) \
	$(PRIVATE_DEBUG_CFLAGS) \
    	-MD -MF $(patsubst %.o,%.d,$@) -o $@ $<
	$(transform-d-to-p)
endef

-include $(c_objects:%.o=%.P)

%.o:%.cpp 
	$(transform-cpp-to-o)


$(MAIN_MODULE):$(src_objects)
	@mkdir -p $(dir $@)
	@echo "target Executable:($@)"
	$(hide) $(CXX) $(src_objects) -o $@ $(PRIVATE_LDFLAGS) $(PRIVATE_LDLIBS)

clean:
	$(hide)find ./ -name "*.o" -print | xargs rm -rf
	$(hide)find ./ -name "*.P" -print | xargs rm -rf
	$(hide) rm -rf $(MAIN_MODULE)
