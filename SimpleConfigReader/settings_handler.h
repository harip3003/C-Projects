#ifndef SETTINGS_HANDLER_H_
#define SETTINGS_HANDLER_H_

#include <stdbool.h>

typedef struct SettingsStruct* SettingsHandle_t;

SettingsHandle_t loadSettingsFromFile(char *);

char* getSettingsValue(SettingsHandle_t, char *);

#endif //SETTINGS_HANDLER_H_