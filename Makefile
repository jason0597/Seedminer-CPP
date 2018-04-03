SOURCES			:= source
INCLUDES		:= include
BUILD			:= build

CC				:= cl
LD				:= link
CCFLAGS 		:= -c -EHsc -I ../$(INCLUDES)
LDFLAGS			:= -out:Seedminer.exe

SOURCEFILES		:= $(basename $(notdir $(wildcard $(SOURCES)/*.cpp)))
CPPFILES		:= $(addprefix ../$(SOURCES)/, 	$(addsuffix .cpp, $(SOURCEFILES)))
OFILES			:= $(addprefix build/, 			$(addsuffix .obj, $(SOURCEFILES)))

all:
	mkdir -p $(BUILD)
	cd $(BUILD) && $(CC) $(CCFLAGS) $(CPPFILES)
	$(LD) $(LDFLAGS) $(OFILES)

clean:
	rm -rf Seedminer.exe $(BUILD)
	