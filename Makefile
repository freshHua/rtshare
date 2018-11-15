CXX := clang++
# protoc 工具
PROTOC := protoc

#链接头文件
PRIVATE_C_INCLUDES := 

PRIVATE_DEBUG_CFLAGS := 

PRIVATE_CFLAGS :=

PRIVATE_CPPFLAGS := -std=c++11 \
		    -Wall -Wextra \
		    -Werror

PRIVATE_LDFLAGS := -lgflags \
		   -lpthread 

PRIVATE_LDLIBS :=

MAIN_MODULE := rtshd

BUILDER_MODULE := builder

TESTER_MODULE := tester

#回显命令
hide:=@

# 代码文件
my_src_files := matrix_keymap.cpp \
		main.cpp \
		fib.cpp

builder_src_files := builder.cpp


tester_src_files := tester.cpp

src_cpp_sources := $(addprefix main/, $(filter %.cpp,$(my_src_files)) )
# objects文件 .cpp -> .o 
src_objects := $(src_cpp_sources:.cpp=.o)


builder_src_cpp_sources := $(addprefix main/, $(filter %.cpp,$(builder_src_files)) )
# objects文件 .cpp -> .o 
builder_src_objects := $(builder_src_cpp_sources:.cpp=.o)


tester_src_cpp_sources := $(addprefix main/, $(filter %.cpp,$(tester_src_files)) )
# objects文件 .cpp -> .o 
tester_src_objects := $(tester_src_cpp_sources:.cpp=.o)

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

cpp_normal_sources := $(filter-out ../%,$(filter %.cpp,$(my_src_files)))

%.o:%.cpp 
	$(transform-cpp-to-o)

.PHONY:clean
.PHONY:tester
$(MAIN_MODULE):$(src_objects)
	@mkdir -p $(dir $@)
	@echo "target Executable:($@)"
	$(hide) $(CXX) $(src_objects) -o $@ $(PRIVATE_LDFLAGS) $(PRIVATE_LDLIBS)

$(BUILDER_MODULE):$(builder_src_objects)
	@mkdir -p $(dir $@)
	@echo "target Executable:($@)"
	$(hide) $(CXX) $(builder_src_objects) -o $@ $(PRIVATE_LDFLAGS) $(PRIVATE_LDLIBS)


$(TESTER_MODULE):$(tester_src_objects)
	@mkdir -p $(dir $@)
	@echo "target Executable:($@)"
	$(hide) $(CXX) $(tester_src_objects) -o $@ $(PRIVATE_LDFLAGS) $(PRIVATE_LDLIBS)


clean:
	$(hide)find ./ -name "*.o" -print | xargs rm -rf
	$(hide)find ./ -name "*.P" -print | xargs rm -rf
	$(hide)rm -rf $(MAIN_MODULE) $(BUILDER_MODULE) $(TESTER_MODULE)
