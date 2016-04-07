CC = gcc
CFLAGS = -Wall
LIBS = -lwiringPi -lrt

LIB_DIR = /opt/piLib/lib
OBJ_DIR = obj
CORE_DIR = core
SENSOR_SD = /sensors
OBJECTS := $(patsubst $(CORE_DIR)/%.c,$(OBJ_DIR)/%.o,$(wildcard $(CORE_DIR)/*.c))
OBJECTS += $(patsubst $(CORE_DIR)$(SENSOR_SD)/%.c,$(OBJ_DIR)$(SENSOR_SD)/%.o,$(wildcard $(CORE_DIR)$(SENSOR_SD)/*.c))
TEST_OBJ += $(OBJ_DIR)/test.o

$(OBJ_DIR)/%.o : $(CORE_DIR)/%.c $(CORE_DIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)$(SENSOR_SD)/%.o : $(CORE_DIR)$(SENSOR_SD)/%.c $(CORE_DIR)$(SENSOR_SD)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_OBJ) : test.c
	$(CC) $(CFLAGS) -c -o $@ $^

test : $(OBJECTS) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
lib : $(OBJECTS)
	$(CC) -shared -o libpiLib.so $^; \
	sudo mv libpiLib.so $(LIB_DIR)/

.PHONY : clean

clean :
	rm -f $(OBJ_DIR)/*.o; \
	rm -f $(OBJ_DIR)$(SENSOR_SD)/*.o; \
	sudo rm -f $(LIB_DIR)/*.so