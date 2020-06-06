.PHONY: all clean

CC := g++

DIR_INC := inc
DIR_SRC := src
DIR_OBJS := objs
DIR_TARGET := target
DIR := $(DIR_OBJS) $(DIR_TARGET)

TPYE_INC := .h
TPYE_SRC := .cpp
TPYE_OBJ := .o

MKDIR := mkdir
RM := rm -rf

vpath %$(TPYE_INC) $(DIR_INC)
vpath %$(TPYE_SRC) $(DIR_SRC)

CFLAG := -I $(DIR_INC) -g
LFLAG := 

APP := $(DIR_TARGET)/app.out

HDRS := $(wildcard $(DIR_INC)/*$(TPYE_INC))
HDRS := $(notdir $(HDRS))
OBJS := $(wildcard $(DIR_SRC)/*$(TPYE_SRC))
OBJS := $(OBJS:%$(TPYE_SRC)=%$(TPYE_OBJ))
OBJS := $(patsubst $(DIR_SRC)/%, $(DIR_OBJS)/%, $(OBJS))

all : $(DIR) $(APP)
	@echo "Target file ==> $(APP)"

$(DIR):
	$(MKDIR) $@

$(APP):$(OBJS)
	$(CC) $(LFLAG) -o $@ $^

$(DIR_OBJS)/%$(TPYE_OBJ):%$(TPYE_SRC) $(HDRS)
	$(CC) $(CFLAG) -o $@ -c $<

clean:
	$(RM) $(DIR)
